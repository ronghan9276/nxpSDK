/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>

#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_codec_common.h"

#include "app_data.h"
#include "app_streamer.h"
#include "streamer_pcm_app.h"
#include "app_definitions.h"
#include "main.h"
#include "logging.h"

#ifdef EAP32_PROC
#include "eap_proc.h"
#endif

#define APP_STREAMER_MSG_QUEUE     "app_queue"
#define STREAMER_TASK_NAME         "Streamer"
#define STREAMER_MESSAGE_TASK_NAME "StreamerMessage"

#define STREAMER_TASK_STACK_SIZE         16 * 1024
#define STREAMER_MESSAGE_TASK_STACK_SIZE 512

static STREAMER_T *streamer;
static ringbuf_t *audioBuffer;
OSA_MUTEX_HANDLE_DEFINE(audioMutex);
OSA_TASK_HANDLE_DEFINE(msg_thread);

static void (*progress_handler)(int current, int total);

extern codec_handle_t codecHandle;
extern app_handle_t app;

/*!
 * @brief Streamer task for communicating messages
 *
 * This function is the entry point of a task that is manually created by
 * STREAMER_Create.  It listens on a message queue and receives status updates
 * about errors, audio playback state and position.  The application can make
 * use of this data.
 *
 * @param arg Data to be passed to the task
 */
static void STREAMER_MessageTask(void *arg)
{
    STREAMER_MSG_T msg;
    bool exit_thread = false;
    osa_status_t ret;

    if (get_app_data()->logEnabled)
    {
        PRINTF("[EAP STREAMER] Message Task started\r\n");
    }

    while (!streamer)
    {
        OSA_TimeDelay(1);
    }
    if (streamer->mq_out == NULL)
    {
        PRINTF("[EAP STREAMER] osa_mq_open failed: %d\r\n");
        return;
    }

    int trackLength = 0;

    progress_handler(0, trackLength);

    do
    {
        ret = OSA_MsgQGet(&streamer->mq_out, (void *)&msg, osaWaitForever_c);
        if (ret != KOSA_StatusSuccess)
        {
            PRINTF("[EAP STREAMER] osa_mq_receiver error: %d\r\n", ret);
            continue;
        }

        switch (msg.id)
        {
            case STREAM_MSG_DESTROY_PIPELINE:
                progress_handler(0, trackLength);
                break;
            case STREAM_MSG_ERROR:
                PRINTF("[EAP STREAMER] STREAM_MSG_ERROR\r\n");
                exit_thread = true;
                progress_handler(0, 0);
                /* propagate stop request to main application state machine */
                get_eap_att_control()->command = kAttCmdStop;
                break;
            case STREAM_MSG_EOS:
                if (get_app_data()->logEnabled)
                {
                    PRINTF("\n[EAP STREAMER] STREAM_MSG_EOS\r\n");
                }
                progress_handler(0, trackLength);
                exit_thread = true;
                /* propagate stop request to main application state machine */
                get_eap_att_control()->command = kAttCmdStop;
                break;
            case STREAM_MSG_UPDATE_POSITION:
                if (get_app_data()->logEnabled)
                {
                    PRINTF("[EAP STREAMER] STREAM_MSG_UPDATE_POSITION..");
                    PRINTF(" position: %d ms\r", msg.event_data);
                }
                progress_handler(msg.event_data, trackLength);
                break;
            case STREAM_MSG_UPDATE_DURATION:
                if (get_app_data()->logEnabled)
                {
                    PRINTF("[EAP STREAMER] STREAM_MSG_UPDATE_DURATION: %d\r\n", msg.event_data);
                }
                trackLength = msg.event_data;
                break;
            case STREAM_MSG_CLOSE_TASK:
                if (get_app_data()->logEnabled)
                {
                    PRINTF("[EAP STREAMER] STREAM_MSG_CLOSE_TASK\r\n");
                }
                exit_thread = true;
                break;
            default:
                break;
        }

    } while (!exit_thread);

    OSA_MsgQDestroy(&streamer->mq_out);
    streamer->mq_out = NULL;

    OSA_TaskDestroy(msg_thread);
}

int STREAMER_Read(uint8_t *data, uint32_t size)
{
    uint32_t bytes_read;

    OSA_MutexLock(&audioMutex, osaWaitForever_c);
    bytes_read = ringbuf_read(audioBuffer, data, size);
    OSA_MutexUnlock(&audioMutex);

    if (bytes_read != size)
    {
        PRINTF("[STREAMER WARN] read underrun: size: %d, read: %d\r\n", size, bytes_read);
    }

    return bytes_read;
}

int STREAMER_Write(uint8_t *data, uint32_t size)
{
    uint32_t written;

    OSA_MutexLock(&audioMutex, osaWaitForever_c);
    written = ringbuf_write(audioBuffer, data, size);
    OSA_MutexUnlock(&audioMutex);

    if (written != size)
    {
        PRINTF("[STREAMER ERR] write overflow: size %d, written %d\r\n", size, written);
    }

    return written;
}

bool STREAMER_IsPlaying(streamer_handle_t *handle)
{
    return handle->audioPlaying;
}

status_t STREAMER_PCM_Create(char *filename, int volume)
{
    STREAMER_CREATE_PARAM params;
    osa_task_def_t thread_attr;
    ELEMENT_PROPERTY_T prop;
    int ret;

    eap_att_control_t *control = get_eap_att_control();

    /* Create message process thread */
    thread_attr.tpriority = OSA_PRIORITY_HIGH;
    thread_attr.tname     = (uint8_t *)STREAMER_MESSAGE_TASK_NAME;
    thread_attr.pthread   = &STREAMER_MessageTask;
    thread_attr.stacksize = STREAMER_MESSAGE_TASK_STACK_SIZE;
    ret                   = OSA_TaskCreate(&msg_thread, &thread_attr, (void *)control);
    if (KOSA_StatusSuccess != ret)
    {
        return kStatus_Fail;
    }

    /* Create streamer */
    strcpy(params.out_mq_name, APP_STREAMER_MSG_QUEUE);
    params.stack_size = STREAMER_TASK_STACK_SIZE;
    params.task_name  = STREAMER_TASK_NAME;
#ifdef EAP32_PROC
    if (get_app_data()->num_channels == 2)
    {
        params.pipeline_type = STREAM_PIPELINE_PCM_EAP_AUDIO;
    }
    else
    {
        params.pipeline_type = STREAM_PIPELINE_PCM_AUDIO;
    }
#else
    params.pipeline_type = STREAM_PIPELINE_PCM_AUDIO;
#endif /* EAP_PROC */
    params.task_name    = STREAMER_TASK_NAME;
    params.in_dev_name  = "";
    params.out_dev_name = "";

    streamer = streamer_create(&params);
    if (!streamer)
    {
        return kStatus_Fail;
    }

    prop.prop = PROP_FILESRC_SET_LOCATION;
    prop.val  = (uintptr_t)filename;

    streamer_set_property(streamer, prop, true);

    prop.prop = PROP_FILESRC_SET_SAMPLE_RATE;
    prop.val  = DEMO_SAMPLE_RATE;

    streamer_set_property(streamer, prop, true);

    prop.prop = PROP_FILESRC_SET_NUM_CHANNELS;
    prop.val  = get_app_data()->num_channels;

    streamer_set_property(streamer, prop, true);

    prop.prop = PROP_FILESRC_SET_BIT_WIDTH;
    prop.val  = DEMO_BIT_WIDTH;

    streamer_set_property(streamer, prop, true);

    prop.prop = PROP_FILESRC_SET_CHUNK_SIZE;
    prop.val  = get_app_data()->num_channels * DEMO_BYTE_WIDTH * DEMO_SAMPLE_RATE / 100;

    streamer_set_property(streamer, prop, true);

    prop.prop = PROP_AUDIOSINK_SET_VOLUME;
    prop.val  = volume;
    streamer_set_property(streamer, prop, true);

#ifdef EAP32_PROC
    if (get_app_data()->num_channels == 2)
    {
        register_post_process(streamer);
    }
#endif

    return kStatus_Success;
}

/* EAP Audio Tuning Tool control integration - START */
/* this functions should not be called internally to prevent possible issues caused by broken state machine */
eap_att_code_t play()
{
    init_logging();

    /* Uncomment below to turn on full debug logging for the streamer. */
    //     set_debug_module(0xffffffff);
    //     set_debug_level(LOGLVL_DEBUG);
    //     get_debug_state();
    streamer_pcm_init();

    if (STREAMER_PCM_Create((char *)get_eap_att_control()->input, DEMO_VOLUME) == kStatus_Success)
    {
        if (streamer_set_state(streamer, 0, STATE_PLAYING, true) == 0)
        {
            PRINTF("[EAP STREAMER] Starting playback\r\n");
            return kEapAttCodeOk;
        }
        else
        {
            PRINTF("[EAP STREAMER] Playback start failed\r\n");
            return kEapAttCodeStreamControlFailure;
        }
    }
    else
    {
        PRINTF("[EAP STREAMER] create_stream failed\r\n");
    }
    return kEapAttCodeStreamCreateFailed;
}

eap_att_code_t resume()
{
    if (streamer_set_state(streamer, 0, STATE_PLAYING, true) == 0)
    {
        return kEapAttCodeOk;
    }
    return kEapAttCodeStreamControlFailure;
}

eap_att_code_t pause()
{
    if (streamer_set_state(streamer, 0, STATE_PAUSED, true) == 0)
    {
        return kEapAttCodeOk;
    }
    return kEapAttCodeStreamControlFailure;
}

eap_att_code_t set_volume(int volume)
{
    ELEMENT_PROPERTY_T prop;
    prop.prop = PROP_AUDIOSINK_SET_VOLUME;
    prop.val  = volume;
    if (streamer_set_property(streamer, prop, true) == 0)
    {
        return kEapAttCodeOk;
    }
    return kEapAttCodeStreamControlFailure;
}

eap_att_code_t reset()
{
    return kEapAttCodeOk;
}

eap_att_code_t destroy()
{
    if (streamer != NULL)
    {
        streamer_destroy(streamer);
        streamer = 0;
        /* Suspend the tasks for memory cleanup */
        vTaskSuspend(app.shell_task_handle);
        vTaskDelay(100);
        vTaskResume(app.shell_task_handle);

        if (audioBuffer != NULL)
        {
            ringbuf_destroy(audioBuffer);
            audioBuffer = NULL;
        }

        deinit_logging();
#ifdef EAP32_PROC
        eap_att_control_t *control = get_eap_att_control();
        control->handle            = 0;
#endif
        PRINTF("[EAP STREAMER] destroyed\r\n");
    }
    return kEapAttCodeOk;
}

eap_att_code_t stop()
{
    if (streamer_set_state(streamer, 0, STATE_NULL, true) == 0)
    {
        /* Empty input ringbuffer. */
        if (audioBuffer)
        {
            ringbuf_clear(audioBuffer);
        }
        destroy();
        return kEapAttCodeOk;
    }
    return kEapAttCodeStreamControlFailure;
}

#ifdef EAP32_PROC
static eap_att_code_t update()
{
    eap_att_code_t status = kEapAttCodeOk;
    PRINTF("[EAP_STREAMER] update notified\r\n");
    eap_att_control_t *control = get_eap_att_control();
    if (((get_app_data()->lastPreset != control->eapPreset)
#if (ALGORITHM_XO == 1)
         || (get_eap_att_control()->controlParam->XO_OperatingMode != get_app_data()->lastXOOperatingMode)
#endif
             ) &&
        control->handle != 0)
    {
        if (get_app_data()->lastPreset != control->eapPreset)
        {
            PRINTF("[EAP_STREAMER] preset changed, forcing update\r\n");
            get_app_data()->lastPreset = control->eapPreset;
        }
        else
        {
            // reset presets to bypass preset reload during eap init
            get_app_data()->lastPreset = control->eapPreset = 0;
            PRINTF("[EAP_STREAMER] force update is requested\r\n");
        }

        if (control->status == kAttRunning)
        {
            status = pause();
            if (status == kEapAttCodeOk)
            {
                EAP_Deinit();
                EAP_Init(&get_app_data()->eap_args);
                status = resume();
            }
        }
        else
        {
            EAP_Deinit();
            EAP_Init(&get_app_data()->eap_args);
        }
    }

    return status;
}
#endif

void STREAMER_Init(void)
{
    eap_att_control_t *att_control = get_eap_att_control();

    progress_handler = att_control->progress;

    att_control->play       = &play;
    att_control->pause      = &pause;
    att_control->reset      = &reset;
    att_control->stop       = &stop;
    att_control->destroy    = &destroy;
    att_control->resume     = &resume;
    att_control->set_volume = &set_volume;
    att_control->logme      = PRINTF;
    att_control->volume     = 75;

#ifdef EAP32_PROC
    att_control->update = &update;
    // explicitly specify platform during initialization
    att_control->instParams->Platform = LVM_IMXRT1060;
#endif
}

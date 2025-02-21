/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_AK4497_ADAPTER_H_
#define _FSL_AK4497_ADAPTER_H_

#include "fsl_codec_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif
/*!
 * @brief Codec initilization.
 *
 * @param handle codec handle.
 * @param config codec configuration.
 * @return kStatus_Success is success, else initial failed.
 */
status_t HAL_CODEC_AK4497_Init(codec_handle_t *handle, void *config);

/*!
 * @brief Codec de-initilization.
 *
 * @param handle codec handle.
 * @return kStatus_Success is success, else de-initial failed.
 */
status_t HAL_CODEC_AK4497_Deinit(codec_handle_t *handle);

/*!
 * @brief set audio data format.
 *
 * @param handle codec handle.
 * @param mclk master clock frequency in HZ.
 * @param sampleRate sample rate in HZ.
 * @param bitWidth bit width.
 * @return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_AK4497_SetFormat(codec_handle_t *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth);

/*!
 * @brief set audio codec module volume.
 *
 * @param handle codec handle.
 * @param channel audio codec play channel, can be a value or combine value of _codec_play_channel.
 * @param volume volume value, support 0 ~ 100, 0 is mute, 100 is the maximum volume value.
 * @return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_AK4497_SetVolume(codec_handle_t *handle, uint32_t playChannel, uint32_t volume);

/*!
 * @brief set audio codec module mute.
 *
 * @param handle codec handle.
 * @param channel audio codec play channel, can be a value or combine value of _codec_play_channel.
 * @param isMute true is mute, false is unmute.
 * @return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_AK4497_SetMute(codec_handle_t *handle, uint32_t playChannel, bool isMute);

/*!
 * @brief set audio codec module power.
 *
 * @param handle codec handle.
 * @param module audio codec module.
 * @param powerOn true is power on, false is power down.
 * @return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_AK4497_SetPower(codec_handle_t *handle, codec_module_t module, bool powerOn);

/*!
 * @brief codec set record source.
 *
 * @param handle codec handle.
 * @param source audio codec record source, can be a value or combine value of _codec_record_source.
 *
 * @return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_AK4497_SetRecord(codec_handle_t *handle, uint32_t recordSource);

/*!
 * @brief codec set record channel.
 *
 * @param handle codec handle.
 * @param leftRecordChannel audio codec record channel, reference _codec_record_channel, can be a value or combine value
 of member in _codec_record_channel.
 * @param rightRecordChannel audio codec record channel, reference _codec_record_channel, can be a value combine of
 member in _codec_record_channel.

 * @return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_AK4497_SetRecordChannel(codec_handle_t *handle,
                                           uint32_t leftRecordChannel,
                                           uint32_t rightRecordChannel);

/*!
 * @brief codec set play source.
 *
 * @param handle codec handle.
 * @param playSource audio codec play source, can be a value or combine value of _codec_play_source.
 *
 * @return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_AK4497_SetPlay(codec_handle_t *handle, uint32_t playSource);

/*!
 * @brief codec module control.
 *
 * This function is used for codec module control, support switch digital interface cmd, can be expand to support codec
 * module specific feature
 *
 * @param handle codec handle.
 * @param cmd module control cmd, reference _codec_module_ctrl_cmd.
 * @param data value to write, when cmd is kCODEC_ModuleRecordSourceChannel, the data should be a value combine
 *  of channel and source, please reference macro CODEC_MODULE_RECORD_SOURCE_CHANNEL(source, LP, LN, RP, RN), reference
 *  codec specific driver for detail configurations.
 * @return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_AK4497_ModuleControl(codec_handle_t *handle, codec_module_ctrl_cmd_t cmd, uint32_t data);

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_AK4497_ADAPTER_H_ */

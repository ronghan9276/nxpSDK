/*
 * Copyright 2013 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "../source/system/nt_system_prv.h"
#include "../source/system/nt_system_mem_prv.h"
#include "../source/modules/nt_modules_prv.h"
#include "../source/controls/nt_controls_prv.h"
#if (NT_SAFETY_SUPPORT == 1)
#include "../source/safety/nt_safety_prv.h"
#include "../include/nt_safety.h"
#endif /* NT_SAFETY_SUPPORT */
#include "../include/nt_system.h"
#include "nt_types.h"

struct nt_kernel nt_kernel_data;

/* System data check */
int32_t _nt_system_check_data(const struct nt_system *system)
{
    if (system->modules == NULL)
    {
        return (int32_t)NT_FAILURE;
    }
    if (system->controls == NULL)
    {
        return (int32_t)NT_FAILURE;
    }
    if (system->time_period == 0U)
    {
        return (int32_t)NT_FAILURE;
    }
    return (int32_t)NT_SUCCESS;
}

/* Get the count of pointer array terminated by NULL pointer. */
uint32_t _nt_system_count_pointer_array(const void *const *pointer_array)
{
    const void *const *array = pointer_array;
    uint32_t count           = 0;

    if (array == NULL)
    {
        return 0;
    }

    while ((bool)(*array++ != NULL))
    {
        count++;
    }

    return count;
}

/* internal function */
int32_t _nt_system_init(const struct nt_system *system)
{
    NT_ASSERT(system != NULL);
    if (_nt_system_check_data(system) < (int32_t)NT_SUCCESS)
    {
        return (int32_t)NT_FAILURE;
    }

    nt_kernel_data.controls_cnt = (uint8_t)_nt_system_count_pointer_array((const void *const *)system->controls);
    nt_kernel_data.modules_cnt  = (uint8_t)_nt_system_count_pointer_array((const void *const *)system->modules);

    nt_kernel_data.controls = _nt_mem_alloc((uint32_t)(sizeof(void *) * (uint32_t)nt_kernel_data.controls_cnt));

    if (nt_kernel_data.controls == NULL)
    {
        return (int32_t)NT_OUT_OF_MEMORY;
    }

    nt_kernel_data.modules = _nt_mem_alloc(sizeof(void *) * (uint32_t)nt_kernel_data.modules_cnt);

    if (nt_kernel_data.modules == NULL)
    {
        return (int32_t)NT_OUT_OF_MEMORY;
    }

    nt_kernel_data.rom          = system;
    nt_kernel_data.time_counter = 0U;

    return (int32_t)NT_SUCCESS;
}

/* private function */
struct nt_kernel *_nt_system_get(void)
{
    return &nt_kernel_data;
}

/* private function */
void _nt_system_increment_time_counter(void)
{
    nt_kernel_data.time_counter += nt_kernel_data.rom->time_period;
}

/* private function */
uint32_t _nt_system_get_time_period(void)
{
    return (uint32_t)nt_kernel_data.rom->time_period;
}

/* public function */
#if (NT_SAFETY_SUPPORT == 1)
uint32_t _nt_system_get_safety_period(void)
{
    return ((uint32_t)nt_kernel_data.rom->time_period * (uint32_t)nt_kernel_data.rom->safety_period_multiple);
}
#endif /* NT_SAFETY_SUPPORT */

/* public function */
uint32_t nt_system_get_time_offset(uint32_t event_stamp)
{
    uint32_t time_counter = nt_system_get_time_counter();
    if (time_counter > event_stamp)
    {
        return (time_counter - event_stamp);
    }
    else
    {
        return (event_stamp - time_counter);
    }
}

/* private function */
uint32_t _nt_system_get_time_offset_from_period(uint32_t event_period)
{
    if ((bool)event_period)
    {
        uint32_t time_period = _nt_system_get_time_period();
        return (uint32_t)((nt_system_get_time_counter() / time_period) % event_period);
    }
    else
    {
        return 1U; /* returns positive number, event should not be triggered */
    }
}

/* public function */
uint32_t nt_system_get_time_counter(void)
{
    return nt_kernel_data.time_counter;
}

/* internal function */
int32_t _nt_system_module_function(uint32_t option)
{
    uint32_t result;
    struct nt_module_data *module;
    uint32_t i;

    switch (option)
    {
        case (uint32_t)NT_SYSTEM_MODULE_INIT:
            result = (int32_t)NT_SUCCESS;
            break;
        case (uint32_t)NT_SYSTEM_MODULE_CHECK_DATA:
            result = (int32_t)NT_FAILURE;
            break;
        default:
        {
            result = (int32_t)NT_FAILURE;
        }
        break;
    }

    /* steps through all control pointers */
    for (i = 0; i < nt_kernel_data.modules_cnt; i++)
    {
        module = nt_kernel_data.modules[i];
        switch (option)
        {
            case (uint32_t)NT_SYSTEM_MODULE_INIT:
            {
                nt_kernel_data.modules[i] = _nt_module_init(nt_kernel_data.rom->modules[i]);
                if (nt_kernel_data.modules[i] == NULL)
                {
                    result |= (uint32_t)NT_OUT_OF_MEMORY; /* failure stops the entire init phase  */
                }                                         /* if any module has not enough memory */
            }
            break;
            case (uint32_t)NT_SYSTEM_MODULE_TRIGGER:
                if (_nt_module_trigger(module) == (int32_t)NT_SCAN_IN_PROGRESS)
                {
                    result = (uint32_t)NT_FAILURE; /* module not ready, triggering continues */
                }
                break;
            case (uint32_t)NT_SYSTEM_MODULE_PROCESS:
                result = (uint32_t)_nt_module_process(module);
                break;
#if (NT_SAFETY_SUPPORT == 1)
            case (uint32_t)NT_SYSTEM_MODULE_SAFETY_PROCESS:
                result = (uint32_t)_nt_module_process_safety(module);
                break;
#endif /* NT_SAFETY_SUPPORT */
            case (uint32_t)NT_SYSTEM_MODULE_CHECK_DATA:
                if (!(bool)(_nt_module_get_flag(module, (int32_t)NT_MODULE_NEW_DATA_FLAG)))
                {
                    result &= (uint32_t)NT_FAILURE; /* module has not processed all data yet */
                }
                else
                {
                    result &= (uint32_t)NT_SUCCESS; /* module has processed all data yet */
                }                                   /* at least one module succeed to process the control */
                break;
            default:
            {
                result = (int32_t)NT_FAILURE; /* module not ready, triggering continues */
            }
            break;
        }
        module++;
    }
    return (int32_t)result;
}

/* internal function */
int32_t _nt_system_control_function(uint32_t option)
{
    struct nt_control_data *control;
    int32_t result = (int32_t)NT_SUCCESS;
    uint32_t i;

    /* steps through all control pointers */
    for (i = 0; i < nt_kernel_data.controls_cnt; i++)
    {
        control = nt_kernel_data.controls[i];

        switch (option)
        {
            case (int32_t)NT_SYSTEM_CONTROL_INIT:
            {
                nt_kernel_data.controls[i] = _nt_control_init(nt_kernel_data.rom->controls[i]);
                if (nt_kernel_data.controls[i] == NULL)
                {
                    return (int32_t)NT_OUT_OF_MEMORY; /* failure stops the entire init phase */
                }
            }
            break;
            case (int32_t)NT_SYSTEM_CONTROL_OVERRUN:
                if (_nt_control_overrun(control) < (int32_t)NT_SUCCESS)
                {
                    result = (int32_t)NT_FAILURE; /* overrun error, trigger others anyway */
                }
                break;
            case (int32_t)NT_SYSTEM_CONTROL_PROCESS:
            {
                const struct nt_control_interface *interface =
                    (const struct nt_control_interface *)control->rom->interface;
                if (interface->process != NULL)
                {
                    if (interface->process(control) < (int32_t)NT_SUCCESS)
                    {
                        result = (int32_t)NT_FAILURE; /* data not ready */
                    }
                }
            }
            break;
            case (int32_t)NT_SYSTEM_CONTROL_DATA_READY:
                _nt_control_set_flag(control, (uint32_t)NT_CONTROL_NEW_DATA_FLAG);
                break;
            default:
                result = (int32_t)NT_NOT_SUPPORTED;
                break;
        }
    }
    return result;
}

void _nt_system_invoke_callback(uint32_t event, union nt_system_event_context *context)
{
    struct nt_kernel *system = _nt_system_get();

    if (system->callback == NULL)
    {
        return;
    }

    switch (event)
    {
        case (uint32_t)NT_SYSTEM_EVENT_OVERRUN:
            system->callback(NT_SYSTEM_EVENT_OVERRUN, NULL);
            break;
        case (uint32_t)NT_SYSTEM_EVENT_DATA_READY:
            system->callback(NT_SYSTEM_EVENT_DATA_READY, NULL);
            break;
        case (uint32_t)NT_SYSTEM_EVENT_MODULE_DATA_READY:
            system->callback(NT_SYSTEM_EVENT_MODULE_DATA_READY, context);
            break;
        case (uint32_t)NT_SYSTEM_EVENT_DATA_OVERFLOW:
            system->callback(NT_SYSTEM_EVENT_DATA_OVERFLOW, NULL);
            break;
        case (uint32_t)NT_SYSTEM_EVENT_SIGNAL_HIGH:
            system->callback(NT_SYSTEM_EVENT_SIGNAL_HIGH, context);
            break;
        case (uint32_t)NT_SYSTEM_EVENT_SIGNAL_LOW:
            system->callback(NT_SYSTEM_EVENT_SIGNAL_LOW, context);
            break;
        case (uint32_t)NT_SYSTEM_EVENT_ELEC_SHORT_VDD:
            system->callback(NT_SYSTEM_EVENT_ELEC_SHORT_VDD, context);
            break;
        case (uint32_t)NT_SYSTEM_EVENT_ELEC_SHORT_GND:
            system->callback(NT_SYSTEM_EVENT_ELEC_SHORT_GND, context);
            break;
        case (uint32_t)NT_SYSTEM_EVENT_ELEC_SHORT_ADJ:
            system->callback(NT_SYSTEM_EVENT_ELEC_SHORT_ADJ, context);
            break;
        case (uint32_t)NT_SYSTEM_EVENT_CRC_FAILED:
            system->callback(NT_SYSTEM_EVENT_CRC_FAILED, NULL);
            break;
        default:
            system->callback(NT_SYSTEM_EVENT_OVERRUN, NULL);
            break;
    }
}

void nt_system_register_callback(nt_system_callback callback)
{
    nt_kernel_data.callback = callback;
}

void nt_error_register_callback(nt_error_callback callback)
{
#if (NT_DEBUG != 0)
    nt_kernel_data.error_callback = callback;
#else
    (void)callback;
#endif
}

void _nt_system_modules_data_ready(struct nt_module_data *module)
{
    union nt_system_event_context context;

    context.module_data = module;

    _nt_module_clear_flag(module, (int32_t)NT_MODULE_BUSY_FLAG);

    if (_nt_system_module_function((uint32_t)NT_SYSTEM_MODULE_CHECK_DATA) == (int32_t)NT_SUCCESS)
    {
        /* all modules have been processed, set data ready for all controls */

        _nt_system_invoke_callback((uint32_t)NT_SYSTEM_EVENT_MODULE_DATA_READY, &context);
        (void)(int32_t) _nt_system_control_function((uint32_t)NT_SYSTEM_CONTROL_DATA_READY);
    }
}

const struct nt_module *_nt_system_get_module(uint32_t interface_address, uint32_t instance)
{
    const struct nt_module *const *module = nt_kernel_data.rom->modules;

    while (*module != NULL)
    {
        if ((uint32_t)((*module)->interface) == interface_address)
        {
            if ((bool)(((*module)->instance) == instance))
            {
                return *module;
            }
        }
        module++;
    }

    return NULL;
}

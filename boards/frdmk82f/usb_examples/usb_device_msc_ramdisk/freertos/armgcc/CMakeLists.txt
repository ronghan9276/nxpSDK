INCLUDE(CMakeForceCompiler)

# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

 
# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})


SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -DDEBUG")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -D__STARTUP_CLEAR_BSS")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -g")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mcpu=cortex-m4")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -Wall")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mfloat-abi=hard")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mfpu=fpv4-sp-d16")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mthumb")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fno-common")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mapcs")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -std=gnu99")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -D__STARTUP_CLEAR_BSS")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mcpu=cortex-m4")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -Wall")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mfloat-abi=hard")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mfpu=fpv4-sp-d16")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mthumb")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fno-common")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mapcs")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -std=gnu99")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG=1")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCPU_MK82FN256VDC15")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DUSB_STACK_FREERTOS_HEAP_SIZE=32768")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DUSB_STACK_FREERTOS")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DFSL_RTOS_FREE_RTOS")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DFRDM_K82F")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DFREEDOM")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mcpu=cortex-m4")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mfloat-abi=hard")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mfpu=fpv4-sp-d16")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mthumb")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -MMD")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -MP")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-common")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mapcs")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=gnu99")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -D_DEBUG=0")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DCPU_MK82FN256VDC15")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DUSB_STACK_FREERTOS_HEAP_SIZE=32768")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DUSB_STACK_FREERTOS")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DFSL_RTOS_FREE_RTOS")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DFRDM_K82F")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DFREEDOM")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mcpu=cortex-m4")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mfloat-abi=hard")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mfpu=fpv4-sp-d16")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mthumb")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -MMD")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -MP")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-common")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mapcs")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -std=gnu99")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mcpu=cortex-m4")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wall")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mfloat-abi=hard")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mfpu=fpv4-sp-d16")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --specs=nano.specs")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -fno-common")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mthumb")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mapcs")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --gc-sections")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -static")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -z")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} muldefs")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mcpu=cortex-m4")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Wall")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mfloat-abi=hard")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mfpu=fpv4-sp-d16")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --specs=nano.specs")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fno-common")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mthumb")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mapcs")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --gc-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -static")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -z")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} muldefs")

include_directories(${ProjDirPath}/..)

include_directories(${ProjDirPath}/..)

include_directories(${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/portable/GCC/ARM_CM4F)

include_directories(${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/include)

include_directories(${ProjDirPath}/..)

include_directories(${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source)

include_directories(${ProjDirPath}/../../../../../../devices/MK82F25615/utilities)

include_directories(${ProjDirPath}/../../../../../../middleware/usb_1.0.0)

include_directories(${ProjDirPath}/../../../../../../middleware/usb_1.0.0/osa)

include_directories(${ProjDirPath}/../../../../../../middleware/usb_1.0.0/include)

include_directories(${ProjDirPath}/../../../../../../middleware/usb_1.0.0/device)

include_directories(${ProjDirPath}/../../../../../../CMSIS/Include)

include_directories(${ProjDirPath}/../../../..)

include_directories(${ProjDirPath}/../../../../../../devices/MK82F25615/drivers)

include_directories(${ProjDirPath}/../../../../../../devices/MK82F25615)

include_directories(${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/portable/GCC/ARM_CM4F)

include_directories(${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/include)

include_directories(${ProjDirPath}/..)

include_directories(${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source)

include_directories(${ProjDirPath}/../../../../../../devices/MK82F25615/utilities)

include_directories(${ProjDirPath}/../../../../../../middleware/usb_1.0.0)

include_directories(${ProjDirPath}/../../../../../../middleware/usb_1.0.0/osa)

include_directories(${ProjDirPath}/../../../../../../middleware/usb_1.0.0/include)

include_directories(${ProjDirPath}/../../../../../../middleware/usb_1.0.0/device)

include_directories(${ProjDirPath}/../../../../../../CMSIS/Include)

include_directories(${ProjDirPath}/../../../..)

include_directories(${ProjDirPath}/../../../../../../devices/MK82F25615/drivers)

include_directories(${ProjDirPath}/../../../../../../devices/MK82F25615)

add_executable(dev_msc_ramdisk_freertos.elf 
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/portable/GCC/ARM_CM4F/port.c"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/portable/GCC/ARM_CM4F/portmacro.h"
"${ProjDirPath}/../../../../../../devices/MK82F25615/utilities/fsl_sbrk.c"
"${ProjDirPath}/../../../../../../devices/MK82F25615/gcc/startup_MK82F25615.S"
"${ProjDirPath}/../../../../../../middleware/usb_1.0.0/device/usb_device_khci.c"
"${ProjDirPath}/../../../../../../middleware/usb_1.0.0/device/usb_device_khci.h"
"${ProjDirPath}/../../../../../../devices/MK82F25615/drivers/fsl_lpuart.h"
"${ProjDirPath}/../../../../../../devices/MK82F25615/drivers/fsl_lpuart.c"
"${ProjDirPath}/../../../../../../middleware/usb_1.0.0/osa/usb_osa.h"
"${ProjDirPath}/../../../../../../middleware/usb_1.0.0/osa/usb_osa_freertos.h"
"${ProjDirPath}/../../../../../../middleware/usb_1.0.0/osa/usb_osa_freertos.c"
"${ProjDirPath}/../usb_device_ch9.c"
"${ProjDirPath}/../usb_device_ch9.h"
"${ProjDirPath}/../usb_device_class.c"
"${ProjDirPath}/../usb_device_class.h"
"${ProjDirPath}/../usb_device_msc.c"
"${ProjDirPath}/../usb_device_msc.h"
"${ProjDirPath}/../usb_device_msc_ufi.c"
"${ProjDirPath}/../usb_device_msc_ufi.h"
"${ProjDirPath}/../disk.c"
"${ProjDirPath}/../disk.h"
"${ProjDirPath}/../usb_device_descriptor.c"
"${ProjDirPath}/../usb_device_descriptor.h"
"${ProjDirPath}/../usb_device_config.h"
"${ProjDirPath}/../FreeRTOSConfig.h"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/include/croutine.h"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/include/event_groups.h"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/include/FreeRTOS.h"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/include/list.h"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/include/mpu_wrappers.h"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/include/portable.h"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/include/projdefs.h"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/include/queue.h"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/include/semphr.h"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/include/StackMacros.h"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/include/task.h"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/include/timers.h"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/croutine.c"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/portable/MemMang/heap_4.c"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/list.c"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/queue.c"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/tasks.c"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/timers.c"
"${ProjDirPath}/../../../../../../rtos/freertos_8.2.3/Source/event_groups.c"
"${ProjDirPath}/../../../../../../devices/MK82F25615/system_MK82F25615.c"
"${ProjDirPath}/../../../../../../devices/MK82F25615/system_MK82F25615.h"
"${ProjDirPath}/../../../../../../devices/MK82F25615/utilities/fsl_debug_console.c"
"${ProjDirPath}/../../../../../../devices/MK82F25615/utilities/fsl_debug_console.h"
"${ProjDirPath}/../../../../../../middleware/usb_1.0.0/include/usb.h"
"${ProjDirPath}/../../../../../../middleware/usb_1.0.0/device/usb_device.h"
"${ProjDirPath}/../../../../../../middleware/usb_1.0.0/device/usb_device_dci.c"
"${ProjDirPath}/../../../../../../middleware/usb_1.0.0/device/usb_device_dci.h"
"${ProjDirPath}/../../../../../../devices/MK82F25615/drivers/fsl_port.h"
"${ProjDirPath}/../../../../../../devices/MK82F25615/drivers/fsl_sim.c"
"${ProjDirPath}/../../../../../../devices/MK82F25615/drivers/fsl_clock.h"
"${ProjDirPath}/../../../../../../devices/MK82F25615/drivers/fsl_clock.c"
"${ProjDirPath}/../../../../../../devices/MK82F25615/drivers/fsl_mpu.h"
"${ProjDirPath}/../../../../../../devices/MK82F25615/drivers/fsl_mpu.c"
"${ProjDirPath}/../../../../../../devices/MK82F25615/drivers/fsl_common.h"
"${ProjDirPath}/../../../../../../devices/MK82F25615/drivers/fsl_common.c"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../../../../../../devices/MK82F25615/drivers/fsl_gpio.h"
"${ProjDirPath}/../../../../../../devices/MK82F25615/drivers/fsl_gpio.c"
"${ProjDirPath}/../../../../../../devices/MK82F25615/drivers/fsl_smc.h"
"${ProjDirPath}/../../../../../../devices/MK82F25615/drivers/fsl_smc.c"
)


set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -T${ProjDirPath}/MK82FN256xxx15_flash.ld -static")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -T${ProjDirPath}/MK82FN256xxx15_flash.ld -static")

TARGET_LINK_LIBRARIES(dev_msc_ramdisk_freertos.elf -Wl,--start-group)
target_link_libraries(dev_msc_ramdisk_freertos.elf debug m)

target_link_libraries(dev_msc_ramdisk_freertos.elf debug c)

target_link_libraries(dev_msc_ramdisk_freertos.elf debug gcc)

target_link_libraries(dev_msc_ramdisk_freertos.elf debug nosys)

target_link_libraries(dev_msc_ramdisk_freertos.elf optimized m)

target_link_libraries(dev_msc_ramdisk_freertos.elf optimized c)

target_link_libraries(dev_msc_ramdisk_freertos.elf optimized gcc)

target_link_libraries(dev_msc_ramdisk_freertos.elf optimized nosys)

TARGET_LINK_LIBRARIES(dev_msc_ramdisk_freertos.elf -Wl,--end-group)


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


SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -DDEBUG")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -D__STARTUP_CLEAR_BSS")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -D__STARTUP_INITIALIZE_NONCACHEDATA")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -g")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -march=armv7-a")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -Wall")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -mfloat-abi=hard")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -mfpu=vfpv4")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -fno-common")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -ffunction-sections")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -fdata-sections")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -ffreestanding")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -fno-builtin")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -mthumb")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -mapcs")

SET(CMAKE_ASM_FLAGS_DDR_DEBUG "${CMAKE_ASM_FLAGS_DDR_DEBUG} -std=gnu99")

SET(CMAKE_ASM_FLAGS_DDR_RELEASE "${CMAKE_ASM_FLAGS_DDR_RELEASE} -D__STARTUP_CLEAR_BSS")

SET(CMAKE_ASM_FLAGS_DDR_RELEASE "${CMAKE_ASM_FLAGS_DDR_RELEASE} -D__STARTUP_INITIALIZE_NONCACHEDATA")

SET(CMAKE_ASM_FLAGS_DDR_RELEASE "${CMAKE_ASM_FLAGS_DDR_RELEASE} -march=armv7-a")

SET(CMAKE_ASM_FLAGS_DDR_RELEASE "${CMAKE_ASM_FLAGS_DDR_RELEASE} -Wall")

SET(CMAKE_ASM_FLAGS_DDR_RELEASE "${CMAKE_ASM_FLAGS_DDR_RELEASE} -mfloat-abi=hard")

SET(CMAKE_ASM_FLAGS_DDR_RELEASE "${CMAKE_ASM_FLAGS_DDR_RELEASE} -mfpu=vfpv4")

SET(CMAKE_ASM_FLAGS_DDR_RELEASE "${CMAKE_ASM_FLAGS_DDR_RELEASE} -fno-common")

SET(CMAKE_ASM_FLAGS_DDR_RELEASE "${CMAKE_ASM_FLAGS_DDR_RELEASE} -ffunction-sections")

SET(CMAKE_ASM_FLAGS_DDR_RELEASE "${CMAKE_ASM_FLAGS_DDR_RELEASE} -fdata-sections")

SET(CMAKE_ASM_FLAGS_DDR_RELEASE "${CMAKE_ASM_FLAGS_DDR_RELEASE} -ffreestanding")

SET(CMAKE_ASM_FLAGS_DDR_RELEASE "${CMAKE_ASM_FLAGS_DDR_RELEASE} -fno-builtin")

SET(CMAKE_ASM_FLAGS_DDR_RELEASE "${CMAKE_ASM_FLAGS_DDR_RELEASE} -mthumb")

SET(CMAKE_ASM_FLAGS_DDR_RELEASE "${CMAKE_ASM_FLAGS_DDR_RELEASE} -mapcs")

SET(CMAKE_ASM_FLAGS_DDR_RELEASE "${CMAKE_ASM_FLAGS_DDR_RELEASE} -std=gnu99")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -DDEBUG")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -D__STARTUP_CLEAR_BSS")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -D__STARTUP_INITIALIZE_NONCACHEDATA")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -g")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -march=armv7-a")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -Wall")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mfloat-abi=hard")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mfpu=vfpv4")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fno-common")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mthumb")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mapcs")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -std=gnu99")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -D__STARTUP_CLEAR_BSS")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -D__STARTUP_INITIALIZE_NONCACHEDATA")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -march=armv7-a")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -Wall")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mfloat-abi=hard")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mfpu=vfpv4")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fno-common")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mthumb")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mapcs")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -std=gnu99")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -DDEBUG")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -DCPU_MCIMX6G3DVM05")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -DUSB_STACK_FREERTOS_HEAP_SIZE=32768")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -DUSB_STACK_FREERTOS")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -DFSL_RTOS_FREE_RTOS")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -DEVK_MCIMX6UL")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -g")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -O0")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -mno-unaligned-access")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -march=armv7-a")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -Wall")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -mfloat-abi=hard")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -mfpu=vfpv4")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -MMD")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -MP")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -fno-common")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -ffunction-sections")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -fdata-sections")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -ffreestanding")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -fno-builtin")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -mthumb")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -mapcs")

SET(CMAKE_C_FLAGS_DDR_DEBUG "${CMAKE_C_FLAGS_DDR_DEBUG} -std=gnu99")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -DNDEBUG")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -DCPU_MCIMX6G3DVM05")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -DUSB_STACK_FREERTOS_HEAP_SIZE=32768")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -DUSB_STACK_FREERTOS")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -DFSL_RTOS_FREE_RTOS")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -DEVK_MCIMX6UL")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -Os")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -mno-unaligned-access")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -march=armv7-a")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -Wall")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -mfloat-abi=hard")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -mfpu=vfpv4")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -MMD")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -MP")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -fno-common")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -ffunction-sections")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -fdata-sections")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -ffreestanding")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -fno-builtin")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -mthumb")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -mapcs")

SET(CMAKE_C_FLAGS_DDR_RELEASE "${CMAKE_C_FLAGS_DDR_RELEASE} -std=gnu99")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG=1")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCPU_MCIMX6G3DVM05")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DUSB_STACK_FREERTOS_HEAP_SIZE=32768")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DUSB_STACK_FREERTOS")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DFSL_RTOS_FREE_RTOS")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DEVK_MCIMX6UL")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mno-unaligned-access")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -march=armv7-a")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mfloat-abi=hard")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mfpu=vfpv4")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -MMD")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -MP")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-common")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mthumb")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mapcs")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=gnu99")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -D_DEBUG=0")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DCPU_MCIMX6G3DVM05")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DUSB_STACK_FREERTOS_HEAP_SIZE=32768")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DUSB_STACK_FREERTOS")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DFSL_RTOS_FREE_RTOS")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DEVK_MCIMX6UL")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mno-unaligned-access")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -march=armv7-a")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mfloat-abi=hard")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mfpu=vfpv4")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -MMD")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -MP")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-common")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mthumb")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mapcs")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -std=gnu99")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -DDEBUG")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -g")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -O0")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -march=armv7-a")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -Wall")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -mfloat-abi=hard")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -mfpu=vfpv4")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -MMD")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -MP")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -fno-common")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -ffunction-sections")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -fdata-sections")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -ffreestanding")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -fno-builtin")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -mthumb")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -mapcs")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -fno-rtti")

SET(CMAKE_CXX_FLAGS_DDR_DEBUG "${CMAKE_CXX_FLAGS_DDR_DEBUG} -fno-exceptions")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -march=armv7-a")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mfloat-abi=hard")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mfpu=vfpv4")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -MMD")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -MP")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-common")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mthumb")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mapcs")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-rtti")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-exceptions")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=armv7-a")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mfloat-abi=hard")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mfpu=vfpv4")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -MMD")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -MP")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-common")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mthumb")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mapcs")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-rtti")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-exceptions")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -Os")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -march=armv7-a")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -Wall")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -mfloat-abi=hard")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -mfpu=vfpv4")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -MMD")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -MP")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -fno-common")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -ffunction-sections")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -fdata-sections")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -ffreestanding")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -fno-builtin")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -mthumb")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -mapcs")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -fno-rtti")

SET(CMAKE_CXX_FLAGS_DDR_RELEASE "${CMAKE_CXX_FLAGS_DDR_RELEASE} -fno-exceptions")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --defsym=IRQ_Handler=FreeRTOS_IRQ_Handler")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --defsym=SVC_Handler=FreeRTOS_SWI_Handler")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -march=armv7-a")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Wall")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mfloat-abi=hard")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mfpu=vfpv4")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --specs=nano.specs")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --specs=nosys.specs")

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

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --defsym=__usb_ram_size__=0x800")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --defsym=IRQ_Handler=FreeRTOS_IRQ_Handler")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --defsym=SVC_Handler=FreeRTOS_SWI_Handler")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -march=armv7-a")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wall")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mfloat-abi=hard")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mfpu=vfpv4")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --specs=nano.specs")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --specs=nosys.specs")

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

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --defsym=__usb_ram_size__=0x800")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} --defsym=IRQ_Handler=FreeRTOS_IRQ_Handler")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} --defsym=SVC_Handler=FreeRTOS_SWI_Handler")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -march=armv7-a")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -Wall")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -mfloat-abi=hard")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -mfpu=vfpv4")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} --specs=nano.specs")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} --specs=nosys.specs")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -fno-common")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -ffunction-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -fdata-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -ffreestanding")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -fno-builtin")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -mthumb")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -mapcs")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} --gc-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -static")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -z")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} muldefs")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} --defsym=__usb_ram_size__=0x800")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -g")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} --defsym=IRQ_Handler=FreeRTOS_IRQ_Handler")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} --defsym=SVC_Handler=FreeRTOS_SWI_Handler")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -march=armv7-a")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -Wall")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -mfloat-abi=hard")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -mfpu=vfpv4")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} --specs=nano.specs")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} --specs=nosys.specs")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -fno-common")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -ffunction-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -fdata-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -ffreestanding")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -fno-builtin")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -mthumb")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -mapcs")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} --gc-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -static")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -z")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} muldefs")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} --defsym=__usb_ram_size__=0x800")

include_directories(${ProjDirPath}/../../../..)

include_directories(${ProjDirPath}/..)

include_directories(${ProjDirPath}/../../../../../../CMSIS/Include)

include_directories(${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/ARM_CA9)

include_directories(${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/include)

include_directories(${ProjDirPath}/../../../../../../CORTEXA/Include)

include_directories(${ProjDirPath}/../../../../../../devices)

include_directories(${ProjDirPath}/../../../../../../platform/drivers)

include_directories(${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source)

include_directories(${ProjDirPath}/../../../../../../middleware/usb_1.6.3)

include_directories(${ProjDirPath}/../../../../../../middleware/usb_1.6.3/osa)

include_directories(${ProjDirPath}/../../../../../../middleware/usb_1.6.3/include)

include_directories(${ProjDirPath}/../../../../../../middleware/usb_1.6.3/device)

include_directories(${ProjDirPath}/../../../../../../middleware/sdmmc_2.1.2/inc)

include_directories(${ProjDirPath}/../../../../../../middleware/sdmmc_2.1.2/src)

include_directories(${ProjDirPath}/../../../../../../middleware/sdmmc_2.1.2/port)

include_directories(${ProjDirPath}/../../../../../../devices/MCIMX6G3/utilities)

include_directories(${ProjDirPath}/../../../../../../devices/MCIMX6G3/drivers)

include_directories(${ProjDirPath}/../../../../../../middleware/usb_1.6.3/phy)

include_directories(${ProjDirPath}/../../../../../../platform/utilities/debug_console)

include_directories(${ProjDirPath}/../../../../../../platform/utilities/debug_console/io)

include_directories(${ProjDirPath}/../../../../../../platform/utilities/debug_console/str)

include_directories(${ProjDirPath}/../../../../../../devices/MCIMX6G3)

add_executable(dev_msc_sdcard_freertos_ca.elf 
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/utilities/fsl_sbrk.c"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/ARM_CA9/port.c"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/ARM_CA9/portASM.S"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/ARM_CA9/portmacro.h"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/gcc/startup_MCIMX6G3.S"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/drivers/fsl_gpio.h"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/drivers/fsl_gpio.c"
"${ProjDirPath}/../../../../../../middleware/usb_1.6.3/device/usb_device_ehci.c"
"${ProjDirPath}/../../../../../../middleware/usb_1.6.3/device/usb_device_ehci.h"
"${ProjDirPath}/../../../../../../middleware/usb_1.6.3/include/usb_ehci.h"
"${ProjDirPath}/../../../../../../middleware/usb_1.6.3/phy/usb_phy.c"
"${ProjDirPath}/../../../../../../middleware/usb_1.6.3/phy/usb_phy.h"
"${ProjDirPath}/../fsl_host.c"
"${ProjDirPath}/../event.c"
"${ProjDirPath}/../usb_device_msc_config.h"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/drivers/fsl_usdhc.c"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/drivers/fsl_usdhc.h"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/drivers/fsl_uart.h"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/drivers/fsl_uart.c"
"${ProjDirPath}/../../../../../../middleware/usb_1.6.3/osa/usb_osa.h"
"${ProjDirPath}/../../../../../../middleware/usb_1.6.3/osa/usb_osa_freertos.h"
"${ProjDirPath}/../../../../../../middleware/usb_1.6.3/osa/usb_osa_freertos.c"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/portable/MemMang/heap_4.c"
"${ProjDirPath}/../usb_device_ch9.c"
"${ProjDirPath}/../usb_device_ch9.h"
"${ProjDirPath}/../usb_device_class.c"
"${ProjDirPath}/../usb_device_class.h"
"${ProjDirPath}/../usb_device_msc.c"
"${ProjDirPath}/../usb_device_msc.h"
"${ProjDirPath}/../usb_device_msc_ufi.c"
"${ProjDirPath}/../usb_device_msc_ufi.h"
"${ProjDirPath}/../../../../../../middleware/sdmmc_2.1.2/src/fsl_sd.c"
"${ProjDirPath}/../../../../../../middleware/sdmmc_2.1.2/src/fsl_sdmmc.c"
"${ProjDirPath}/../disk_sdcard.c"
"${ProjDirPath}/../disk_sdcard.h"
"${ProjDirPath}/../usb_device_descriptor.c"
"${ProjDirPath}/../usb_device_descriptor.h"
"${ProjDirPath}/../usb_device_config.h"
"${ProjDirPath}/../FreeRTOSConfig.h"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/include/croutine.h"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/include/event_groups.h"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/include/FreeRTOS.h"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/include/list.h"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/include/mpu_wrappers.h"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/include/portable.h"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/include/projdefs.h"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/include/queue.h"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/include/semphr.h"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/include/StackMacros.h"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/include/task.h"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/include/timers.h"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/include/deprecated_definitions.h"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/croutine.c"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/list.c"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/queue.c"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/tasks.c"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/timers.c"
"${ProjDirPath}/../../../../../../rtos/freertos_9.0.0/Source/event_groups.c"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/system_MCIMX6G3.c"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/system_MCIMX6G3.h"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/utilities/fsl_debug_console.c"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/utilities/fsl_debug_console.h"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/utilities/fsl_debug_console_conf.h"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/utilities/fsl_io.c"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/utilities/fsl_io.h"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/utilities/fsl_log.c"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/utilities/fsl_log.h"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/utilities/fsl_str.c"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/utilities/fsl_str.h"
"${ProjDirPath}/../../../../../../middleware/usb_1.6.3/include/usb.h"
"${ProjDirPath}/../../../../../../middleware/usb_1.6.3/include/usb_misc.h"
"${ProjDirPath}/../../../../../../middleware/usb_1.6.3/include/usb_spec.h"
"${ProjDirPath}/../../../../../../middleware/usb_1.6.3/device/usb_device.h"
"${ProjDirPath}/../../../../../../middleware/usb_1.6.3/device/usb_device_dci.c"
"${ProjDirPath}/../../../../../../middleware/usb_1.6.3/device/usb_device_dci.h"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/drivers/fsl_clock.h"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/drivers/fsl_clock.c"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/drivers/fsl_common.h"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/drivers/fsl_common.c"
"${ProjDirPath}/../../../../../../middleware/sdmmc_2.1.2/inc/fsl_card.h"
"${ProjDirPath}/../../../../../../middleware/sdmmc_2.1.2/inc/fsl_host.h"
"${ProjDirPath}/../../../../../../middleware/sdmmc_2.1.2/inc/fsl_sdmmc.h"
"${ProjDirPath}/../../../../../../middleware/sdmmc_2.1.2/inc/fsl_specification.h"
"${ProjDirPath}/../clock_config_ocram.c"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../../../../../../devices/MCIMX6G3/drivers/fsl_iomuxc.h"
)


set(CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DDR_DEBUG} -T${ProjDirPath}/MCIMX6G3xxx05_ram.ld -static")

set(CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DDR_RELEASE} -T${ProjDirPath}/MCIMX6G3xxx05_ram.ld -static")

set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -T${ProjDirPath}/MCIMX6G3xxx05_flash.ld -static")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -T${ProjDirPath}/MCIMX6G3xxx05_flash.ld -static")

TARGET_LINK_LIBRARIES(dev_msc_sdcard_freertos_ca.elf -Wl,--start-group)
target_link_libraries(dev_msc_sdcard_freertos_ca.elf optimized m)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf optimized c)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf optimized gcc)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf optimized nosys)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf optimized m)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf optimized c)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf optimized gcc)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf optimized nosys)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf debug m)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf debug c)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf debug gcc)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf debug nosys)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf optimized m)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf optimized c)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf optimized gcc)

target_link_libraries(dev_msc_sdcard_freertos_ca.elf optimized nosys)

TARGET_LINK_LIBRARIES(dev_msc_sdcard_freertos_ca.elf -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET dev_msc_sdcard_freertos_ca.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/dev_msc_sdcard_freertos_ca.elf ${EXECUTABLE_OUTPUT_PATH}/sdk20-app.bin)

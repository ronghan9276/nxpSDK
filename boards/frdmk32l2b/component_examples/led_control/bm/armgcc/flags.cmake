SET(CMAKE_ASM_FLAGS_DEBUG " \
    -DDEBUG \
    -D__STARTUP_CLEAR_BSS \
    -g \
    -mcpu=cortex-m0plus \
    -Wall \
    -mfloat-abi=soft \
    -mthumb \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mapcs \
    -std=gnu99 \
")
SET(CMAKE_ASM_FLAGS_RELEASE " \
    -DNDEBUG \
    -D__STARTUP_CLEAR_BSS \
    -mcpu=cortex-m0plus \
    -Wall \
    -mfloat-abi=soft \
    -mthumb \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mapcs \
    -std=gnu99 \
")
SET(CMAKE_C_FLAGS_DEBUG " \
    -DDEBUG \
    -DCPU_K32L2B31VLH0A \
    -DUSB_STACK_BM=1 \
    -DDEBUG_CONSOLE_TRANSFER_NON_BLOCKING \
    -DFSL_OSA_TASK_ENABLE=1 \
    -DFRDM_K32L2B \
    -DFREEDOM \
    -DDEBUG_CONSOLE_RX_ENABLE=0 \
    -DSERIAL_PORT_TYPE_UART=1 \
    -g \
    -O0 \
    -mcpu=cortex-m0plus \
    -Wall \
    -mfloat-abi=soft \
    -mthumb \
    -MMD \
    -MP \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mapcs \
    -std=gnu99 \
")
SET(CMAKE_C_FLAGS_RELEASE " \
    -DNDEBUG \
    -DCPU_K32L2B31VLH0A \
    -DUSB_STACK_BM=1 \
    -DDEBUG_CONSOLE_TRANSFER_NON_BLOCKING \
    -DFSL_OSA_TASK_ENABLE=1 \
    -DFRDM_K32L2B \
    -DFREEDOM \
    -DDEBUG_CONSOLE_RX_ENABLE=0 \
    -DSERIAL_PORT_TYPE_UART=1 \
    -Os \
    -mcpu=cortex-m0plus \
    -Wall \
    -mfloat-abi=soft \
    -mthumb \
    -MMD \
    -MP \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mapcs \
    -std=gnu99 \
")
SET(CMAKE_CXX_FLAGS_DEBUG " \
    -DDEBUG \
    -DCPU_K32L2B31VLH0A \
    -DSERIAL_PORT_TYPE_UART=1 \
    -g \
    -O0 \
    -mcpu=cortex-m0plus \
    -Wall \
    -mfloat-abi=soft \
    -mthumb \
    -MMD \
    -MP \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mapcs \
    -fno-rtti \
    -fno-exceptions \
")
SET(CMAKE_CXX_FLAGS_RELEASE " \
    -DNDEBUG \
    -DCPU_K32L2B31VLH0A \
    -DSERIAL_PORT_TYPE_UART=1 \
    -Os \
    -mcpu=cortex-m0plus \
    -Wall \
    -mfloat-abi=soft \
    -mthumb \
    -MMD \
    -MP \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mapcs \
    -fno-rtti \
    -fno-exceptions \
")
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG " \
    -g \
    -mcpu=cortex-m0plus \
    -Wall \
    -mfloat-abi=soft \
    --specs=nano.specs \
    --specs=nosys.specs \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -Xlinker \
    --gc-sections \
    -Xlinker \
    -static \
    -Xlinker \
    -z \
    -Xlinker \
    muldefs \
    -Xlinker \
    -Map=output.map \
    -T${ProjDirPath}/K32L2B31xxxxA_flash.ld -static \
")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE " \
    -mcpu=cortex-m0plus \
    -Wall \
    -mfloat-abi=soft \
    --specs=nano.specs \
    --specs=nosys.specs \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -Xlinker \
    --gc-sections \
    -Xlinker \
    -static \
    -Xlinker \
    -z \
    -Xlinker \
    muldefs \
    -Xlinker \
    -Map=output.map \
    -T${ProjDirPath}/K32L2B31xxxxA_flash.ld -static \
")

;/*
; * Copyright (c) 2009-2022 Arm Limited
; *
; * Licensed under the Apache License, Version 2.0 (the "License");
; * you may not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; *     http://www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an "AS IS" BASIS,
; * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; *
; *
; * This file is derivative of CMSIS V5.00 gcc_arm.ld
; */

/* Linker script to configure memory regions. */
/* This file will be run trough the pre-processor. */

#include "region_defs.h"

MEMORY
{
#ifdef M_BOOT_FLASH_CONF_START             //NXP
/* Flash configuration block(FCB) is used to configure the FlexSPI interface during the boot process. */
  m_flash_config        (RX)  : ORIGIN = M_BOOT_FLASH_CONF_START, LENGTH = M_BOOT_FLASH_CONF_SIZE     //NXP
#endif
  FLASH    (rx)  : ORIGIN = S_CODE_START, LENGTH = S_CODE_SIZE
  RAM      (rwx) : ORIGIN = S_DATA_START, LENGTH = S_DATA_SIZE
#if defined(S_CODE_SRAM_ALIAS_BASE)
  CODE_RAM (rwx) : ORIGIN = S_CODE_SRAM_ALIAS_BASE, LENGTH = TOTAL_CODE_SRAM_SIZE
#endif

#if defined(PSA_PROXY_SHARED_MEMORY_BASE)
  PSA_PROXY_SHARED_MEMORY_RAM (rw) : ORIGIN = PSA_PROXY_SHARED_MEMORY_BASE, LENGTH = PSA_PROXY_SHARED_MEMORY_SIZE
#endif

}

__heap_size__  = S_HEAP_SIZE;
#if !defined(TFM_PSA_API)
__psp_stack_size__ = S_PSP_STACK_SIZE;
#endif
__msp_init_stack_size__ = S_MSP_STACK_SIZE; //NXP S_MSP_STACK_SIZE_INIT

/* Library configurations */
GROUP(libgcc.a libc.a libm.a libnosys.a libc_nano.a)

ENTRY(Reset_Handler)

SECTIONS
{
// --------- NXP --------------
#ifdef M_BOOT_FLASH_CONF_START
    .flash_config :
    {
      . = ALIGN(4);
      __FLASH_BASE = .;
      KEEP(* (.flash_conf))     /* flash config section */
      . = ALIGN(4);
    } > m_flash_config
#endif
// --------- NXP end --------------

    .TFM_VECTORS : ALIGN(4)
    {
        __vectors_start__ = .;
        KEEP(*(.vectors))
        __vectors_end__ = .;
    } > FLASH

#ifndef TFM_MULTI_CORE_TOPOLOGY
    ASSERT(. <= ADDR(.TFM_VECTORS) + S_CODE_VECTOR_TABLE_SIZE, ".TFM_VECTORS section size overflow.")
    . = ADDR(.TFM_VECTORS) + S_CODE_VECTOR_TABLE_SIZE;
    /*
     * Place the CMSE Veneers (containing the SG instruction) after the code, in
     * a separate 32 bytes aligned region so that the SAU can programmed to just
     * set this region as Non-Secure Callable.
     */
    .gnu.sgstubs ALIGN(32) : ALIGN(32)
    {
        *(.gnu.sgstubs*)
        . = ALIGN(32);
    } > FLASH
    Image$$ER_VENEER$$Base = ADDR(.gnu.sgstubs);
    Image$$VENEER_ALIGN$$Limit = ADDR(.gnu.sgstubs) + SIZEOF(.gnu.sgstubs);
#endif

    .copy.table : ALIGN(4)
    {
        __copy_table_start__ = .;
#ifdef RAM_VECTORS_SUPPORT
        /* Copy interrupt vectors from flash to RAM */
        LONG (__vectors_start__)                            /* From */
        LONG (__ram_vectors_start__)                        /* To   */
        LONG (__vectors_end__ - __vectors_start__)          /* Size */
#endif
        LONG (LOADADDR(.TFM_DATA))
        LONG (ADDR(.TFM_DATA))
        LONG (SIZEOF(.TFM_DATA))

        LONG (LOADADDR(.TFM_PSA_ROT_LINKER_DATA))
        LONG (ADDR(.TFM_PSA_ROT_LINKER_DATA))
        LONG (SIZEOF(.TFM_PSA_ROT_LINKER_DATA))

        LONG (LOADADDR(.TFM_APP_ROT_LINKER_DATA))
        LONG (ADDR(.TFM_APP_ROT_LINKER_DATA))
        LONG (SIZEOF(.TFM_APP_ROT_LINKER_DATA))

#if defined (S_RAM_CODE_START)
        LONG (LOADADDR(.TFM_RAM_CODE))
        LONG (ADDR(.TFM_RAM_CODE))
        LONG (SIZEOF(.TFM_RAM_CODE))
#endif
#if defined(S_CODE_SRAM_ALIAS_BASE)
        LONG (LOADADDR(.ER_CODE_SRAM))
        LONG (ADDR(.ER_CODE_SRAM))
        LONG (SIZEOF(.ER_CODE_SRAM))
#endif
        __copy_table_end__ = .;
    } > FLASH

    .zero.table : ALIGN(4)
    {
        __zero_table_start__ = .;
        LONG (ADDR(.TFM_BSS))
        LONG (SIZEOF(.TFM_BSS))
#if !defined(TFM_PSA_API)
        LONG (ADDR(.TFM_SECURE_STACK))
        LONG (SIZEOF(.TFM_SECURE_STACK))
#endif /* !defined(TFM_PSA_API) */
        LONG (ADDR(.TFM_PSA_ROT_LINKER_BSS))
        LONG (SIZEOF(.TFM_PSA_ROT_LINKER_BSS))

        LONG (ADDR(.TFM_APP_ROT_LINKER_BSS))
        LONG (SIZEOF(.TFM_APP_ROT_LINKER_BSS))
#if defined(PSA_PROXY_SHARED_MEMORY_BASE)
        LONG (PSA_PROXY_SHARED_MEMORY_BASE)
        LONG (PSA_PROXY_SHARED_MEMORY_SIZE)
#endif
#if defined(CONFIG_TFM_PARTITION_META)
        LONG (ADDR(.TFM_SP_META_PTR))
        LONG (SIZEOF(.TFM_SP_META_PTR))
#endif
        __zero_table_end__ = .;
    } > FLASH

    /**** Section for holding partition RO load data */
    .TFM_SP_LOAD_LIST : ALIGN(4)
    {
       KEEP(*(.part_load))
    } > FLASH
    Image$$TFM_SP_LOAD_LIST$$RO$$Base = ADDR(.TFM_SP_LOAD_LIST);
    Image$$TFM_SP_LOAD_LIST$$RO$$Limit = ADDR(.TFM_SP_LOAD_LIST) + SIZEOF(.TFM_SP_LOAD_LIST);
    . = ALIGN(32);

    /**** PSA RoT RO part (CODE + RODATA) start here */
    Image$$TFM_PSA_CODE_START$$Base = .;

    .TFM_PSA_ROT_LINKER : ALIGN(32)
    {
        *tfm_psa_rot_partition*:*(.text*)
        *tfm_psa_rot_partition*:*(.rodata*)
        *(TFM_*_PSA-ROT_ATTR_FN)
        . = ALIGN(32);
    } > FLASH

    Image$$TFM_PSA_ROT_LINKER$$RO$$Base = ADDR(.TFM_PSA_ROT_LINKER);
    Image$$TFM_PSA_ROT_LINKER$$RO$$Limit = ADDR(.TFM_PSA_ROT_LINKER) + SIZEOF(.TFM_PSA_ROT_LINKER);
    Image$$TFM_PSA_ROT_LINKER$$Base = ADDR(.TFM_PSA_ROT_LINKER);
    Image$$TFM_PSA_ROT_LINKER$$Limit = ADDR(.TFM_PSA_ROT_LINKER) + SIZEOF(.TFM_PSA_ROT_LINKER);

    /**** PSA RoT RO part (CODE + RODATA) end here */
    Image$$TFM_PSA_CODE_END$$Base = .;

    /**** APPLICATION RoT RO part (CODE + RODATA) start here */
    Image$$TFM_APP_CODE_START$$Base = .;

    .TFM_APP_ROT_LINKER : ALIGN(32)
    {
// --------- NXP --------------
// #ifdef TFM_PARTITION_PROTECTED_STORAGE
        *tfm_ps_req_mngr.*(.text*)
        *tfm_ps_req_mngr.*(.rodata*)
        *tfm_protected_storage.*(.text*)
        *tfm_protected_storage.*(.rodata*)
        *ps_object_system.*(.text*)
        *ps_object_system.*(.rodata*)
        *ps_object_table.*(.text*)
        *ps_object_table.*(.rodata*)
        *ps_utils.*(.text*)
        *ps_utils.*(.rodata*)
        *ps_crypto_interface.*(.text*)
        *ps_crypto_interface.*(.rodata*)
        *ps_encrypted_object.*(.text*)
        *ps_encrypted_object.*(.rodata*)
        *ps_nv_counters.*(.text*)
        *ps_nv_counters.*(.rodata*)
        *intermedia_tfm_protected_storage.*(.text*)
        *intermedia_tfm_protected_storage.*(.rodata*)
        *load_info_tfm_protected_storage.*(.text*)
        *load_info_tfm_protected_storage.*(.rodata*)
        *tfm_ps_secure_api.*(.text*)
        *tfm_ps_secure_api.*(.rodata*)
        *tfm_ps_secure_api.*(.text*)
        *tfm_ps_secure_api.*(.rodata*)
        *(TFM_SP_PS_ATTR_FN)

// #ifdef TEST_NS_CORE
        *tfm_ss_core_test_2.*(.text*)
        *tfm_ss_core_test_2.*(.rodata*)
        *intermedia_tfm_ss_core_test_2.*(.text*)
        *intermedia_tfm_ss_core_test_2.*(.rodata*)
        *load_info_tfm_ss_core_test_2.*(.text*)
        *load_info_tfm_ss_core_test_2.*(.rodata*)
        *(TFM_SP_CORE_TEST_2_ATTR_FN)

// #ifdef TFM_PARTITION_IPC_TEST
        *tfm_ipc_client_test.*(.text*)
        *tfm_ipc_client_test.*(.rodata*)
        *intermedia_tfm_ipc_client_test.*(.text*)
        *intermedia_tfm_ipc_client_test.*(.rodata*)
        *load_info_tfm_ipc_client_test.*(.text*)
        *load_info_tfm_ipc_client_test.*(.rodata*)
        *(TFM_SP_IPC_CLIENT_TEST_ATTR_FN)

// #ifdef TEST_FRAMEWORK_S
        *tfm_secure_client_2.*(.text*)
        *tfm_secure_client_2.*(.rodata*)
        *intermedia_tfm_secure_client_2.*(.text*)
        *intermedia_tfm_secure_client_2.*(.rodata*)
        *load_info_tfm_secure_client_2.*(.text*)
        *load_info_tfm_secure_client_2.*(.rodata*)
        *tfm_secure_client_2_api.*(.text*)
        *tfm_secure_client_2_api.*(.rodata*)
        *tfm_secure_client_2_api.*(.text*)
        *tfm_secure_client_2_api.*(.rodata*)
        *(TFM_SP_SECURE_CLIENT_2_ATTR_FN)

// #ifdef TEST_NS_SLIH_IRQ
        *tfm_slih_test_service.*(.text*)
        *tfm_slih_test_service.*(.rodata*)
        *tfm_irq_test_service.*(.text*)
        *tfm_irq_test_service.*(.rodata*)
        *intermedia_tfm_slih_test_service.*(.text*)
        *intermedia_tfm_slih_test_service.*(.rodata*)
        *load_info_tfm_slih_test_service.*(.text*)
        *load_info_tfm_slih_test_service.*(.rodata*)
        *(TFM_SP_SLIH_TEST_ATTR_FN)

// #ifdef TEST_NS_FLIH_IRQ
        *tfm_flih_test_service.*(.text*)
        *tfm_flih_test_service.*(.rodata*)
        *tfm_irq_test_service.*(.text*)
        *tfm_irq_test_service.*(.rodata*)
        *intermedia_tfm_flih_test_service.*(.text*)
        *intermedia_tfm_flih_test_service.*(.rodata*)
        *load_info_tfm_flih_test_service.*(.text*)
        *load_info_tfm_flih_test_service.*(.rodata*)
        *(TFM_SP_FLIH_TEST_ATTR_FN)

// #ifdef TEST_PARTITION_FPU_TEST
        *tfm_fpu_service_test.*(.text*)
        *tfm_fpu_service_test.*(.rodata*)
        *intermedia_tfm_fpu_service_test.*(.text*)
        *intermedia_tfm_fpu_service_test.*(.rodata*)
        *load_info_tfm_fpu_service_test.*(.text*)
        *load_info_tfm_fpu_service_test.*(.rodata*)
        *(TFM_SP_FPU_SERVICE_TEST_ATTR_FN)

// --------- NXP end --------------
        *(TFM_*_APP-ROT_ATTR_FN)
        . = ALIGN(32);
    } > FLASH

    Image$$TFM_APP_ROT_LINKER$$RO$$Base = ADDR(.TFM_APP_ROT_LINKER);
    Image$$TFM_APP_ROT_LINKER$$RO$$Limit = ADDR(.TFM_APP_ROT_LINKER) + SIZEOF(.TFM_APP_ROT_LINKER);
    Image$$TFM_APP_ROT_LINKER$$Base = ADDR(.TFM_APP_ROT_LINKER);
    Image$$TFM_APP_ROT_LINKER$$Limit = ADDR(.TFM_APP_ROT_LINKER) + SIZEOF(.TFM_APP_ROT_LINKER);

    /**** APPLICATION RoT RO part (CODE + RODATA) end here */
    Image$$TFM_APP_CODE_END$$Base = .;

#if defined(S_CODE_SRAM_ALIAS_BASE)
    .ER_CODE_SRAM : ALIGN(4)
    {
        *Driver_GFC100_EFlash.o(.text*)
        *Driver_GFC100_EFlash.o(.rodata*)
        *gfc100_eflash_drv.o(.text*)
        *gfc100_eflash_drv.o(.rodata*)
        *musca_b1_eflash_drv.o(.text*)
        *musca_b1_eflash_drv.o(.rodata*)
        . = ALIGN(4); /* This alignment is needed to make the section size 4 bytes aligned */
    } > CODE_RAM AT > FLASH
    Image$$ER_CODE_SRAM$$RO$$Base = ADDR(.ER_CODE_SRAM);
    Image$$ER_CODE_SRAM$$RO$$Limit = ADDR(.ER_CODE_SRAM) + SIZEOF(.ER_CODE_SRAM);
    Image$$ER_CODE_SRAM$$Base = ADDR(.ER_CODE_SRAM);
    Image$$ER_CODE_SRAM$$Limit = ADDR(.ER_CODE_SRAM) + SIZEOF(.ER_CODE_SRAM);
#endif

#if TFM_LVL != 1
    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > FLASH
    __exidx_end = .;

#endif /* TFM_LVL != 1 */

    .ER_TFM_CODE : ALIGN(4)
    {
        *startup*(.text*)
        *libplatform_s*:*(.text*)
        *libtfm_spm*:*(.text*)

        *libplatform_s*:*(.rodata*)
        *libtfm_spm*:*(.rodata*)
    } > FLASH

    /**** Base address of secure data area */
    .tfm_secure_data_start :
    {
        . = ABSOLUTE(S_DATA_START) ;
    } > RAM

    /*
     * MPU on Armv6-M/v7-M core in multi-core topology may require more strict
     * alignment that MPU region base address must align with the MPU region
     * size.
     * As a result, in multi-core topology, to save memory resource and MPU
     * regions, unprivileged data sections and privileged data sections are
     * separated and gathered in unprivileged/privileged data area respectively.
     * Keep BL2 shared data and MSP stack at the beginning of the secure data
     * area in single Armv8-M topology, while move the two areas to the
     * beginning of privileged data region in multi-core topology.
     */
#ifndef TFM_MULTI_CORE_TOPOLOGY
#ifdef CODE_SHARING
    /* The code sharing between bootloader and runtime requires to share the
     * global variables.
     */
    .TFM_SHARED_SYMBOLS : ALIGN(32)
    {
        . += SHARED_SYMBOL_AREA_SIZE;
    } > RAM
#endif

    /* shared_data and msp_stack are overlapping on purpose when
     * msp_stack is extended until the beginning of RAM, when shared_date
     * was read out by partitions
     */
    .tfm_bl2_shared_data : ALIGN(32)
    {
        . += BOOT_TFM_SHARED_DATA_SIZE;
    } > RAM

    .msp_stack : ALIGN(32)
    {
        . += __msp_init_stack_size__;
    } > RAM
    Image$$ARM_LIB_STACK$$ZI$$Base = ADDR(.msp_stack);
    Image$$ARM_LIB_STACK$$ZI$$Limit = ADDR(.msp_stack) + SIZEOF(.msp_stack);

# if !defined(TFM_PSA_API)
    /* PSP is unprivileged in single-core topology */
    .psp_stack : ALIGN(32)
    {
        . += (__psp_stack_size__ - 0x8); // reserve space for stack seal (8 bytes)
    } > RAM
    Image$$ER_INITIAL_PSP$$ZI$$Base = ADDR(.psp_stack);
    Image$$ER_INITIAL_PSP$$ZI$$Limit = ADDR(.psp_stack) + SIZEOF(.psp_stack);

    .psp_stack_seal_res :
    {
        . += 0x8;
    } > RAM
    Image$$ER_INITIAL_PSP_SEAL$$ZI$$Base = ADDR(.psp_stack_seal_res);
    Image$$ER_INITIAL_PSP_SEAL$$ZI$$Limit = ADDR(.psp_stack_seal_res) + SIZEOF(.psp_stack_seal_res);
# endif
#endif

#if !defined(TFM_PSA_API)
    .TFM_SECURE_STACK : ALIGN(128)
    {
        . += 0x2000;
    } > RAM
    Image$$TFM_SECURE_STACK$$ZI$$Base = ADDR(.TFM_SECURE_STACK);
    Image$$TFM_SECURE_STACK$$ZI$$Limit = ADDR(.TFM_SECURE_STACK) + SIZEOF(.TFM_SECURE_STACK);
#endif /* !defined(TFM_PSA_API) */

#if (TFM_LVL == 1)
    .heap : ALIGN(8)
    {
        __end__ = .;
        PROVIDE(end = .);
        __HeapBase = .;
        . += __heap_size__;
        __HeapLimit = .;
        __heap_limit = .; /* Add for _sbrk */
    } > RAM
#endif /* TFM_LVL == 1 */

#if defined(CONFIG_TFM_PARTITION_META)
    .TFM_SP_META_PTR : ALIGN(32)
    {
        *(.bss.SP_META_PTR_SPRTL_INST)
    } > RAM
    Image$$TFM_SP_META_PTR$$ZI$$Base = ADDR(.TFM_SP_META_PTR);
    Image$$TFM_SP_META_PTR$$ZI$$Limit = ADDR(.TFM_SP_META_PTR) + SIZEOF(.TFM_SP_META_PTR);
#endif

    /**** APPLICATION RoT DATA start here */
    . = ALIGN(32);
    Image$$TFM_APP_RW_STACK_START$$Base = .;

    .TFM_APP_ROT_LINKER_DATA : ALIGN(32)
    {
// --------- NXP --------------
// #ifdef TFM_PARTITION_PROTECTED_STORAGE
        *tfm_ps_req_mngr.*(.data*)
        *tfm_protected_storage.*(.data*)
        *ps_object_system.*(.data*)
        *ps_object_table.*(.data*)
        *ps_utils.*(.data*)
        *ps_crypto_interface.*(.data*)
        *ps_encrypted_object.*(.data*)
        *ps_nv_counters.*(.data*)
        *intermedia_tfm_protected_storage.*(.data*)
        *load_info_tfm_protected_storage.*(.data*)
        *tfm_ps_secure_api.*(.data*)
        *tfm_ps_secure_api.*(.data*)
        *(TFM_SP_PS_ATTR_RW)

// #ifdef TEST_NS_CORE
        *tfm_ss_core_test_2.*(.data*)
        *intermedia_tfm_ss_core_test_2.*(.data*)
        *load_info_tfm_ss_core_test_2.*(.data*)
        *(TFM_SP_CORE_TEST_2_ATTR_RW)

// #ifdef TFM_PARTITION_IPC_TEST
        *tfm_ipc_client_test.*(.data*)
        *intermedia_tfm_ipc_client_test.*(.data*)
        *load_info_tfm_ipc_client_test.*(.data*)
        *(TFM_SP_IPC_CLIENT_TEST_ATTR_RW)

// #ifdef TEST_FRAMEWORK_S
        *tfm_secure_client_2.*(.data*)
        *intermedia_tfm_secure_client_2.*(.data*)
        *load_info_tfm_secure_client_2.*(.data*)
        *tfm_secure_client_2_api.*(.data*)
        *tfm_secure_client_2_api.*(.data*)
        *(TFM_SP_SECURE_CLIENT_2_ATTR_RW)

// #ifdef TEST_NS_SLIH_IRQ
        *tfm_slih_test_service.*(.data*)
        *tfm_irq_test_service.*(.data*)
        *intermedia_tfm_slih_test_service.*(.data*)
        *load_info_tfm_slih_test_service.*(.data*)
        *(TFM_SP_SLIH_TEST_ATTR_RW)

// #ifdef TEST_NS_FLIH_IRQ
        *tfm_flih_test_service.*(.data*)
        *tfm_irq_test_service.*(.data*)
        *intermedia_tfm_flih_test_service.*(.data*)
        *load_info_tfm_flih_test_service.*(.data*)
        *(TFM_SP_FLIH_TEST_ATTR_RW)

// #ifdef TEST_PARTITION_FPU_TEST
        *tfm_fpu_service_test.*(.data*)
        *intermedia_tfm_fpu_service_test.*(.data*)
        *load_info_tfm_fpu_service_test.*(.data*)
        *(TFM_SP_FPU_SERVICE_TEST_ATTR_RW)

// --------- NXP end --------------
        *(TFM_*_APP-ROT_ATTR_RW)
        . = ALIGN(32);
    } > RAM AT> FLASH
    Image$$TFM_APP_ROT_LINKER_DATA$$RW$$Base = ADDR(.TFM_APP_ROT_LINKER_DATA);
    Image$$TFM_APP_ROT_LINKER_DATA$$RW$$Limit = ADDR(.TFM_APP_ROT_LINKER_DATA) + SIZEOF(.TFM_APP_ROT_LINKER_DATA);

    .TFM_APP_ROT_LINKER_BSS : ALIGN(32)
    {
        start_of_TFM_APP_ROT_LINKER = .;
// --------- NXP --------------
// #ifdef TFM_PARTITION_PROTECTED_STORAGE
        *tfm_ps_req_mngr.*(.bss*)
        *tfm_ps_req_mngr.*(COMMON)
        *tfm_protected_storage.*(.bss)
        *tfm_protected_storage.*(COMMON)
        *ps_object_system.*(.bss*)
        *ps_object_system.*(COMMON)
        *ps_object_table.*(.bss*)
        *ps_object_table.*(COMMON)
        *ps_utils.*(.bss*)
        *ps_utils.*(COMMON)
        *ps_crypto_interface.*(.bss*)
        *ps_crypto_interface.*(COMMON)
        *ps_encrypted_object.*(.bss*)
        *ps_encrypted_object.*(COMMON)
        *ps_nv_counters.*(.bss*)
        *ps_nv_counters.*(COMMON)
        *intermedia_tfm_protected_storage.*(.bss*)
        *intermedia_tfm_protected_storage.*(COMMON)
        *load_info_tfm_protected_storage.*(.bss)
        *load_info_tfm_protected_storage.*(COMMON)
        *tfm_ps_secure_api.*(.bss*)
        *tfm_ps_secure_api.*(COMMON)
        *tfm_ps_secure_api.*(.bss*)
        *tfm_ps_secure_api.*(COMMON)
        *(TFM_SP_PS_ATTR_ZI)

// #ifdef TEST_NS_CORE
        *tfm_ss_core_test_2.*(.bss .bss.invert_buffer.0)
        *tfm_ss_core_test_2.*(COMMON)
        *intermedia_tfm_ss_core_test_2.*(.bss*)
        *intermedia_tfm_ss_core_test_2.*(COMMON)
        *load_info_tfm_ss_core_test_2.*(.bss)
        *load_info_tfm_ss_core_test_2.*(COMMON)
        *(TFM_SP_CORE_TEST_2_ATTR_ZI)

// #ifdef TFM_PARTITION_IPC_TEST
        *tfm_ipc_client_test.*(.bss .bss.service_in_use)
        *tfm_ipc_client_test.*(COMMON)
        *intermedia_tfm_ipc_client_test.*(.bss*)
        *intermedia_tfm_ipc_client_test.*(COMMON)
        *load_info_tfm_ipc_client_test.*(.bss)
        *load_info_tfm_ipc_client_test.*(COMMON)
        *(TFM_SP_IPC_CLIENT_TEST_ATTR_ZI)

// #ifdef TEST_FRAMEWORK_S
        *tfm_secure_client_2.*(.bss)
        *tfm_secure_client_2.*(COMMON)
        *intermedia_tfm_secure_client_2.*(.bss*)
        *intermedia_tfm_secure_client_2.*(COMMON)
        *load_info_tfm_secure_client_2.*(.bss)
        *load_info_tfm_secure_client_2.*(COMMON)
        *tfm_secure_client_2_api.*(.bss*)
        *tfm_secure_client_2_api.*(COMMON)
        *tfm_secure_client_2_api.*(.bss*)
        *tfm_secure_client_2_api.*(COMMON)
        *(TFM_SP_SECURE_CLIENT_2_ATTR_ZI)

// #ifdef TEST_NS_SLIH_IRQ
        *tfm_slih_test_service.*(.bss)
        *tfm_slih_test_service.*(COMMON)
        *tfm_irq_test_service.*(.bss*)
        *tfm_irq_test_service.*(COMMON)
        *intermedia_tfm_slih_test_service.*(.bss*)
        *intermedia_tfm_slih_test_service.*(COMMON)
        *load_info_tfm_slih_test_service.*(.bss)
        *load_info_tfm_slih_test_service.*(COMMON)
        *(TFM_SP_SLIH_TEST_ATTR_ZI)

// #ifdef TEST_NS_FLIH_IRQ
        *tfm_flih_test_service.*(.bss)
        *tfm_flih_test_service.*(COMMON)
        *tfm_irq_test_service.*(.bss*)
        *tfm_irq_test_service.*(COMMON)
        *intermedia_tfm_flih_test_service.*(.bss*)
        *intermedia_tfm_flih_test_service.*(COMMON)
        *load_info_tfm_flih_test_service.*(.bss)
        *load_info_tfm_flih_test_service.*(COMMON)
        *(TFM_SP_FLIH_TEST_ATTR_ZI)

// #ifdef TEST_PARTITION_FPU_TEST
        *tfm_fpu_service_test.*(.bss)
        *tfm_fpu_service_test.*(COMMON)
        *intermedia_tfm_fpu_service_test.*(.bss*)
        *intermedia_tfm_fpu_service_test.*(COMMON)
        *load_info_tfm_fpu_service_test.*(.bss)
        *load_info_tfm_fpu_service_test.*(COMMON)
        *(TFM_SP_FPU_SERVICE_TEST_ATTR_ZI)

// --------- NXP end --------------
        *(TFM_*_APP-ROT_ATTR_ZI)
        . += (. - start_of_TFM_APP_ROT_LINKER) ? 0 : 4;
        . = ALIGN(32);
    } > RAM AT> RAM
    Image$$TFM_APP_ROT_LINKER_DATA$$ZI$$Base = ADDR(.TFM_APP_ROT_LINKER_BSS);
    Image$$TFM_APP_ROT_LINKER_DATA$$ZI$$Limit = ADDR(.TFM_APP_ROT_LINKER_BSS) + SIZEOF(.TFM_APP_ROT_LINKER_BSS);

    /**** APPLICATION RoT DATA end here */
    Image$$TFM_APP_RW_STACK_END$$Base = .;

#if TFM_LVL != 1
#ifdef TFM_PARTITION_TEST_SECURE_SERVICES
    .TFM_SP_SECURE_TEST_PARTITION_LINKER_DATA : ALIGN(32)
    {
        *libc_nano*:*(.data*)
        . = ALIGN(32);
    } > RAM AT> FLASH

    .TFM_SP_SECURE_TEST_PARTITION_LINKER_BSS : ALIGN(32)
    {
        /* FixMe:
         * Test framework use printf to print out test result. Implementation of
         * printf in GCC libc use static data and heap as well. To be able to
         * execute test suites with TFM_LVL=3 this workaround is needed to
         * allocate libc static data and heap within the data section of secure
         * test partition. This can be removed if test service will be executed
         * in privileged mode.
         */
        *libc_nano*:*(.bss*)
        *libc_nano*:*(COMMON)

        __end__ = .;
        PROVIDE(end = .);
        __HeapBase = .;
        . += __heap_size__;
        __HeapLimit = .;
        __heap_limit = .; /* Add for _sbrk */

        . = ALIGN(32);
    } > RAM AT> RAM
#else /* TFM_PARTITION_TEST_SECURE_SERVICES */
    .heap : ALIGN(8)
    {
        __end__ = .;
        PROVIDE(end = .);
        __HeapBase = .;
        . += __heap_size__;
        __HeapLimit = .;
        __heap_limit = .; /* Add for _sbrk */
    } > RAM AT> RAM
#endif /* TFM_PARTITION_TEST_SECURE_SERVICES */
#endif /* TFM_LVL != 1 */

#ifdef TFM_MULTI_CORE_TOPOLOGY
#ifdef S_DATA_PRIV_START
    /**** Privileged data area base address specified by multi-core platform */
    .tfm_secure_priv_data_boundary :
    {
        . = ABSOLUTE(S_DATA_PRIV_START) ;
    } > RAM
#endif

    /*
     * Move BL2 shared area and MSP stack to the beginning of privileged data
     * area in multi-core topology.
     */

    /* shared_data and msp_stack are overlapping on purpose when
     * msp_stack is extended until the beginning of RAM, when shared_date
     * was read out by partitions
     */
    .tfm_bl2_shared_data : ALIGN(32)
    {
        . += BOOT_TFM_SHARED_DATA_SIZE;
    } > RAM AT> RAM

    .msp_stack : ALIGN(32)
    {
        . += __msp_init_stack_size__;
    } > RAM
    Image$$ARM_LIB_STACK$$ZI$$Base = ADDR(.msp_stack);
    Image$$ARM_LIB_STACK$$ZI$$Limit = ADDR(.msp_stack) + SIZEOF(.msp_stack);
#endif

    /**** PSA RoT DATA start here */

    Image$$TFM_PSA_RW_STACK_START$$Base = .;

    .TFM_PSA_ROT_LINKER_DATA : ALIGN(32)
    {
        *tfm_psa_rot_partition*:*(.data*)
        *(TFM_*_PSA-ROT_ATTR_RW)
        . = ALIGN(32);
    } > RAM AT> FLASH
    Image$$TFM_PSA_ROT_LINKER_DATA$$RW$$Base = ADDR(.TFM_PSA_ROT_LINKER_DATA);
    Image$$TFM_PSA_ROT_LINKER_DATA$$RW$$Limit = ADDR(.TFM_PSA_ROT_LINKER_DATA) + SIZEOF(.TFM_PSA_ROT_LINKER_DATA);

    .TFM_PSA_ROT_LINKER_BSS : ALIGN(32)
    {
        start_of_TFM_PSA_ROT_LINKER = .;
        *tfm_psa_rot_partition*:*(.bss*)
        *tfm_psa_rot_partition*:*(COMMON)
        *(TFM_*_PSA-ROT_ATTR_ZI)
        . += (. - start_of_TFM_PSA_ROT_LINKER) ? 0 : 4;
        . = ALIGN(32);
    } > RAM AT> RAM
    Image$$TFM_PSA_ROT_LINKER_DATA$$ZI$$Base = ADDR(.TFM_PSA_ROT_LINKER_BSS);
    Image$$TFM_PSA_ROT_LINKER_DATA$$ZI$$Limit = ADDR(.TFM_PSA_ROT_LINKER_BSS) + SIZEOF(.TFM_PSA_ROT_LINKER_BSS);

    /**** PSA RoT DATA end here */
    Image$$TFM_PSA_RW_STACK_END$$Base = .;

    .TFM_UNPRIV_CODE : ALIGN(32)
    {
        *(SFN)
        *(.text*)

        KEEP(*(.init))
        KEEP(*(.fini))

        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        /* .dtors */
         *crtbegin.o(.dtors)
         *crtbegin?.o(.dtors)
         *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
         *(SORT(.dtors.*))
         *(.dtors)

        *(.rodata*)

        KEEP(*(.eh_frame*))
        . = ALIGN(32);
    } > FLASH
    Image$$TFM_UNPRIV_CODE$$RO$$Base = ADDR(.TFM_UNPRIV_CODE);
    Image$$TFM_UNPRIV_CODE$$RO$$Limit = ADDR(.TFM_UNPRIV_CODE) + SIZEOF(.TFM_UNPRIV_CODE);

#ifdef RAM_VECTORS_SUPPORT
    .ramVectors (NOLOAD) : ALIGN(256)
    {
        __ram_vectors_start__ = .;
        KEEP(*(.ram_vectors))
        __ram_vectors_end__   = .;
    } > RAM
    .TFM_DATA __ram_vectors_end__ : ALIGN(4)
#else

     .TFM_DATA : ALIGN(4)
#endif
    {
        *(CodeQuickAccess)       /* CodeQuickAccess sections */ //NXP
        *(DataQuickAccess)       /* DataQuickAccess sections */ //NXP

        *(.data*)

        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);

        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);

        KEEP(*(.jcr*))
        . = ALIGN(4);

    } > RAM AT> FLASH
    Image$$ER_TFM_DATA$$RW$$Base = ADDR(.TFM_DATA);
    Image$$ER_TFM_DATA$$RW$$Limit = ADDR(.TFM_DATA) + SIZEOF(.TFM_DATA);

    .TFM_BSS : ALIGN(4)
    {
        __bss_start__ = .;
        __partition_runtime_start__ = .;
        KEEP(*(.bss.part_runtime))
        __partition_runtime_end__ = .;
        . = ALIGN(4);
        __service_runtime_start__ = .;
        KEEP(*(.bss.serv_runtime))
        __service_runtime_end__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > RAM AT> RAM
    Image$$ER_TFM_DATA$$ZI$$Base = ADDR(.TFM_BSS);
    Image$$ER_TFM_DATA$$ZI$$Limit = ADDR(.TFM_BSS) + SIZEOF(.TFM_BSS);
    Image$$ER_PART_RT_POOL$$ZI$$Base = __partition_runtime_start__;
    Image$$ER_PART_RT_POOL$$ZI$$Limit = __partition_runtime_end__;
    Image$$ER_SERV_RT_POOL$$ZI$$Base = __service_runtime_start__;
    Image$$ER_SERV_RT_POOL$$ZI$$Limit = __service_runtime_end__;

    Image$$ER_TFM_DATA$$Base = ADDR(.TFM_DATA);
    Image$$ER_TFM_DATA$$Limit = ADDR(.TFM_DATA) + SIZEOF(.TFM_DATA) + SIZEOF(.TFM_BSS);

#if defined(PSA_PROXY_SHARED_MEMORY_BASE)
    /* If a variable defined with __attribute__((section())) keyword the
     * variable is treated like an initialized variable. To not waste memory
     * NOLOAD attribute used here. The whole section is zero initialized by
     * adding section information to .zero.table */
    .PSA_PROXY_SHARED_MEMORY (NOLOAD) :
    {
        KEEP(*(PSA_PROXY_SHARED_MEMORY_SECTION))
    } > PSA_PROXY_SHARED_MEMORY_RAM
#endif

#if defined (S_RAM_CODE_START)
    /* Code executed from RAM */
    .TFM_RAM_CODE S_RAM_CODE_START :
    {
        KEEP(*(.ramfunc))
    } > RAM AT> FLASH
#endif

    Load$$LR$$LR_NS_PARTITION$$Base = NS_PARTITION_START;

#ifdef BL2
    Load$$LR$$LR_SECONDARY_PARTITION$$Base = SECONDARY_PARTITION_START;
#endif /* BL2 */

    PROVIDE(__stack = Image$$ARM_LIB_STACK$$ZI$$Limit);
}
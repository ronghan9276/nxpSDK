/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2020 NXP
* All rights reserved.
*
* \file
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#ifdef CPU_QN9080C
#include "Eeprom.h"
#else
#include "main.h"
#include "Eeprom_Boot.h"
#endif
#include "fsl_flash.h"
#include "OtapBootloader.h"
#include "FunctionLib.h"

/*! *********************************************************************************
*************************************************************************************
* Private Memory Declarations
*************************************************************************************
********************************************************************************** */
/* Variables used by the Bootloader */
volatile bootFlags_t *gpBootInfo;
volatile uint32_t gBootStorageStartAddress;
extern flash_config_t gFTFx_config;

/* Bootloader version */
#ifdef CPU_QN9080C
const uint8_t aBootloaderVersion[FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE] =
{
    gBootloaderVerMajor_c,
    gBootloaderVerMinor_c,
    gBootloaderVerPatch_c,
    gBootloaderBuildNo_c
};
#endif

/*! *********************************************************************************
*************************************************************************************
* Public Functions Prototypes
*************************************************************************************
********************************************************************************** */
uint32_t Boot_GetInternalStorageStartAddr(void);
uint8_t Boot_InitExternalStorage(void);
uint8_t Boot_ReadExternalStorage(uint16_t NoOfBytes, uint32_t Addr, uint8_t *outbuf);
void Boot_LoadImage (void);

#ifdef CPU_QN9080C
extern void hardware_init(void);
#endif

/*! *********************************************************************************
*************************************************************************************
* Public Functions
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
* \brief   This function determines the start address of the internal sorage.
*          If value is 0xFFFFFFFF then external storage should be used!
*
* \return the start address of the internal storage
*
********************************************************************************** */
uint32_t Boot_GetInternalStorageStartAddr(void)
{
    uint8_t mDelimiter[] = {gBootData_StartMarker_Value_c};
    uint32_t addr = gBootInvalidAddress_c;

    /* Check if the address of the internal storage from the boot flags is valid */
    if ((gpBootInfo->u2.internalStorageStart > gUserFlashStart_d) &&
        (gpBootInfo->u2.internalStorageStart < gMcuFlashSize))
    {
        addr = gpBootInfo->u2.internalStorageStart;
    }
    else
    {
        uint8_t *flash_addr = (uint8_t*)gUserFlashStart_d;

        /* Search for the internal storage start marker */
        while ((uint32_t)flash_addr < gMcuFlashSize)
        {
            if (FLib_MemCmp(mDelimiter, flash_addr, sizeof(mDelimiter)))
            {
                addr = (uint32_t)flash_addr + FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE;
                break;
            }

            flash_addr += gFlashErasePage_c; /* Advance to next Sector */
        }
    }

    return addr;
}

/*! *********************************************************************************
* \brief   Initialize the external storage
*
* \return status
*
********************************************************************************** */

uint8_t Boot_InitExternalStorage(void)
{
    uint8_t status = 0;

#ifdef CPU_QN9080C
#if (gEepromType_d != gEepromDevice_InternalFlash_c)
    status = (EEPROM_Init());
#endif /* gEepromDevice_InternalFlash_c */
#else
    if (gBootInvalidAddress_c == gBootStorageStartAddress)
    {
        status = EEPROM_Init();
    }
#endif
    return status;
}

/*! *********************************************************************************
* \brief   Read data from the external stoage
*
* \param[in]  NoOfBytes  number of byter to read
* \param[in]  Addr       read memory address
* \param[out] outbuf     location where read data is stored
*
* \return error code. 0 if success
*
********************************************************************************** */
uint8_t Boot_ReadExternalStorage(uint16_t NoOfBytes, uint32_t Addr, uint8_t *outbuf)
{
    uint8_t status = 0;

#ifdef CPU_QN9080C
#if (gEepromType_d != gEepromDevice_InternalFlash_c)
    status = EEPROM_ReadData(NoOfBytes, Addr, outbuf);
#else
    Addr += gBootStorageStartAddress;
    FLib_MemCpy(outbuf, (void*)Addr, NoOfBytes);
#endif
#else /* CPU_QN9080C */
    if (gBootInvalidAddress_c == gBootStorageStartAddress)
    {
        status = EEPROM_ReadData(NoOfBytes, Addr, outbuf);
    }
    else
    {
        Addr += gBootStorageStartAddress;
        FLib_MemCpy(outbuf, (void*)Addr, NoOfBytes);
    }
#endif

    return status;
}


/*! *********************************************************************************
* \brief   This function will copy the User Application from the external memory
*          into the program Flash
*
********************************************************************************** */
void Boot_LoadImage (void)
{
    uint8_t status = kStatus_FLASH_Success;
    static uint8_t bitmapBuffer[gBootData_SectorsBitmap_Size_c];
    uint8_t bootProcessCompleteFlag[FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE] = {0};
    uint8_t  buffer[gFlashErasePage_c];
    uint32_t remaingImgSize, len, i;
    uint32_t flashAddr      = gUserFlashStart_d;
    uint8_t  bitMask;
    uint8_t *pBitmap;

#if defined(MCU_MK21DX256)
    vuint8_t* pFlexRamAddress;
    uint8_t  EEEDataSetSize;
    uint16_t size;
#endif

    /* Check if we have a valid internal storage start address. */
    gBootStorageStartAddress = Boot_GetInternalStorageStartAddr();

#ifdef CPU_QN9080C
#if (gEepromType_d == gEepromDevice_InternalFlash_c)
    if(gBootInvalidAddress_c == gBootStorageStartAddress)
    {
      return;
    }
#endif
#endif

#if defined(CPU_QN9080C)
    /* Initialize the hardware */
    hardware_init();

    /* Enable Data Path 16/8MHz clock(some of the flash operations need this)
    * enable BiV clock include RTC BiV register  */
    SYSCON->CLK_EN = SYSCON_CLK_EN_CLK_DP_EN_MASK | SYSCON_CLK_EN_CLK_BIV_EN_MASK;

    FLASH_GetDefaultConfig(&gFTFx_config);
    gFTFx_config.blockBase &= 0x000fffff; //In linker config file, flash addresses start from zero, do the same for flash configuration
#endif
    /* Init the flash module */
    FLASH_Init(&gFTFx_config);

#if (defined(CPU_MKW36A512VHT4) || defined(CPU_MKW36A512VFP4) || defined(CPU_MKW36A512VFT4) || \
     defined(CPU_MKW36Z512VHT4) || defined(CPU_MKW36Z512VFP4) || defined(CPU_MKW34A512VFT4))
    /* KW36 has 256KB of FlexNVM mapped at adress 0x1000 0000 which also has an alias starting from address 0x0004 0000.
     * Configured the Flash driver to treat the PFLASH bloxk and FlexNVM block as a continuous memory block. */
    gFTFx_config.DFlashBlockBase = FSL_FEATURE_FLASH_PFLASH_BLOCK_SIZE * FSL_FEATURE_FLASH_PFLASH_BLOCK_COUNT;
#endif

    /* Init the external storage */
    Boot_InitExternalStorage();

    /* Read image size */
    if (Boot_ReadExternalStorage(gBootData_ImageLength_Size_c, gBootData_ImageLength_Offset_c, (uint8_t*)(&remaingImgSize)))
    {
        gHandleBootError_d();
    }

    /* Read sector bitmap */
    if (Boot_ReadExternalStorage(gBootData_SectorsBitmap_Size_c, gBootData_SectorsBitmap_Offset_c, bitmapBuffer))
    {
        gHandleBootError_d();
    }

    /* Ignore sector bitmap representing Bootloader Flash */
    len = gUserFlashStart_d / gFlashErasePage_c;
    pBitmap = &bitmapBuffer[len / 8];
    bitMask = gBitMaskInit_c << (len % 8);

    /* Ignore sector bitmap representing the internal storage */
    if (gBootInvalidAddress_c != gBootStorageStartAddress)
    {
        len = (gBootStorageStartAddress +
               gBootData_ImageLength_Size_c +
               gBootData_SectorsBitmap_Size_c +
               remaingImgSize +
               gFlashErasePage_c - 1) / gFlashErasePage_c;

        for (i = gBootStorageStartAddress / gFlashErasePage_c; i < len; i++)
        {
            bitmapBuffer[i / 8U] &= ~(gBitMaskInit_c << (i % 8U));
        }
    }

#ifdef CPU_QN908X
    /* Ignore sector bitmap representing FLASH Configuration page (last 3 FLASH sectors) */
    bitmapBuffer[31] &= gFlashConfigPageMask_c;

#if defined(gPreserveNvmStorage_c) && (gPreserveNvmStorage_c > 0)
    /* User shall update the preserving mask if the NVM is increased/decreased as size or stored at different location.
       The bitmap buffer contains 1 bit for each sector, 512/2k = 256 bits = 32 x uint8_t, little endian representation.
       If the bit is zero, the corresponding sector will be preserved, otherwise it will be erased */
    bitmapBuffer[31] &= gNvmPreserveMask_d;
#endif

#endif

    /* Start writing the image. Do not alter the last sector which contains HW specific data! */
#ifndef CPU_QN9080C
    while (flashAddr < (gMcuFlashSize - gFlashErasePage_c))
#else
    /* Start writing the image. Do not alter the last 3 sectors which contains HW specific data (NVDS, NVDS backup, system config) */
    while (flashAddr < (gMcuFlashSize - (gFlashErasePage_c << 2)))
#endif
    {
        if (remaingImgSize > gFlashErasePage_c)
        {
            len = gFlashErasePage_c;
        }
        else
        {
            len = remaingImgSize;
        }

        /* Check if bitmap indicates that this sector is write protected and shouldn't be updated */
        if( *pBitmap & bitMask )
        {
            /* Erase Flash sector */
            status = FLASH_Erase(&gFTFx_config,
                                 flashAddr,
                                 gFlashErasePage_c
#ifndef CPU_QN9080C
                                 ,kFLASH_ApiEraseKey  //skip this parameter for QN9080C
#endif
                                 );

            if (kStatus_FLASH_Success != status)
            {
                gHandleBootError_d();
            }

            if (len)
            {
                /* Read a new image block */
                if (Boot_ReadExternalStorage(len, flashAddr - gUserFlashStart_d + gBootData_Image_Offset_c, buffer))
                {
                    gHandleBootError_d();
                }

                if ((flashAddr <= gBootImageFlagsAddress_c) && (flashAddr + len > gBootImageFlagsAddress_c))
                {
                    uint32_t offset = gBootImageFlagsAddress_c - flashAddr;

                    /* Program the Flash before boot flags */
#if defined(FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD) && FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD
                    status = FLASH_ProgramSection(&gFTFx_config,
                                                  flashAddr,
                                                  (uint32_t*)buffer,
                                                  offset);
#else
                    status = FLASH_Program(&gFTFx_config,
                                           flashAddr,
                                           (uint32_t*)buffer,
                                           offset);
#endif
                    if (kStatus_FLASH_Success != status)
                    {
                        gHandleBootError_d();
                    }

                    offset += (sizeof(bootFlags_t) + (FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE - 1)) & (~(FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE - 1));

                    /* Program the Flash after the boot flags*/
#if defined(FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD) && FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD
                    status = FLASH_ProgramSection(&gFTFx_config,
                                                  flashAddr + offset,
                                                  (uint32_t*)&buffer[offset],
                                                  len - offset);
#else
                    status = FLASH_Program(&gFTFx_config,
                                           flashAddr + offset,
                                           (uint32_t*)&buffer[offset],
                                           len - offset);
#endif
                    if (kStatus_FLASH_Success != status)
                    {
                        gHandleBootError_d();
                    }
                }
                else
                {
                    /* Program the image block to Flash */
                    uint32_t alignedLen = len;

                    if (alignedLen & (FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE - 1))
                    {
                        alignedLen &= ~(FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE - 1);
                        alignedLen += FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE;
                    }

#if defined(FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD) && FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD
                    status = FLASH_ProgramSection(&gFTFx_config,
                                                  flashAddr,
                                                  (uint32_t*)buffer,
                                                  alignedLen);
#else
                    status = FLASH_Program(&gFTFx_config,
                                           flashAddr,
                                           (uint32_t*)buffer,
                                           alignedLen);
#endif
                    if (kStatus_FLASH_Success != status)
                    {
                        gHandleBootError_d();
                    }
                }
            }
        }

        /* Update Bitmask */
        bitMask <<= 1;
        if (bitMask == 0)
        {
            /* This was last bit in the current bitmap byte. Move to next bitmap byte */
            bitMask = gBitMaskInit_c;
            pBitmap++;
        }

        /* Update the current flash address */
        flashAddr += gFlashErasePage_c;

        /* Update the remaining bytes*/
        if (remaingImgSize)
        {
            remaingImgSize -= len;
        }
    } /* while */

#if defined(MCU_MK21DX256)

    while((FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK) != FTFL_FSTAT_CCIF_MASK)
    {
        /* wait till CCIF bit is set */
    }

    /* clear RDCOLERR & ACCERR & FPVIOL flag in flash status register */
    FTFL_FSTAT = (FTFL_FSTAT_RDCOLERR_MASK | FTFL_FSTAT_ACCERR_MASK |
                  FTFL_FSTAT_FPVIOL_MASK);

    /* Write Command Code to FCCOB0 */
    FTFL_FCCOB0 = FLASH_READ_RESOURCE;
    /* Write address to FCCOB1/2/3 */
    FTFL_FCCOB1 = ((uint8_t)(FLASH_DFLASH_IFR_READRESOURCE_ADDRESS >> 16));
    FTFL_FCCOB2 = ((uint8_t)((FLASH_DFLASH_IFR_READRESOURCE_ADDRESS >> 8) & 0xFF));
    FTFL_FCCOB3 = ((uint8_t)(FLASH_DFLASH_IFR_READRESOURCE_ADDRESS & 0xFF));

    /* Write Resource Select Code of 0 to FCCOB8 to select IFR. Without this, */
    /* an access error may occur if the register contains data from a previous command. */
    FTFL_FCCOB8 = 0;

    /* clear CCIF bit */
    FTFL_FSTAT |= FTFL_FSTAT_CCIF_MASK;

    /* check CCIF bit */
    while((FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK) != FTFL_FSTAT_CCIF_MASK)
    {
        /* wait till CCIF bit is set */
    }

    /* read the FlexRAM window size */
    EEEDataSetSize = FTFL_FCCOB6;
    EEEDataSetSize &= 0x0F;

    if((EEEDataSetSize == 2) || (EEEDataSetSize == 3)) /* FlexRAM size is 4KB or 2KB */
    {
        /* Enable EEE */
        FLASH_Boot_SetEEEEnable(FLASH_FLEXRAM_FNC_CTRL_CODE);

        pBitmap = &bitmapBuffer[0] + (uint32_t)((gMcuFlashSize/gFlashErasePage_c)/8);

        if(EEEDataSetSize == 2) /* 4KB */
        {
            if(*pBitmap & 0x01)
            {
                size = gBootFlexRam_4K_Size_c/2;
                pFlexRamAddress = (vuint8_t*)((uint32_t)gBootFlexRAMBaseAddress_c);
                while(size--)
                {
                    /* wait for EEPROM system to be ready */
                    while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
                    *pFlexRamAddress = 0xFF;
                    pFlexRamAddress ++;
                }
            }
            if(*pBitmap & 0x02)
            {
                size = gBootFlexRam_4K_Size_c/2;
                pFlexRamAddress = (vuint8_t*)((uint32_t)(gBootFlexRAMBaseAddress_c + size));
                while(size--)
                {
                    /* wait for EEPROM system to be ready */
                    while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
                    *pFlexRamAddress = 0xFF;
                    pFlexRamAddress ++;
                }
            }
        }
        else if (EEEDataSetSize == 3) /* 2K */
        {
            if(*pBitmap & 0x01)
            {
                size = gBootFlexRam_2K_Size_c/2;
                pFlexRamAddress = (vuint8_t*)((uint32_t)gBootFlexRAMBaseAddress_c);
                while(size--)
                {
                    /* wait for EEPROM system to be ready */
                    while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
                    *pFlexRamAddress = 0xFF;
                    pFlexRamAddress ++;
                }
            }
            if(*pBitmap & 0x02)
            {
                size = gBootFlexRam_2K_Size_c/2;
                pFlexRamAddress = (vuint8_t*)((uint32_t)(gBootFlexRAMBaseAddress_c + size));
                while(size--)
                {
                    /* wait for EEPROM system to be ready */
                    while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
                    *pFlexRamAddress = 0xFF;
                    pFlexRamAddress ++;
                }
            }
        }
    }
#endif

#ifdef CPU_QN9080C
    /* if boot storage start address was erased, restore and write it back to boot flags */
    if(gpBootInfo->u2.internalStorageStart == 0xFFFFFFFFUL)
    {
        gpBootInfo->u2.internalStorageStart = gBootStorageStartAddress;

#if defined(FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD) && FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD
        status = FLASH_ProgramSection(&gFTFx_config,
                                  (uint32_t)&gpBootInfo->u2.aInternalStorageStart,
                                  (uint32_t*)&gpBootInfo->u2.aInternalStorageStart,
                                  sizeof(gpBootInfo->u2.aInternalStorageStart));
#else
        status = FLASH_Program(&gFTFx_config,
                           (uint32_t)&gpBootInfo->u2.aInternalStorageStart,
                           (uint32_t*)&gpBootInfo->u2.aInternalStorageStart,
                           sizeof(gpBootInfo->u2.aInternalStorageStart));
#endif
      if( kStatus_FLASH_Success != status )
      {
          gHandleBootError_d();
      }
    }

    /* Write the bootloader version */
    if(FLib_MemCmpToVal((const void*)gpBootInfo->aBootVersion, 0xFF, sizeof(gpBootInfo->aBootVersion)))
    {
#if defined(FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD) && FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD
        status = FLASH_ProgramSection(&gFTFx_config,
                                  (uint32_t)&gpBootInfo->aBootVersion,
                                  (uint32_t*)&aBootloaderVersion,
                                  sizeof(aBootloaderVersion));
#else
        status = FLASH_Program(&gFTFx_config,
                           (uint32_t)&gpBootInfo->aBootVersion,
                           (uint32_t*)&aBootloaderVersion,
                           sizeof(aBootloaderVersion));
#endif
      if( kStatus_FLASH_Success != status )
      {
          gHandleBootError_d();
      }
    }
#endif /* QN9080C */

    /* Set the bBootProcessCompleted Flag */
#if defined(FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD) && FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD
    status = FLASH_ProgramSection(&gFTFx_config,
                                  (uint32_t)gpBootInfo->u1.aBootProcessCompleted,
                                  (uint32_t*)&bootProcessCompleteFlag,
                                  sizeof(bootProcessCompleteFlag));
#else
    status = FLASH_Program(&gFTFx_config,
                           (uint32_t)gpBootInfo->u1.aBootProcessCompleted,
                           (uint32_t*)&bootProcessCompleteFlag,
                           sizeof(bootProcessCompleteFlag));
#endif
    if( kStatus_FLASH_Success != status )
    {
        gHandleBootError_d();
    }

    /* Reseting MCU */
    Boot_ResetMCU();
}

void Boot_CheckOtapFlags(void)
{
    /* Check if there is no boot image available in the external EEPROM and if eventually
    the booting of the previous one has been completed. If both conditions are met, start
    running the application in the internal Flash. Else, start the process of booting from
    external EEPROM */
    gpBootInfo = (bootFlags_t*)gBootImageFlagsAddress_c;

#ifdef CPU_QN9080C
    if ((gpBootInfo->u0.aNewBootImageAvailable[0] != gBootValueForTRUE_c) &&
        (gpBootInfo->u1.aBootProcessCompleted[0] ==  gBootValueForTRUE_c))
    {
        return;
    }
    else
    {
        /* Write the new image */
        Boot_LoadImage();
    }
#else
    if ( !FLib_MemCmpToVal((const void*)gpBootInfo->u0.aNewBootImageAvailable, 0xFF, sizeof(gpBootInfo->u0.aNewBootImageAvailable)) ||
          FLib_MemCmpToVal((const void*)gpBootInfo->u1.aBootProcessCompleted, 0xFF, sizeof(gpBootInfo->u1.aBootProcessCompleted)))
    {
        /* Write the new image */
        Boot_LoadImage();
    }
#endif
}

//-----------------------------------------------------------------------------

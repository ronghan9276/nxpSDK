/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* \file
*
* This is the header file for the Memory Manager interface.
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H


/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include <stddef.h>

#include "EmbeddedTypes.h"
#include "GenericList.h"

#if defined (__IAR_SYSTEMS_ICC__)
#include "iccarm_builtin.h"
#endif /* (__IAR_SYSTEMS_ICC__) */


/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */
/*Defines pools by block size and number of blocks. Must be alligned to 4 bytes.*/
#ifndef PoolsDetails_c
#define PoolsDetails_c \
         _block_size_  64  _number_of_blocks_    8 _pool_id_(0) _eol_  \
         _block_size_ 128  _number_of_blocks_    2 _pool_id_(0) _eol_  \
         _block_size_ 256  _number_of_blocks_    6 _pool_id_(0) _eol_
#endif

#if defined (__IAR_SYSTEMS_ICC__)
/* __get_LR() declaration included from "iccarm_builtin.h" to avoid compatibility issues with different versions of IAR compiler */
#elif defined(__GNUC__)
#define __get_LR() __builtin_return_address(0)
#elif defined(__CC_ARM)
#define __get_LR() __return_address()
#endif

/* If a buffer (that is not allocated forever using MEM_BufferAllocForever()) is not freed
   in MEM_CheckMemBufferThreshold_c ms, the device will enter into panic */
#ifndef MEM_CheckMemBufferThreshold_c
#define MEM_CheckMemBufferThreshold_c     120000 /* ms */
#endif

/* How often the device should check if the above threshold expired */
#ifndef MEM_CheckMemBufferInterval_c
#define MEM_CheckMemBufferInterval_c      15000 /* ms */
#endif

/* Default memory allocator */
#ifndef MEM_BufferAlloc
#define MEM_BufferAlloc(numBytes)   MEM_BufferAllocWithId(numBytes, 0, (uint32_t*)__get_LR())
#endif

/* Allocate a block from the memory pools forever.*/
#define MEM_BufferAllocForever(numBytes,poolId)   MEM_BufferAllocWithId(numBytes, poolId, (uint32_t*)((uintptr_t)__get_LR() | 0x80000000U ))

#ifdef MEM_TRACKING
/* Which pool to optimize */
#ifndef POOL_TO_OPTIMIZE
#define POOL_TO_OPTIMIZE                0
#endif /* POOL_TO_OPTIMIZE */
/* Maximum buffer size to track */
#ifndef MAX_SUPPORTED_BUFFER_SIZE
#define MAX_SUPPORTED_BUFFER_SIZE       512
#endif /* MAX_SUPPORTED_BUFFER_SIZE */
#endif /* MEM_TRACKING */

/*! *********************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
********************************************************************************** */
/*Defines statuses used in MEM_BufferAlloc and MEM_BufferFree*/
typedef enum
{
  MEM_SUCCESS_c = 0,                    /* No error occurred */
  MEM_INIT_ERROR_c,                     /* Memory initialization error */
  MEM_ALLOC_ERROR_c,                    /* Memory allocation error */
  MEM_FREE_ERROR_c,                     /* Memory free error */
  MEM_UNKNOWN_ERROR_c                   /* something bad has happened... */
} memStatus_t;

#ifdef MEM_ALLOC_FAIL_CB
/* Buffer allocation failure callback type definition. */
typedef void (*pfMemAllocFailCb_t)(uint8_t poolId, void *pCaller, uint32_t numBytes);
#endif
/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
/*Initialises the Memory Manager.*/
memStatus_t MEM_Init(void);
#ifdef MEM_ALLOC_FAIL_CB
/*Register callback for buffer allocation failure notification */
void MEM_RegisterAllocFailCb(pfMemAllocFailCb_t callback);
#endif
/*Returns the number of available blocks that fit the given size.*/
uint32_t MEM_GetAvailableBlocks(uint32_t size);
/*Frees the givem buffer.*/
memStatus_t MEM_BufferFree(void* buffer);
/*Returns the allocated buffer of the given size.*/
void* MEM_BufferAllocWithId(uint32_t numBytes , uint8_t  poolId, void *pCaller);
/*Returns the size of a given buffer*/
uint16_t MEM_BufferGetSize(void* buffer);
/*Performs a write-read-verify test accross all pools*/
void* MEM_CallocAlt(size_t len, size_t val);
/*MEM Manager free alternative implementation.*/
void MEM_FreeAlt(void* pData);
#if (defined MULTICORE_MEM_MANAGER) && ((MULTICORE_APPLICATION_CORE) || (MULTICORE_CONNECTIVITY_CORE))
/*Free a buffer on the Master core*/
memStatus_t MEM_BufferFreeOnMaster(uint8_t * pBuff);
/*Free a buffer on the Slave core*/
memStatus_t MEM_BufferFreeOnSlave(uint8_t * pBuff);
#endif

/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */
#if defined(MEM_STATISTICS) && defined(DEBUG_ASSERT)
#define MEM_ASSERT(condition) if(!(condition))while(TRUE);
#else
#define MEM_ASSERT(condition) (void)(condition);
#endif


/*! *********************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
********************************************************************************** */

#ifdef MEM_STATISTICS
/*Statistics structure definition. Used by pools.*/
typedef struct poolStat_tag
{
  uint16_t numBlocks;
  uint16_t allocatedBlocks;
  uint16_t allocatedBlocksPeak;
  uint16_t allocationFailures;
  uint16_t freeFailures;
#ifdef MEM_TRACKING
  uint16_t poolFragmentWaste;
  uint16_t poolFragmentWastePeak;
  uint16_t poolFragmentMinWaste;
  uint16_t poolFragmentMaxWaste;
#endif /*MEM_TRACKING*/
} poolStat_t;
#endif /*MEM_STATISTICS*/

#ifdef MEM_TRACKING
/*Definition for alloc indicators. Used in buffer tracking.*/
typedef enum
{
  MEM_TRACKING_FREE_c = 0,
  MEM_TRACKING_ALLOC_c,
} memTrackingStatus_t;

/*Tracking structure definition.*/
typedef PACKED_STRUCT BlockTracking_tag
{
  void *blockAddr;                  /*Addr of Msg, note that this pointer is
                                     4 bytes bigger than the addr in the pool
                                     has the header of the msg is 4 bytes */
  uint16_t blockSize;               /*Size of block in bytes.*/
  uint16_t fragmentWaste;           /*Size requested by allocator.*/
  void *allocAddr;                  /*Return address of last Alloc made */
  void *freeAddr;                   /*Return address of last Free made */
  uint16_t allocCounter;            /*No of time this msg has been allocated */
  uint16_t freeCounter;             /*No of time this msg has been freed */
  memTrackingStatus_t allocStatus;  /*1 if currently allocated, 0 if currently free */
  uint32_t timeStamp;
  void *pCaller;
  uint16_t requested_size;
} blockTracking_t;
#endif /*MEM_TRACKING*/

/*Header description for buffers.*/
typedef struct
{
  listElement_t link;
  struct pools_tag *pParentPool;
} listHeader_t;

/*Buffer pools. Used by most functions*/
typedef struct pools_tag
{
  list_t anchor; /* MUST be first element in pools_t struct */
  uint16_t nextBlockSize;
  uint16_t blockSize;
  uint16_t  poolId;
#ifdef MEM_STATISTICS
  poolStat_t poolStatistics;
#endif /*MEM_STATISTICS*/
  uint8_t numBlocks;
  uint8_t allocatedBlocks;
} pools_t;

/*Buffer pool description. Used by MM_Init() for creating the buffer pools. */
typedef struct
{
  uint16_t blockSize;
  uint16_t poolSize;
  uint16_t poolId;
  uint8_t  padding[2];
} poolInfo_t;

/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */
#ifdef MEM_TRACKING
uint8_t MEM_Track(listHeader_t *block, memTrackingStatus_t alloc, uint32_t address, uint16_t requestedSize, void *pCaller);
uint8_t MEM_BufferCheck(uint8_t *p, uint32_t size);
void MEM_CheckIfMemBuffersAreFreed(void);

/* The timestamp function used by MEM Manager for debug purpose.
   The timestamp must be in milliseconds! */
#if defined(__IAR_SYSTEMS_ICC__)
extern __weak uint32_t MEM_GetTimeStamp(void);
#elif defined(__GNUC__)
extern __attribute__((weak)) uint32_t MEM_GetTimeStamp(void);
#endif

void MEM_CalcOptimalPoolConfiguration(uint32_t numBytes, uint8_t poolId);
#else
#define MEM_CalcOptimalPoolConfiguration(numBytes, poolId)
#endif /*MEM_TRACKING*/

#endif /* MEM_MANAGER_H */

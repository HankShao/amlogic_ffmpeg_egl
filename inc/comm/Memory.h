#ifndef __MEMORY_MANAGENENT_API_H__
#define __MEMORY_MANAGENENT_API_H__

#include "Types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMORY_BLOCK
{
	HANDLE		handle;
	BYTE*		ptr;
	BYTE*		header;
	uint32_t		length;	
	uint32_t		size;
	struct MEMORY_BLOCK *next;
	struct MEMORY_BLOCK *prev;
	uint32_t		flag1;
	uint32_t		flag2;
}MEMORY_BLOCK;

int32_t MemoryAlloc(MEMORY_BLOCK * pBlock, uint32_t dwBytes);

int32_t MemorySetLength(HANDLE hMemory, uint32_t dwBytes);

int32_t MemoryAddRef(HANDLE hMemory);

int32_t MemoryRelease(HANDLE hMemory);

void *ExtraMemoryAlloc(int32_t nSize);

void ExtraMemoryFree(void *pBuf);

void *ExtraMemoryCopy(void *pDest, const void *pSrc, int32_t nCount);

void *ExtraMemorySet(void *pDest, int32_t c, int32_t nCount);

#ifdef __cplusplus
}
#endif

#endif

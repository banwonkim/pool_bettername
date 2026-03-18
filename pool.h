#pragma once

#include <stdint.h>

#define POOL_BLOCKS_INITIAL 1

typedef struct poolFreed{
	struct poolFreed *nextFree;
} poolFreed;

typedef struct {
	uint32_t elementSize; // memory size of one element
	uint32_t elementCnt; // max count of element <- blockSize
	uint32_t nowElementIdx; // index of using element <- used
	int32_t nowBlockIdx; //index of using block / present block <- block
	poolFreed *freeList; // freeList <- freed
	uint32_t blockListCnt; // size of blocks, or count. <- blocksUsed
	uint8_t **blockList; //blocks[0] , [1], [2]... <- blocks 
} pool;

void poolInitialize(pool *p, const uint32_t elementSize, const uint32_t elementCnt);
void poolFreePool(pool *p);

#ifndef DISABLE_MEMORY_POOLING
void *poolMalloc(pool *p);
void poolFree(pool *p, void *ptr);
#else
#include <stdlib.h>
#define poolMalloc(p) malloc((p)->elementCnt)
#define poolFree(p, d) free(d)
#endif
void poolFreeAll(pool *p);

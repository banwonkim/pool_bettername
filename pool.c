#include <string.h>
#include <stdlib.h>

#include "pool.h"

#ifndef max
#define max(a,b) ((a)<(b)?(b):(a))
#endif

void poolInitialize(pool *p, const uint32_t elementSize, const uint32_t elementCnt)
{
	uint32_t i;

	p->elementSize = max(elementSize, sizeof(poolFreed));
	p->elementCnt = elementCnt;
	
	poolFreeAll(p);

	p->blockListCnt = POOL_BLOCKS_INITIAL;
	p->blockList = malloc(sizeof(uint8_t*)* p->blockListCnt);

	for(i = 0; i < p->blockListCnt; ++i)
		p->blockList[i] = NULL;
}

void poolFreePool(pool *p)
{
	uint32_t i;
	for(i = 0; i < p->blockListCnt; ++i) {
		if(p->blockList[i] == NULL)
			break;
		else
			free(p->blockList[i]);
	}

	free(p->blockList);
}

#ifndef DISABLE_MEMORY_POOLING
void *poolMalloc(pool *p)
{
	if(p->freeList != NULL) {
		void *recycle = p->freeList;
		p->freeList = p->freeList->nextFree;
		return recycle;
	}

	if(++p->nowElementIdx == p->elementCnt) {
		p->nowElementIdx = 0;
		if(++p->nowBlockIdx == (int32_t)p->blocksUsed) {
			uint32_t i;

			p->blocksUsed <<= 1;
			p->blockList = realloc(p->blockList, sizeof(uint8_t*)* p->blocksUsed);

			for(i = p->blocksUsed >> 1; i < p->blocksUsed; ++i)
				p->blockList[i] = NULL;
		}

		if(p->blockList[p->nowBlockIdx] == NULL)
			p->blockList[p->nowBlockIdx] = malloc(p->elementSize * p->elementCnt);
	}
	
	return p->blockList[p->nowBlockIdx] + p->nowElementIdx * p->elementSize;
}

void poolFree(pool *p, void *ptr)
{
	poolFreed *pFreed = p->freeList;

	p->freeList = ptr;
	p->freeList->nextFree = pFreed;
}
#endif

void poolFreeAll(pool *p)
{
	p->nowElementIdx = p->elementCnt - 1;
	p->nowBlockIdx = -1;
	p->freeList = NULL;
}

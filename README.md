# pool (forked)
A generic C memory pool. + modified, How to Use

doc in progress

## modified // original
```c
typedef struct {
	uint32_t elementSize; // memory size of one element
	uint32_t elementCnt; // blockSize
	uint32_t nowElementIdx; // Used what? <- used 
	int32_t nowBlockIdx; //index of using block / present block <- block (what block?)
	poolFreed *freeList; // <- freed
	uint32_t blockListCnt; // size of blocks, or count.
	uint8_t **blockList; //blocks[0] , [1], [2]... 
} pool;
```

- original version (wrong name)
```c

typedef struct {
	uint32_t elementSize; //Ok
	uint32_t blockSize; //This means elementSize, not blockSize
	uint32_t used; // used what?
	int32_t block; // what block? pointer? count of block? index?
	poolFreed *freed; //not bad but I prefer freeList
	uint32_t blocksUsed; //no. It's counts/Size of blocks.
	uint8_t **blocks; //blocks[0] , [1]... 연속
} pool;

```

The distinction between 'size' and 'count' is unclear.<br>
I used `size` as memory size (byte), `cnt` is for **max count** or **size** in a general sense. <br>
And `now` is for **now using data**.
If you don't like it, please change it on your own.

## How to use?

```
blocks[0] -> [elem 0][elem 1][elem 2]...[elem N-1] (N=elementCnt)
blocks[1] -> [elem 0][elem 1][elem 2]...[elem N-1]
blocks[2] -> [elem 0][elem 1][elem 2]...[elem N-1]

...
blocks[X] = [elem 0][elem 1] ... [elem N-1] // Now using
...
blocks[M]
(M=blockListCnt)
```
- only for single thread. multithread x

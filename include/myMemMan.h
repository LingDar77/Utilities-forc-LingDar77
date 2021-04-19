#ifndef AC300A1F_6EF7_4397_BB8F_C1086832251E
#define AC300A1F_6EF7_4397_BB8F_C1086832251E

/**
 * myMemMan.h
 * my memory manager implement in c 
 * Author: LingDar77
 * 4/18/2021
 */

#include <stdlib.h>
#include <pthread.h>
#include "gList.h"

GLIST_WITH_NODE(void *, MemMan, mNode);

//generally use helpful macro instead of this func
void initMyMemMan(MemMan *man);
//generally use helpful macro instead of this func
void mTerminate(MemMan *man);
//generally use helpful macro instead of this func
const void *mMalloc(MemMan *man, unsigned space);
//generally use helpful macro instead of this func
const void *mRealloc(MemMan *man, unsigned space, unsigned size);
//gc_thread, do not use
void *thread_gc();

//helpful macros
#define DECLEAR_MEM_MANAGER()           \
    static MemMan __GENERATED_MEMMAN__; \
    static MemMan __GENERATED_GARBAGE__
#define GENERATE_MEM_MANAGER() initMyMemMan(&__GENERATED_MEMMAN__)
#define MEMNAN_TERMINATE() mTerminate(&__GENERATED_MEMMAN__)
#define Malloc(space) mMalloc(&__GENERATED_MEMMAN__, space)
#define Realloc(space, size) mRealloc(&__GENERATED_MEMMAN__, space, size)
#endif /* AC300A1F_6EF7_4397_BB8F_C1086832251E */

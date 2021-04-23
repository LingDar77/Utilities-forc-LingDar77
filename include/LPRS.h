#ifndef AC300A1F_6EF7_4397_BB8F_C1086832251E
#define AC300A1F_6EF7_4397_BB8F_C1086832251E

/* * * * * * * * * * * * * * * * * * * * *
 * LPRS.h                                *
 * LingDar77's Ptr Releaser Sys          *
 * my ptr releaser implement in C        * 
 * Author: LingDar77                     *
 * Version: 0.0.1                        *
 * Started: 4/21/2021                    *
 * Modified: 4/21/2021                   *
 * * * * * * * * * * * * * * * * * * * * */

#include <stdlib.h>
#include "gList.h"

GLIST_WITH_NODE(void *, PtrPool, lNode);

static PtrPool *GetPtrPool()
{
    static PtrPool *pool = NULL;
    if (pool == NULL)
        pool = PtrPool_Maker();
    return pool;
}
static void LPRSDELETOR(void **p)
{
    if (*p)
        free(*p);
}
static int LPRSCMP(void *p1, void *p2) { return p1 == p2; }
#define allocate(Type, Name)           \
    Type *Name = malloc(sizeof(Type)); \
    PtrPool_PushBack(GetPtrPool(), Name)

#define alloc(Type, Name, Value) \
    allocate(Type, Name);        \
    *Name = Value

#define release(Ptr) \
    PtrPool_Del(GetPtrPool(), Ptr, &LPRSCMP, &LPRSDELETOR)

#define rel() \
    PtrPool_Destory(GetPtrPool(), &LPRSDELETOR);

#endif /* AC300A1F_6EF7_4397_BB8F_C1086832251E */


#include "myMemMan.h"
#include <stdio.h>
int comp(void *p1, void *p2)
{
    printf("%d,%d\n", *(int *)(p1), *(int *)(p2));
    return (*(int *)(p1) != *(int *)(p2) ? 0 : 1);
}
void destructor(void **pp)
{
    if (!*pp)
        printf("NULL!\n");
    else
    {
        free(*pp);
        printf("freed one element!\n");
    }
}
void initMyMemMan(MemMan *man)
{
    if (man == NULL)
    {
        man = malloc(sizeof(MemMan));
        man->beg = NULL;
        man->end = NULL;
        man->len = 0;
        man->reserve = 0;
    }
    int *buf1 = malloc(sizeof(int)), *buf2 = malloc(sizeof(int)), *buf3 = malloc(sizeof(int)), *buf4 = malloc(sizeof(int)), *buf5 = malloc(sizeof(int));
    *buf1 = 1;
    *buf2 = 2;
    *buf3 = 3;
    *buf4 = 4;
    *buf5 = 5;
    MemMan_PushBack(man, buf1);
    MemMan_InsertBack(man, buf2, 0);
    MemMan_InsertBack(man, buf3, 1);
    MemMan_PushBack(man, buf4);
    MemMan_PushBack(man, buf5);
    MemMan_Reserve(man, 3, NULL);
    MemMan_Reserve(man, 0, &destructor);
}

void mTerminate(MemMan *man)
{
    if (man != NULL && man->len > 0)
    {
        printf("Started Termination!\n");
        MemMan_Destory(man, &destructor);
        printf("Terminated Successfully!\n");
    }
}


#include "myMemMan.h"
#include <stdio.h>
int comp(void *p1, void *p2)
{
    printf("%d,%d\n", *(int *)(p1), *(int *)(p2));
    return (*(int *)(p1) != *(int *)(p2) ? 0 : 1);
}

void initMyMemMan(MemMan *man)
{
    if (man == NULL)
    {
        man = malloc(sizeof(MemMan));
        man->beg = NULL;
        man->end = NULL;
        man->len = 0;
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
    int a = 6;
    mNode_pair *b = MemMan_findElement(man, &a, &comp);
    printf("%d %d\n", b->Index, *(int *)(b->MemMan_Node->val));
    free(b);
}
void mTerminate(MemMan *man)
{
    if (man != NULL && man->len > 0)
    {
        printf("Started Termination!\n");
        if (man->len > 0)
        {
            mNode *iterator = man->beg;
            while (iterator)
            {
                mNode *buf = iterator->next;
                if (buf)
                    buf->pre = NULL;
                //should check
                free(iterator->val);
                free(iterator);
                printf("Successfully freed an element!\n");
                iterator = buf;
            }
        }
        printf("Terminated Successfully!\n");
    }
}

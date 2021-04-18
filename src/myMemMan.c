
#include "myMemMan.h"
#include <stdio.h>

void initMyMemMan(MemMan *man)
{
    if (man == NULL)
    {
        man = malloc(sizeof(MemMan));
        man->beg = NULL;
        man->end = NULL;
        man->len = 0;
    }
    //int *buf1 = malloc(sizeof(int)), *buf2 = malloc(sizeof(int)), *buf3 = malloc(sizeof(int));
    //MemMan_PushBack(man, buf1);
    //MemMan_InsertBack(man, buf2, 0);
    //MemMan_InsertBack(man, buf3, 1);
    //printf("%d,%d%d%d\n", man->len, man->beg->val, man->beg->next->val, man->beg->next->next->val);
}
void mTerminate(MemMan *man)
{
    if (man != NULL && man->len > 0)
    {
        printf("Started Termination\n");
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
                printf("Successfully free an element!\n");
                iterator = buf;
            }
        }
        else
            free(man);
    }
}

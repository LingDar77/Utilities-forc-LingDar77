#include <stdio.h>
#include "gList.h"
#include <time.h>
#include <pthread.h>
#include "vld.h"
GLIST_WITH_NODE(int, List_int, Node_int);
void *deleter(void **p)
{
    // pthread_detach(pthread_self);
    //printf("called\n");
    if (*p != NULL)
        free(*p);
    //pthread_exit(NULL);
    return NULL;
}
void test()
{
    List_int *L2 = List_int_Maker();
    List_int *L1 = List_int_Maker();

    for (int i = 0; i < 1000; ++i)
    {
        List_int_PushBack(L1, i + 1);
        List_int_PushBack(L2, i + 1);
    }
    for (int i = 0; i < 500; ++i)
    {
        List_int_PopBack(L1);
        List_int_PopBack(L2);
    }
    time_t t1, t2, t3, t4;
    t1 = clock();
    List_int_Destory_Threads(L1, NULL);
    t2 = clock();
    printf("Destory_Threads Freed 1000 Elements Took %d ms\n", t2 - t1);

    t3 = clock();
    List_int_Destory(L2, NULL);
    t4 = clock();
    printf("Destory Freed 1000 Elements Took %d ms\n", t4 - t3);
    //printf("%d\n", data[2]->val);
}
void *thread(void *p)
{
    static int cnt = 0;
    printf("cnt = %d!\n", cnt++);
    free(p);
    return NULL;
}

int main(int argc, char const *argv[])
{
    test();

    return 0;
}

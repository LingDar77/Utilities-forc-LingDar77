#include "vld.h"
#include <stdio.h>
#include "gList.h"
#include <time.h>
#include <pthread.h>
#include "LPRS.h"

//GLIST_WITH_NODE(int, List_int, Node_int);
void *deleter(void **p)
{
    // pthread_detach(pthread_self);
    //printf("called\n");
    if (*p != NULL)
        free(*p);
    //pthread_exit(NULL);
    return NULL;
}
int comp(int a, int b)
{
    return a == b;
}

/*
void test()
{

    List_int *L1 = List_int_Maker();
    int num;
    scanf("%d", &num);

    for (int i = 0; i < num; ++i)
    {
        List_int_PushBack(L1, i + 1);
    }
    //for (int i = 0; i < num / 2; ++i)
    //{
    //    List_int_PopBack(L1);
    //}
    time_t t1, t2, t3, t4;

    t1 = clock();
    printf("%d\n", List_int_GetIteratorByIndex(L1, 3 * num / 4)->val);
    t2 = clock();
    printf("Access the %dth element took %d ms\n", 3 * num / 4, t2 - t1);

    //printf("found 3 appears %d times\n", List_int_Count(L1, 3, &comp));
    t3 = clock();
    List_int_Destory(L1, NULL);
    t4 = clock();
    printf("Destory Freed %d Elements Took %d ms\n", num, t4 - t3);
    //printf("%d\n", data[2]->val);
}*/
void *thread(void *p)
{
    static int cnt = 0;
    printf("cnt = %d!\n", cnt++);
    free(p);
    return NULL;
}

void tLPRS2()
{
    alloc(int, ia, 11);
    printf("%d, %d\n", *(int *)(GetPtrPool())->beg->val, ia);
    rel();
}
void tLPRS1()
{
    alloc(int, ia, 11);
    printf("%d, %d\n", *(int *)(GetPtrPool())->beg->val, ia);
    rel();
}

int main(int argc, char const *argv[])
{
    //test();
    tLPRS1();
    tLPRS2();
    getchar();
    getchar();

    return 0;
}

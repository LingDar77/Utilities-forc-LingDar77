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
    List_int *Li = List_int_Maker();
    //for (int i = 0; i < num; ++i)
    List_int_PushBack(Li, 1);
    List_int_PushFront(Li, 3);
    List_int_PushBack(Li, 2);
    List_int_PushFront(Li, 5);
    List_int_PushBack(Li, 4);       //5 3 1 2 4
    List_int_Remove(Li, 0); //3 1 2 4

    List_int_InsertFront(Li, 2, 1); //3 2 1 2 4

    List_int_InsertBack(Li, 3, 3);  //3 2 1 2 3 4

    Node_int *data[Li->len];
    Node_int *iterator = Li->beg;
    for (int i = 0; i < Li->len; ++i)
        data[i] = iterator, iterator = iterator->next;
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

    getchar();
    getchar();

    return 0;
}

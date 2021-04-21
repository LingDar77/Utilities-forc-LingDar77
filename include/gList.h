#ifndef A2EA3F69_7DFF_4B88_A3CF_256B119A4A69
#define A2EA3F69_7DFF_4B88_A3CF_256B119A4A69

/**
* Generic list implement in C
* Author: LingDar77
* Version: 0.0.2
* Started: 4/18/2021
* Modified: 4/20/2021
**/

//#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define DECLEAR_GNode(Type, Name)  \
    typedef struct GNode_##Name    \
    {                              \
        Type val;                  \
        struct GNode_##Name *pre;  \
        struct GNode_##Name *next; \
    } Name

#define DECLEAR_GList(NodeName, Name) \
    typedef struct GList_##Name       \
    {                                 \
        NodeName *beg;                \
        NodeName *end;                \
        unsigned len;                 \
        unsigned reserve;             \
    } Name
#define GENERATED_GLIST_BODY(Type, NodeName, Name) GENERATED_GLIST_FUNCTIONS(Type, NodeName, Name);

//this macro is used to generate a list with its functions
#define GLIST(Type, Name)                  \
    DECLEAR_GNode(Type, GENERATED_##Name); \
    DECLEAR_GList(GENERATED_##Name, Name); \
    GENERATED_GLIST_BODY(Type, GENERATED_##Name, Name)

//this macro is used to generate a list and rename its node and relating functions
#define GLIST_WITH_NODE(Type, Name, NodeName) \
    DECLEAR_GNode(Type, NodeName);            \
    DECLEAR_GList(NodeName, Name);            \
    GENERATED_GLIST_BODY(Type, NodeName, Name)

/*this macro is used to generate helpful functions*/
#define GENERATED_GLIST_FUNCTIONS(Type, NodeName, Name)                                                  \
    typedef struct GENERATED_##NodeName##_PAIR                                                           \
    {                                                                                                    \
        NodeName *Name##_Node;                                                                           \
        unsigned Index;                                                                                  \
    } NodeName##_pair;                                                                                   \
    /*Make a List, better use this to create a list*/                                                    \
    static const Name *Name##_Maker()                                                                    \
    {                                                                                                    \
        Name *buffer = malloc(sizeof(Name));                                                             \
        buffer->len = 0, buffer->reserve = 0, buffer->beg = NULL, buffer->end = NULL;                    \
        return buffer;                                                                                   \
    }                                                                                                    \
    /*Find an iterator by index*/                                                                        \
    static const NodeName *Name##_GetIteratorByIndex(Name *target, unsigned Index)                       \
    {                                                                                                    \
        if (target->len <= 0 || Index >= target->len)                                                    \
        {                                                                                                \
            fprintf(stderr, "Error: Out Of Range!\n");                                                   \
            abort();                                                                                     \
        }                                                                                                \
        if (!Index)                                                                                      \
            return target->beg;                                                                          \
        if (Index == target->len - 1)                                                                    \
            return target->end;                                                                          \
        NodeName *iterator = NULL;                                                                       \
        if (target->len / Index > 2)                                                                     \
        {                                                                                                \
            /*printf("left\n");*/                                                                        \
            iterator = target->beg;                                                                      \
            while (Index && iterator)                                                                    \
            {                                                                                            \
                iterator = iterator->next;                                                               \
                --Index;                                                                                 \
            }                                                                                            \
            if (Index)                                                                                   \
            {                                                                                            \
                fprintf(stderr, "Error: Can Not Reach Correct Iterator!\n");                             \
                abort();                                                                                 \
            }                                                                                            \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            /*printf("right\n");*/                                                                       \
            iterator = target->end;                                                                      \
            unsigned cnt = target->len - Index - 1;                                                      \
            while (iterator && cnt)                                                                      \
            {                                                                                            \
                iterator = iterator->pre;                                                                \
                --cnt;                                                                                   \
            }                                                                                            \
            if (cnt)                                                                                     \
            {                                                                                            \
                fprintf(stderr, "Error: Can Not Reach Correct Iterator!\n");                             \
                abort();                                                                                 \
            }                                                                                            \
        }                                                                                                \
        return iterator;                                                                                 \
    } /*                                                                                                 \
    Change the reserve of a list                                                                         \
    when decreasing the reserve you can provide a deletor to deal with your data                         \
    or just a NULL to jump over                                                                          \
    */                                                                                                   \
    static void Name##_Reserve(Name *target, unsigned num, void (*destructor)(Type *))                   \
    {                                                                                                    \
        if (target->len <= 0 || target->reserve < 0)                                                     \
        {                                                                                                \
            fprintf(stderr, "Error: Invalid List!\n");                                                   \
            abort();                                                                                     \
        }                                                                                                \
        if (num > target->reserve)                                                                       \
        {                                                                                                \
            while (num - target->reserve)                                                                \
            {                                                                                            \
                NodeName *buf = malloc(sizeof(NodeName));                                                \
                if (target->reserve > 0)                                                                 \
                {                                                                                        \
                    NodeName *reserve = target->end->next;                                               \
                    buf->next = reserve;                                                                 \
                    buf->val = NULL;                                                                     \
                    buf->pre = target->end;                                                              \
                    reserve->pre = buf;                                                                  \
                    target->end->next = buf;                                                             \
                    ++target->reserve;                                                                   \
                }                                                                                        \
                else                                                                                     \
                {                                                                                        \
                    target->end->next = buf;                                                             \
                    buf->pre = target->end;                                                              \
                    buf->val = NULL;                                                                     \
                    buf->next = NULL;                                                                    \
                    ++target->reserve;                                                                   \
                }                                                                                        \
            }                                                                                            \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            while (target->reserve - num)                                                                \
            {                                                                                            \
                if (target->reserve == 1)                                                                \
                {                                                                                        \
                    NodeName *buf = target->end->next;                                                   \
                    if (destructor != NULL)                                                              \
                        (*destructor)(&buf->val);                                                        \
                    free(buf);                                                                           \
                    target->end->next = NULL;                                                            \
                    --target->reserve;                                                                   \
                }                                                                                        \
                else                                                                                     \
                {                                                                                        \
                    NodeName *reserve = target->end->next;                                               \
                    if (destructor != NULL)                                                              \
                        (*destructor)(&reserve->val);                                                    \
                    target->end->next = reserve->next;                                                   \
                    reserve->next->pre = target->end;                                                    \
                    free(reserve);                                                                       \
                    --target->reserve;                                                                   \
                }                                                                                        \
            }                                                                                            \
        }                                                                                                \
    }                                                                                                    \
    /*Add an element at the front of a list*/                                                            \
    static const NodeName *Name##_PushFront(Name *target, Type value)                                    \
    {                                                                                                    \
        if (target->len < 0 || target->reserve < 0)                                                      \
        {                                                                                                \
            perror("Error: Uninitialized List!\n");                                                      \
            abort();                                                                                     \
        }                                                                                                \
        if (target->reserve == 0)                                                                        \
        {                                                                                                \
            NodeName *buffer = malloc(sizeof(NodeName));                                                 \
            if (buffer == NULL)                                                                          \
            {                                                                                            \
                perror("Error: Malloc Failed!\n");                                                       \
                abort();                                                                                 \
            }                                                                                            \
            if (target->beg == NULL)                                                                     \
            {                                                                                            \
                buffer->pre = NULL;                                                                      \
                buffer->next = NULL;                                                                     \
                buffer->val = value;                                                                     \
                target->beg = buffer;                                                                    \
                target->end = buffer;                                                                    \
                ++target->len;                                                                           \
                return target->beg;                                                                      \
            }                                                                                            \
            else if (target->beg != NULL && target->len > 0)                                             \
            {                                                                                            \
                buffer->pre = NULL;                                                                      \
                buffer->next = target->beg;                                                              \
                buffer->val = value;                                                                     \
                target->beg->pre = buffer;                                                               \
                target->beg = buffer;                                                                    \
                ++target->len;                                                                           \
                return target->beg;                                                                      \
            }                                                                                            \
            else                                                                                         \
            {                                                                                            \
                perror("Error: Undefined Case!\n");                                                      \
                abort();                                                                                 \
            }                                                                                            \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            NodeName *r0 = target->end->next;                                                            \
            if (r0->next)                                                                                \
                r0->next->pre = target->end;                                                             \
            target->end->next = r0->next;                                                                \
            if (target->beg == NULL)                                                                     \
                r0->next = target->end;                                                                  \
            else                                                                                         \
                r0->next = target->beg;                                                                  \
            r0->pre = NULL;                                                                              \
            r0->val = value;                                                                             \
            target->beg->pre = r0;                                                                       \
            target->beg = r0;                                                                            \
            ++target->len;                                                                               \
            --target->reserve;                                                                           \
            return target->beg;                                                                          \
        }                                                                                                \
    }                                                                                                    \
    /*Add an element at the end of a list*/                                                              \
    static const NodeName *Name##_PushBack(Name *target, Type value)                                     \
    {                                                                                                    \
        if (target->len < 0 || target->reserve < 0)                                                      \
        {                                                                                                \
            perror("Error: Uninitialized List!\n");                                                      \
            abort();                                                                                     \
        }                                                                                                \
        if (target->reserve == 0)                                                                        \
        {                                                                                                \
            NodeName *buffer = malloc(sizeof(NodeName));                                                 \
            if (buffer == NULL)                                                                          \
            {                                                                                            \
                perror("Error: Malloc Failed!\n");                                                       \
                abort();                                                                                 \
            }                                                                                            \
            if (target->end == NULL)                                                                     \
            {                                                                                            \
                buffer->pre = NULL;                                                                      \
                buffer->next = NULL;                                                                     \
                buffer->val = value;                                                                     \
                target->beg = buffer;                                                                    \
                target->end = buffer;                                                                    \
                ++target->len;                                                                           \
                return target->end;                                                                      \
            }                                                                                            \
            else if (target->end != NULL && target->len > 0)                                             \
            {                                                                                            \
                buffer->next = NULL;                                                                     \
                buffer->pre = target->end;                                                               \
                buffer->val = value;                                                                     \
                target->end->next = buffer;                                                              \
                target->end = buffer;                                                                    \
                ++target->len;                                                                           \
                return target->end;                                                                      \
            }                                                                                            \
            else                                                                                         \
            {                                                                                            \
                perror("Error: Undefined Case!\n");                                                      \
                abort();                                                                                 \
            }                                                                                            \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            target->end = target->end->next;                                                             \
            target->end->val = value;                                                                    \
            ++target->len;                                                                               \
            --target->reserve;                                                                           \
            return target->end;                                                                          \
        }                                                                                                \
    }                                                                                                    \
    /*Pop the first on element*/                                                                         \
    static const Type *Name##_PopFront(Name *target)                                                     \
    {                                                                                                    \
        if (target->len <= 0 || target->reserve < 0)                                                     \
        {                                                                                                \
            fprintf(stderr, "Error: Invalid List!\n");                                                   \
            abort();                                                                                     \
        }                                                                                                \
        if (target->beg == target->end)                                                                  \
        {                                                                                                \
            fprintf(stderr, "Error: Can Not Pop The Only One Element!\n");                               \
            abort();                                                                                     \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            NodeName *reserve = target->beg;                                                             \
            target->beg = target->beg->next;                                                             \
            target->beg->pre = NULL;                                                                     \
            --target->len;                                                                               \
            ++target->reserve;                                                                           \
            reserve->next = target->end->next;                                                           \
            reserve->pre = target->end;                                                                  \
            target->end->next = reserve;                                                                 \
            if (target->end->next)                                                                       \
                target->end->next->pre = reserve;                                                        \
        }                                                                                                \
    }                                                                                                    \
    /*Pop the last one but not the only one element*/                                                    \
    static const Type *Name##_PopBack(Name *target)                                                      \
    {                                                                                                    \
        if (target->len <= 0 || target->reserve < 0)                                                     \
        {                                                                                                \
            fprintf(stderr, "Error: Invalid List!\n");                                                   \
            abort();                                                                                     \
        }                                                                                                \
        if (target->end == target->beg)                                                                  \
        {                                                                                                \
            fprintf(stderr, "Error: Can Not Pop The Only One Element!\n");                               \
            abort();                                                                                     \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            target->end = target->end->pre;                                                              \
            --target->len;                                                                               \
            ++target->reserve;                                                                           \
            return target->end->next->val;                                                               \
        }                                                                                                \
    }                                                                                                    \
    /*Insert an element at the back of element of a certain index*/                                      \
    static const Name *Name##_InsertFront(Name *target, Type value, unsigned Index)                      \
    {                                                                                                    \
        if (target->len <= 0 || target->reserve < 0)                                                     \
        {                                                                                                \
            fprintf(stderr, "Error: Invalid List!\n");                                                   \
            abort();                                                                                     \
        }                                                                                                \
        if (Index == 0 || target->len == 1)                                                              \
        {                                                                                                \
            return (Name##_PushFront(target, value));                                                    \
        }                                                                                                \
        if (target->reserve == 0)                                                                        \
        {                                                                                                \
            NodeName *iterator = Name##_GetIteratorByIndex(target, Index);                               \
            NodeName *buf = malloc(sizeof(NodeName));                                                    \
            NodeName *Pre = iterator->pre;                                                               \
            ++target->len;                                                                               \
            Pre->next = buf;                                                                             \
            buf->pre = Pre;                                                                              \
            buf->val = value;                                                                            \
            buf->next = iterator;                                                                        \
            iterator->pre = buf;                                                                         \
            return target;                                                                               \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            NodeName *reserve = target->end->next;                                                       \
            NodeName *iterator = Name##_GetIteratorByIndex(target, Index);                               \
            NodeName *Pre = iterator->pre;                                                               \
            target->end->next = reserve->next;                                                           \
            if (reserve->next != NULL)                                                                   \
                reserve->next->pre = target->end;                                                        \
            reserve->val = value;                                                                        \
            ++target->len;                                                                               \
            --target->reserve;                                                                           \
            Pre->next = reserve;                                                                         \
            reserve->pre = Pre;                                                                          \
            reserve->val = value;                                                                        \
            reserve->next = iterator;                                                                    \
            iterator->pre = reserve;                                                                     \
            return target;                                                                               \
        }                                                                                                \
    }                                                                                                    \
    /*Insert an element at the back of element of a certain index*/                                      \
    static const Name *Name##_InsertBack(Name *target, Type value, unsigned Index)                       \
    {                                                                                                    \
        if (target->len <= 0 || target->reserve < 0)                                                     \
        {                                                                                                \
            fprintf(stderr, "Error: Invalid List!\n");                                                   \
            abort();                                                                                     \
        }                                                                                                \
        if (Index == target->len - 1 || target->len == 1)                                                \
        {                                                                                                \
            return (Name##_PushBack(target, value));                                                     \
        }                                                                                                \
        if (target->reserve == 0)                                                                        \
        {                                                                                                \
            NodeName *iterator = Name##_GetIteratorByIndex(target, Index);                               \
            NodeName *buf = malloc(sizeof(NodeName));                                                    \
            NodeName *Next = iterator->next;                                                             \
            buf->pre = iterator;                                                                         \
            buf->next = Next;                                                                            \
            buf->val = value;                                                                            \
            iterator->next = buf;                                                                        \
            Next->pre = buf;                                                                             \
            ++target->len;                                                                               \
            return target;                                                                               \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            NodeName *reserve = target->end->next;                                                       \
            NodeName *iterator = Name##_GetIteratorByIndex(target, Index);                               \
                                                                                                         \
            target->end->next = reserve->next;                                                           \
            if (reserve->next != NULL)                                                                   \
                reserve->next->pre = target->end;                                                        \
            reserve->next = iterator->next;                                                              \
            reserve->pre = iterator;                                                                     \
            reserve->val = value;                                                                        \
            --target->reserve;                                                                           \
            ++target->len;                                                                               \
            return target;                                                                               \
        }                                                                                                \
    }                                                                                                    \
    /*                                                                                                   \
    Remove an element from a list at certain index                                                       \
    You Need To Be Cautious to Remove The Last One Element                                               \
    This Behavior Will Clear All The Elements And Reserves In A Rude Way                                 \
    */                                                                                                   \
    static const Type *Name##_Remove(Name *target, unsigned Index)                                       \
    {                                                                                                    \
        if (target->len <= 0 || target->reserve < 0)                                                     \
        {                                                                                                \
            fprintf(stderr, "Error: Invalid List!\n");                                                   \
            abort();                                                                                     \
        }                                                                                                \
        if (Index == target->len - 1 || target->len == 1)                                                \
        {                                                                                                \
            Name##_Reserve(target, 0, NULL);                                                             \
            free(target->beg);                                                                           \
            target->end = NULL;                                                                          \
            target->beg = NULL;                                                                          \
            target->len = 0;                                                                             \
            return NULL;                                                                                 \
        }                                                                                                \
        if (Index == 0 && target->len > 1)                                                               \
        {                                                                                                \
            return (Name##_PopFront(target));                                                            \
        }                                                                                                \
        NodeName *iterator = Name##_GetIteratorByIndex(target, Index);                                   \
        NodeName *Pre = iterator->pre;                                                                   \
        NodeName *Next = iterator->next;                                                                 \
        Pre->next = Next;                                                                                \
        Next->pre = Pre;                                                                                 \
        NodeName *buf = target->end->next;                                                               \
        target->end->next = iterator;                                                                    \
        iterator->pre = target->end;                                                                     \
        iterator->next = buf;                                                                            \
        --target->len;                                                                                   \
        ++target->reserve;                                                                               \
        return &iterator->val;                                                                           \
    }                                                                                                    \
    /*                                                                                                   \
    Find a element in a list, return a pointer to pair                                                   \
    you can provide a method to compare , or NULL to use ==                                              \
    */                                                                                                   \
    static const NodeName##_pair *Name##_FindElement(Name *target, Type Element, int (*cmp)(Type, Type)) \
    {                                                                                                    \
        NodeName *Forward = target->beg;                                                                 \
        NodeName *Backward = target->end;                                                                \
        NodeName *buf = NULL;                                                                            \
        unsigned cnt = 0;                                                                                \
        if (target->len <= 0)                                                                            \
        {                                                                                                \
            fprintf(stderr, "Error: No Elements!\n");                                                    \
            abort();                                                                                     \
        }                                                                                                \
        if (target->len <= 2)                                                                            \
        {                                                                                                \
            if (cmp != NULL)                                                                             \
            {                                                                                            \
                if ((*cmp)(Forward->val, Element))                                                       \
                {                                                                                        \
                    buf = Forward;                                                                       \
                    cnt = 0;                                                                             \
                }                                                                                        \
                else if ((*cmp)(Backward->val, Element))                                                 \
                {                                                                                        \
                    buf = Backward;                                                                      \
                    cnt = target->len - 1;                                                               \
                }                                                                                        \
            }                                                                                            \
            else                                                                                         \
            {                                                                                            \
                if (Forward->val == Element)                                                             \
                {                                                                                        \
                    buf = Forward;                                                                       \
                    cnt = 0;                                                                             \
                }                                                                                        \
                else if (Backward->val == Element)                                                       \
                {                                                                                        \
                    buf = Backward;                                                                      \
                    cnt = target->len - 1;                                                               \
                }                                                                                        \
            }                                                                                            \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            unsigned iterator = 0;                                                                       \
            if (target->len % 2 == 0)                                                                    \
            {                                                                                            \
                if (cmp != NULL)                                                                         \
                {                                                                                        \
                    while (iterator < target->len / 2)                                                   \
                    {                                                                                    \
                        if ((*cmp)(Forward->val, Element))                                               \
                        {                                                                                \
                            buf = Forward;                                                               \
                            break;                                                                       \
                        }                                                                                \
                        if ((*cmp)(Backward->val, Element))                                              \
                        {                                                                                \
                            buf = Backward;                                                              \
                            cnt = target->len - cnt - 1;                                                 \
                            break;                                                                       \
                        }                                                                                \
                        ++cnt;                                                                           \
                        Forward = Forward->next;                                                         \
                        Backward = Backward->pre;                                                        \
                        ++iterator;                                                                      \
                    }                                                                                    \
                }                                                                                        \
                else                                                                                     \
                {                                                                                        \
                    while (iterator < target->len / 2)                                                   \
                    {                                                                                    \
                        if (Forward->val == Element)                                                     \
                        {                                                                                \
                            buf = Forward;                                                               \
                            break;                                                                       \
                        }                                                                                \
                        if (Backward->val == Element)                                                    \
                        {                                                                                \
                            buf = Backward;                                                              \
                            cnt = target->len - cnt - 1;                                                 \
                            break;                                                                       \
                        }                                                                                \
                        ++cnt;                                                                           \
                        Forward = Forward->next;                                                         \
                        Backward = Backward->pre;                                                        \
                        ++iterator;                                                                      \
                    }                                                                                    \
                }                                                                                        \
            }                                                                                            \
            else                                                                                         \
            {                                                                                            \
                if (cmp != NULL)                                                                         \
                {                                                                                        \
                    while (iterator < target->len / 2)                                                   \
                    {                                                                                    \
                        if ((*cmp)(Forward->val, Element))                                               \
                        {                                                                                \
                            buf = Forward;                                                               \
                            break;                                                                       \
                        }                                                                                \
                        if ((*cmp)(Backward->val, Element))                                              \
                        {                                                                                \
                            buf = Backward;                                                              \
                            cnt = target->len - cnt - 1;                                                 \
                            break;                                                                       \
                        }                                                                                \
                        ++cnt;                                                                           \
                        Forward = Forward->next;                                                         \
                        Backward = Backward->pre;                                                        \
                        ++iterator;                                                                      \
                    }                                                                                    \
                    if ((*cmp)(Forward->val, Element))                                                   \
                    {                                                                                    \
                        buf = Forward;                                                                   \
                    }                                                                                    \
                    else                                                                                 \
                    {                                                                                    \
                        while (iterator < target->len / 2)                                               \
                        {                                                                                \
                            if (Forward->val == Element)                                                 \
                            {                                                                            \
                                buf = Forward;                                                           \
                                break;                                                                   \
                            }                                                                            \
                            if (Backward->val == Element)                                                \
                            {                                                                            \
                                buf = Backward;                                                          \
                                cnt = target->len - cnt - 1;                                             \
                                break;                                                                   \
                            }                                                                            \
                            ++cnt;                                                                       \
                            Forward = Forward->next;                                                     \
                            Backward = Backward->pre;                                                    \
                            ++iterator;                                                                  \
                        }                                                                                \
                        if (Forward->val == Element)                                                     \
                        {                                                                                \
                            buf = Forward;                                                               \
                        }                                                                                \
                    }                                                                                    \
                }                                                                                        \
            }                                                                                            \
            if (buf)                                                                                     \
            {                                                                                            \
                NodeName##_pair *ret = malloc(sizeof(NodeName##_pair));                                  \
                ret->Name##_Node = buf;                                                                  \
                ret->Index = cnt;                                                                        \
                return ret;                                                                              \
            }                                                                                            \
            fprintf(stderr, "Error: No Such Element Found!\n");                                          \
            abort();                                                                                     \
        }                                                                                                \
    }                                                                                                    \
    /*The Generated Free-Thread*/                                                                        \
    static void *GENERATED_FREE_THREAD(void *p)                                                          \
    {                                                                                                    \
        pthread_detach(pthread_self);                                                                    \
        /*static int cnt = 0;*/                                                                          \
        if (p == NULL)                                                                                   \
            printf("Invald ptr\n");                                                                      \
        else                                                                                             \
            free(p);                                                                                     \
        /*printf("free called %d times\n", cnt++);*/                                                     \
        pthread_exit(NULL);                                                                              \
        return NULL;                                                                                     \
    } /*Thread Version Of Destory, Currently Slower Than Destory, I Do Not Know Why*/                    \
    static void Name##_Destory_Threads(Name *target, void (*destructor_thread)(Type *))                  \
    {                                                                                                    \
        if (target->len <= 0 && target->reserve <= 0)                                                    \
        {                                                                                                \
            fprintf(stderr, "Error: Invalid List!\n");                                                   \
            abort();                                                                                     \
        }                                                                                                \
        if (target->end == target->beg)                                                                  \
        {                                                                                                \
            NodeName *Reserve = target->end->next;                                                       \
            if (destructor_thread != NULL)                                                               \
            {                                                                                            \
                pthread_t pt1;                                                                           \
                pthread_create(&pt1, NULL, destructor_thread, &target->end->val);                        \
            }                                                                                            \
            pthread_t ptn;                                                                               \
            pthread_create(&ptn, NULL, &GENERATED_FREE_THREAD, target->end);                             \
                                                                                                         \
            pthread_t pts[target->reserve], pt2[target->reserve];                                        \
            unsigned cnt = 0;                                                                            \
            for (; Reserve; ++cnt)                                                                       \
            {                                                                                            \
                NodeName *buf1 = Reserve->next;                                                          \
                if (destructor_thread != NULL)                                                           \
                {                                                                                        \
                    pthread_create(&pt2[cnt], NULL, destructor_thread, &Reserve->val);                   \
                }                                                                                        \
                pthread_create(&pts[cnt], NULL, &GENERATED_FREE_THREAD, Reserve);                        \
                Reserve = buf1;                                                                          \
            }                                                                                            \
            free(target);                                                                                \
        }                                                                                                \
        else if (target->end && target->beg)                                                             \
        {                                                                                                \
            NodeName *Beg = target->beg, *End = target->end, *Reserve = End->next;                       \
            unsigned cnt = 0;                                                                            \
            pthread_t pt1[target->len], ptn[target->len], pt2[target->reserve], pts[target->reserve];    \
            for (; cnt * 2 <= target->len || Reserve != NULL; ++cnt)                                     \
            {                                                                                            \
                NodeName *buf1 = Beg->next, *buf2 = End->pre;                                            \
                if (cnt * 2 < target->len)                                                               \
                {                                                                                        \
                    if (destructor_thread != NULL)                                                       \
                    {                                                                                    \
                        pthread_create(&pt1[cnt * 2], NULL, destructor_thread, &End->val);               \
                        pthread_create(&pt1[cnt * 2 + 1], NULL, destructor_thread, &Beg->val);           \
                    }                                                                                    \
                    pthread_create(&ptn[cnt * 2], NULL, &GENERATED_FREE_THREAD, Beg);                    \
                    pthread_create(&ptn[cnt * 2 + 1], NULL, &GENERATED_FREE_THREAD, End);                \
                    Beg = buf1;                                                                          \
                    End = buf2;                                                                          \
                }                                                                                        \
                else if (cnt == target->len / 2 && target->len % 2 == 1)                                 \
                {                                                                                        \
                    if (destructor_thread != NULL)                                                       \
                    {                                                                                    \
                        pthread_create(&pt1[cnt], NULL, destructor_thread, &End->val);                   \
                    }                                                                                    \
                    pthread_create(&ptn[cnt], NULL, &GENERATED_FREE_THREAD, Beg);                        \
                }                                                                                        \
                if (Reserve)                                                                             \
                {                                                                                        \
                    NodeName *buf1 = Reserve->next;                                                      \
                                                                                                         \
                    if (destructor_thread != NULL)                                                       \
                    {                                                                                    \
                        pthread_create(&pt2[cnt], NULL, destructor_thread, &Reserve->val);               \
                    }                                                                                    \
                    pthread_create(&pts[cnt], NULL, &GENERATED_FREE_THREAD, Reserve);                    \
                    Reserve = buf1;                                                                      \
                }                                                                                        \
            }                                                                                            \
            free(target);                                                                                \
        }                                                                                                \
                                                                                                         \
        else                                                                                             \
        {                                                                                                \
            fprintf(stderr, "Error: Invalid List!\n");                                                   \
            abort();                                                                                     \
        }                                                                                                \
    }                                                                                                    \
    /*Destory a list, you can provide a func to deal with your data or just give a NULL*/                 \
    static void Name##_Destory(Name *target, void (*destructor)(Type *))                                 \
    {                                                                                                    \
        if (target->len <= 0 && target->reserve <= 0)                                                    \
        {                                                                                                \
            fprintf(stderr, "Error: Invalid List!\n");                                                   \
            abort();                                                                                     \
        }                                                                                                \
        if (target->end == target->beg)                                                                  \
        {                                                                                                \
            NodeName *Reserve = target->end->next;                                                       \
            if (destructor != NULL)                                                                      \
            {                                                                                            \
                (*destructor)(&target->end->val);                                                        \
            }                                                                                            \
            free(target->end);                                                                           \
            while (Reserve)                                                                              \
            {                                                                                            \
                NodeName *buf1 = Reserve->next;                                                          \
                if (destructor != NULL)                                                                  \
                {                                                                                        \
                    (*destructor)(&Reserve->val);                                                        \
                }                                                                                        \
                free(Reserve);                                                                           \
                Reserve = buf1;                                                                          \
            }                                                                                            \
            free(target);                                                                                \
        }                                                                                                \
        else if (target->end && target->beg)                                                             \
        {                                                                                                \
            NodeName *Beg = target->beg, *End = target->end, *Reserve = End->next;                       \
            unsigned cnt = 0;                                                                            \
            for (; cnt <= target->len / 2 || Reserve != NULL; ++cnt)                                     \
            {                                                                                            \
                NodeName *buf1 = Beg->next, *buf2 = End->pre;                                            \
                if (cnt < target->len / 2)                                                               \
                {                                                                                        \
                    if (destructor != NULL)                                                              \
                    {                                                                                    \
                        (*destructor)(&Beg->val);                                                        \
                        (*destructor)(&End->val);                                                        \
                    }                                                                                    \
                    free(Beg);                                                                           \
                    free(End);                                                                           \
                    Beg = buf1;                                                                          \
                    End = buf2;                                                                          \
                }                                                                                        \
                else if (cnt == target->len / 2 && target->len % 2 == 1)                                 \
                {                                                                                        \
                    if (destructor != NULL)                                                              \
                    {                                                                                    \
                        (*destructor)(&End->val);                                                        \
                    }                                                                                    \
                    free(End);                                                                           \
                }                                                                                        \
                if (Reserve)                                                                             \
                {                                                                                        \
                    NodeName *buf1 = Reserve->next;                                                      \
                                                                                                         \
                    if (destructor != NULL)                                                              \
                    {                                                                                    \
                        (*destructor)(&Reserve->val);                                                    \
                    }                                                                                    \
                    free(Reserve);                                                                       \
                    Reserve = buf1;                                                                      \
                }                                                                                        \
            }                                                                                            \
            free(target);                                                                                \
        }                                                                                                \
                                                                                                         \
        else                                                                                             \
        {                                                                                                \
            fprintf(stderr, "Error: Invalid List!\n");                                                   \
            abort();                                                                                     \
        }                                                                                                \
    }                                                                                                    \
    /*                                                                                                   \
    Count how many times the given element appears in the list                                           \
    you can provide a method to compare or NULL to use ==                                                \
    */                                                                                                   \
    static const unsigned Name##_Count(Name *target, Type value, int (*cmp)(Type, Type))                 \
    {                                                                                                    \
        if (target->len <= 0)                                                                            \
        {                                                                                                \
            fprintf(stderr, "Error: No Elements!\n");                                                    \
            abort();                                                                                     \
        }                                                                                                \
        NodeName *Begin = target->beg, *End = target->end;                                               \
        unsigned cnt = 0, iterator = 0;                                                                  \
        if (target->len % 2 == 0)                                                                        \
        {                                                                                                \
            if (cmp != NULL)                                                                             \
            {                                                                                            \
                while (iterator < target->len / 2)                                                       \
                {                                                                                        \
                    if ((*cmp)(Begin->val, value))                                                       \
                        ++cnt;                                                                           \
                    if ((*cmp)(End->val, value))                                                         \
                        ++cnt;                                                                           \
                    Begin = Begin->next;                                                                 \
                    End = End->pre;                                                                      \
                    ++iterator;                                                                          \
                }                                                                                        \
            }                                                                                            \
            else                                                                                         \
            {                                                                                            \
                while (iterator < target->len / 2)                                                       \
                {                                                                                        \
                    if (Begin->val == value)                                                             \
                        ++cnt;                                                                           \
                    if (End->val == value)                                                               \
                        ++cnt;                                                                           \
                    Begin = Begin->next;                                                                 \
                    End = End->pre;                                                                      \
                    ++iterator;                                                                          \
                }                                                                                        \
            }                                                                                            \
            return cnt;                                                                                  \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            if (cmp != NULL)                                                                             \
            {                                                                                            \
                while (iterator < target->len / 2)                                                       \
                {                                                                                        \
                    if ((*cmp)(Begin->val, value))                                                       \
                        ++cnt;                                                                           \
                    if ((*cmp)(End->val, value))                                                         \
                        ++cnt;                                                                           \
                    Begin = Begin->next;                                                                 \
                    End = End->pre;                                                                      \
                    ++iterator;                                                                          \
                }                                                                                        \
                if ((*cmp)(Begin->val, value))                                                           \
                    ++cnt;                                                                               \
            }                                                                                            \
            else                                                                                         \
            {                                                                                            \
                while (iterator < target->len / 2)                                                       \
                {                                                                                        \
                    if (Begin->val == value)                                                             \
                        ++cnt;                                                                           \
                    if (End->val == value)                                                               \
                        ++cnt;                                                                           \
                    Begin = Begin->next;                                                                 \
                    End = End->pre;                                                                      \
                    ++iterator;                                                                          \
                }                                                                                        \
                if (Begin->val == value)                                                                 \
                    ++cnt;                                                                               \
            }                                                                                            \
            return cnt;                                                                                  \
        }                                                                                                \
    }

#endif /* A2EA3F69_7DFF_4B88_A3CF_256B119A4A69 */

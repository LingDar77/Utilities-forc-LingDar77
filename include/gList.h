#ifndef A2EA3F69_7DFF_4B88_A3CF_256B119A4A69
#define A2EA3F69_7DFF_4B88_A3CF_256B119A4A69

/**
* Generic list implement in C
* Author: LingDar77
* Version: 0.0.1
* 4/18/2021
*/
//#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

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
    }                                                                                                    \
    /*add an element at the end of a list*/                                                              \
    static const Name *Name##_PushBack(Name *target, Type value)                                         \
    {                                                                                                    \
        if (target->reserve <= 0)                                                                        \
        {                                                                                                \
            if (target->reserve < 0)                                                                     \
                target->reserve = 0;                                                                     \
            NodeName *buffer = malloc(sizeof(NodeName));                                                 \
            if (buffer == NULL)                                                                          \
            {                                                                                            \
                perror("Error: Malloc Failed!\n");                                                       \
                abort();                                                                                 \
            }                                                                                            \
            buffer->val = value;                                                                         \
            buffer->next = NULL;                                                                         \
            if (target->len <= 0)                                                                        \
            {                                                                                            \
                target->beg = buffer;                                                                    \
                target->end = buffer;                                                                    \
                buffer->pre = NULL;                                                                      \
                target->len = 1;                                                                         \
                return target;                                                                           \
            }                                                                                            \
            target->end->next = buffer;                                                                  \
            buffer->pre = target->end;                                                                   \
            target->end = buffer;                                                                        \
            ++target->len;                                                                               \
            return target;                                                                               \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            target->end = target->end->next;                                                             \
            target->end->val = value;                                                                    \
            ++target->len;                                                                               \
            --target->reserve;                                                                           \
            return target;                                                                               \
        }                                                                                                \
    }                                                                                                    \
    /*Pop the last one element*/                                                                         \
    static const Type *Name##_PopBack(Name *target)                                                      \
    {                                                                                                    \
        if (target->len <= 0 || target->reserve < 0)                                                     \
        {                                                                                                \
            fprintf(stderr, "Error: Invalid List!\n");                                                   \
            abort();                                                                                     \
        }                                                                                                \
        ++target->reserve;                                                                               \
        target->end = target->end->pre;                                                                  \
        --target->len;                                                                                   \
        return &target->end->next->val;                                                                  \
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
            NodeName *buf = target->end->next;                                                           \
            NodeName *iterator = Name##_GetIteratorByIndex(target, Index);                               \
            if (target->reserve > 1)                                                                     \
            {                                                                                            \
                target->end->next = buf->next;                                                           \
                buf->next->pre = target->end;                                                            \
                buf->next = iterator->next;                                                              \
                buf->pre = iterator;                                                                     \
                buf->val = value;                                                                        \
                --target->reserve;                                                                       \
                ++target->len;                                                                           \
                return target;                                                                           \
            }                                                                                            \
        }                                                                                                \
    }                                                                                                    \
    /*Remove an element from a list at certain index*/                                                   \
    static const Type *Name##_Remove(Name *target, unsigned Index)                                       \
    {                                                                                                    \
        if (target->len <= 0 || target->reserve < 0)                                                     \
        {                                                                                                \
            fprintf(stderr, "Error: Invalid List!\n");                                                   \
            abort();                                                                                     \
        }                                                                                                \
        if (Index == target->len - 1 || target->len == 1)                                                \
        {                                                                                                \
            return (Name##_PopBack(target));                                                             \
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
    /*find a element in a list, return a pointer to pair*/                                               \
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
            if ((*cmp)(Forward->val, Element))                                                           \
            {                                                                                            \
                buf = Forward;                                                                           \
                cnt = 0;                                                                                 \
            }                                                                                            \
            else if ((*cmp)(Backward->val, Element))                                                     \
            {                                                                                            \
                buf = Backward;                                                                          \
                cnt = target->len - 1;                                                                   \
            }                                                                                            \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            if (target->len % 2 == 0)                                                                    \
            {                                                                                            \
                while (Forward->pre != Backward->next)                                                   \
                {                                                                                        \
                    if ((*cmp)(Forward->val, Element))                                                   \
                    {                                                                                    \
                        buf = Forward;                                                                   \
                        break;                                                                           \
                    }                                                                                    \
                    if ((*cmp)(Backward->val, Element))                                                  \
                    {                                                                                    \
                        buf = Backward;                                                                  \
                        cnt = target->len - cnt - 1;                                                     \
                        break;                                                                           \
                    }                                                                                    \
                    ++cnt;                                                                               \
                    Forward = Forward->next;                                                             \
                    Backward = Backward->pre;                                                            \
                }                                                                                        \
            }                                                                                            \
            else                                                                                         \
            {                                                                                            \
                while (cnt <= target->len / 2)                                                           \
                {                                                                                        \
                    if ((*cmp)(Forward->val, Element))                                                   \
                    {                                                                                    \
                        buf = Forward;                                                                   \
                        break;                                                                           \
                    }                                                                                    \
                    if ((*cmp)(Backward->val, Element))                                                  \
                    {                                                                                    \
                        buf = Backward;                                                                  \
                        cnt = target->len - cnt - 1;                                                     \
                        break;                                                                           \
                    }                                                                                    \
                    ++cnt;                                                                               \
                    Forward = Forward->next;                                                             \
                    Backward = Backward->pre;                                                            \
                }                                                                                        \
            }                                                                                            \
        }                                                                                                \
        if (buf)                                                                                         \
        {                                                                                                \
            NodeName##_pair *ret = malloc(sizeof(NodeName##_pair));                                      \
            ret->Name##_Node = buf;                                                                      \
            ret->Index = cnt;                                                                            \
            return ret;                                                                                  \
        }                                                                                                \
        fprintf(stderr, "Error: No Such Element Found!\n");                                              \
        abort();                                                                                         \
    }                                                                                                    \
    /*Destory a list,you can provaide a func to deal with your data or just give a NULL*/                \
    static void Name##_Destory(Name *target, void (*destructor)(Type *))                                 \
    {                                                                                                    \
        if (target->len <= 0 || target->reserve < 0)                                                     \
        {                                                                                                \
            fprintf(stderr, "Error: Invalid List!\n");                                                   \
            abort();                                                                                     \
        }                                                                                                \
        NodeName *iterator = target->beg;                                                                \
        while (iterator != NULL)                                                                         \
        {                                                                                                \
            NodeName *buf = iterator->next;                                                              \
            if (destructor != NULL)                                                                      \
                (*destructor)(&iterator->val);                                                           \
            free(iterator);                                                                              \
            iterator = buf;                                                                              \
        }                                                                                                \
    }                                                                                                    \
    /*                                                                                                   \
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
    }

#endif /* A2EA3F69_7DFF_4B88_A3CF_256B119A4A69 */

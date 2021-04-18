#ifndef A2EA3F69_7DFF_4B88_A3CF_256B119A4A69
#define A2EA3F69_7DFF_4B88_A3CF_256B119A4A69

/**
* Generic list implement
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
    } Name
#define GENERATED_GLIST_BODY(Type, NodeName, Name) GENERATED_GLIST_FUNC(Type, NodeName, Name);

//this macro is used to generate a list
#define GLIST(Type, Name)                  \
    DECLEAR_GNode(Type, GENERATED_##Name); \
    DECLEAR_GList(GENERATED_##Name, Name); \
    GENERATED_GLIST_BODY(Type, GENERATED_##Name, Name)

//this macro is used to generate a list and rename its node
#define GLIST_WITH_NODE(Type, Name, NodeName) \
    DECLEAR_GNode(Type, NodeName);            \
    DECLEAR_GList(NodeName, Name);            \
    GENERATED_GLIST_BODY(Type, NodeName, Name)

/*this macro is used to generate helpful functions*/
#define GENERATED_GLIST_FUNC(Type, NodeName, Name)                                                 \
    typedef struct GENERATED_##NodeName##_PAIR                                                     \
    {                                                                                              \
        NodeName *Name##_Node;                                                                     \
        unsigned Index;                                                                            \
    } NodeName##_pair;                                                                             \
    /*Find an iterator by index*/                                                                  \
    static NodeName *Name##_getIteratorByIndex(Name *target, unsigned Index)                       \
    {                                                                                              \
        if (target->len <= 0 || Index >= target->len)                                              \
        {                                                                                          \
            fprintf(stderr, "Error: Out Of Range!\n");                                             \
            abort();                                                                               \
        }                                                                                          \
        if (!Index)                                                                                \
            return target->beg;                                                                    \
        if (Index == target->len - 1)                                                              \
            return target->end;                                                                    \
        NodeName *iterator = NULL;                                                                 \
        if (target->len / Index > 2)                                                               \
        {                                                                                          \
            /*printf("left\n");*/                                                                  \
            iterator = target->beg;                                                                \
            while (Index && iterator)                                                              \
            {                                                                                      \
                iterator = iterator->next;                                                         \
                --Index;                                                                           \
            }                                                                                      \
            if (Index)                                                                             \
            {                                                                                      \
                fprintf(stderr, "Error: Can Not Reach Correct Iterator!\n");                       \
                abort();                                                                           \
            }                                                                                      \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            /*printf("right\n");*/                                                                 \
            iterator = target->end;                                                                \
            unsigned cnt = target->len - Index - 1;                                                \
            while (iterator && cnt)                                                                \
            {                                                                                      \
                iterator = iterator->pre;                                                          \
                --cnt;                                                                             \
            }                                                                                      \
            if (cnt)                                                                               \
            {                                                                                      \
                fprintf(stderr, "Error: Can Not Reach Correct Iterator!\n");                       \
                abort();                                                                           \
            }                                                                                      \
        }                                                                                          \
        return iterator;                                                                           \
    }                                                                                              \
    /*add an element at the end of a list*/                                                        \
    static Name *Name##_PushBack(Name *target, Type value)                                         \
    {                                                                                              \
        NodeName *buffer = malloc(sizeof(NodeName));                                               \
        if (buffer == NULL)                                                                        \
        {                                                                                          \
            perror("Error: Malloc Failed!\n");                                                     \
            abort();                                                                               \
        }                                                                                          \
        buffer->val = value;                                                                       \
        buffer->next = NULL;                                                                       \
        if (target->len <= 0)                                                                      \
        {                                                                                          \
            target->beg = buffer;                                                                  \
            target->end = buffer;                                                                  \
            buffer->pre = NULL;                                                                    \
            target->len = 1;                                                                       \
            return target;                                                                         \
        }                                                                                          \
        target->end->next = buffer;                                                                \
        buffer->pre = target->end;                                                                 \
        target->end = buffer;                                                                      \
        ++target->len;                                                                             \
        return target;                                                                             \
    }                                                                                              \
    /*Pop the last one element*/                                                                   \
    static NodeName *Name##_PopBack(Name *target)                                                  \
    {                                                                                              \
        if (target->len <= 0)                                                                      \
        {                                                                                          \
            fprintf(stderr, "Error: No Element To Pop!\n");                                        \
            abort();                                                                               \
        }                                                                                          \
        NodeName *buf = target->end;                                                               \
        target->end = buf->pre;                                                                    \
        target->end->next = NULL;                                                                  \
        --target->len;                                                                             \
        return buf;                                                                                \
    }                                                                                              \
    /*Insert an element at the back of element of a certain index*/                                \
    static Name *Name##_InsertBack(Name *target, Type value, unsigned Index)                       \
    {                                                                                              \
        if (Index == target->len - 1 || target->len == 1)                                          \
        {                                                                                          \
            return (Name##_PushBack(target, value));                                               \
        }                                                                                          \
        NodeName *iterator = Name##_getIteratorByIndex(target, Index);                             \
        NodeName *buf = malloc(sizeof(NodeName));                                                  \
        NodeName *Next = iterator->next;                                                           \
        buf->pre = iterator;                                                                       \
        buf->next = Next;                                                                          \
        buf->val = value;                                                                          \
        iterator->next = buf;                                                                      \
        Next->pre = buf;                                                                           \
        ++target->len;                                                                             \
        return target;                                                                             \
    }                                                                                              \
    /*Remove an element from a list at certain index*/                                             \
    static NodeName *Name##_Remove(Name *target, unsigned Index)                                   \
    {                                                                                              \
        if (Index == target->len - 1 || target->len == 1)                                          \
        {                                                                                          \
            return (Name##_PopBack(target));                                                       \
        }                                                                                          \
        NodeName *iterator = Name##_getIteratorByIndex(target, Index);                             \
        NodeName *Pre = iterator->pre;                                                             \
        NodeName *Next = iterator->next;                                                           \
        Pre->next = Next;                                                                          \
        Next->pre = Pre;                                                                           \
        iterator->pre = NULL;                                                                      \
        iterator->next = NULL;                                                                     \
        --target->len;                                                                             \
        return iterator;                                                                           \
    }                                                                                              \
    /*find a element in a list, return a pointer to pair*/                                         \
    static NodeName##_pair *Name##_findElement(Name *target, Type Element, int (*cmp)(Type, Type)) \
    {                                                                                              \
        NodeName *Forward = target->beg;                                                           \
        NodeName *Backward = target->end;                                                          \
        NodeName *buf = NULL;                                                                      \
        unsigned cnt = 0;                                                                          \
        if (target->len <= 0)                                                                      \
        {                                                                                          \
            fprintf(stderr, "Error: No Elements!\n");                                              \
            abort();                                                                               \
        }                                                                                          \
        if (target->len <= 2)                                                                      \
        {                                                                                          \
            if ((*cmp)(Forward->val, Element))                                                     \
            {                                                                                      \
                buf = Forward;                                                                     \
                cnt = 0;                                                                           \
            }                                                                                      \
            else if ((*cmp)(Backward->val, Element))                                               \
            {                                                                                      \
                buf = Backward;                                                                    \
                cnt = target->len - 1;                                                             \
            }                                                                                      \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            if (target->len % 2 == 0)                                                              \
            {                                                                                      \
                while (Forward->pre != Backward->next)                                             \
                {                                                                                  \
                    if ((*cmp)(Forward->val, Element))                                             \
                    {                                                                              \
                        buf = Forward;                                                             \
                        break;                                                                     \
                    }                                                                              \
                    if ((*cmp)(Backward->val, Element))                                            \
                    {                                                                              \
                        buf = Backward;                                                            \
                        cnt = target->len - cnt - 1;                                               \
                        break;                                                                     \
                    }                                                                              \
                    ++cnt;                                                                         \
                    Forward = Forward->next;                                                       \
                    Backward = Backward->pre;                                                      \
                }                                                                                  \
            }                                                                                      \
            else                                                                                   \
            {                                                                                      \
                while (cnt <= target->len / 2)                                                     \
                {                                                                                  \
                    if ((*cmp)(Forward->val, Element))                                             \
                    {                                                                              \
                        buf = Forward;                                                             \
                        break;                                                                     \
                    }                                                                              \
                    if ((*cmp)(Backward->val, Element))                                            \
                    {                                                                              \
                        buf = Backward;                                                            \
                        cnt = target->len - cnt - 1;                                               \
                        break;                                                                     \
                    }                                                                              \
                    ++cnt;                                                                         \
                    Forward = Forward->next;                                                       \
                    Backward = Backward->pre;                                                      \
                }                                                                                  \
            }                                                                                      \
        }                                                                                          \
        if (buf)                                                                                   \
        {                                                                                          \
            NodeName##_pair *ret = malloc(sizeof(NodeName##_pair));                                \
            ret->Name##_Node = buf;                                                                \
            ret->Index = cnt;                                                                      \
            return ret;                                                                            \
        }                                                                                          \
        fprintf(stderr, "Error: No Such Element Found!\n");                                        \
        abort();                                                                                   \
    }

#endif /* A2EA3F69_7DFF_4B88_A3CF_256B119A4A69 */

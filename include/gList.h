#ifndef A2EA3F69_7DFF_4B88_A3CF_256B119A4A69
#define A2EA3F69_7DFF_4B88_A3CF_256B119A4A69

/**
* generic list implement
* Author: LingDar77
* 4/18/2021
*/
//#include <assert.h>
#include <stdlib.h>

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

//this macro is used to generate helpful functions
#define GENERATED_GLIST_FUNC(Type, NodeName, Name)                           \
    /*add an element at the end of a list*/                                  \
    static Name *Name##_PushBack(Name *target, Type value)                   \
    {                                                                        \
        NodeName *buffer = malloc(sizeof(NodeName));                         \
        if (buffer == NULL)                                                  \
        {                                                                    \
            perror("Error: Malloc Failed!\n");                               \
            abort();                                                         \
        }                                                                    \
        buffer->val = value;                                                 \
        buffer->next = NULL;                                                 \
        if (target->len <= 0)                                                \
        {                                                                    \
            target->beg = buffer;                                            \
            target->end = buffer;                                            \
            buffer->pre = NULL;                                              \
            target->len = 1;                                                 \
            return target;                                                   \
        }                                                                    \
        target->end->next = buffer;                                          \
        buffer->pre = target->end;                                           \
        target->end = buffer;                                                \
        ++target->len;                                                       \
        return target;                                                       \
    }                                                                        \
    static NodeName *Name##_PopBack(Name *target)                            \
    {                                                                        \
        if (target->len <= 0)                                                \
        {                                                                    \
            perror("Error: No Element To Pop!\n");                           \
            abort();                                                         \
        }                                                                    \
        NodeName *buf = target->end;                                         \
        target->end = buf->pre;                                              \
        target->end->next = NULL;                                            \
        --target->len;                                                       \
        return buf;                                                          \
    }                                                                        \
    static Name *Name##_InsertBack(Name *target, Type value, unsigned Index) \
    {                                                                        \
        if (target->len <= 0 || Index >= target->len)                        \
        {                                                                    \
            perror("Error: Out Of Range!\n");                                \
            abort();                                                         \
        }                                                                    \
        if (Index == target->len - 1 || target->len == 1)                    \
        {                                                                    \
            return (Name##_PushBack(target, value));                         \
        }                                                                    \
        NodeName *iterator = target->beg;                                    \
        while (Index && iterator)                                            \
        {                                                                    \
            iterator = iterator->next;                                       \
            --Index;                                                         \
        }                                                                    \
        if (Index)                                                           \
        {                                                                    \
            perror("Error: Can Not Reach Correct Iterator!\n");              \
            abort();                                                         \
        }                                                                    \
        NodeName *buf = malloc(sizeof(NodeName));                            \
        NodeName *Next = iterator->next;                                     \
        buf->pre = iterator;                                                 \
        buf->next = Next;                                                    \
        buf->val = value;                                                    \
        iterator->next = buf;                                                \
        Next->pre = buf;                                                     \
        ++target->len;                                                       \
        return target;                                                       \
    }

#endif /* A2EA3F69_7DFF_4B88_A3CF_256B119A4A69 */

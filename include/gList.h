#ifndef A2EA3F69_7DFF_4B88_A3CF_256B119A4A69
#define A2EA3F69_7DFF_4B88_A3CF_256B119A4A69

/**
* GList.h 
* Generic list implement in C
* Author: LingDar77
* Version: 0.1.2
* Started: 4/18/2021
* Modified: 4/21/2021
**/

//#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "gListFunc.h"

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

//this macro is used to generate a list with its functions
#define GLIST(Type, Name)                  \
    DECLEAR_GNode(Type, GENERATED_##Name); \
    DECLEAR_GList(GENERATED_##Name, Name); \
    GENERATED_GLIST_FUNCTIONS(Type, GENERATED_##Name, Name)

//this macro is used to generate a list and rename its node and relating functions
#define GLIST_WITH_NODE(Type, Name, NodeName) \
    DECLEAR_GNode(Type, NodeName);            \
    DECLEAR_GList(NodeName, Name);            \
    GENERATED_GLIST_FUNCTIONS(Type, NodeName, Name)

#endif /* A2EA3F69_7DFF_4B88_A3CF_256B119A4A69 */

#ifndef EDA4F13B_4E58_4DC8_8CC7_98E37CD1624F
#define EDA4F13B_4E58_4DC8_8CC7_98E37CD1624F
#include <stdio.h>
#include <stdlib.h>

/**
 * myString.h
 * my string implement in c 
 * Author: LingDar77
 * 4/17/2021
 */

//macro
#define sNode struct node_string
#define String struct string

//basic node struct for linked list
sNode
{
    sNode *pre;
    sNode *next;
    char val;
};

//an implement of string by linked list
String
{
    sNode *beg;
    sNode *end;
    int length;
};

//constructor of my string
String *makeString(const char *s);
//add a string to the end of another string
String *addString(String *target, String *s);
//add a cstring to the end of a string
String *addCString(String *target, const char *s);
//add a char to the end of a string
String *addChar(String *target, const char c);
//insert a char at a certain place
String *insertChar(String *target, const char c, unsigned index);
//insert a string at a certain place
String *insertString(String *target, String *s, unsigned index);
//remove the certain char at the index
String *removeCharByIndex(String *source, const unsigned index);
//only remove the target char that first appears
String *removeChar(String *source, const char target);
//swap two chars by index
String *swapCharByIndex(String *target, const unsigned index1, const unsigned index2);
//get a copy of cut string
String *cutString(String *target, const unsigned beg, const unsigned end);
//try to find the char that first appears and return its index + 1 or return 0 when failed
const unsigned findChar(String *source, const char target);
//try to find the string that first appears and return the index + 1 that the target string's first char appears
const unsigned findString(String *source, String *target);
//get a copy of the string
String *cpyString(const String *s);
//get a reference of the string
//!BE CAUTIOUS TO USE THE REFERENCE OF ANY STRING
String *refString(const String *s, const unsigned beg, const unsigned end);
//delete a string
//make sure that you del all the pointer for safety
void delString(String *s);
//return 1 if the two strings are equal else return 0
unsigned cmpString(String *lhs, String *rhs);
//get a cstring of a string
char *cStr(String *s);
//unsafe ver, do not forget to free this pointer
//get a char by an index
const char getCharFromString(String *s, unsigned index);
//sort a string
//!UNFINISHED, NOT SAFE, DO NOT USE!
String *mergeSort(String *target);
//sort a string and return a copy of sorted string
String *bubbleSort(String *target);
String *reverse(String *target);
//print string
void prints(String *s);
//count the times that c appears
int count(String *target, char c);
#endif /* EDA4F13B_4E58_4DC8_8CC7_98E37CD1624F */
#include "myString.h"
#include <string.h>

/**
* 
* 
*/
String *makeString(const char *s)
{
    char *iterator = s;
    sNode *pre = NULL;
    sNode *beg = NULL;
    int len = strlen(s);
    if (*s == '\0')
    {
        String *buffer = malloc(sizeof(String));
        buffer->length = -1;
        buffer->beg = NULL;
        buffer->end = NULL;
        return buffer;
    }
    while (*s != '\0')
    {
        sNode *buf = malloc(sizeof(sNode));
        if (beg == NULL)
        {
            buf->pre = NULL;
            buf->val = *s;
            buf->next = NULL;
            beg = buf;
            pre = buf;
        }
        else
        {
            buf->pre = pre;
            buf->val = *s;
            buf->next = NULL;
            pre->next = buf;
            pre = buf;
        }

        ++s;
    }
    //pre = NULL;
    String *buffer = malloc(sizeof(String));
    buffer->beg = beg;
    buffer->end = pre;
    buffer->length = len;
    return buffer;
}
String *cpyString(const String *s)
{
    char *buff = cStr(s);
    String *result = makeString(buff);
    free(buff);
    return result;
}
String *refString(const String *s, const unsigned beg, const unsigned end)
{
    String *buf = malloc(sizeof(String));
    sNode *iterator = s->beg;
    unsigned cnt = 0;
    sNode *Begin = NULL, *End = NULL;
    while (cnt < s->length)
    {
        if (cnt == beg)
            Begin = iterator;
        if (cnt == end)
            End = iterator;
        if (End && Begin)
            break;
        ++cnt;
        iterator = iterator->next;
    }
    buf->beg = Begin;
    buf->end = End;
    buf->length = end - beg + 1;
    return buf;
}
void prints(String *s)
{
    char *buf = cStr(s);
    printf("%s\n", buf);
    free(buf);
}
const char getCharFromString(String *s, unsigned index)
{
    if (index >= s->length)
        return NULL;
    sNode *literater = s->beg;
    int cnt = 0;
    while (literater && literater != s->end->next)
    {
        if (cnt == index)
            return literater->val;
        literater = literater->next;
        ++cnt;
    }
}
char *cStr(String *s)
{
    if (s->length <= 0)
        return ('\0');
    //printf("%d\n", s->length);
    char *buff = malloc(sizeof(char) * (s->length + 1));
    sNode *literator = s->beg;
    buff[s->length] = '\0';
    unsigned cnt = 0;
    while (cnt < s->length)
        buff[cnt] = literator->val,
        literator = literator->next,
        ++cnt;
    return buff;
}
String *addString(String *target, String *s)
{
    if (target->beg == target->end)
    {
        String *buff = cpyString(s);
        target->beg = buff->beg;
        target->end = buff->end;
        target->length = buff->length;
        return target;
    }
    String *buff = cpyString(s);
    target->end->next = buff->beg;
    buff->beg->pre = target->end;
    target->end = buff->end;
    target->length += buff->length;
    free(buff);
    return target;
}
String *addCString(String *target, const char *s)
{
    addString(target, makeString(s));
    return target;
}
String *addChar(String *target, const char c)
{
    if (target->length <= 0)
    {
        sNode *buf = malloc(sizeof(sNode));
        buf->val = c;
        target->beg = buf;
        target->length = 1;
        return target;
    }
    sNode *buf = malloc(sizeof(sNode));
    buf->val = c;
    ++target->length;
    buf->pre = target->end;
    target->end->next = buf;
    target->end = buf;
    return target;
}
void delString(String *s)
{
    sNode *iterator = s->beg;
    if (s->end && s->end->next)
        s->end->next->pre = NULL;
    while (iterator && s->end && iterator != s->end->next)
    {
        sNode *buf = iterator->next;
        free(iterator);
        iterator = buf;
    }
    free(s);
}
String *removeChar(String *source, const char target)
{
    sNode *literator = source->beg;
    while (literator && literator != source->end->next)
    {
        if (literator->val == target)
        {
            sNode *pre = literator->pre;
            sNode *next = literator->next;
            pre->next = next;
            next->pre = pre;
            --source->length;
            free(literator);
            return source;
        }
        literator = literator->next;
    }
    return source;
}
String *removeCharByIndex(String *source, const unsigned index)
{
    sNode *literator = source->beg;
    for (int i = 0; i < index; ++i)
        literator = literator->next;
    sNode *pre = literator->pre;
    sNode *next = literator->next;
    pre->next = next;
    next->pre = pre;
    --source->length;
    free(literator);
    return source;
}
String *insertChar(String *target, const char c, unsigned index)
{
    sNode *buf = malloc(sizeof(sNode));
    buf->val = c;
    sNode *literator = target->beg;
    for (int i = 0; literator && i < index; ++i)
    {
        literator = literator->next;
    }
    sNode *Next = literator->next;
    literator->next = buf;
    buf->pre = literator;
    buf->next = Next;
    Next->pre = buf;
    ++target->length;
    return target;
}
String *insertStringByIndex(String *target, String *s, unsigned index)
{
    String *buf = cpyString(s);
    printf("%s\n", cStr(buf));
    sNode *literator = target->beg;
    for (int i = 0; i < index; ++i)
    {
        literator = literator->next;
    }
    sNode *Next = literator->next;
    literator->next = buf->beg;
    buf->beg->pre = literator;
    buf->end->next = Next;
    Next->pre = buf->end;
    target->length += s->length;
    return target;
}
String *swapChar(String *target, const unsigned index1, const unsigned index2)
{
    if (index1 >= target->length || index2 >= target->length)
        return target;
    unsigned i1, i2;
    if (index1 > index2)
        i2 = index1, i1 = index2;
    i1 = index1, i2 = index2;
    sNode *literator = target->beg;
    unsigned cnt = 0;
    sNode *lli = NULL, *rli = NULL;
    while (literator)
    {
        if (i1 == cnt)
            lli = literator;
        if (i2 == cnt)
            rli = literator;
        if (lli != NULL && rli != NULL)
            break;
        literator = literator->next;
        ++cnt;
    }
    char buf = lli->val;
    lli->val = rli->val;
    rli->val = buf;
    return target;
}
String *cutString(String *target, const unsigned beg, const unsigned end)
{
    String *buffer = cpyString(target);
    sNode *Begin = buffer->beg;
    sNode *End = buffer->end;
    for (int i = 0; i < beg; ++i)
    {
        sNode *Next = Begin->next;
        free(Begin);
        Begin = Next;
    }
    buffer->beg = Begin;
    for (int i = target->length - 1; i > end; --i)
    {
        sNode *Pre = End->pre;
        free(End);
        End = Pre;
    }
    buffer->end = End;
    buffer->length = end - beg + 1;
    return buffer;
}
const unsigned findChar(String *source, const char target)
{
    int index = 0;
    for (; index < source->length; ++index)
    {
        if (getCharFromString(source, index) == target)
            return index + 1;
    }
    return index;
}
unsigned cmpString(String *lhs, String *rhs)
{
    if (lhs->length != rhs->length)
        return 0;

    sNode *lBeg = lhs->beg;
    sNode *rBeg = rhs->beg;

    while (lBeg && rBeg && lBeg != lhs->end->next)
    {
        if (lBeg->val != rBeg->val)
            return 0;
        lBeg = lBeg->next;
        rBeg = rBeg->next;
    }
    return 1;
}
const unsigned findString(String *source, String *target)
{
    for (int i = 0; i < source->length; ++i)
    {
        String *buffer = cutString(source, i, i + target->length - 1);
        //printf("%s,%s,%d\n",StringToCString(buffer),StringToCString(target),cmpString(buffer, target));
        if (cmpString(buffer, target) == 1)
        {
            free(buffer);
            return i + 1;
        }
        free(buffer);
    }
    return 0;
}
String *merge(String *lhs, String *rhs)
{
    String *buffer = malloc(sizeof(String));
    sNode *lli = lhs->beg;
    sNode *rli = rhs->beg;

    while (lli != lhs->end->next && rli != rhs->end->next)
    {
        if (lli->val <= rli->val)
        {
            addChar(buffer, lli->val);
            lli = lli->next;
        }
        else
        {
            addChar(buffer, rli->val);
            rli = rli->next;
        }
    }
    while (lli != lhs->end->next)
    {
        addChar(buffer, lli->val);
        lli = lli->next;
    }
    while (rli != rhs->end->next)
    {
        addChar(buffer, rli->val);
        rli = rli->next;
    }
    prints(buffer);
    return (buffer);
}
String *mergeSort(String *target)
{
    if (target->length < 3)
        return target;
    String *lhalf = refString(target, 0, target->length / 2);
    String *rhalf = refString(target, target->length / 2 + 1, target->length - 1);
    lhalf = mergeSort(lhalf);
    rhalf = mergeSort(rhalf);
    String *result = merge(lhalf, rhalf);
    return (result);
}
String *bubbleSort(String *target)
{
    String *buffer = cpyString(target);
    sNode *Begin = buffer->beg;
    sNode *End = buffer->end;
    if (target->length % 2 == 1)
    {
        while (Begin != End)
        {
            for (sNode *cmp = Begin->next; cmp != buffer->end; cmp = cmp->next)
            {
                if (Begin->val > cmp->val)
                {
                    char buf = Begin->val;
                    Begin->val = cmp->val;
                    cmp->val = buf;
                }
            }
            Begin = Begin->next;
            for (sNode *cmp = End->pre; cmp != buffer->beg; cmp = cmp->pre)
            {
                if (End->val < cmp->val)
                {
                    char buf = End->val;
                    End->val = cmp->val;
                    cmp->val = buf;
                }
            }
            End = End->pre;
        }
    }
    else
    {
        while (Begin->next != End)
        {
            for (sNode *cmp = Begin->next; cmp != buffer->end; cmp = cmp->next)
            {
                if (Begin->val > cmp->val)
                {
                    char buf = Begin->val;
                    Begin->val = cmp->val;
                    cmp->val = buf;
                }
            }
            Begin = Begin->next;
            for (sNode *cmp = End->pre; cmp != buffer->beg; cmp = cmp->pre)
            {
                if (End->val < cmp->val)
                {
                    char buf = End->val;
                    End->val = cmp->val;
                    cmp->val = buf;
                }
            }
            End = End->pre;
        }
    }

    return buffer;
}
String *reverse(String *target)
{
    String *buffer = cpyString(target);
    sNode *Begin = buffer->beg;
    sNode *End = buffer->end;
    if (buffer->length % 2 == 0)
    {
        for (unsigned cnt = 0; cnt < buffer->length / 2; ++cnt)
        {
            //printf("%d\n", cnt);
            char buf = Begin->val;
            Begin->val = End->val;
            End->val = buf;
            Begin = Begin->next;
            End = End->pre;
        }
    }
    else
    {
        while (Begin != End)
        {
            char buf = Begin->val;
            Begin->val = End->val;
            End->val = buf;
            Begin = Begin->next;
            End = End->pre;
        }
    }
    return buffer;
}
int count(String *target, char c)
{
    unsigned cnt = 0;
    for (sNode *iterator = target->beg; iterator != target->end->next; iterator = iterator->next)
    {
        if (iterator->val == c)
            ++cnt;
    }
    return cnt;
}

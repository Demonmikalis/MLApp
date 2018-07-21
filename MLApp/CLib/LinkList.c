/* Program to implement a LinkList */
/* author : MR.Black */
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include"LinkList.h"

//create a linklist
LinkList *createLinkList()
{
    LinkList * re = (LinkList *) malloc(sizeof(LinkList));  
    re->count = 0;  
    re->first = NULL;  
    re->last = NULL;  
    re->equal = NULL;  
    return re;  
}

//free a linklist
void freeLinkList(LinkList * list)
{
	ListNode * p;  
    while (list->first)  
    {  
        p = list->first->next;  
        free(list->first);  
        list->first = p;  
    }  
    free(list);  
}

//insert at tail
void LinkListInsertDataAtLast(LinkList * const list, void* const data)  
{  
    ListNode * node = (ListNode *) malloc(sizeof(ListNode));  
    node->data = data;  
    node->next = NULL;  
    if (list->count)  
    {  
        list->last->next = node;  
        list->last = node;  
    }  
    else  
    {  
        list->first = node;  
        list->last = node;  
    }  
    (list->count)++;  
}

//insert at head  
void LinkListInsertDataAtFirst(LinkList * const list, void* const data)  
{  
    ListNode * node = (ListNode *) malloc(sizeof(ListNode));  
    node->data = data;  
    node->next = NULL;  
  
    if (list->count)  
    {  
        node->next = list->first;  
        list->first = node;  
    }  
    else  
    {  
        list->first = node;  
        list->last = node;  
    }  
    (list->count)++;  
}

//length  
int LinkListGetSize(const LinkList * const list)  
{  
    return list->count;  
}  

//print  
void LinkListOutput(const LinkList * const list, void(*pt)(const void * const))  
{  
    ListNode * p = list->first;  
    while (p)  
    {  
        (*pt)(p->data);  
        p = p->next;  
    }  
}  

//delete at head 
void* LinkListRemoveDataAtFirst(LinkList * const list)  
{  
    ListNode *p = list->first;  
    list->first = p->next;  
    void * re = p->data;  
    free(p);  
    (list->count)--;  
    if (list->count == 0)  
    {  
        list->last = NULL;  
    }  
    return re;  
}  

//delete at tail 
void* LinkListRemoveDataAtLast(LinkList* const list)
{  
    if (list->count == 1)  
    {  
        return LinkListRemoveDataAtFirst(list);  
    }  
    ListNode * p = list->first;  
    while (p->next != list->last)  
    {  
        p = p->next;  
    }  
    void *re = list->last->data;  
    free(list->last);  
    p->next = NULL;  
    list->last = p;  
    (list->count)--;  
    return re;  
}  

//insert  
void LinkListInsertDataAt(LinkList * const list, void* const data, int index)  
{  
    if (index == 0)  
    {  
        LinkListInsertDataAtFirst(list, data);  
        return;  
    }  
    if (index == list->count)  
    {  
        LinkListInsertDataAtLast(list, data);  
        return;  
    }  
    ListNode * node = (ListNode *) malloc(sizeof(ListNode));  
    node->data = data;  
    node->next = NULL;  
  
    ListNode * p = list->first;  
    for (int i = 0; i < index - 1; i++)  
    {  
        p = p->next;  
    }  
    node->next = p->next;  
    p->next = node;  
  
    (list->count)++;  
}  
  
//delete at index  
void* LinkListRemoveDataAt(LinkList* const list, int index)  
{  
    if (index == 0)  
    {  
        return LinkListRemoveDataAtFirst(list);  
    }  
    if (index == list->count - 1)  
    {  
        return LinkListRemoveDataAtLast(list);  
    }  
  
    ListNode * p = list->first;  
    for (int i = 0; i < index - 1; i++)  
    {  
        p = p->next;  
    }  
    ListNode *tp = p->next;  
    p->next = p->next->next;  
    void * re = tp->data;  
    free(tp);  
    (list->count)--;  
    return re;  
}  
  
//get data  
void* LinkListGetDataAt(const LinkList * const list, int index)  
{  
    if (index == list->count - 1)  
    {  
        return LinkListGetDataAtLast(list);  
    }  
    ListNode * p = list->first;  
    for (int i = 0; i < index; i++)  
    {  
        p = p->next;  
    }  
    return p->data;  
}  
  
// get the first data  
void* LinkListGetDataAtFirst(const LinkList * const list)  
{  
    return list->first->data;  
}  
// get the last data  
void* LinkListGetDataAtLast(const LinkList * const list)  
{  
    return list->last->data;  
}

//search for a specific data  
// if does not exist, return -1 otherwize return the first appear position 
int LinkListFindDataIndex(const LinkList * const list, void * data)  
{  
    ListNode * p = list->first;  
    int re = 0;  
    if (list->equal)  
    {  
        while (p)  
        {  
            if (p->data == data || (*(list->equal))(p->data, data))  
            {  
                return re;  
            }  
            re++;  
            p = p->next;  
        }  
  
    }  
    else  
    {  
        while (p)  
        {  
            if (p->data == data)  
            {  
                return re;  
            }  
            re++;  
            p = p->next;  
        }  
    }  
    return -1;  
}  
  
  
LinkList* createSearchLinkList(int(*equal)(void * a, void * b))  
{  
    LinkList * re = createLinkList();  
    re->equal = equal;  
    return re;  
}  
  
//create iterator for linklist  
LinkListIterator* createLinkListIterator(const LinkList * const list)  
{  
    LinkListIterator * re = (LinkListIterator *) malloc(sizeof(LinkListIterator));  
    re->p = list->first;  
    re->allSize = list->count;  
    re->count = 0;  
    return re;  
}  
  
//free iterator for linklist  
void freeLinkListIterator(LinkListIterator* iterator)  
{  
    free(iterator);  
}  
  
//Iterator has next
int LinkListIteratorHasNext(const LinkListIterator* const iterator)  
{  
    return iterator->count < iterator->allSize;  
}  
  
//get the next element from iterator   
void * LinkListIteratorNext(LinkListIterator* const iterator)  
{  
    void * re = iterator->p->data;  
    iterator->p = iterator->p->next;  
    (iterator->count)++;  
    return re;  
}  
  
//delete object in linklist 
int LinkListRemoveDataObject(LinkList* const list, void * data)  
{  
    LinkListIterator * it = createLinkListIterator(list);  
    int a = 0;  
    while (LinkListIteratorHasNext(it))  
    {  
        void * ld = LinkListIteratorNext(it);  
        if (data == ld || (list->equal != NULL && (*(list->equal))(ld, data)))  
        {  
            a = 1;  
            break;  
        }  
    }  
    if (a)  
    {  
        LinkListRemoveDataAt(list, it->count - 1);
    }  
    return a;  
} 

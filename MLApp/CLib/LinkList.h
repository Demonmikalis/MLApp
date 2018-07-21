#ifndef _LINKLIST_H
#define _LINKLIST_H
#include<stdio.h>
#include<stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct ListNode  
{  
    void * data;  
    struct ListNode *next;  
} ListNode;  
  
typedef struct LinkList  
{  
    ListNode * first;  
    ListNode * last;  
    int count;  
    int (*equal)(void * a, void * b);  
} LinkList;  
  
typedef struct LinkListIterator  
{  
    ListNode * p;  
    int count;  
    int allSize;  
} LinkListIterator;  
  
//create  
LinkList *createLinkList();  
  
//create search 
LinkList *createSearchLinkList(int(*equal)(void * a, void * b));  
  
//free  
void freeLinkList(LinkList * list);  
  
//insertTail  
void LinkListInsertDataAtLast(LinkList* const list, void* const data);  
  
//insertHead  
void LinkListInsertDataAtFirst(LinkList * const list, void* const data);  
  
//insert  
void LinkListInsertDataAt(LinkList * const list, void* const data, int index);  
  
//delTail  
void* ListRemoveDataAtLast(LinkList* const list);  
  
//delHead  
void* LinkListRemoveDataAtFirst(LinkList * const list);  
  
//del
void* LinkListRemoveDataAt(LinkList* const list, int index);  
  
//delData  
int LinkListRemoveDataObject(LinkList* const list, void * data);  
  
//length  
int LinkListGetSize(const LinkList * const list);  
  
//Print  
void LinkListOutput(const LinkList * const list, void(*pt)(const void * const));  
  
//get  
void* LinkListGetDataAt(const LinkList * const list, int index);  
  
//getFirst  
void* LinkListGetDataAtFirst(const LinkList * const list);  
  
//getLast  
void* LinkListGetDataAtLast(const LinkList * const list);  
  
//search for a specific data  
// if does not exist, return -1 otherwize return the first appear position
int LinkListFindDataIndex(const LinkList * const list, void * data);  
  
//createIterator  
LinkListIterator* createLinkListIterator(const LinkList * const list);  
  
//freeIterator  
void freeLinkListIterator(LinkListIterator* iterator);  
  
//Iterator has next  
int LinkListIteratorHasNext(const LinkListIterator* const iterator);  
  
//get the next element from iterator  
void *LinkListIteratorNext(LinkListIterator* const iterator);
#ifdef __cplusplus
}
#endif
#endif  /* _LINKLIST_H */

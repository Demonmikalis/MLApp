/* Program to implement HashSet data structure*/
/* author : MR.Black */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"HashSet.h"

// create HashSet 
HashSet *createHashSet(int(*hashCode)(void *data), int(*equal)(void *data1, void *data2))  
{  
    HashSet *re = malloc(sizeof(HashSet));  
    re->size = 0;  
    re->loadFactor = DEFAULT_LOAD_FACTOR;  
    re->initialCapacity = DEFAULT_INITIAL_CAPACITY;  
    re->dataList = (LinkList **) malloc(sizeof(LinkList*) * re->initialCapacity);  
    re->hashCode = hashCode;
    re->equal = equal;  
    for (int i = 0; i < re->initialCapacity; i++)  
    {  
        re->dataList[i] = createSearchLinkList(equal);  
    }  
    return re;  
}

//create HashSet by params  
HashSet *createHashSetForAll(int initialCapacity, float loadFactor, int(*hashCode)(void *data), int(*equal)(void *data1, void *data2))  
{  
    HashSet *re = createHashSet(hashCode, equal);  
    re->initialCapacity = initialCapacity;  
    re->loadFactor = loadFactor;  
    return re;  
}  
  
//free HashSet  
void freeHashSet(HashSet * set)  
{  
    for (int i = 0; i < set->initialCapacity; i++)  
    {  
        freeLinkList(set->dataList[i]);  
    }  
    free(set->dataList);  
    free(set);  
}  
  
//whether contains data  
int HashSetContains(HashSet * const set, void * const data)  
{  
    int hasCode = (*(set->hashCode))(data);  
    hasCode %= set->initialCapacity;  
    if (hasCode<0)  
        hasCode+=set->initialCapacity;  
    int re = LinkListFindDataIndex(set->dataList[hasCode], data);  
    return re > -1;  
}  
  
void rebuildHashSet(HashSet * set)  
{  
    int newSize = set->initialCapacity * 2;  
    LinkList **newdataList = (LinkList **) malloc(sizeof(LinkList*) * newSize);  
    for (int i = 0; i < newSize; i++)  
    {  
        newdataList[i] = createLinkList();  
    }  
    HashSetIterator* it = createHashSetIterator(set);  
    while (HashSetIteratorHasNext(it))  
    {  
        void * data = HashSetIteratorNext(it);  
        int hasCode = (*(set->hashCode))(data);  
        hasCode %= newSize;  
        LinkListInsertDataAtLast(newdataList[hasCode], data);  
    }  
    freeHashSetIterator(it);  
    for (int i = 0; i < set->initialCapacity; i++)  
    {  
        freeLinkList(set->dataList[i]);  
    }  
    free(set->dataList);  
    set->dataList = newdataList;  
    set->initialCapacity = newSize;  
}  
  
//insert new data  
int HashSetAddData(HashSet * const set, void * const data)  
{  
    int hasCode = (*(set->hashCode))(data);  
    hasCode %= set->initialCapacity;  
    if (hasCode<0)  
        hasCode+=set->initialCapacity;  
    int re = LinkListFindDataIndex(set->dataList[hasCode], data);  
    if (re == -1)  
    {  
        LinkListInsertDataAtLast(set->dataList[hasCode], data);  
        (set->size)++;  
        if (set->size > set->initialCapacity * set->loadFactor)  
        {  
            rebuildHashSet(set);  
        }  
        return 1;  
    }  
    return 0;  
}  
  
//capacity  
int HashSetGetSize(const HashSet * const set)  
{  
    return set->size;  
}  
  
//create iterator  
HashSetIterator* createHashSetIterator(HashSet * const set)  
{  
    HashSetIterator* re = (HashSetIterator*) malloc(  
                                sizeof(HashSetIterator));  
    re->count = 0;  
    re->index = 0;  
    re->set = set;  
    re->current = set->dataList[0]->first;  
    return re;  
}  
  
//free iterator  
void freeHashSetIterator(HashSetIterator* iterator)  
{  
    free(iterator);  
}  
  
//whether iterator has next element  
int HashSetIteratorHasNext(HashSetIterator* iterator)  
{  
    return iterator->count < iterator->set->size;  
}  
  
//visit next
void* HashSetIteratorNext(HashSetIterator* iterator)  
{  
    (iterator->count)++;  
    while (!(iterator->current))  
    {  
        (iterator->index)++;  
        iterator->current = iterator->set->dataList[iterator->index]->first;  
    }  
    void * re = iterator->current->data;  
    iterator->current = iterator->current->next;  
    return re;  
}  
  
//delete a data  
int HashSetRemoveData(HashSet * const set, void * const data)  
{  
    int hasCode = (*(set->hashCode))(data);  
    hasCode %= set->initialCapacity;  
    if (hasCode<0)  
        hasCode+=set->initialCapacity;  
    int re = LinkListRemoveDataObject(set->dataList[hasCode], data);  
    if (re)  
    {  
        (set->size)--;  
    }  
    return re;  
}  
  
//merge *other into *set  
int HashSetAddAllSet(HashSet * set,HashSet *other)  
{  
    int ssize=set->size;  
    HashSetIterator * it=createHashSetIterator(other);  
    while (HashSetIteratorHasNext(it))  
    {  
        HashSetAddData(set,HashSetIteratorNext(it));  
    }  
    freeHashSetIterator(it);  
    int re=set->size-ssize;  
    return re;  
}  
  
//copy HashSet  
HashSet* HashSetCopy(HashSet * set)  
{  
    HashSet* re=createHashSetForAll(set->initialCapacity,set->loadFactor,set->hashCode,set->equal);  
    HashSetAddAllSet(re,set);  
    return re;  
}  
  
//loop dump 
void HashSetOutput(HashSet *set, void(*pt)(void*))  
{  
    HashSetIterator * it=createHashSetIterator(set);  
    while (HashSetIteratorHasNext(it))  
    {  
        pt(HashSetIteratorNext(it));  
    }  
    freeHashSetIterator(it);  
}


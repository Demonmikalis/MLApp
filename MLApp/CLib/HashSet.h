#ifndef _HASHSET_H
#define _HASHSET_H
#include "HashMap.h"
#include "LinkList.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct HashSet  
{  
    int size; //sz  
    int initialCapacity; //capacity
    float loadFactor; //loading factor  
    int (*hashCode)(void *data);  
    int (*equal)(void *data1, void *data2);  
    LinkList **dataList;  
} HashSet;  
  
typedef struct HashSetIterator  
{  
    int index; //which linklist 
    HashSet *set;  
    ListNode *current;  
    int count; //which data  
} HashSetIterator;  
  
//create HashSet  
HashSet *createHashSet(int (*hashCode)(void *data),int (*equal)(void *data1,void *data2));  
  
//create HashSet by params  
HashSet *createHashSetForAll(int initialCapacity,float loadFactor,int (*hashCode)(void *data),int (*equal)(void *data1,void *data2));  
  
//free HashSet  
void freeHashSet(HashSet * set);  
  
//whether contains data  
int HashSetContains(HashSet * const set, void * const data);  
  
//insert a new data  
int HashSetAddData(HashSet * const set, void * const data);  
  
//data capacity 
int HashSetGetSize(const HashSet * const set);  
  
//create iterator  
HashSetIterator* createHashSetIterator(HashSet * const set);  
  
//free iterator  
void freeHashSetIterator(HashSetIterator* iterator);  
  
//whether iterator has next  
int HashSetIteratorHasNext(HashSetIterator* iterator);  
  
//visit next  
void* HashSetIteratorNext(HashSetIterator* iterator);  
  
//delete one data  
int HashSetRemoveData(HashSet * const set, void * const data);  
  
//add the other set to the set, merge  
int HashSetAddAllSet(HashSet * set,HashSet *other);  
  
//copy HashSet  
HashSet* HashSetCopy(HashSet * set);  
  
//loop-all  
void HashSetOutput(HashSet *set, void(*pt)(void*));  

#ifdef __cplusplus
}
#endif
#endif  /* _HASHSET_H */

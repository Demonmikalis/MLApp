/* Program to implement HashMap data structure*/
/* author : MR.Black */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"HashMap.h"

/* -------------------------- equalfunc -------------------------- */
int EqualDefault(void * a, void *b)  
{  
    return a == b;  
}  
  
 
int EqualInt(void * a, void *b)  
{  
    int *aa = (int*) a;  
    int *bb = (int *) b;  
    return *aa == *bb;  
}  

int EqualDouble(void * a, void *b)  
{  
    double *aa = (double *) a;  
    double *bb = (double *) b;  
    return *aa == *bb;  
}  

int EqualChar(void * a, void *b)  
{  
    char *aa = (char *) a;  
    char *bb = (char *) b;  
    return *aa = *bb;  
}  
  
  
int EqualString(void * a, void *b)  
{  
    char *aa = (char *) a;  
    char *bb = (char *) b;  
    return strcmp(aa, bb)==0;  
}  

/* -------------------------- hashfunc -------------------------- */
  
int HashCodeDefault(void * a)  
{  
	int * aa = (int *) a;
    return *aa;  
}  
  

int HashCodeInt(void * a)  
{  
    int * aa = (int *) a;  
    return *aa;  
}
  

int HashCodeChar(void * a)  
{  
    char *aa = (char *) a;  
    return *aa;  
}  
  
int HashCodeString(void * a)  
{  
    int re = 0;  
    char *aa = (char *) a;  
    while (*aa)  
    {  
        re += HASHCODE_MULT * *aa;  
        aa++;  
    }  
    return re;  
}  

// whether a key in a entry 
Entry* listContainsEntry(LinkList * list, void * key, 
				         int(*equal)(void *key1, void *key2)) {  
    LinkListIterator* it = createLinkListIterator(list);  
    while (LinkListIteratorHasNext(it)) {  
        Entry * entry = (Entry *) (LinkListIteratorNext(it));  
        if (entry->key == key || (equal != NULL && (*equal)(entry->key, key))) {  
            return entry;  
        }  
    }  
    freeLinkListIterator(it);  
    return NULL;  
}  


//create HashMap  
HashMap *createHashMap(int(*hashCode)(void *key),  
        int(*equal)(void *key1, void *key2)) {  
    HashMap *re = (HashMap *) malloc(sizeof(HashMap));  
    re->size = 0;  
    re->loadFactor = DEFAULT_LOAD_FACTOR;  
    re->initialCapacity = DEFAULT_INITIAL_CAPACITY;  
    re->entryList = (LinkList **) malloc(sizeof(LinkList*)*re->initialCapacity);  
    re->hashCode = hashCode;  
    re->equal = equal;  
    for (int i = 0; i < re->initialCapacity; i++) {  
        re->entryList[i] = createLinkList();  
    }  
    return re;  
}  

//create HashMap by params  
HashMap *createHashMapForAll(int initialCapacity, float loadFactor,  
        int(*hashCode)(void *key), int(*equal)(void *key1, void *key2)) {  
    HashMap *re = createHashMap(hashCode, equal);  
    re->initialCapacity = initialCapacity;  
    re->loadFactor = loadFactor;  
    return re;  
}


//contain key  
int HashMapContainsKey(HashMap * const map, void * const key) {  
    int hasCode = (*(map->hashCode))(key);  
    hasCode %= map->initialCapacity;  
    if (hasCode < 0)  
        hasCode += map->initialCapacity;  
    Entry * re = listContainsEntry(map->entryList[hasCode], key, map->equal);  
    return re != NULL;  
}  

void rebuildHashMap(HashMap * map) {  
    int newSize = map->initialCapacity * 2;  
    LinkList **newentryList = (LinkList **) malloc(sizeof(LinkList*) * newSize);  
    for (int i = 0; i < newSize; i++) {  
        newentryList[i] = createLinkList();  
    }  
    HashMapEntryIterator* it = createHashMapEntryIterator(map);  
    while (HashMapEntryIteratorHasNext(it)) {  
        Entry * entry = HashMapEntryIteratorNext(it);  
        int hasCode = (*(map->hashCode))(entry->key);  
        hasCode %= newSize;  
        if (hasCode < 0)  
            hasCode += newSize;  
        LinkListInsertDataAtLast(newentryList[hasCode], entry);  
    }  
    freeHashMapEntryIterator(it);  
    for (int i = 0; i < map->initialCapacity; i++) {  
        freeLinkList(map->entryList[i]);  
    }  
    free(map->entryList);  
    map->entryList = newentryList;  
    map->initialCapacity = newSize;  
}  

//insert data with key 
void HashMapPutData(HashMap * const map, void * const key,  
        void * const value) {  
    int hasCode = (*(map->hashCode))(key);  
    hasCode %= map->initialCapacity;  
    if (hasCode < 0)  
        hasCode += map->initialCapacity;  
    Entry * re = listContainsEntry(map->entryList[hasCode], key, map->equal);  
    if (re == NULL) {  
        Entry * entry = (Entry*) malloc(sizeof(Entry));  
        entry->key = key;  
        entry->value = value;  
        LinkListInsertDataAtLast(map->entryList[hasCode], entry);  
        (map->size)++;  
        if (map->size > map->initialCapacity * map->loadFactor) {  
            rebuildHashMap(map);  
        }  
    } else {  
        re->value = value;  
    }  
}  
  
//get data from key
void* HashMapGetDataByKey(HashMap * const map, void * const key) {  
    int hasCode = (*(map->hashCode))(key);  
    hasCode %= map->initialCapacity;  
    if (hasCode < 0)  
        hasCode += map->initialCapacity;  
    Entry * re = listContainsEntry(map->entryList[hasCode], key, map->equal);  
    if (re == NULL) {  
        return NULL;  
    }  
    return re->value;  
}  
  
//hashmap size  
int HashMapGetSize(const HashMap * const map) {  
    return map->size;  
}  
  
//create entry iterator
HashMapEntryIterator* createHashMapEntryIterator(HashMap * const map) {  
    HashMapEntryIterator* re = (HashMapEntryIterator*) malloc(  
            sizeof(HashMapEntryIterator));  
    re->count = 0;  
    re->index = 0;  
    re->map = map;  
    re->current = map->entryList[0]->first;  
    return re;  
}  
  
//release entry iterator  
void freeHashMapEntryIterator(HashMapEntryIterator* iterator) {  
    free(iterator);  
}  
  
//whether entry has next element 
int HashMapEntryIteratorHasNext(HashMapEntryIterator* iterator) {  
    return iterator->count < iterator->map->size;  
}  
  
//next entry element 
Entry* HashMapEntryIteratorNext(HashMapEntryIterator* iterator) {  
    (iterator->count)++;  
    while (!(iterator->current)) {  
        (iterator->index)++;  
        iterator->current = iterator->map->entryList[iterator->index]->first;  
    }  
    Entry * re = (Entry *) iterator->current->data;  
    iterator->current = iterator->current->next;  
    return re;  
}  
  
//delete a data, return whether succeed    
int HashMapRemoveDataByKey(HashMap * const map, void * const key) {  
    int hasCode = (*(map->hashCode))(key);  
    hasCode %= map->initialCapacity;  
    if (hasCode < 0)  
        hasCode += map->initialCapacity;  
    LinkListIterator* it = createLinkListIterator(map->entryList[hasCode]);  
    int re = 0;  
    while (LinkListIteratorHasNext(it)) {  
        Entry * entry = (Entry *) (LinkListIteratorNext(it));  
        if ((*(map->equal))(entry->key, key)) {  
            LinkListRemoveDataAt(map->entryList[hasCode], it->count - 1);  
            re = 1;  
            (map->size)--;  
            break;  
        }  
    }  
    freeLinkListIterator(it);  
    return re;  
}  
  
void FreeFunc(Entry * p){  
    free(p);  
}  
  
//free HashMap  
void freeHashMap(HashMap * map) {  
    HashMapOutput(map, FreeFunc);  
    for (int i = 0; i < map->initialCapacity; i++) {  
        freeLinkList(map->entryList[i]);  
    }  
    free(map->entryList);  
    free(map);  
}  
  
//visit all the element in map  
void HashMapOutput(HashMap *map, void(*pt)(Entry*)) {  
    HashMapEntryIterator* iterator = createHashMapEntryIterator(map);  
    while (HashMapEntryIteratorHasNext(iterator)) {  
        pt(HashMapEntryIteratorNext(iterator));  
    }  
    freeHashMapEntryIterator(iterator);  
}



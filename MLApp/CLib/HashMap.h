#ifndef _HASHMAP_H
#define _HASHMAP_H

#include "LinkList.h" 
#ifdef __cplusplus
extern "C" {
#endif
 
#define DEFAULT_INITIAL_CAPACITY 16  
#define DEFAULT_LOAD_FACTOR 0.75f  
#define HASHCODE_MULT 31 

typedef struct entry  
{  
    void * key;  
    void * value;  
} Entry;  
  
typedef struct HashMap  
{  
    int size;   //sz  
    int initialCapacity; //initial capacity  
    float loadFactor;   //loading factor  
    int (*hashCode)(void *key);  
    int (*equal)(void *key1,void *key2);  
    LinkList ** entryList;  
} HashMap;  
  
typedef struct HashMapEntryIterator  
{  
    int index;       //linklist index  
    HashMap *map;  
    ListNode *current;  
    int count;        //data index  
} HashMapEntryIterator;  
  
//create HashMap  
HashMap *createHashMap(int (*hashCode)(void *key),int (*equal)(void *key1,void *key2));  
  
//create HashMap by parameters
HashMap *createHashMapForAll(int initialCapacity,float loadFactor,int (*hashCode)(void *key),int (*equal)(void *key1,void *key2));  
  
//free HashMap  
void freeHashMap(HashMap * map);  
  
//whether contains key  
int HashMapContainsKey(HashMap *const map,void * const key);  
  
//add data  
void HashMapPutData(HashMap *const map,void * const key,void * const value);  
  
//find data by key  
void* HashMapGetDataByKey(HashMap * const map,void *const key);  
  
//the data size  
int HashMapGetSize(const HashMap * const map);  
  
//create HashMap Iterator  
HashMapEntryIterator* createHashMapEntryIterator(HashMap *const map);  
  
//release HashMap Iterator  
void freeHashMapEntryIterator(HashMapEntryIterator* iterator);  
  
//Entry Iterator has next  
int HashMapEntryIteratorHasNext(HashMapEntryIterator* iterator);  
  
//visit the next element in entry iterator  
Entry* HashMapEntryIteratorNext(HashMapEntryIterator* iterator);  
  
//delete a data, return whether succeed  
int HashMapRemoveDataByKey(HashMap *const map,void * const key);  
  
//for-loop visit  
void HashMapOutput(HashMap *map, void(*pt)(Entry*));  


//-------------------------- hashfunc -------------------------- //
 
//default hashCode  
int HashCodeDefault(void * a);  
  
//int hashCode  
int HashCodeInt(void * a);  
  
//char hashCode  
int HashCodeChar(void * a);  
  
//string hashCode  
int HashCodeString(void * a); 

//-------------------------- equalfunc -------------------------- //

//default equal  
int EqualDefault(void * a, void *b);  
  
//int equal  
int EqualInt(void * a, void *b);  
  
//char equal  
int EqualChar(void * a, void *b);  
  
//string equal  
int EqualString(void * a, void *b);  

// double equal
int EqualDouble(void * a, void *b);

#ifdef __cplusplus
}
#endif
#endif  /* _HASHMAP_H */

#ifndef _MINHEAP_H
#define _MINHEAP_H
#ifdef __cplusplus
extern "C" {
#endif
#define INT_MIN -0xffff
#define INT_MAX 0xffff
typedef struct MinHeap{
    int *harr; /* pointer to array of elements in heap */
    int capacity; /* maximum possible size of min heap */
    int heap_size; /* Current number of elements in min heap*/
}MinHeap;    

void swap(int *x, int *y);

MinHeap *NewHeap(int cap);

void insertKey(MinHeap *heap, int key);

void decreaseKey(MinHeap *heap, int i, int new_val);

void MinHeapify(MinHeap *heap, int i);

void deleteHeap(MinHeap *heap);

int extractMin(MinHeap *heap);

int getMin(MinHeap *heap);

void deleteKey(MinHeap *heap, int i);
#ifdef __cplusplus
}
#endif
#endif  /* _MINHEAP_H */
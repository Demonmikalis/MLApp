/* Program to implement a MinHeap */
/* author : MR.Black */
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include"MinHeap.h"

MinHeap *NewHeap(int cap)
{
    MinHeap *mh = (MinHeap *)malloc(sizeof(MinHeap));
    mh->capacity = cap;
    mh->harr = (int*)malloc(sizeof(int)*cap);
    mh->heap_size = 0;
    return mh;
}

/* A utility function to swap two elements */
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

static int parent(int i) { return (i-1)/2; }

// to get index of left child of node at index i
static int left(int i) { return (2*i + 1); }

// to get index of right child of node at index i
int right(int i) { return (2*i + 2); }

/* Inserts a new key 'k'*/
void insertKey(MinHeap *heap, int key)
{
    
    if (heap->heap_size == heap->capacity)
    {
        //cout << "\nOverflow: Could not insertKey\n";
        printf("\nOverflow: Could not insertKey\n");
        return;
    }

    // First insert the new key at the end
    heap->heap_size++;
    int i = heap->heap_size - 1;
    heap->harr[i] = key;

    // Fix the min heap property if it is violated
    while (i != 0 && heap->harr[parent(i)] > heap->harr[i])
    {
       swap(&heap->harr[i], &heap->harr[parent(i)]);
       i = parent(i);
    }
}

// A recursive method to heapify a subtree with root at given index
// This method assumes that the subtrees are already heapified
void MinHeapify(MinHeap *heap, int i)
{
    int l,r,smallest;
    l = left(i);
    r = right(i);
    smallest = i;
    if (l < heap->heap_size && heap->harr[l] < heap->harr[i])
        smallest = l;
    if (r < heap->heap_size && heap->harr[r] < heap->harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&heap->harr[i], &heap->harr[smallest]);
        MinHeapify(heap,smallest);
    }
}


// Method to remove minimum element (or root) from min heap
int extractMin(MinHeap *heap)
{
    int root;
    if (heap->heap_size <= 0)
        return INT_MAX;
    if (heap->heap_size == 1)
    {
        heap->heap_size--;
        return heap->harr[0];
    }

    // Store the minimum value, and remove it from heap
    root = heap->harr[0];
    heap->harr[0] = heap->harr[heap->heap_size-1];
    heap->heap_size--;
    MinHeapify(heap,0);

    return root;
}


// Decreases value of key at index 'i' to new_val.  It is assumed that
// new_val is smaller than harr[i].
void decreaseKey(MinHeap *heap, int i, int new_val)
{
    heap->harr[i] = new_val;
    while (i != 0 && heap->harr[parent(i)] > heap->harr[i])
    {
       swap(&heap->harr[i], &heap->harr[parent(i)]);
       i = parent(i);
    }
}

// Returns the minimum key (key at root) from min heap
int getMin(MinHeap *heap) { return heap->harr[0]; }

// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void deleteKey(MinHeap *heap, int i)
{
    decreaseKey(heap,i, INT_MIN);
    extractMin(heap);
}

void deleteHeap(MinHeap *heap)
{
    free(heap->harr);
    free(heap);
}

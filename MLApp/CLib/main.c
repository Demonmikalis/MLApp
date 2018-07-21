/* Program to implement a unit tests for data structure */
/* author : MR.Black */

#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include <string.h>
#include "LinkList.h"
#include "MinHeap.h"
#include "HashMap.h"
#include "HashSet.h"
#include "HMem.h"
#include "HMath.h"
#include "MathInterf.h"
#include "Stack.h"

char* strs[10]=  
{  
    "abc",  
    "qq",  
    "hello",  
    "abc",  
    "lmy",  
    "ab",  
    "qq",  
    "lqw",  
    "sww",  
    "lqw"  
};  

typedef struct a  
{  
    int i;  
    char c;  
} A;  
  
void ppt(const void* const p)  
{  
    A* pp= (A*)p;  
    printf("%d(%c) ", pp->i, pp->c);  
}  

void test_queue()
{
    printf("------- test queue ------\n");
    /* Create a queue with items 1 2 3*/
    char* a[3] = {"asdf","def","zw"};
    struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    q->stack1 = NULL;
    q->stack2 = NULL;
    enQueue(q, a[0]);
    enQueue(q, a[1]);
    enQueue(q, a[2]);
    
    /* Dequeue items */
    printf("%s ", (char*)deQueue(q));
    printf("%s ", (char*)deQueue(q));
    printf("%s ", (char*)deQueue(q));
    printf("\n");
    free(q);
}

void test_MinHeap()
{
    printf("------- test MinHeap ------\n");
    MinHeap *h = NewHeap(11);
    int ans,ans2;
    insertKey(h,11);
    insertKey(h,2);
    deleteKey(h,1);
    insertKey(h,15);
    insertKey(h,5);
    insertKey(h,4);
    insertKey(h,45);
    ans = extractMin(h);
    ans2 = getMin(h);
    printf("%d,%d\n",ans,ans2);
    decreaseKey(h, 2, 1);
    ans2 = getMin(h);
    printf("%d\n",ans2);
    deleteHeap(h);
    // answer should be [2,4,1]
}

void test_linklist()
{
    printf("------- test linklist ------\n");
    const int S =10;  
  
    //create data
    A * data= malloc(sizeof(A)*S);  
    for (int i=0; i< S; i++)  
    {  
        data[i].i=i;  
        data[i].c=(char)('A'+0);  
    }  
  
	//create linklist
    LinkList * list= createLinkList();  
  
    // test insert  
    LinkListInsertDataAtLast( list, &data[0]);  
    LinkListInsertDataAtFirst( list, &data[4]);  
    LinkListInsertDataAt(list, &data[1], 1 );  
  
  
    // test search  
    int index = LinkListFindDataIndex(list, &data[2]);  
    printf("%d\n", index);  
    index = LinkListFindDataIndex(list, &data[4]);  
    printf("%d\n", index);  
  
    //print  
    LinkListOutput(list, ppt);  
    puts("");  
  
    //test print using iterator  
    LinkListIterator * it = createLinkListIterator(list);  
    while(LinkListIteratorHasNext(it))  
    {  
        A * pp = LinkListIteratorNext(it);  
        printf("%d[%c] ", pp->i, pp->c);  
    }  
    puts("");  
    //free iterator  
    freeLinkListIterator(it);  
  
    //free linklist  
    freeLinkList(list);  
  
    //free data  
    free(data);  
 
}


void test_hashmap()
{
	printf("------- test hashmap ------\n");
    int S = 10;
    int*  data = malloc(sizeof(int)* S);  
    for (int i=0; i<S; i++)  
    {  
        data[i]=i;  
    }  
  
    //create hashmap  
    HashMap * map = createHashMap(HashCodeString, EqualString);  
  
    //insert  
    for (int i=0; i<S; i++)  
    {  
        HashMapPutData(map, strs[i], &data[i]);  
    }  
  
    //dump the size 
    printf("size=%d\n",HashMapGetSize(map));  
  
    //test remove  
    HashMapRemoveDataByKey(map,"qq");  
    HashMapRemoveDataByKey(map,"ab");  
    HashMapRemoveDataByKey(map,"qwert");  
  
    //dump the size 
    printf("after remove size=%d\n",HashMapGetSize(map));  
  
    //iterator
    HashMapEntryIterator * it = createHashMapEntryIterator(map);  
    while(HashMapEntryIteratorHasNext(it))  
    {  
        Entry * pp= HashMapEntryIteratorNext(it);  
        char * key = pp-> key;  
        int * value = pp->value;  
        printf("%s(%d)\n", key, *value);  
    }  
    //free iterator  
    freeHashMapEntryIterator(it);  
  
    //free hashmap  
    freeHashMap(map);  
  
    //free data  
    free(data);   
}


void test_hashset()
{
    printf("------- test hashset ------\n");
    int S = 10;
    //create hashset  
    HashSet * set = createHashSet(HashCodeString, EqualString);  
  
    //insert  
    for (int i=0; i<S; i++)  
    {  
        HashSetAddData(set, strs[i]);  
    }  
  
    //dump size  
    printf("size=%d\n",HashSetGetSize(set));  
  
    //test remove  
    HashSetRemoveData(set,"qq");  
    HashSetRemoveData(set,"ab");  
    HashSetRemoveData(set,"qwert");  
  
    //dump size  
    printf("after remove size=%d\n",HashSetGetSize(set));  
  
    //iterator  
    HashSetIterator * it = createHashSetIterator(set);  
    while(HashSetIteratorHasNext(it))  
    {  
        char * pp= HashSetIteratorNext(it);  
        puts(pp);  
    }  
    //release  
    freeHashSetIterator(it);  
  
    //release  
    freeHashSet(set);  
}

void test_HMath()
{
    printf("------- test math ------\n");
    CreateHeap(&gstack, "Global Stack",  MSTAK, 1, 0.0, 100000, ULONG_MAX );
    // test vector
    DVector vv; DMatrix m,m_inv,m_res;
    int n1 = 3;
    int n = 10; int i,j;
    vv = CreateDVector(&gstack,n);
    for(i=1;i<=n;++i) vv[i]=i;
    ShowDVector("vv",vv,n);
    
    FreeDVector(&gstack,vv);
    // test matrix invert
    m = CreateDMatrix(&gstack,n1,n1);
    //ZeroDMatrix(m);
    m_inv = CreateDMatrix(&gstack,n1,n1);
    double mm[3][3] = {{1.0,2.0,3.0},{3.0,1.0,2.0},{1.0,3.0,2.0}};
    
    for(i=1;i<=n1;i++)
    {
        for(j=1;j<=n1;j++)
        {
            m[i][j] = mm[i-1][j-1];
        }
    }
    
    DMatInvert(m,m_inv);
    ShowDMatrix("m_inv",m_inv,n1,n1);
    
    m_res = CreateDMatrix(&gstack,n1,n1);
    Dmat_mul(m,m_inv,m_res);
    ShowDMatrix("m_res",m_res,n1,n1);
    
    FreeDMatrix(&gstack,m_res);
    FreeDMatrix(&gstack,m_inv);
    FreeDMatrix(&gstack,m);
    
    // test matrix mul
    DMatrix m1,m2,m3;
    m1 = CreateDMatrix(&gstack,3,2);
    m2 = CreateDMatrix(&gstack,2,3);
    m3 = CreateDMatrix(&gstack,3,3);
    
    double m1_arr[][2] = {{1,2},{1,3},{2,3}};
    double m2_arr[][3] = {{1,2,3},{1,3,2}};
    // copy data m1
    for(i=1;i<=NumDRows(m1);i++)
    {
        for(j=1;j<=NumDCols(m1);j++)
        {
            m1[i][j] = m1_arr[i-1][j-1];
        }
    }
    // copy data m2
    for(i=1;i<=NumDRows(m2);i++)
    {
        for(j=1;j<=NumDCols(m2);j++)
        {
            m2[i][j] = m2_arr[i-1][j-1];
        }
    }
    // mat_mul
    Dmat_mul(m1,m2,m3);
    ShowDMatrix("m3",m3,3,3);
    // mat mul val
    Dmat_mul_val(m3,2.0,m3);
    ShowDMatrix("m3",m3,3,3);
    // transpose
    //m4 = CreateDMatrix(&gstack,3,3);
    Dmat_T(m3,m3);
    ShowDMatrix("m3T",m3,3,3);
    // release
    FreeDMatrix(&gstack,m3);
    FreeDMatrix(&gstack,m2);
    FreeDMatrix(&gstack,m1);
    ResetHeap(&gstack);
    DeleteHeap(&gstack);
    
}

void test_stack()
{
    /* Create a queue with items 1 2 3*/
    printf("------- test stack ------\n");
    int a[] = {1,2,3,4,5};
    Stack *s = (Stack*)malloc(sizeof(struct Stack));
    int sz = 0;
    StackPush(&s,&a[1],&sz);
    StackPush(&s,&a[2],&sz);
    StackPush(&s,&a[3],&sz);
    StackPush(&s,&a[4],&sz);
    /* Dequeue items */
    printf("%d ", *(int*)StackPop(&s,&sz));
    printf("%d ", *(int*)StackPop(&s,&sz));
    printf("%d ", *(int*)StackPop(&s,&sz));
    printf("size = %d\n",sz);
    StackFree(&s,sz);
    free(s);
}

void unit_test()
{
    
    test_MinHeap();
    test_linklist();
    test_hashmap();
    test_queue();
    test_hashset();
    test_HMath();
    test_stack();
}

int main()
{
    test_HMath();
    return 0;
}

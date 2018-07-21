/* Program to implement stack */
/* author : MR.Black */
#include<stdio.h>
#include<stdlib.h>
#include"Stack.h"

/* Function to push an item to stack*/
void StackPush(struct Stack** top_ref, void* new_data,int *size)
{
    /* allocate node */
    struct Stack* new_node =
        (struct Stack*) malloc(sizeof(struct Stack));
    
    if(new_node == NULL)
    {
        printf("Stack overflow \n");
        getchar();
        exit(0);
        
    }

    /* put in the data */
    new_node->data = new_data;

    /* link the old list off the new node */
    new_node->next = (*top_ref);

    /* move the head to point to the new node */
    (*top_ref) = new_node;
    (*size)+=1;
}


/* Function to pop an item from stack*/
void* StackPop(struct Stack** top_ref,int *size)
{
    void* res;
    struct Stack *top;
    
    if(*size==0)
    {
        printf("Stack is empty \n");
        return;
    }
    
    /*If stack is empty then error */
    if(*top_ref == NULL)
    {
        printf("Stack overflow \n");
        getchar();
        exit(0);
        
    }
    else
    {
        (*size)-=1;
        top = *top_ref;
        res = top->data;
        *top_ref = top->next;
        free(top);
        return res;
    }
}

/* Get the top element */
void* StackTop(struct Stack* s)
{
    void *res;
    if(s==NULL)
        return NULL;
    res = s->data;
    return res;
}

/* release stack */
void StackFree(struct Stack** top_ref, int size)
{
   int i; int sz;
   sz = size;
   for(i=0;i<sz;++i)
   {
       StackPop(top_ref,&size);
	   //free(data);
   }
}

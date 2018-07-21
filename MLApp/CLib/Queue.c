/* Program to implement a queue using two stacks */
/* author : MR.Black */
#include<stdio.h>
#include<stdlib.h>
#include"Queue.h"

/* Function to push an item to stack*/
static void push(struct sNode** top_ref, void* new_data);

/* Function to pop an item from stack*/
static void* pop(struct sNode** top_ref);

/* Function to enqueue an item to queue */
void enQueue(struct queue *q, void* x)
{
    push(&q->stack1, x);
}

/* Function to dequeue an item from queue */
void* deQueue(struct queue *q)
{
    void* x;
    /* If both stacks are empty then error */
    if(q->stack1 == NULL && q->stack2 == NULL)
    {
        printf("Q is empty");
        getchar();
        exit(0);
    }

    /* Move elements from satck1 to stack 2 only if
    stack2 is empty */
    if(q->stack2 == NULL)
    {
        while(q->stack1 != NULL)
        {
            x = pop(&q->stack1);
            push(&q->stack2, x);
            
        }
    }

    x = pop(&q->stack2);
    return x;
}

/* Function to push an item to stack*/
void push(struct sNode** top_ref, void* new_data)
{
    /* allocate node */
    struct sNode* new_node =
        (struct sNode*) malloc(sizeof(struct sNode));
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
}

/* Function to pop an item from stack*/
void* pop(struct sNode** top_ref)
{
    void* res;
    struct sNode *top;
    
    /*If stack is empty then error */
    if(*top_ref == NULL)
    {
        printf("Stack overflow \n");
        getchar();
        exit(0);
        
    }
    else
    {
        top = *top_ref;
        res = top->data;
        *top_ref = top->next;
        free(top);
        return res;
        
    }
}

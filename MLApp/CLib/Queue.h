#ifndef _QUEUE_H
#define _QUEUE_H
#ifdef __cplusplus
extern "C" {
#endif

/* structure of a stack node */
typedef struct sNode
{
    void* data;
    struct sNode *next;
}sNode;

/* structure of queue having two stacks */
typedef struct queue
{
    struct sNode *stack1;
    struct sNode *stack2;
}queue;

/* Function to enqueue an item to queue */
void enQueue(struct queue *q, void* x);

/* Function to dequeue an item from queue */
void* deQueue(struct queue *q);
    

#ifdef __cplusplus
}
#endif
#endif  /* _QUEUE_H */

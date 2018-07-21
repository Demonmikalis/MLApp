#ifndef _STACK_H
#define _STACK_H
#ifdef __cplusplus
extern "C" {
#endif


/* structure of a stack node */
typedef struct Stack
{
    void* data;
    struct Stack *next;
}Stack;

/* Function to push an item to stack*/
void StackPush(struct Stack** top_ref, void* new_data, int *size);

/* Function to pop an item from stack*/
void* StackPop(struct Stack** top_ref, int *size);

/* Get the top element */
void* StackTop(struct Stack* s);

/* release stack */
void StackFree(struct Stack** top_ref,int size);

#ifdef __cplusplus
}
#endif
#endif  /* _STACK_H */

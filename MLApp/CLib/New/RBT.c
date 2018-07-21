#include <stdio.h>
#include <string.h>
#include <stdlib.h>
static int counter = 0;
enum Color {RED, BLACK};
/* ------------------------------ Queue ------------------------------ */
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

/* Function to push an item to stack*/
static void push(struct sNode** top_ref, void* new_data)
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
static void* pop(struct sNode** top_ref)
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

int isEmpty(struct queue *q)
{
	 if(q->stack1 == NULL && q->stack2 == NULL)
	 {
		 return 1;
	 }
	 return 0;
}

/* ------------------------------ Red Black Tree ------------------------------ */

typedef struct Node
{
    int data;
    int color;
    struct Node *left, *right, *parent;
}Node;

Node* new_node(int data)
{
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->color = RED;
	node->left = NULL; node->right=NULL;
	node->parent=NULL;
	return node;
}

// A recursive function to do level order traversal
void inorderHelper(Node *root)
{
    if (root == NULL)
        return;
 
    inorderHelper(root->left);
    //cout << root->data << "  ";
    printf("%d ",root->data);
    inorderHelper(root->right);
}

/* A utility function to insert a new node with given key
   in BST */
Node* BSTInsert(Node* root, Node *pt)
{
    /* If the tree is empty, return a new node */
    if (root == NULL)
       return pt;
 
    /* Otherwise, recur down the tree */
    if (pt->data < root->data)
    {
        root->left  = BSTInsert(root->left, pt);
        root->left->parent = root;
    }
    else if (pt->data > root->data)
    {
        root->right = BSTInsert(root->right, pt);
        root->right->parent = root;
    }
 
    /* return the (unchanged) node pointer */
    return root;
}

// Utility function to do level order traversal
void levelOrderHelper(Node *root)
{
	if (root == NULL)
        return;
    queue *que = (queue *)malloc(sizeof(queue));
    que->stack1=NULL; que->stack2=NULL;
    enQueue(que,root);
    while(!isEmpty(que))
    {
		Node *tmp = (Node*) deQueue(que);
		printf("%d ",tmp->data);
		if(tmp->left!=NULL)
		{
			enQueue(que,tmp->left);
		}
		if(tmp->right!=NULL)
		{
			enQueue(que,tmp->right);
		}
	}
	printf("\n");
    free(que);
}


void RBTreeRotateLeft(Node **root, Node **pt)
{
	Node *pt_right = (*pt)->right;
 
    (*pt)->right = pt_right->left;
 
    if ((*pt)->right != NULL)
        (*pt)->right->parent = (*pt);
 
    pt_right->parent = (*pt)->parent;
 
    if ((*pt)->parent == NULL)
        *root = pt_right;
 
    else if ((*pt) == (*pt)->parent->left)
        (*pt)->parent->left = pt_right;
 
    else
        (*pt)->parent->right = pt_right;
 
    pt_right->left = (*pt);
    (*pt)->parent = pt_right;
}

void RBTreeRotateRight(Node **root, Node **pt)
{
	Node *pt_left = (*pt)->left;
	(*pt)->left = pt_left->right;
 
    if ((*pt)->left != NULL)
        (*pt)->left->parent = *pt;
 
    pt_left->parent = (*pt)->parent;
 
    if ((*pt)->parent == NULL)
        *root = pt_left;
 
    else if (*pt == (*pt)->parent->left)
        (*pt)->parent->left = pt_left;
 
    else
        (*pt)->parent->right = pt_left;
 
    pt_left->right = *pt;
    (*pt)->parent = pt_left;
}

static void swap(int *a, int *b)
{
	int tmp = *b;
	*b = *a;
	*a = tmp;
}
 
// This function fixes violations caused by BST insertion
void RBTreeFixViolation(Node **root, Node **pt)
{
    Node *parent_pt = NULL;
    Node *grand_parent_pt = NULL;
 
    while (((*pt) != (*root)) && ((*pt)->color != BLACK) &&
           ((*pt)->parent->color == RED))
    {
 
        parent_pt = (*pt)->parent;
        grand_parent_pt = (*pt)->parent->parent;
        /*  Case : A
            Parent of pt is left child of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->left)
        {
			
            Node *uncle_pt = grand_parent_pt->right;
 
            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color == RED)
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                *pt = grand_parent_pt;
            }
 
            else
            {
                /* Case : 2
                   pt is right child of its parent
                   Left-rotation required */
                if (*pt == parent_pt->right)
                {
                    RBTreeRotateLeft(root, &parent_pt);
                    *pt = parent_pt;
                    parent_pt = (*pt)->parent;
                }
 
                /* Case : 3
                   pt is left child of its parent
                   Right-rotation required */
                RBTreeRotateRight(root, &grand_parent_pt);
                swap(&(parent_pt->color), &(grand_parent_pt->color));
                *pt = parent_pt;
            }
        }
 
        /* Case : B
           Parent of pt is right child of Grand-parent of pt */
        else
        {
            Node *uncle_pt = grand_parent_pt->left;
 
            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color == RED))
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                *pt = grand_parent_pt;
            }
            else
            {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (*pt == parent_pt->left)
                {
                    RBTreeRotateRight(root, &parent_pt);
                    *pt = parent_pt;
                    parent_pt = (*pt)->parent;
                }
 
                /* Case : 3
                   pt is right child of its parent
                   Left-rotation required */
                RBTreeRotateLeft(root, &grand_parent_pt);
                swap(&(parent_pt->color), &(grand_parent_pt->color));
                *pt = parent_pt;
            }
        }
    }
 
    (*root)->color = BLACK;
}


void RBTreeInsert(Node **root, int data)
{
	counter++;
	Node *pt = new_node(data);
	*root = BSTInsert(*root,pt);
	RBTreeFixViolation(root, &pt);
}

int main(int argc, char *argv[])
{
	printf("hello\n");
	Node *root=NULL;
	RBTreeInsert(&root,7);
	RBTreeInsert(&root,6);
	RBTreeInsert(&root,5);
	RBTreeInsert(&root,4);
	RBTreeInsert(&root,3);
	RBTreeInsert(&root,2);
	RBTreeInsert(&root,1);
	inorderHelper(root);
	printf("\n");
	levelOrderHelper(root);
	printf("\n");
	
	Node *root2=NULL;
	RBTreeInsert(&root2,10);
	RBTreeInsert(&root2,20);
	RBTreeInsert(&root2,30);
	RBTreeInsert(&root2,15);
	inorderHelper(root2);
	printf("\n");
	levelOrderHelper(root2);
	printf("\n");
	return 0;
}

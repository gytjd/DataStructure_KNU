#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 8
#define MAX_COL 10
#define INF 9999

typedef struct node* nodePointer;
typedef struct node {
    int data;
    nodePointer leftChild;
    nodePointer rightChild;
}node;

typedef struct stackNode {
    nodePointer data;
    struct stackNode* link;
}stackNode;

typedef struct stackType {
    stackNode* top;
}stackType;

typedef struct queueNode {
    nodePointer data;
    struct queueNode* link;
}queueNode;

typedef struct queueType {
    queueNode* front;
    queueNode* rear;
}queueType;

nodePointer root;
int winTree[16];

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_stack(stackType* s)
{
    s->top = NULL;
}

int is_stack_empty(stackType* s)
{
    return s->top == NULL;
}

void push(stackType* s, nodePointer data)
{
    stackNode* new_node = (stackNode*)malloc(sizeof(stackNode));
    new_node->data = data;
    new_node->link = NULL;

    if (is_stack_empty(s))
    {
        s->top = new_node;
    }
    else
    {
        new_node->link = s->top;
        s->top = new_node;
    }
}

nodePointer pop(stackType* s)
{
    stackNode* removed = s->top;
    nodePointer data = removed->data;

    s->top = removed->link;
    free(removed);

    return data;
}

void init_queue(queueType* q)
{
    q->front = NULL;
    q->rear = NULL;
}

int is_queue_empty(queueType* q)
{
    return q->rear == NULL && q->front == NULL;
}

void enqueue(queueType* q, nodePointer data)
{
    queueNode* new_node = (queueNode*)malloc(sizeof(queueNode));
    new_node->data = data;
    new_node->link = NULL;

    if (is_queue_empty(q))
    {
        q->front = new_node;
        q->rear = new_node;
    }
    else
    {
        q->rear->link = new_node;
        q->rear = new_node;
    }
}

nodePointer dequeue(queueType* q)
{
    queueNode* removed = q->front;
    nodePointer data = removed->data;

    q->front = removed->link;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(removed);

    return data;
}

nodePointer peek(queueType* q)
{
    return q->front->data;
}

void display(int** mat, int row, int col)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}



nodePointer create_node(int data, nodePointer left, nodePointer right)
{
    nodePointer new_node = (nodePointer)malloc(sizeof(node));
    new_node->data = data;
    new_node->leftChild = left;
    new_node->rightChild = right;

    return new_node;
}


nodePointer set_initTree(nodePointer* q, int n)
{
    int i;
    stackType s;
    init_stack(&s);

    nodePointer op1, op2;

    nodePointer tempA, tempB;

    for (i = 0; i < n; i += 2)
    {
        if (q[i]->data > q[i + 1]->data)
        {
            push(&s, create_node(q[i + 1]->data, q[i], q[i + 1]));
        }
        else
        {
            push(&s, create_node(q[i]->data, q[i], q[i + 1]));
        }
    }

    op2 = pop(&s);
    op1 = pop(&s);

    if (op1->data > op2->data)
    {
        tempB = create_node(op2->data, op1, op2);
    }
    else
    {
        tempB = create_node(op1->data, op1, op2);
    }

    op2 = pop(&s);
    op1 = pop(&s);

    if (op1->data > op2->data)
    {
        tempA = create_node(op2->data, op1, op2);
    }
    else
    {
        tempA = create_node(op1->data, op1, op2);
    }


    if (tempA->data > tempB->data)
    {
        push(&s, create_node(tempB->data, tempA, tempB));
    }
    else
    {
        push(&s, create_node(tempA->data, tempA, tempB));
    }

    return pop(&s);
}

void level_order(nodePointer root)
{
    int i = 0;
    queueType q;
    init_queue(&q);


    enqueue(&q, root);

    while (!is_queue_empty(&q))
    {
        root = dequeue(&q);
        winTree[++i] = root->data;
        printf("%d ", root->data);

        if (root->leftChild != NULL)
        {
            enqueue(&q, root->leftChild);
        }

        if (root->rightChild != NULL)
        {
            enqueue(&q, root->rightChild);
        }
    }
}

int delete_node(queueType* queue)
{
    int i;
    int q, w;
    int item = winTree[1];
    nodePointer temp;

    for (i = 8; i <= 15; i++)
    {
        if (item == winTree[i])
        {
            break;
        }
    }

    if (is_queue_empty(&queue[i - 8]))
    {

        winTree[i] = INF;
    }
    else
    {
        temp = dequeue(&queue[i - 8]);
        winTree[i] = temp->data;
    }


    int child = i;
    int parent = i / 2;



    while (child != 1)
    {
        if (child % 2 == 0)
        {
            if (winTree[child] > winTree[child + 1])
            {
                child++;
            }

            winTree[parent] = winTree[child];
        }
        else
        {
            if (winTree[child] > winTree[child - 1])
            {
                child--;
            }

            winTree[parent] = winTree[child];
        }
        child = parent;
        parent = child / 2;

    }

    return item;
}


int main()
{
    int i, j;

    FILE* fa;
    fa = fopen("input.txt", "r");

    int data;
    nodePointer initial[MAX_ROW];
    queueType queue[MAX_ROW];

    for (i = 0; i < MAX_ROW; i++)
    {
        init_queue(&queue[i]);
    }



    printf("<<<<<<<<<<< run data >>>>>>>>>>>>\n\n");
    for (i = 0; i < MAX_ROW; i++)
    {
        printf("%d-th run:\n", i + 1);

        for (j = 0; j < MAX_COL; j++)
        {
            fscanf(fa, "%3d ", &data);
            enqueue(&queue[i], create_node(data, NULL, NULL));
            printf("%3d ", data);
        }
        printf("\n");
    }

    for (i = 0; i < MAX_ROW; i++)
    {
        initial[i] = dequeue(&queue[i]);
    }

    root = set_initTree(initial, MAX_ROW);
    printf("\nLevel-order traversal for initial min-winner tree\n");
    level_order(root);
    printf("\n\n");

    printf("sorting with min-winner tree...\n");
    printf("\nsorted result\n");
    for (i = 0; i < MAX_COL; i++)
    {
        for (j = 0; j < MAX_ROW; j++)
        {
            printf("%3d ", delete_node(queue));
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}


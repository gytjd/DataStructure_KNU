
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100
#define INF 9999

typedef struct node* nodePointer;
typedef struct node {
    int data;
    nodePointer leftChild;
    nodePointer rightChild;
}node;

nodePointer root;

nodePointer stack[MAX_STACK_SIZE];
nodePointer queue[MAX_QUEUE_SIZE];

int top = -1;

int front = -1;
int rear = -1;

int winTree[16];

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_stack(void)
{
    top = -1;
}

int is_stack_empty(void)
{
    return top == -1;
}

int is_stack_full(void)
{
    return (top == MAX_STACK_SIZE - 1);
}

void push(nodePointer data)
{
    if (is_stack_full())
    {
        error("스택이 꽉 차있습니다.");
    }
    stack[++top] = data;
}

nodePointer pop(void)
{
    if (is_stack_empty())
    {
        return NULL;
    }
    return stack[top--];
}



void init_queue(void)
{
    front = -1;
    rear = -1;
}

int is_queue_empty(void)
{
    return front == rear;
}

int is_queue_full(void)
{
    return rear == MAX_QUEUE_SIZE - 1;
}

void enqueue(nodePointer data)
{
    if (is_queue_full())
    {
        error("큐가 꽉 차있습니다.");
    }
    queue[++rear] = data;
}

nodePointer dequeue(void)
{
    if (is_queue_empty())
    {
        error("큐가 비어있습니다.");
    }
    return queue[++front];
}


nodePointer create_node(int data, nodePointer left, nodePointer right)
{
    nodePointer new_node = (nodePointer)malloc(sizeof(node));
    new_node->data = data;
    new_node->leftChild = left;
    new_node->rightChild = right;

    return new_node;
}

nodePointer make_initial_winnerTree(nodePointer* q, int n)
{
    int i;

    nodePointer op1, op2;

    nodePointer tempA, tempB;

    for (i = 0; i < n; i += 2)
    {
        if (q[i]->data > q[i + 1]->data)
        {
            push(create_node(q[i + 1]->data, q[i], q[i + 1]));
        }
        else
        {
            push(create_node(q[i]->data, q[i], q[i + 1]));
        }
    }

    op2 = pop();
    op1 = pop();

    if (op1->data > op2->data)
    {
        tempB = create_node(op2->data, op1, op2);
    }
    else
    {
        tempB = create_node(op1->data, op1, op2);
    }

    op2 = pop();
    op1 = pop();

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
        push(create_node(tempB->data, tempA, tempB));
    }
    else
    {
        push(create_node(tempA->data, tempA, tempB));
    }

    return pop();
}

void inorder_my(nodePointer root)
{
    if (root)
    {
        inorder_my(root->leftChild);
        printf("%d ", root->data);
        inorder_my(root->rightChild);
    }
}

void set_winnerTree(nodePointer root)
{

    int i = 0;

    enqueue(root);

    while (!is_queue_empty())
    {
        root = dequeue();

        winTree[++i] = root->data;

        if (root->leftChild != NULL)
        {
            enqueue(root->leftChild);
        }

        if (root->rightChild != NULL)
        {
            enqueue(root->rightChild);
        }
    }
}

int delete_node(void)
{
    int i;
    int item = winTree[1];

    for (i = 8; i <= 15; i++)
    {
        if (item == winTree[i])
        {
            break;
        }
    }

    winTree[i] = INF;

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

void display(int n)
{
    int i;
    for (i = 1; i <= (2 * n) - 1; i++)
    {
        printf("%d ", winTree[i]);
    }
    printf("\n");
}
int main()
{
    int i;
    int data;
    int n, seed;

    nodePointer initial[MAX_SIZE];
    int result[MAX_SIZE];

    printf("<<<<<<<<<<< sorting with winner >>>>>>>>>>\n");
    printf("the number of keys ( 4, 8, 16, or 32 as a power of 2 ) >> ");
    scanf("%d", &n);

    printf("\nvalue of seed >> ");
    scanf("%d", &seed);

    srand(seed);

    for (i = 0; i < n; i++)
    {
        data = rand() % 500 + 1;
        initial[i] = create_node(data, NULL, NULL);
        printf("%d ", data);
    }

    printf("\n\ninitialization of min_winner tree\n\n");
    root = make_initial_winnerTree(initial, n);
    set_winnerTree(root);

    printf("inorder traversal for min-winner tree\n");
    display(n);

    for (i = 0; i < 8; i++)
    {
        result[i] = delete_node();
        if (i == 1)
        {
            printf("Winner Tree inorder traversal after find 2 winners\n\n");
            display(n);
        }
    }

    printf("\n\nsorting with min-winner tree...\n");
    printf("\nsorted result\n");
    for (i = 0; i < 8; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");


    return 0;
}


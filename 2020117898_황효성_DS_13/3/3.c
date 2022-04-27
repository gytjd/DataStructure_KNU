#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100
#define MAX_STACK_SIZE 100

typedef struct node* treePointer;
typedef struct node {
	char data;
	treePointer leftChild;
	treePointer rightChild;
	int visited;
}node;

treePointer root = NULL;
treePointer queue[MAX_QUEUE_SIZE];
treePointer stack[MAX_STACK_SIZE];

int front;
int rear;

int top = -1;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue()
{
	front = -1;
	rear = -1;
}

int is_queue_empty()
{
	return front == rear;
}

int is_queue_full()
{
	return rear == MAX_QUEUE_SIZE - 1;
}

void init_stack()
{
	top = -1;
}

int is_stack_empty()
{
	return top == -1;
}

int is_stack_full()
{
	return top == MAX_STACK_SIZE - 1;
}

treePointer createNode(char data, treePointer left, treePointer right)
{
	treePointer new_node = (treePointer)malloc(sizeof(node));
	new_node->data = data;
	new_node->leftChild = left;
	new_node->rightChild = right;
	new_node->visited = 0;

	return new_node;
}

void enqueue(treePointer data)
{
	if (is_queue_full())
	{
		error("큐가 가득찼습니다.");
	}
	queue[++rear] = data;
}

treePointer dequeue()
{
	if (is_queue_empty())
	{
		error("큐가 비어있습니다.");
	}
	return queue[++front];
}

treePointer get_front()
{
	int temp = front + 1;
	return queue[temp];
}

void push(treePointer data)
{
	if (is_stack_full())
	{
		error("스택이 가득찼습니다. ");
	}
	stack[++top] = data;
}

treePointer pop()
{
	if (is_stack_empty())
	{
		return NULL;
	}

	return stack[top--];
}
void insert(treePointer* pRoot, treePointer pNode)
{
	treePointer temp;

	if ((*pRoot) == NULL)
	{
		(*pRoot) = pNode;
	}
	else
	{
		temp = get_front();

		if (temp->leftChild == NULL)
		{
			temp->leftChild = pNode;
		}
		else if (temp->rightChild == NULL)
		{
			temp->rightChild = pNode;
			dequeue();
		}
	}
	enqueue(pNode);
}

void preorder_iter(treePointer root)
{
	init_stack();
	int count = 0;

	while (1)
	{
		for (;root;root = root->leftChild)
		{
			printf("%c", root->data);
			push(root);
			count++;
		}
		root = pop();

		if (root == NULL)
		{
			break;
		}

		root = root->rightChild;
	}

	printf("\npush_cnt = %d\n", count);
}

void postorder_iter(treePointer root)
{
	init_stack();
	int count = 0;




	while (1)
	{
		while (root != NULL && root->visited != 1)
		{
			push(root);
			count++;
			root = root->leftChild;
		}

		root = pop();

		if (root == NULL)
		{
			break;
		}

		if (root->rightChild != NULL)
		{
			if (root->rightChild->visited == 1)
			{
				printf("%c", root->data);
				root->visited = 1;
				root = NULL;
			}
			else
			{
				push(root);

				count++;
				root = root->rightChild;
			}
		}
		else
		{
			printf("%c", root->data);
			root->visited = 1;
			root = NULL;
		}
	}

	printf("\npush_cnt = %d\n", count);
}


int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	char data;
	treePointer op1;
	treePointer op2;

	printf("the length of input string should be less than 80\n");
	printf("input string (postifx expression) : ");

	while (fscanf(fa, "%c", &data) != EOF)
	{
		printf("%c", data);
		if (data == '+' || data == '-' || data == '*' || data == '/' || data == '%')
		{
			op2 = pop();
			op1 = pop();

			switch (data)
			{
			case '+':
				push(createNode(data, op1, op2));
				break;
			case '-':
				push(createNode(data, op1, op2));
				break;
			case '*':
				push(createNode(data, op1, op2));
				break;
			case '/':
				push(createNode(data, op1, op2));
				break;
			case '%':
				push(createNode(data, op1, op2));
				break;

			}
		}
		else
		{
			push(createNode(data, NULL, NULL));
		}
	}
	root = pop();

	printf("\ncreating its binary tree\n\n");

	printf("iterative preorder traversal   : ");
	preorder_iter(root);
	printf("\n");

	printf("iterative postorder traversal  : ");
	postorder_iter(root);
	printf("\n");
	return 0;
}
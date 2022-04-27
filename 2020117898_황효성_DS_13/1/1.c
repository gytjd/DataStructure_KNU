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
}node;

treePointer root=NULL;
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


int is_stack_empty()
{
	return top == -1;
}

int is_stack_full()
{
	return top == MAX_STACK_SIZE - 1;
}

treePointer createNode(char data,treePointer left,treePointer right)
{
	treePointer new_node = (treePointer)malloc(sizeof(node));
	new_node->data = data;
	new_node->leftChild = left;
	new_node->rightChild = right;

	return new_node;
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
		error("스택이 비어있습니다. ");
	}

	return stack[top--];
}

void inorder_my(treePointer root)
{
	if (root)
	{
		inorder_my(root->leftChild);
		printf("%c ", root->data);
		inorder_my(root->rightChild);
	}
}

void preorder_my(treePointer root)
{
	if (root)
	{
		printf("%c ", root->data);
		preorder_my(root->leftChild);
		preorder_my(root->rightChild);
	}
}

void postorder_my(treePointer root)
{
	if (root)
	{
		postorder_my(root->leftChild);
		postorder_my(root->rightChild);
		printf("%c ", root->data);
	}
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

	printf("inorder traversal   : ");
	inorder_my(root);
	printf("\n");

	printf("preorder traversal  : ");
	preorder_my(root);
	printf("\n");

	printf("postorder traversal : ");
	postorder_my(root);
	printf("\n");

	return 0;
}
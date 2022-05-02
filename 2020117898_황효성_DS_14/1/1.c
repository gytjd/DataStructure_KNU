#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0


typedef struct node* nodePointer;
typedef struct node {
	char data;
	int eval;
	nodePointer leftChild;
	nodePointer rightChild;
}node;

nodePointer root = NULL;
nodePointer stack[MAX_STACK_SIZE];
int top;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
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

void push(nodePointer data)
{
	if (is_stack_full())
	{
		error("스택이 꽉 차있습니다.");
	}
	stack[++top] = data;
}

nodePointer pop()
{
	if (is_stack_empty())
	{
		error("스택이 비어있습니다.");
	}
	return stack[top--];
}

nodePointer create_node(char data,nodePointer left,nodePointer right)
{
	nodePointer new_node = (nodePointer)malloc(sizeof(node));
	new_node->data = data;
	new_node->eval = 1;
	new_node->leftChild = left;
	new_node->rightChild = right;

	return new_node;
}

void postOrderEval(nodePointer node,int i,int j,int k)
{
	if (node) {

		postOrderEval(node->leftChild, i, j, k);
		postOrderEval(node->rightChild, i, j, k);

		switch (node->data)
		{
		case '~':
			node->eval = !(node->rightChild->eval);
			break;
		case '&':
			node->eval = (node->rightChild->eval) && (node->leftChild->eval);
			break;
		case '|':
			node->eval = (node->rightChild->eval) || (node->leftChild->eval);
			break;

		default:
			if (node->data == 'a')
			{
				node->eval = i;
			}
			else if (node->data == 'b')
			{
				node->eval = j;
			}
			else
			{
				node->eval = k;
			}
			break;
		}
	}
}

int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	init_stack();
	nodePointer op1, op2;

	int i, j, k;

	char data;
	printf("input string(postfix)    : ");


	while (fscanf(fa, "%c", &data) != EOF)
	{
		printf("%c", data);
		if (data == '&')
		{
			op2 = pop();
			op1 = pop();

			push(create_node(data,op1, op2));
		}
		else if (data == '|')
		{
			op2 = pop();
			op1 = pop();

			push(create_node(data,op1, op2));
		}
		else if (data == '~')
		{
			op1 = pop();
			push(create_node(data,NULL, op1));
		}
		else
		{
			push(create_node(data,NULL, NULL));
		}
	}
	printf("\n");
	root = pop();

	printf("find true condition\n");

	for (i = 0;i < 2;i++)
	{
		for (j = 0;j < 2;j++)
		{
			for (k = 0;k < 2;k++)
			{
				postOrderEval(root, i, j, k);

				if (root->eval)
				{
					printf("a=%d, b=%d, c=%d\n", i, j, k);
				}
			}
		}
	}


	return 0;
}
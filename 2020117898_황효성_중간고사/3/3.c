#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 80

typedef struct stackNode {
	int data;
	struct stackNode* link;
}stackNode;

typedef struct stackType {
	stackNode* top;
}stackType;

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

void push(stackType* s, int data)
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

int pop(stackType* s)
{
	stackNode* removed = s->top;
	int data = removed->data;
	s->top = removed->link;

	free(removed);

	return data;
}

int calculate_postfix(char* pa)
{
	int i, n;
	n = strlen(pa);

	char ch;
	int value;
	int op1, op2;

	stackType s;
	init_stack(&s);

	printf("postfix expression : %s\n", pa);
	for (i = 0;i < n;i++)
	{
		ch = pa[i];

		if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
		{
			op2 = pop(&s);
			printf("pop : %d\n", op2);
			op1 = pop(&s);
			printf("pop : %d\n", op1);

			switch (ch)
			{
			case '+':
				push(&s, op1 + op2);
				printf("push : %d (%d + %d)\n",op1+op2, op1, op2);
				break;
			case '-':
				push(&s, op1 - op2);
				printf("push : %d (%d - %d)\n",op1-op2, op1, op2);
				break;
			case '*':
				push(&s, op1 * op2);
				printf("push : %d (%d * %d)\n",op1*op2, op1, op2);
				break;
			case '/':
				push(&s, op1 / op2);
				printf("push : %d (%d / %d)\n",op1/op2, op1, op2);
				break;
			case '%':

				push(&s, op1 % op2);
				printf("push : %d (%d %% %d)\n", op1%op2,op1, op2);
				break;
			}
		}
		else
		{
			value = pa[i] - '0';
			printf("push : %d\n", value);
			push(&s, value);
		}
	}

	return pop(&s);

}
int main()
{
	FILE* fa;
	fa = fopen("input3.txt", "r");

	char line[MAX_SIZE];
	fgets(line, MAX_SIZE, fa);

	printf("\n계산 결과 : %d\n", calculate_postfix(line));

	return 0;
}
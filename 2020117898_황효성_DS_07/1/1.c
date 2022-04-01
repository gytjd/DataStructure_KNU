#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_NOT_SIZE 100

char stack[MAX_STACK_SIZE];
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
	return top == (MAX_STACK_SIZE - 1);
}

void push(char* s, char data)
{
	if (is_stack_full())
	{
		error("스택이 꽉 차있습니다.");
	}

	s[++top] = data;
}

char pop(char* s)
{
	if (is_stack_empty())
	{
		error("스택이 비어있습니다.");
	}

	return s[top--];
}

int eval(char* s)
{
	char ch, open_ch;
	int n = strlen(s);

	int i, value;
	int op1, op2;

	for (i = 0; i < n; i++)
	{
		ch = s[i];

		if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%')
		{
			value = ch - '0';
			push(stack, value);
		}
		else
		{
			op2 = pop(stack);
			op1 = pop(stack);

			switch (ch)
			{
			case '+':
				push(stack, op1 + op2);
				break;
			case '-':
				push(stack, op1 - op2);
				break;
			case '*':
				push(stack, op1 * op2);
				break;
			case '/':
				push(stack, op1 / op2);
				break;
			case '%':
				push(stack, op1 % op2);
				break;
			}
		}
	}

	return pop(stack);

}

int main()
{

	int i;
	FILE* fa, * fb;

	int num = 0;
	char not[MAX_NOT_SIZE];

	int result;



	fa = fopen("input.txt", "r");
	fb = fopen("output.txt", "w");

	while (1)
	{
		if (!(fgets(not, MAX_NOT_SIZE, fa)))
			break;
		fscanf_s(fa, "%c", &not[num++]);
	}

	result = eval(not);

	printf("postfix expression : %s \n", not);
	printf("the evaluation value : %d\n", result);


	fprintf(fb, "postfix expression : %s \n", not);
	fprintf(fb, "the evaluation value : %d\n", result);


	return 0;
}

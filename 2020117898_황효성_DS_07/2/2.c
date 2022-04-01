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

char peek(char* s)
{
	return s[top];
}

int prec(char data)
{
	switch (data)
	{
	case '(': case ')':
		return 0;
	case '+': case '-':
		return 1;
	case '*': case'/': case '%':
		return 2;
	}
	return -1;
}

char* infix_to_postfix(char* s)
{
	char ch, open_ch;
	int n = strlen(s);
	int i;

	int num = 0;


	char* pa;
	char postfix[MAX_NOT_SIZE];

	pa = postfix;



	for (i = 0; i < n; i++)
	{
		ch = s[i];

		switch (ch)
		{
		case '+': case '-': case '*': case '/': case '%':

			if (!is_stack_empty(stack) && prec(ch) <= prec(peek(stack)))
			{
				char n = pop(stack);
				printf("%c", n);
				postfix[num++] = n;
			}

			push(stack, ch);
			break;

		case '(':
		{
			push(stack, ch);
			break;
		}

		case ')':
		{
			open_ch = pop(stack);

			while (open_ch != '(')
			{
				printf("%c", open_ch);
				postfix[num++] = open_ch;
				open_ch = pop(stack);
			}

			break;
		}
		default:
		{
			printf("%c", ch);
			postfix[num++] = ch;
			break;
		}
		}
	}

	while (!is_stack_empty(stack))
	{
		n = pop(stack);
		printf("%c", n);
		postfix[num++] = n;
	}
	postfix[num] = '\0';
	return pa;
}

void main()
{
	FILE* fa, * fb;

	int num = 0;

	char not[MAX_NOT_SIZE];
	char* post;


	fa = fopen("input.txt", "r");
	fb = fopen("output.txt", "w");


	while (1)
	{
		if (!(fgets(not, MAX_NOT_SIZE, fa)))
			break;
		fscanf_s(fa, "%c", &not[num++]);
	}

	printf("<<<<<<<<infix to postfix >>>>>>>>>>\n");
	printf("infix expression : %s\n", not);
	printf("postfix expression : ");
	post = infix_to_postfix(not);

	fprintf(fb, "% s", post);

	printf("\n");

}

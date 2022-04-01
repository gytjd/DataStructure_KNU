#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 5
#define MAX_LEN 20

typedef struct {
	int id;
	char name[MAX_LEN];
}element;

element stack[MAX_STACK_SIZE];
int top = -1;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

int is_stack_empty()
{
	return (top == -1);
}

int is_stack_full()
{
	return (top == MAX_STACK_SIZE - 1);
}

void sprint(element stack[])
{
	if (is_stack_empty())
	{
	}
	int i;
	for (i = 0;i <= top;i++)
	{
		printf("%d %s\n", stack[i].id, stack[i].name);
	}
	printf("\n\n\n");
}


void push(element stack[],element student)
{
	if (is_stack_full())
	{
		printf("stack is full, cannot add element\n");
		printf("current stack elements : \n");
		sprint(stack);
		exit(1);
	}
	top += 1;
	stack[top].id = student.id;
	strcpy(stack[top].name,student.name);
}

element pop(element stack[])
{
	if (is_stack_empty())
	{
		error("스택이 비어있습니다.");
	}
	return stack[top--];
}

int main()
{
	FILE* fpa;

	char* delimiter = " \n";
	char* context;
	char* op = NULL;

	element student;
	char line[MAX_LEN];

	printf("<< stack operations where MAX_STACK_SIZE is 5 >>\n");
	printf("The format of the stack operation is as follows\n");
	printf("push 1 Jung\n");
	printf("pop\n");
	printf("\n***************************************\n");

	if (fopen_s(&fpa,"input.txt", "r"))
		exit(1);

	while (1)
	{
		if (!(fgets(line, MAX_LEN, fpa)))
			break;

		op = strtok_s(line, delimiter, &context);

		if (!strcmp(op, "push"))
		{
			sscanf_s(context, "%d %s", &student.id, student.name,(unsigned int)sizeof(student.name));
			push(stack, student);
		}
		else if (!strcmp(op, "pop"))
		{
			pop(stack);
		}
		else if (!strcmp(op, "sprint"))
		{
			sprint(stack);
		}
		else if (!strcmp(op, "quit"))
		{
			break;
		}
		else
		{
			printf("wrong command! try again!\n");
		}
	}
	fclose(fpa);

	return 0;
}
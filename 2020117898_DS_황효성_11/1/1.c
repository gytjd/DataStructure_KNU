#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_SIZE 24

typedef struct StackNode {
	int data;
	struct StackNode* link;
}StackNode;

typedef struct StackType {
	StackNode* top;
}StackType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void init_stack(StackType* s)
{
	s->top = NULL;
}
int is_stack_empty(StackType* s)
{
	return (s->top == NULL);
}

void push(StackType* s,int data)
{
	StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
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

int pop(StackType* s)
{
	StackNode* removed = s->top;
	int data = removed->data;

	s->top = removed->link;

	free(removed);

	return data;
}

void display(StackType* s)
{
	StackNode* p = s->top;
	while (p != NULL)
	{

		printf("(%d %d %d) ", &(*p),p->data,(p->link));
		p = p->link;
	}
	printf("\n");
}

void output_equivalence(short int *out,StackType *seq,int n)
{
	int i, j;
	StackNode* x;
	StackNode* y;

	StackType stack;
	init_stack(&stack);

	for (i = 0;i < n;i++)
	{
		if (out[i] == TRUE)
		{
			printf("\nNew class: %5d", i);
			out[i] = FALSE;
			x = seq[i].top;

			for (;;)
			{
				while (x!=NULL)
				{
					j = x->data;

					if (out[j] == TRUE)
					{
						printf("%5d", j);
						out[j] = FALSE;
						push(&stack, j);
						x = x->link;
					}
					else
					{
						x = x->link;
					}
				}

				if (stack.top==NULL)
				{
					break;
				}
				x = seq[pop(&stack)].top;
			}
		}
	}
}

int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	short int out[MAX_SIZE];
	StackType seq[MAX_SIZE];
	StackNode* x;
	StackNode* y;

	int i, j, n;
	fscanf(fa, "%d", &n);
	printf("/* MAX_SIZE of a set S : 24 */");
	printf("current size of S : %d\n", n);

	printf("S= { ");
	for (i = 0;i < n;i++)
	{
		printf("%d ", i);
		out[i] = TRUE;
		init_stack(&seq[i]);
	}
	printf("}\n");

	int a, b;
	printf("input pairs : ");

	while(fscanf(fa, "%d %d", &a, &b)!=EOF)
	{
		printf("%dR%d ", a, b);
		push(&seq[a], b);
		push(&seq[b], a);
	}
	printf("\n\n");

	printf("symmetric 관계 linked List\n");
	for (i = 0;i < n;i++)
	{
		printf("%d : symmetric 관계: \n",i);
		display(&seq[i]);
	}
	output_equivalence(out, seq, n);

	return 0;
}
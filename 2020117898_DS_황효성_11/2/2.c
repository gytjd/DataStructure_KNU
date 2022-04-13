#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer llink;
	nodePointer rlink;
}node;

nodePointer header = NULL;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_Dlist(nodePointer d)
{

	d->llink = d;
	d->rlink = d;
}

int is_Dlist_empty(nodePointer d)
{
	return (d->llink == d && d->rlink == d);
}

void display_Dlist_backward(nodePointer head)
{
	nodePointer p = head->llink;
	int i = 1;
	while (p != head)
	{
		if (i % 4 == 0)
		{
			printf("\n");
		}
		printf("(%d %d %d) ", (p->llink), p->data, (p->rlink));
		p = p->llink;
		i++;
	}
	printf("\n");
}

void display_Dlist_forward(nodePointer head)
{
	nodePointer p = head->rlink;
	int i = 1;
	while (p != head)
	{
		if (i % 4 == 0)
		{
			printf("\n");
		}
		printf("(%d %d %d) ", (p->llink), p->data, (p->rlink));
		p = p->rlink;
		i++;
	}
	printf("\n");
}

void delete_less50(nodePointer head)
{
	nodePointer removed;
	nodePointer p = head->rlink;
	nodePointer pre = NULL;

	while (p != head)
	{
		if (p->data < 50)
		{
			removed = p;
			pre->rlink = p->rlink;
			p->rlink->llink = pre;
			p = p->rlink;
			free(removed);
			
		}
		else
		{
			pre = p;
			p = p->rlink;
		}
	}
}
void insert_last(nodePointer head, int data)
{
	nodePointer new_node = (nodePointer)malloc(sizeof(node));
	new_node->data = data;

	new_node->llink = head->llink;
	new_node->rlink = head;
	head->llink->rlink = new_node;
	head->llink = new_node;


}

int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	header = (nodePointer)malloc(sizeof(node));
	init_Dlist(header);

	int i, j;

	while (fscanf(fa, "%d", &i) != EOF)
	{
		insert_last(header, i);
	}
	printf("After creating a doubly linked circular list with a head node : \n");
	printf("forward\n");
	display_Dlist_forward(header);
	printf("\n\n");

	printf("backward\n");
	display_Dlist_backward(header);
	printf("\n\n");

	printf("After deleting numbers less than and eqaul to 50\n");
	delete_less50(header);
	printf("forward\n");
	display_Dlist_forward(header);
	printf("\n\n");

	printf("backward\n");
	display_Dlist_backward(header);
	printf("\n\n");

	return 0;
}

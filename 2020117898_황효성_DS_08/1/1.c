#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 10

typedef struct listNode* listPointer;
struct listNode {
	int data;
	listPointer link;
}listNode;
listPointer first;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void SWAP(int* pa, int* pb)
{
	int temp;
	temp = *pa;
	*pa = *pb;
	*pb = temp;
}
void selection_sort(int* pa)
{
	int i, j, minpos;

	for (i = 0; i < 11; i++)
	{
		minpos = i;
		for (j = i + 1; j < 12; j++)
		{
			if (pa[j] < pa[minpos])
			{
				minpos = j;
			}
		}

		SWAP(&pa[i], &pa[minpos]);
	}
}

void display(listPointer head)
{
	int count = 0;
	listPointer p = head;

	while (p != NULL)
	{
		if ((count % 3) == 0)
		{
			printf("\n");
		}
		printf("(%d %d, %d)", &(*p), p->data, p->link);
		p = p->link;
		count++;
	}
	printf("\n");
}

void insert_node(listPointer* head, listPointer x, int data)
{
	listPointer temp = (listPointer)malloc(sizeof(listPointer));
	temp->data = data;
	temp->link = NULL;

	if ((*head) == NULL)
	{
		temp->link = NULL;
		*head = temp;
	}
	else
	{
		if (x == NULL)
		{
			temp->link = (*head);
			(*head) = temp;
		}
		else
		{
			temp->link = x->link;
			x->link = temp;
		}
	}
}

void delete(listPointer* first, listPointer trail, listPointer x)
{
	if (trail)
	{
		trail->link = x->link;
	}
	else
	{
		*first = (*first)->link;
	}
}

void delete_odd(listPointer* head)
{
	listPointer p = *head;
	listPointer pre = NULL;
	while (p != NULL)
	{
		if ((p->data % 2) != 0)
		{
			if (pre == NULL)
			{
				delete(&first, pre, p);
			}
			else
			{
				delete(&first, pre, p);
			}
			p = p->link;
		}
		else
		{
			pre = p;
			p = p->link;
		}
	}
}

void delete_all(listPointer* head)
{
	listPointer p = *head;

	while (p != NULL)
	{
		delete(&first, NULL, p);
		p = p->link;
	}
}
int main()
{
	FILE* fpa;

	char* delimiter = " \n";
	char* context;
	char* op = NULL;
	char line[MAX_LEN];

	int i, j;
	int data[12] = { 0 };


	if (fopen_s(&fpa, "input.txt", "r"))
		exit(1);

	for (i = 0; i < 12; i++)
	{
		fscanf_s(fpa, "%d", &data[i]);
	}
	selection_sort(data);

	for (i = 11; i >= 0; i--)
	{
		insert_node(&first, NULL, data[i]);
	}

	printf("The ordered list contains :\n");
	display(first);

	printf("\n\nAfter deleting nodes with odd value");
	delete_odd(&first);
	display(first);

	delete_all(&first);
	display(first);
	fclose(fpa);

	return 0;
}
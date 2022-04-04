#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 10

typedef struct listNode {
	int data;
	struct listNode* link;
}listNode;

listNode* first = NULL;

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

void display(listNode* head)
{
	int count = 0;
	listNode* p = head;
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

void insert_node(listNode** head, listNode* pre, int data)
{
	listNode* new_node = (listNode*)malloc(sizeof(listNode));
	new_node->link = NULL;
	new_node->data = data;

	if (new_node == NULL)
	{
		error("메모리할당 에러");
	}
	else
	{
		if ((*head) == NULL)
		{
			*head = new_node;
		}
		else if (pre == NULL)
		{
			new_node->link = (*head);
			(*head) = new_node;
		}
		else
		{
			new_node->link = pre->link;
			pre->link = new_node;
		}
	}
}

void delete_node(listNode** head, listNode* pre, listNode* data)
{
	listNode* removed = data;
	if (pre == NULL)
	{
		removed = *head;
		(*head) = removed->link;
	}
	else
	{
		pre->link = removed->link;
	}
}

void delete_odd(listNode* head)
{
	listNode* p = head;
	listNode* pre = NULL;
	while (p != NULL)
	{
		if ((p->data % 2) != 0)
		{
			if (pre == NULL)
			{
				delete_node(&first, pre, p);
			}
			else
			{
				delete_node(&first, pre, p);
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

void delete_all(listNode* head)
{
	listNode* p = head;
	while (p != NULL)
	{
		delete_node(&first, NULL, p);
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
	delete_odd(first);
	display(first);


	delete_all(first);
	display(first);
	fclose(fpa);

	return 0;
}
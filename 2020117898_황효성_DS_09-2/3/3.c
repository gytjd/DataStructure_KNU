#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 10

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}listNode;

listPointer first;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void display(listPointer head)
{
	int count = 0;
	listPointer p = head->link;

	while (p != head)
	{
		if ((count % 3) == 0)
		{
			printf("\n");
		}
		printf("(%d %d, %d)", &(*p), p->data, p->link);
		p = p->link;
		count++;
	}
	printf("(%d, %d, %d)", &(*p), p->data, p->link);
	printf("\n");
}

void display_odd(listPointer head)
{
	if (head == NULL)
	{
		printf("\n");
	}
	else
	{
		int count = 0;
		listPointer p = head->link;

		while (p != head)
		{
			if ((count % 3) == 0)
			{
				printf("\n");
			}
			printf("(%d %d, %d)", &(*p), p->data, p->link);
			p = p->link;
			count++;
		}
		printf("\n(%d, %d, %d)", &(*p), p->data, p->link);
	}
	printf("\n");
}

void init_list() {
	first = NULL;
}
int is_list_empty() {
	return first == NULL;
}

void insert_first(listPointer *head, int data)
{
	listPointer new_node = (listPointer)malloc(sizeof(listPointer));
	new_node->data = data;
	new_node->link = NULL;

	if ((*head)==NULL)
	{
		*head = new_node;
		new_node->link = new_node;
	}
	else
	{
		new_node->link = (*head)->link;
		(*head)->link = new_node;
	}
}

void insert_last(listPointer* head, int data)
{
	listPointer new_node = (listPointer)malloc(sizeof(listPointer));
	new_node->data = data;
	new_node->link = NULL;

	if ((*head)==NULL)
	{
		(*head) = new_node;
		new_node->link = new_node;
	}
	else
	{
		new_node->link = (*head)->link;
		(*head)->link = new_node;
		*head = new_node;
	}
}


listPointer delete_odd(listPointer head)
{
	listPointer p = head->link;
	listPointer pre = head;
	listPointer ex = head->link;

	do
	{
		if ((p->data % 2) != 0)
		{
			pre->link = p->link;
		}
		else
		{
			pre = p;
		}
		p = p->link;
	} while (p != head);

	pre = head;
	do {
		pre = pre->link;
	} while (pre->link != head);

	pre->link = p->link;

	return pre;
}

int delete_first(listPointer* head)
{

	listPointer removed = (*head)->link;
	int item = removed->data;

	if (is_list_empty())
	{
		error("리스트가 비어있습니다.");
	}
	else
	{
		if (removed == (*head))
		{
			(*head) = NULL;
		}
		else
		{
			(*head)->link = removed->link;
		}

	}

	return item;
}

void delete_all(listPointer* head)
{
	while (*head != NULL)
	{
		delete_first(head);
	}
}
int main()
{
	FILE* fpa;

	char* delimiter = " \n";
	char* context;
	char* op = NULL;
	char line[MAX_LEN];

	init_list();
	int i, j;
	int data[12] = { 0 };


	fpa = fopen("input.txt", "r");


	for (i = 0; i < 12; i++)
	{
		fscanf_s(fpa, "%d", &data[i]);
	}

	for (i = 0; i <12; i++)
	{
		insert_last(&first, data[i]);
	}

	printf("The Circularly Linked List contains:\n");
	display(first);
	printf("\n\n\n");

	printf("After deleting nodes with odd value\n");
	first=delete_odd(first);
	display_odd(first);

	
	delete_all(&first);
	display_odd(first);
	fclose(fpa);

	return 0;
}
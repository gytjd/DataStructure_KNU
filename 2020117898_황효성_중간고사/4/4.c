#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100

typedef struct listNode* listPointer;

typedef struct {
	char name[MAX_NAME];
	char from[MAX_NAME];
	char gender[MAX_NAME];
	int age;
}element;

typedef struct listNode {
	element data;
	listPointer link;
}listNode;

listPointer total = NULL;
listPointer man = NULL;
listPointer woman = NULL;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void insert(listPointer* head, listPointer* x,element data)
{
	listPointer new_node = (listPointer)malloc(sizeof(listNode));
	new_node->data = data;
	new_node->link = NULL;

	if ((*head) == NULL)
	{
		(*head) = new_node;
	}
	else if ((*x) == NULL)
	{
		new_node->link = (*head);
		(*head) = new_node;
	}
	else
	{
		new_node->link = (*x)->link;
		(*x)->link = new_node;
	}
}

void insert_last(listPointer* head, element data)
{
	listPointer new_node = (listPointer)malloc(sizeof(listNode));
	new_node->data = data;
	new_node->link = NULL;

	if ((*head) == NULL)
	{
		(*head) = new_node;
	}
	else
	{
		listPointer p = (*head);
		while (p->link != NULL)
		{
			p = p->link;
		}

		p->link = new_node;
	}
}
void delete(listPointer* head, listPointer* x)
{
	listPointer removed;

	if ((*x) == NULL)
	{
		removed = (*head);
		(*head) = removed->link;
		free(removed);
	}
	else
	{
		removed = (*x)->link;
		(*x)->link = removed->link;
		free(removed);
	}
}

void display(listPointer head)
{
	listPointer p = head;
	int i = 0;

	while (p != NULL)
	{
		if (i % 2 == 0)
		{
			printf("\n");
		}
		printf("(%d, %5s, %5s,%5s, %2d, %d)  ", &(*p), p->data.name, p->data.from, p->data.gender, p->data.age, p->link);
		p = p->link;
		i++;
	}
}

listPointer make_array_man(listPointer* head)
{
	listPointer p = (*head);
	listPointer temp=NULL;

	while (p != NULL)
	{

		if (strcmp(p->data.gender, "남자") == 0)
		{
			insert_last(&temp, p->data);
		}
		p = p->link;
	}
	return temp;
}

listPointer make_array_woman(listPointer* head)
{
	listPointer p = (*head);
	listPointer temp = NULL;
	while (p != NULL)
	{
		if (strcmp(p->data.gender, "여자") == 0)
		{
			insert_last(&temp, p->data);
		}
		p = p->link;
	}

	return temp;
}

void make_all_array(listPointer* a, listPointer* b)
{
	listPointer p = (*b);

	while (p->link != NULL)
	{
		p = p->link;
	}
	p->link = (*a);
}

void reverse_array(listPointer* a)
{
	listPointer p = (*a);
	listPointer current;
	listPointer pre = NULL;

	while (p != NULL)
	{
		current = p;
		p = p->link;
		current->link = pre;
		pre = current;
	}

	(*a) = pre;
}
int main()
{
	FILE* fa;
	fa = fopen("input4.txt", "r");

	char line[MAX_NAME];
	element data;

	while (1)
	{
		if (!fgets(line, MAX_NAME, fa))
			break;
		sscanf(line, "%s %s %s %d", data.name, data.from, data.gender, &data.age);

		insert_last(&total, data);
	}
	printf("전체 리스트\n");
	display(total);
	printf("\n\n");

	printf("남자 리스트\n");
	man=make_array_man(&total);
	display(man);
	printf("\n\n");

	printf("여자 리스트\n");
	woman=make_array_woman(&total);
	display(woman);
	printf("\n\n");

	printf("합친 리스트\n");
	make_all_array(&man, &woman);
	display(woman);
	printf("\n\n");

	printf("역방향 리스트\n");
	reverse_array(&woman);
	display(woman);
	printf("\n\n");


	return 0;
}
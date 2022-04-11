#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
struct listNode {
	int coef;
	int exp;
	listPointer link;
}listNode;

listPointer a = NULL;
listPointer b = NULL;
listPointer c = NULL;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

int is_list_empty(listPointer* head)
{
	return (*head) == NULL;
}

void display(listPointer head)
{
	listPointer p=head->link;
	while (p != head)
	{
		printf("(%d :   %dx^%d : %d)\n", &(*p), p->coef, p->exp, (p->link));
		p = p->link;
	}
	printf("(%d :   %dx^%d : %d)\n", &(*p), p->coef, p->exp, (p->link));
}

void insert_first(listPointer* head, int coef, int exp)
{
	listPointer new_node = (listPointer)malloc(sizeof(listNode));
	new_node->coef = coef;
	new_node->exp = exp;
	new_node->link = new_node;

	if (is_list_empty(head))
	{
		*head = new_node;
	}
	else
	{
		new_node->link = (*head)->link;
		(*head)->link = new_node;
	}
}

void insert_last(listPointer* head, int coef, int exp)
{
	listPointer new_node = (listPointer)malloc(sizeof(listNode));

	new_node->coef = coef;
	new_node->exp = exp;
	new_node->link = new_node;

	if (is_list_empty(head))
	{
		*head = new_node;
	}
	else
	{
		new_node->link = (*head)->link;
		(*head)->link = new_node;
		(*head) = new_node;
	}
}
void poly_add(listPointer* a, listPointer* b)
{
	listPointer EndA = (*a)->link;
	listPointer EndB = (*b)->link;
	listPointer startA = (*a)->link->link;
	listPointer startB = (*b)->link->link;

	while (startA != EndA && startB != EndB)
	{
		if (startA->exp > startB->exp)
		{
			insert_last(&c, startA->coef, startA->exp);
			startA = startA->link;
		}
		else if (startA->exp < startB->exp)
		{
			insert_last(&c, startB->coef, startB->exp);
			startB = startB->link;
		}
		else
		{
			if (startA->coef + startB->coef == 0)
			{
				startA = startA->link;
				startB = startB->link;
				continue;
			}
			else
			{
				insert_last(&c, startA->coef + startB->coef, startA->exp);
			}
			startA = startA->link;
			startB = startB->link;
		}
	}

	for (;startA != EndA;startA = startA->link)
	{
		insert_last(&c, startA->coef, startA->exp);
	}
	for (;startB != EndB;startB = startB->link)
	{
		insert_last(&c, startB->coef, startB->exp);
	}

	listPointer new_node = (listPointer)malloc(sizeof(listNode));
	new_node->exp = -1;
	new_node->link = NULL;

	new_node->link = (c)->link;
	(c)->link = new_node;
}

void delete_all(listPointer* head)
{
	listPointer removed;
	listPointer p = *head;

	while (p != NULL)
	{

		*head = p->link;
		removed = p;
		p = p->link;
		free(removed);
	}
}

void avail(listPointer* a, listPointer* b, listPointer* c)
{
	listPointer p = (*c)->link->link;
	(*c)->link = (*b)->link;
	(*b)->link = (*a)->link;
	(*a)->link = p;

	listPointer new_node = (listPointer)malloc(sizeof(listNode));
	new_node->exp = -1;
	new_node->link = NULL;

	new_node->link = (*a)->link;
	(*a)->link = new_node;
	(*a) = new_node;
}
int main()
{
	FILE* fa, * fb;
	fa = fopen("a.txt", "r");
	fb = fopen("b.txt", "r");

	int coef, exp;
	char input;

	fscanf(fa, "%c", &input);

	if (input == 'd')
	{
		while (fscanf(fa, "%d %d", &coef, &exp) != EOF)
		{
			insert_last(&a, coef, exp);
		}
		listPointer new_node = (listPointer)malloc(sizeof(listNode));
		new_node->exp = -1;
		new_node->link = NULL;

		new_node->link = (a)->link;
		(a)->link = new_node;
	}
	else if (input == 'a')
	{
		while (fscanf(fb, "%d %d", &coef, &exp) != EOF)
		{

			insert_last(&b, coef, exp);
		}
	}

	fscanf(fb, "%c", &input);

	if (input == 'd')
	{
		while (fscanf(fb, "%d %d", &coef, &exp) != EOF)
		{
			insert_last(&a, coef, exp);
		}
	}
	else if (input == 'a')
	{
		while (fscanf(fb, "%d %d", &coef, &exp) != EOF)
		{
			printf("%d %d\n", coef, exp);
			insert_first(&b, coef, exp);
		}
		listPointer new_node = (listPointer)malloc(sizeof(listNode));
		new_node->exp = -1;
		new_node->link = NULL;

		new_node->link = (b)->link;
		(b)->link = new_node;
	}

	printf("   a:\n");
	display(a);
	printf("   b:\n");
	display(b);

	printf("a+b=c\n");
	poly_add(&a, &b);
	display(c);

	avail(&a, &b, &c);
	printf("avail : \n");
	display(a);
	return 0;
}
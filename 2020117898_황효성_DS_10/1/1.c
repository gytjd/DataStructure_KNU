#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
struct listNode {
	int coef;
	int exp;
	listPointer link;
}listNode;

listPointer a=NULL;
listPointer b=NULL;
listPointer c = NULL;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

int is_list_empty(listPointer *l)
{
	return *l == NULL;
}

void display(listPointer head)
{
	listPointer p = head;
	while (p != NULL)
	{
		printf("(%d :   %dx^%d : %d)\n", &(*p), p->coef, p->exp,(p->link));
		p = p->link;
	}
}

void insert_first(listPointer* head, int coef, int exp)
{
	listPointer new_node = (listPointer)malloc(sizeof(listNode));

	new_node->coef = coef;
	new_node->exp = exp;
	new_node->link = NULL;

	if (is_list_empty(head))
	{
		*head = new_node;
	}
	else
	{
		new_node->link = (*head);
		*head = new_node;
	}
}
void insert_last(listPointer* head, int coef, int exp)
{
	listPointer new_node = (listPointer)malloc(sizeof(listNode));
	listPointer p = *head;

	new_node->coef = coef;
	new_node->exp = exp;
	new_node->link = NULL;


	if (is_list_empty(head))
	{
		*head = new_node;
	}
	else
	{
		while (p->link != NULL)
		{
			p = p->link;
		}

		p->link = new_node;
	}
}

void poly_add(listPointer* a, listPointer* b)
{
	listPointer startA=*a;
	listPointer startB=*b;

	while (startA != NULL && startB != NULL)
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
			insert_last(&c, startA->coef + startB->coef, startA->exp);
			startA = startA->link;
			startB = startB->link;
		}
	}

	for (;startA;startA = startA->link)
	{
		insert_last(&c, startA->coef, startA->exp);
	}
	for (;startB;startB = startB->link)
	{
		insert_last(&c, startB->coef, startB->exp);
	}
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
	}
	else if (input == 'a')
	{
		while (fscanf(fb, "%d %d", &coef, &exp) != EOF)
		{

			insert_first(&b, coef, exp);
		}
	}

	fscanf(fb, "%c", &input);

	if (input == 'd')
	{
		while (fscanf(fa, "%d %d", &coef, &exp) != EOF)
		{

			insert_last(&a, coef, exp);
		}
	}
	else if (input == 'a')
	{
		while (fscanf(fb, "%d %d", &coef, &exp) != EOF)
		{

			insert_first(&b, coef, exp);
		}
	}

	printf("   a:\n");
	display(a);
	printf("   b:\n");
	display(b);

	printf("\na+b=c : \n");
	poly_add(&a, &b);
	display(c);

	delete_all(&a);
	delete_all(&b);
	delete_all(&c);


	return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEAP_SIZE 100

typedef int element;
typedef struct heapType {
	element heap[MAX_HEAP_SIZE];
	int heap_size;
}heapType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_heap(heapType* h)
{
	h->heap_size = 0;
}

int is_heap_empty(heapType* h)
{
	return h->heap_size == 0;
}

void insert_max_heap(heapType* h, element data)
{
	int i = ++(h->heap_size);

	while (i != 1)
	{
		if (data > (h->heap[i / 2]))
		{
			h->heap[i] = h->heap[i / 2];
			i /= 2;
		}
		else
		{
			break;
		}
	}

	h->heap[i] = data;
}

element delete_max_heap(heapType* h)
{
	element data = h->heap[1];
	element temp = h->heap[h->heap_size--];

	int child = 2;
	int parent = 1;

	while (child<=h->heap_size)
	{
		if ((child < h->heap_size) && h->heap[child] < h->heap[child + 1])
		{
			child++;
		}

		if (h->heap[child] < temp)
		{
			break;
		}

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;

	return data;
}

void display(heapType* h)
{
	int i;
	for (i = 1;i <= h->heap_size;i++)
	{
		printf("%d ", h->heap[i]);
	}

	printf("\n");
}

int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	element data;
	heapType h;
	init_heap(&h);
	printf("***** insertion into a max heap *****\n");

	while (fscanf(fa, "%d", &data) != EOF)
	{
		insert_max_heap(&h, data);
		display(&h);
	}

	printf("\n***** deletion from a max heap *****\n");
	while (!is_heap_empty(&h))
	{
		printf("delete data = %d\n", delete_max_heap(&h));
		display(&h);
	}
	return 0;
}




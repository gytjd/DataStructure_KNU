#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct heapType {
	int heap[MAX_SIZE];
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

int is_heap_full(heapType* h)
{
	return h->heap_size == MAX_SIZE-1;
}

void insert_max_heap(heapType* h, int data)
{
	int i = ++(h->heap_size);
	while (i != 1)
	{
		if (data > h->heap[i / 2])
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

int delete_max_heap(heapType* h)
{
	int parent = 1;
	int child = 2;

	int data = h->heap[1];
	int temp = h->heap[(h->heap_size)--];

	while (child < h->heap_size)
	{
		if (child <= h->heap_size && h->heap[child] < h->heap[child + 1])
		{
			child++;
		}

		if (temp > h->heap[child])
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

void display_heap(heapType* h)
{
	int i;
	for (i = 1;i <= h->heap_size;i++)
	{
		printf("%d ", h->heap[i]);
	}
	printf("\n");
}

void display_ary(int a[],int n)
{
	int i;
	for (i = 1;i <= n;i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void adjust(int a[], int root, int n)
{
	int child, rootkey;
	int temp;
	temp = a[root];

	rootkey = a[root];
	child = 2 * root;

	while (child <= n) {
		if ((child < n) && (a[child] < a[child + 1]))
		{
			child++;
		}

		if (rootkey > a[child])
		{
			break;
		}
		else
		{
			a[child / 2] = a[child];
			child *= 2;
		}
	}

	a[child / 2] = temp;
}

void heapSort(int a[], int n)
{
	int i;
	int step = 1;
	int temp;

	for (i = n / 2;i > 0;i--)
	{
		adjust(a, i, n);
	}

	printf("\n\n<<<<<<<<< executing heap sort >>>>>>>>>>>\n");
	printf("after initialization of max heap...\n");
	display_ary(a, n);
	printf("\n\n");

	for (i = n - 1;i > 0;i--)
	{
		temp = a[1];
		a[1] = a[i + 1];
		a[i + 1] = temp;

		adjust(a, 1, i);

		printf("step %d: Ãâ·Â %d : ", step, a[i+1]);
		display_ary(a, i);

		if(i!=1)
		step++;
	}
}
int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	heapType h;
	init_heap(&h);

	int i, num,data;
	int sor;
	int ary[MAX_SIZE];
	int sorted[MAX_SIZE];
	fscanf(fa, "%d", &num);

	printf("<<<<<<<<<<< Input List >>>>>>>>>>>\n");

	for (i = 1;i <= num;i++)
	{
		fscanf(fa, "%d", &data);
		printf("%d ", data);
		ary[i] = data;
	}

	heapSort(ary, num);

	printf("<<<<<<<<<<< Sorted List >>>>>>>>>>>>\n");
	display_ary(ary, num);
	return 0;
}
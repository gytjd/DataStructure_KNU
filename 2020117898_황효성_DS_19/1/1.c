#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICS 100
#define INF 1000L

int parent[MAX_VERTICS];

void set_init(int n)
{
	int i;
	for (i = 0;i < n;i++)
	{
		parent[i] = -1;
	}
}

int set_find(int curr)
{
	if (parent[curr] == -1)
	{
		return curr;
	}
	else
	{
		while (parent[curr] != -1)
		{
			curr = parent[curr];
		}
		return curr;
	}
}

void set_union(int a, int b)
{
	int root1 = set_find(a);
	int root2 = set_find(b);

	if (root1 != root2)
	{
		parent[root1] = root2;
	}
}

typedef struct {
	int start;
	int end;
	int weight;
}element;

typedef struct heapType {
	element heap[MAX_VERTICS];
	int size;
}heapType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_heap(heapType* h)
{
	h->size = 0;

	int i;
	for (i = 0;i < MAX_VERTICS;i++)
	{
		h->heap[i].start = 0;
		h->heap[i].end = 0;
		h->heap[i].weight = INF;
	}
}

int is_heap_empty(heapType* h)
{
	return h->size == 0;
}

int is_heap_full(heapType* h)
{
	return h->size == MAX_VERTICS;
}

void insert_min_heap(heapType* h, element data)
{
	int i = ++(h->size);
	while (i != 1 && h->heap[i / 2].weight > data.weight)
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = data;
}

element delete_min_heap(heapType* h)
{
	element data = h->heap[1];
	element temp = h->heap[h->size--];

	int parent = 1;
	int child = 2;

	while (child <= h->size)
	{
		if (child<h->size && h->heap[child].weight>h->heap[child + 1].weight)
		{
			child++;
		}

		if (temp.weight < h->heap[child].weight)
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

element create_heap(int start, int end, int weight)
{
	element data;
	data.start = start;
	data.end = end;
	data.weight = weight;

	return data;
}

void kruskal(heapType* h)
{
	element e;

	int uset, vset;

	set_init(h->size);

	int i = 0;
	int sum = 0;
	int size = h->size;

	while (i < (size-1))
	{
		e = delete_min_heap(h);
		uset = set_find(e.start);
		vset = set_find(e.end);

		if (uset != vset)
		{
			printf("(%d, %d) %d\n", e.start, e.end, e.weight);
			sum += e.weight;
			set_union(uset, vset);
		}
		i++;
	}
	printf("\n최소비용 : %d\n",sum);
}

int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	int edgeNum;
	int start, end, weight;

	heapType h;
	init_heap(&h);

	fscanf(fa, "%d", &edgeNum);

	int i;
	for (i = 0;i < edgeNum;i++)
	{
		fscanf(fa, "%d %d %d", &start, &end, &weight);
		insert_min_heap(&h, create_heap(start, end, weight));
	}

	kruskal(&h);

	return 0;
}
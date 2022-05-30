#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

static int count = 0;

typedef struct {
	int key;
}element;


void SWAP(element* pa, element* pb)
{
	element temp;
	temp = *pa;
	*pa = *pb;
	*pb = temp;
}
void display(element* pa, int n)
{
	int i;
	for (i = 0;i < n;i++)
	{
		printf("%2d ", pa[i].key);
	}
	printf("\n");
}

int partition(element* list, int left, int right)
{
	int low = left;
	int high = right + 1;
	element temp;

	int pivot = list[left].key;
	count++;
	printf("pivot =%d : ", pivot);
	display(list, 11);

	do {
		do {
			low++;
		} while (low <= right && pivot > list[low].key);

		do {
			high--;
		} while (high >= left && pivot < list[high].key);

		if (low < high)
		{
			SWAP(&list[low],&list[high]);
		}

	} while (low < high);

	SWAP(&list[left],&list[high]);

	return high;
}

void quick_sort(element* list, int left, int right)
{

	if (left < right)
	{
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}
int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	int i, num;
	element ary[MAX_SIZE];

	fscanf(fa, "%d", &num);

	for (i = 0;i < num;i++)
	{
		fscanf(fa, "%d", &ary[i].key);
	}
	printf("<<<<<<<<<<<<<<< Input List >>>>>>>>>>>>>>>>\n");
	display(ary, num);
	printf("\n\n");

	printf("execution of quick sort...\n");
	quick_sort(ary, 0, num-1);

	printf("\ncalls of quick sort: %d\n\n", count);
	printf("<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>>>>\n");
	display(ary, num);

	return 0;
}
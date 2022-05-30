#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

void display(int* pa, int n)
{
	int i;
	for (i = 0;i < n;i++)
	{
		printf("%4d ", pa[i]);
	}
	printf("\n\n");
}

void insertion_sort(int* list, int start, int end, int gap)
{
	int i, j, key;

	for (i = start + gap;i <= end;i += gap)
	{
		key = list[i];

		for (j = i - gap;j >= start && list[j] > key;j -= gap)
		{
			list[j + gap] = list[j];
		}
		list[j + gap] = key;
	}
}

void shell_sort(int* list, int n)
{
	int i, gap;
	for (gap = n / 2;gap > 0;gap /= 2)
	{
		if (gap % 2 == 0)
		{
			gap++;
		}

		printf("gap is %4d ====>\n", gap);

		for (i = 0;i < gap;i++)
		{
			insertion_sort(list, i, n - 1, gap);
		}

		display(list, n);
		printf("\n");
	}
}

int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	int i;
	int num;
	int ary[MAX_SIZE];

	fscanf(fa, "%d", &num);

	for (i = 0;i < num;i++)
	{
		fscanf(fa, "%d", &ary[i]);
	}
	printf("list[] data\n");
	display(ary, num);

	shell_sort(ary, num);
	return 0;

}
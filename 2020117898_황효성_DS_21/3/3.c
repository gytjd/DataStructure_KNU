#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100


void display(int* pa, int n)
{
	int i;
	for (i = 1;i <= n;i++)
	{
		printf(" %2d ", pa[i]);
	}
	printf("\n");
}

void merge(int initList[], int mergedList[], int i, int m, int n)
{
	int j, k, t;
	j = m + 1;
	k = i;

	while (i <= m && j <= n)
	{
		if (initList[i] <= initList[j])
		{
			mergedList[k++] = initList[i++];
		}
		else
		{
			mergedList[k++] = initList[j++];
		}
	}

	if (i > m)
	{
		for (t = j;t <= n;t++)
		{
			mergedList[t] = initList[t];
		}
	}
	else
	{
		for (t = i;t <= m;t++)
		{
			mergedList[k + t - i] = initList[t];
		}
	}
}

void mergePass(int initList[], int mergedList[], int n, int s)
{
	int i, j;

	for (i = 1;i <= n - 2 * s + 1;i += 2 * s)
	{
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
	}

	if (i + s - 1 < n)
	{
		merge(initList, mergedList, i, i + s - 1, n);
	}
	else
	{
		for (j = i;j <= n;j++)
		{
			mergedList[j] = initList[j];
		}
	}
}


void mergeSort(int* pa, int n)
{
	int s = 1;
	int sorted[MAX_SIZE];
	printf("<<<<< executin iterative merge sort >>>>>\n");
	while (s < n)
	{
		printf("segment size : %d\n", s);
		printf("            a: ");
		display(pa, n);
		mergePass(pa, sorted, n, s);
		printf("         temp: ");
		display(sorted, n);
		s *= 2;


		printf("segment size : %d\n", s);
		printf("         temp: ");
		display(sorted, n);
		mergePass(sorted, pa, n, s);
		printf("            a: ");
		display(pa, n);
		s *= 2;

	}
}

int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	int i, num;
	int ary[MAX_SIZE];

	fscanf(fa, "%d", &num);

	for (i = 1;i <= num;i++)
	{
		fscanf(fa, "%d", &ary[i]);
	}
	printf("<<<<<<<<<<<<<< Input List >>>>>>>>>>>>>>>\n");
	display(ary, num);
	printf("\n");


	mergeSort(ary, num);


	printf("\n<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>\n");
	display(ary, num);


	return 0;

}
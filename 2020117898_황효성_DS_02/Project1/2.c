#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 2001


void SWAP(int* pa, int* pb)
{
	int temp;
	temp = *pa;
	*pa = *pb;
	*pb = temp;


}

void display(int* pa)
{
	int i;
	for (i = 0;i < MAX_SIZE;i++)
	{
		printf("%d ", pa[i]);
	}
	printf("\n");
}

void selection_sort(int* pa, int n)
{
	int i, j, minpos;

	for (i = 0;i < n-1;i++)
	{

		minpos = i;

		for (j = i + 1;j < n;j++)
		{
			if (pa[i] > pa[j])
			{
				minpos = j;
			}
		}
		SWAP(&pa[i], &pa[minpos]);
	}
}
int main()
{
	int i,j, n, step = 10;
	int a[MAX_SIZE];
	int least,minpos;

	double duration;
	clock_t start;

	printf("     n      time\n");
	for (n = 0;n <= 2000;n += step)
	{
		for (i = 0;i < n;i++)
		{
			a[i] = n - i;
		}
		start = clock();

		selection_sort(a, n);

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;


		printf("%6d   %f\n", n, duration);

		if (n == 100)
		{
			step = 100;
		}
	}


	return 0;
	
}
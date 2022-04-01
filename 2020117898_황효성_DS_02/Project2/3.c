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

void selection_sort(int* pa, int n)
{
	int i,j,minpos;
	for (i = 0;i < n - 1;i++)
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
	int i, j, n, step = 10;
	int a[MAX_SIZE];
	int minpos;

	double duration;

	printf("     n      repetitions      time\n");
	for (n = 0;n <= 2000;n += step)
	{
		long repetitions = 0;
		clock_t start = clock();

		do
		{
			repetitions++;

			for (i = 0;i < n;i++)
			{
				a[i] = n - i;
			}

			selection_sort(a, n);


		} while (clock() - start < 1000);

		duration = ((double) (clock() - start)) / CLOCKS_PER_SEC;

		duration /= repetitions;


		printf("%6d   %9d          %f\n", n,repetitions,duration);

		if (n == 100)
		{
			step = 100;
		}
	}


	return 0;

}
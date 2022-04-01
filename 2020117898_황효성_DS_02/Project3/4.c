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

void selection_sort(int* pa,int n)
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
	int b[MAX_SIZE];
	int c[MAX_SIZE];

	double duration1,duration2,duration3;

	srand((unsigned)time(NULL));


	printf("     n       역정렬       순정렬        랜덤\n");
	for (n = 0;n <= 2000;n += step)
	{
		long repetitions = 0;
		clock_t start1 = clock();

		do
		{
			repetitions++;

			for (i = 0;i < n;i++)
			{
				a[i] = n - i;
			}

			selection_sort(a,n);


		} while (clock() - start1 < 1000);

		duration1 = ((double)(clock() - start1)) / CLOCKS_PER_SEC;

		duration1 /= repetitions;









		repetitions = 0;
		clock_t start2 = clock();

		do
		{
			repetitions++;

			for (i = 0;i < n;i++)
			{
				b[i] =i;
			}

			selection_sort(b,n);


		} while (clock() - start2 < 1000);

		duration2 = ((double)(clock() - start2)) / CLOCKS_PER_SEC;

		duration2 /= repetitions;
















		repetitions = 0;
		clock_t start3 = clock();

		do
		{
			repetitions++;

			for (i = 0;i < n;i++)
			{
				c[i] = rand()%1001;
			}

			selection_sort(c,n);


		} while (clock() - start3 < 1000);

		duration3 = ((double)(clock() - start3)) / CLOCKS_PER_SEC;

		duration3 /= repetitions;










		printf("%6d     %f       %f       %f\n", n, duration1, duration2,duration3);

		if (n == 100)
		{
			step = 100;
		}
	}


	return 0;

}
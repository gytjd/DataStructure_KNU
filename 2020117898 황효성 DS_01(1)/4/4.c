#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void display(int* pa, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d ", pa[i]);
	}
	printf("\n");
}

void SWAP(int* a, int* b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int binary_search(int pa[], int start, int end, int searchnum)
{
	printf("left %d right %d\n", start, end);
	int mid = (start + end) / 2;


	if (searchnum == pa[mid])
	{
		return mid;
	}
	else if (searchnum < pa[mid])
	{
		return binary_search(pa, start, mid - 1, searchnum);
	}
	else

	{
		return binary_search(pa, mid+1, end, searchnum);
	}

	return -1;
}
int main()
{
	int a;
	int ary[MAX_SIZE] = { 0 };

	srand((unsigned)time(NULL));
	printf("Enter the number of numbers to generate : ");

	scanf_s("%d", &a);
	if (a < 1 || a>100)
	{
		error("0 이상 100 이하의 값을 입력하세요");
	}


	int q;
	for (q = 0; q < a; q++)
	{
		ary[q] = rand() % 1000;
	}

	display(ary, a);

	int i, j, min, minpos;

	for (i = 0; i < a - 1; i++)
	{
		min = ary[i];
		minpos = i;

		for (j = i + 1; j < a; j++)
		{
			if (min > ary[j])
			{
				min = ary[j];
				minpos = j;
			}
		}

		SWAP(&ary[i], &ary[minpos]);
	}

	printf("Sorted array : \n");
	display(ary, a);

	int b;
	printf("Enter the number to search : ");
	scanf_s("%d", &b);

	printf("The search number is present in list[%d]\n", binary_search(ary, 0, a-1, b));



	return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_SIZE 100

int find_min(int* pa, int n)
{
	int i, min;
	min = pa[0];
	for (i = 1;i < n;i++)
	{
		if (pa[i] < min)
		{
			min = pa[i];
		}
	}

	return min;
}

int find_max(int* pa, int n)
{
	int i, max;
	max = pa[0];
	for (i = 1;i < n;i++)
	{
		if (pa[i] > max)
		{
			max = pa[i];
		}
	}

	return max;
}

int main()
{
	FILE* fa;
	fa = fopen("input1.txt", "r");

	int ary[MAX_SIZE];

	int num;
	int sum = 0;
	int count = 0;

	while (fscanf(fa, "%d", &num) != EOF)
	{
		ary[count] = num;
		sum += ary[count];
		count++;
	}

	printf("입력 데이터 수 : %d\n", count);
	printf("합계 : %d\n", sum);
	printf("최대 값 : %d\n", find_max(ary,count));
	printf("최소 값 : %d\n", find_min(ary,count));

	return 0;


}
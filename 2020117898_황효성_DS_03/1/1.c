#include <stdio.h>
#include <stdlib.h>


int* make1dArray(int n)
{
	int* ary = (int*)malloc(sizeof(int) * n);
	int i;
	for (i = 0;i < n;i++)
	{
		ary[i] = rand() % 100;
	}

	return ary;
}
int main()
{
	int* ipp;
	int i, num;
	printf("일차원 배열의 수를 입력하세요: ");

	scanf_s("%d", &num);
	ipp = make1dArray(num);

	for (i = 0; i < num; i++) {
		printf("ipp[%2d] =%2d ", i, ipp[i]);
		if ((i % 5) == 4)
			printf("\n");

	}

	return 0;
}

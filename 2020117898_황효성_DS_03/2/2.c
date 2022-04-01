
#include <stdio.h>
#include <stdlib.h>


int** make2dArray(int a, int b)
{
	int **ary= (int**)malloc(sizeof(int *) * a);

	int i,j;
	for (i = 0;i < a;i++)
	{
		ary[i] = (int*)malloc(sizeof(int) * b);
	}

	for (i = 0;i < a;i++)
	{
		for (j = 0;j < b;j++)
		{
			ary[i][j] = rand() % 100;
		}
	}

	return ary;

}
int main()
{
	int** ipp;
	int i, j, rows, cols;

	printf("������ �迭�� ��� ���� ���� �Է� �ϼ��� : ");
	scanf_s("%d %d", &rows, &cols);

	ipp = make2dArray(rows, cols);

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			printf("ipp[%d][%d] =%d ", i, j, ipp[i][j]);
		}
		printf("\n");
	}

	return 0;
}

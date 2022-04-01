#include <stdio.h>

int sumAry2D_f1(int ary[][3], int ROW, int COL)
{
	int i, j;
	int sum = 0;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			sum += ary[i][j];
		}
	}

	return sum;
}

int sumAry2D_f2(int (*ary)[3], int ROW)
{
	int i,j, sum = 0;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < ROW; j++)
		{
			sum += ary[i][j];
		}
	}
	return sum;
}


int sumAry2D_f3(int ary[3][3])
{
	int i, j, sum = 0;


	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			sum += ary[i][j];
		}
	}
	return sum;
}
int main()
{
	int ary2D[][3] = { {1,2,3},{4,5,6},{7,8,9} };

	printf("sumAry2D_f1() %d\n", sumAry2D_f1(ary2D, 3, 3));
	printf("sumAry2D_f2() %d\n", sumAry2D_f2(ary2D, 3));
	printf("sumAry2D_f3() %d\n\n", sumAry2D_f3(ary2D));


	return 0;
}
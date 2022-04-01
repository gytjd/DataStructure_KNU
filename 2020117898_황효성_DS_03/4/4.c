#include <stdio.h>
#include <stdlib.h>

#define MAX_DEGREE 101

typedef struct {
	int degree;
	int coef[MAX_DEGREE];

}polynomial;

void poly_print(polynomial* poly)
{
	int i;
	int a = poly->degree;
	for (i = 0;i < poly->degree;i++)
	{
		printf("%dx^%d +", poly->coef[i], a--);
	}
	printf("%d", poly->coef[poly->degree]);
	printf("\n");
}

polynomial add_poly(polynomial A, polynomial B)
{
	polynomial c;
	int i;
	int count = 0;
	
	if (A.degree > B.degree)
	{
		c.degree = A.degree;
		while (count < (A.degree - B.degree)) // A와 B의 차수를 뺀 값은 A의 처음 N개의 수
		{
			c.coef[count] = A.coef[count];
			count++;
		}
		// 위의 코드는 B보다 A가 많은 만큼 더하는것

		int dex = 0; // A의 첫부분 부터 더하는 변수
		for (i = count;i <= A.degree;i++)
		{
			c.coef[i] = A.coef[i] + B.coef[dex++];
		}
		//위의 코드는 나머지의 A의 코드와 B의 코드를 더하는것
		//두것을 더하면 C의 다항식이 된다.
	}
	else if (A.degree < B.degree)
	{
		c.degree = B.degree;
		while (count < (B.degree - A.degree))
		{
			c.coef[count] = B.coef[count];
			count++;
		}

		int dex = 0;
		for (i = count;i <= B.degree;i++)
		{
			c.coef[i] = B.coef[i] + A.coef[dex++];
		}
	}
	else

	{
		c.degree = A.degree;

		for (i = 0;i <= A.degree;i++)
		{
			c.coef[i] = A.coef[i] + B.coef[i];
		}
	}

	return c;
}
int main()
{
	int i;
	polynomial A, B,C;
	

	printf("Input the degree ofitems of A(x) : ");
	scanf_s("%d", &A.degree);

	printf("Input the coefficients A(x) : ");

	for (i = 0;i < A.degree + 1;i++)
	{
		scanf_s("%d", &A.coef[i]);
	}


	printf("Input the degree ofitems of B(x) : ");
	scanf_s("%d", &B.degree);

	printf("Input the coefficients B(x) : ");

	for (i = 0;i < B.degree + 1;i++)
	{
		scanf_s("%d", &B.coef[i]);
	}

	printf("A(X) = ");
	poly_print(&A);

	printf("B(X) = ");
	poly_print(&B);

	C = add_poly(A, B);
	printf("C(X) = ");
	poly_print(&C);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>


int* func1()
{
	int* num;
	num= (int *)malloc(sizeof(int));
	*num = 10;

	return num;
}

void func2(int* p)
{
	*p = 100;
}

void func3(int** p)

{
	**p = 200;
}

char* func4(int n)
{
	char* num = (char*)malloc(n);

	return num;
}
int main(void)
{
	int* pNum;
	char* pChar;

	pNum = func1();
	printf("%d\n", *pNum);


	func2(pNum);
	printf("%d\n", *pNum);


	func3(&pNum); 
	printf("%d\n", *pNum);


	pChar = func4(100); 


	printf("입력할 문자열 : ");
	scanf_s("%s", pChar,_msize(pChar));
	printf("pChar contents = %s\n",pChar);


	free(pNum);
	free(pChar);

	return 0;
}

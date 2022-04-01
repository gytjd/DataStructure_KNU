#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0


typedef struct date {
	int month;
	int day;
	int year;
}date;

typedef struct humanBeing {
	char name[20];
	int age;
	float salary;
	date dob;
}humanBeing;

int humansEqual(humanBeing *person1, humanBeing *person2)
{
	if (strcmp(person2->name, person2->name))
	{
		return FALSE;
	}
	if (person1->age != person2->age)
	{
		return FALSE;
	}
	if (person1->salary != person2->salary)
	{
		return FALSE;
	}
	
	return TRUE;
}


int main()
{
	humanBeing person1, person2;

	int a[20];

	printf("Input person1's name, age, salary\n");
	gets(person1.name);
	scanf_s("%d", &person1.age);
	scanf_s("%f", &person1.salary);

	while (getchar() != '\n');

	printf("Input person2's name, age, salary\n");
	gets(person2.name);
	scanf_s("%d", &person2.age);
	scanf_s("%f", &person2.salary);

	if (humansEqual(&person1,&person2) == TRUE)
	{
		printf("The two human beings are the same");
	}
	else
	{
		printf("The two human beings are not the same");
	}

	return 0;
}
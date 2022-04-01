#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100

typedef struct {
    int coef;
    int expon;
}term;

term terms[MAX_TERMS];

void display_terms(term* p,int a,int b)
{
    int i;
    for(i=a;i<b-1;i++)
    {
        printf("%2dx^%2d +",p[i].coef,p[i].expon);
    }
    printf("%2dx^%2d ",p[i].coef,p[i].expon);
    printf("\n");
}

void poly_add(term* p, int EndA, int EndB)
{
    int startA = 0, startB = EndA;
    int startC = EndB;
    int EndC;

    while (startA < EndA && startB < EndB)
    {
        if (p[startA].expon > p[startB].expon)
        {
            terms[startC++]=terms[startA++];

        }
        else if (p[startA].expon < p[startB].expon)
        {
            terms[startC++]=terms[startB++];
        }
        else
        {
            terms[startC].coef=terms[startA].coef+terms[startB].coef;
            terms[startC].expon=terms[startA].expon;
            startC++;
            startA++;
            startB++;
        }
    }

    if (startA <= EndA)
    {
        for (;startB < EndB;startB++)
        {
            terms[startC++] = terms[startB++];
        }
    }
    else
    {
        for (;startB < EndB;startB++)
        {
            terms[startC++] = terms[startA++];
        }
    }
    EndC = startC;

    printf("C(x) =");
    display_terms(terms, EndB, EndC);
}
int main()
{
    int i;
    int EndA, EndB;
    printf("<< D(x) = A(x) + B(x) >>\n");
    printf("Input the number of items of A(x) : ");
    scanf_s("%d", &EndA);

    printf("Input the number of items of A(x) : ");
    scanf_s("%d", &EndB);

    printf("\n");
    printf("input in descending order\n");

    printf("coefficeient and exponent of A(x) = 10x^5 + 8x^3 + 7 (10 5,8 3,7 0) : ");
    for (i = 0;i < EndA;i++)
    {
        scanf_s("%d %d", &terms[i].coef, &terms[i].expon);
    }

    printf("coefficeient and exponent of B(x) = 10x^5 + 8x^3 + 7 (10 5,8 3,7 0) : ");
    for (i = EndA;i < EndA + EndB;i++)
    {
        scanf_s("%d %d", &terms[i].coef, &terms[i].expon);
    }

    printf("A(x) =");
    display_terms(terms, 0, EndA);


    printf("B(x) =");
    display_terms(terms, EndA, EndA+EndB);

    poly_add(terms, EndA, EndA+EndB);


    return 0;

}



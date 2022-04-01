#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TERM_SIZE 400

typedef struct {
    int row;
    int col;
    int value;
}term;




void display(int pa[][20])
{
    int i, j;
    printf("Random generated Matrix(20,20)\n");

    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
        {
            printf("%2d ", pa[i][j]);
        }
        printf("\n");
    }
}



int main()
{
    term T[TERM_SIZE];
    int a, i, j;
    int count = 0;
    int ary[20][20] = { 0 };
    srand((unsigned)time(NULL));

    printf("원소의 개수를 쓰시오 : ");
    scanf_s("%d", &a);

    for (i = 0; i < a; i++)
    {
        ary[rand() % 20][rand() % 20] = rand() % 100 + 1;
    }

    display(ary);

    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (ary[i][j] == 0)
            {
                continue;
            }
            T[count].row = i;
            T[count].col = j;
            T[count].value = ary[i][j];

            count++;
        }
    }

    for (i = 0; i < a; i++)
    {
        printf("%3d %3d %3d\n", T[i].row, T[i].col, T[i].value);
    }



    return 0;

}


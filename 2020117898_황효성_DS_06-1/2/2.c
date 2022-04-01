#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20
#define MAX_STACK_SIZE 100

#define TRUE 1
#define FALSE 0

typedef struct {
    int vert;
    int horiz;
}offsets;

offsets Move[8] ={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};


typedef struct {
    int row;
    int col;
    int dir;
}element;

element stack[MAX_STACK_SIZE];
int top=-1;

void error(char *message)
{
    fprintf(stderr,"%s\n",message);
    exit(1);
}

void init_stack(element *s)
{
    top=-1;
}

int is_stack_empty(element *s)
{
    return top==-1;
}

int is_stack_full(element *s)
{
    return (top==(MAX_STACK_SIZE-1));
}

void push(element *s,element data)
{
    if(is_stack_full(s))
    {
        error("스택이 꽉 차있습니다.");
    }
    s[++top]=data;
}

element pop(element *s)
{
    if(is_stack_empty(s))
    {
        error("스택이 비어있습니다.");
    }
    return s[top--];
}


void init_maze(int A[][20])
{
    int i,j;
    
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
        {
            A[i][j]=1;
        }
    }
}


void path(int maze[][20],int mark[][20],int EXIT_ROW,int EXIT_COL)
{
    int i,row,col,nextRow,nextCol,dir,found=FALSE;
    
    element position;
    
    mark[1][1]=1;
    top=0;
    stack[0].row=1;
    stack[0].col=1;
    stack[0].dir=1;
    
    while (top > -1 && !found) {
        position = pop(stack);
        row = position.row;
        col = position.col;
        dir = position.dir;

        while (dir < 8 && !found)
        {
            nextRow = row + Move[dir].vert;
            nextCol = col + Move[dir].horiz;

            if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
            {
                found = TRUE;
            }

            else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol])
            {
                mark[nextRow][nextCol] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;

                push(stack, position);

                row = nextRow;
                col = nextCol;
                dir = 0;
            }
            else
            {
                ++dir;
            }
        }
    }
    if (found)
    {
        printf("The path is: \n");
        printf("row col\n");

        for (i = 0; i <= top; i++)
        {
            printf("%2d%5d\n", stack[i].row, stack[i].col);
        }

        printf("%2d%5d\n", row, col);
        printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
    }
    else
    {
        printf("The maze does not have a path\n");
    }
}

int main()
{
    
    int row,cols;
    FILE *fa;
    
    int i,j;

    fa=fopen("input.txt", "r");

    fscanf_s(fa, "%d %d",&row,&cols);
    
    int MAZE[MAX_SIZE][MAX_SIZE] = { 0 };
    int MARK[MAX_SIZE][MAX_SIZE]= { 0 };
    
    init_maze(MAZE);
    
    for(i=0;i<row;i++)
    {
        for(j=0;j<cols;j++)
        {
            fscanf_s(fa, "%d", &MAZE[i + 1][j + 1]);
        }
    }
    

    path(MAZE, MARK, 4, 5);


    return 0;
}










#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICS 100

#define TRUE 1
#define FALSE 0

#define INF 999

int found[MAX_VERTICS];
int distance[MAX_VERTICS];

int ary[MAX_VERTICS][MAX_VERTICS];
int index_a[MAX_VERTICS];

typedef struct graphType {
    int size;
    int weight[MAX_VERTICS][MAX_VERTICS];
}graphType;

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_graph(graphType* g)
{
    g->size = 0;

    int i, j;
    for (i = 0; i < MAX_VERTICS; i++)
    {
        for (j = 0; j < MAX_VERTICS; j++)
        {
            if (i == j)
            {
                g->weight[i][j] = 0;
            }
            else
            {
                g->weight[i][j] = INF;
            }
        }
    }
}


void display_graph(graphType* g)
{
    int i, j;
    for (i = 0; i < g->size; i++)
    {
        for (j = 0; j < g->size; j++)
        {
            if (g->weight[i][j] == INF)
            {
                printf("INF  ");
            }
            else
            {
                printf("%3d  ", g->weight[i][j]);
            }
        }
        printf("\n");
    }
}
void init_distance(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        distance[i] = INF;
    }
}

void display_distance(graphType* g, int s)
{
    static int index1 = 0;
    static int index2 = 0;

    index_a[index2++] = s;

    for (int i = 0; i < g->size; i++)
    {
        ary[index1][i] = distance[i];
        printf("%5d", distance[i]);
    }

    index1++;

    printf("\n");
}

void init_found(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        found[i] = FALSE;
    }
}

int choose(int size)
{
    int i, min, minpos;
    min = INF;
    minpos = -1;

    for (i = 0; i < size; i++)
    {
        if (distance[i] < min && !found[i])
        {
            min = distance[i];
            minpos = i;
        }
    }

    return minpos;
}

void Dikstra(graphType* g, int start)
{
    int i, u = 0, w;


    init_distance(g->size);
    init_found(g->size);

    for (i = 0; i < g->size; i++)
    {
        distance[i] = g->weight[start][i];
    }

    found[start] = TRUE;
    distance[start] = 0;

    for (i = 0; i < g->size - 1; i++)
    {
        printf("%d : ", u);
        display_distance(g, u);
        u = choose(g->size);
        found[u] = TRUE;

        for (w = 0; w < g->size; w++)
        {
            if (!found[w])
            {
                if (distance[u] + g->weight[u][w] < distance[w])
                {
                    distance[w] = distance[u] + g->weight[u][w];
                }
            }
        }
    }
    printf("\n\n");

}

int main()
{
    FILE* fa;
    fa = fopen("input.txt", "r");

    graphType g;
    init_graph(&g);

    int i, j, k;
    int verNum, edgeNum;
    int start, end, weight;

    fscanf(fa, "%d %d", &verNum, &edgeNum);
 
    g.size = verNum;

    for (i = 0; i < edgeNum; i++)
    {
        fscanf(fa, "%d %d %d", &start, &end, &weight);
        g.weight[start][end] = weight;
        g.weight[end][start] = weight;
    }

    Dikstra(&g, 0);


    for (i = 1; i <= g.size - 1; i++)
    {
        printf("distance[%d-%d]=%2d     : ", 0, i, ary[5][i]);
        for (k = 1; k <= 6; k++)
        {
            for (j = 1; j <= 6; j++)
            {
                if (ary[j - 1][i] != ary[5][i])
                    if (index_a[j] == 6)
                        printf("<%d->%d> ", index_a[j - 1], i - 1);
                    else if (index_a[j - 1] == 6)
                        break;
                    else
                        printf("<%d->%d> ", index_a[j - 1], index_a[j]);
                else break;
            }
            if (index_a[j - 1] == 6)
                printf("<%d->%d> ", i - 1, i);
            else
                printf("<%d->%d> ", index_a[j - 1], i);
            if (j != 6) break;
        }
        printf("\n");
    }
    return 0;
}


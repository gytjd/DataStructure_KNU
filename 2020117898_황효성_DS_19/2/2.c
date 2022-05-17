#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICS 100
#define INF 1000

typedef struct graphType {
	int n;
	int weight[MAX_VERTICS][MAX_VERTICS];
}graphType;

int selected[MAX_VERTICS];
int distance[MAX_VERTICS];

void init_graph(graphType* g)
{
	int i,j;
	for (i = 0;i < MAX_VERTICS;i++)
	{
		for (j = 0;j < MAX_VERTICS;j++)
		{
			g->weight[i][j] = INF;
		}
	}
}

int get_min_vertex(int n)
{
	int i,v;
	for (i = 0;i < n;i++)
	{
		if (!selected[i])
		{
			v = i;
			break;
		}
	}

	for (i = 0;i < n;i++)
	{
		if (!selected[i] && (distance[i] < distance[v]))
		{
			v = i;
		}
	}

	return v;
}

void display_distance(int n)
{
	int i;
	for (i = 0;i < n;i++)
	{
		if (distance[i] == INF)
		{
			printf(" INF");
		}
		else
		{
			printf("%4d", distance[i]);
		}
	}
}

void prim(graphType* g, int s)
{
	int i, u, v,w;
	int sum = 0;

	for (u = 0;u < g->n;u++)
	{
		distance[u] = INF;
	}
	distance[0] = 0;

	for (i = 0;i < g->n;i++)
	{
		w = u;
		u = get_min_vertex(g->n);
		sum += distance[u];
		selected[u] = TRUE;


		if (distance[u] == INF)
		{
			return;
		}

		for (v = 0;v < g->n;v++)
		{
			if (g->weight[u][v] != INF)
			{
				if (!selected[v] && g->weight[u][v] < distance[v])
				{
					distance[v] = g->weight[u][v];
				}
			}
		}

		if (u == 0)
		{
			printf("선택 vertex : %d,   distance :", u);
			display_distance(g->n);
			printf("\n");
		}
		else
		{
			printf("선택 vertex : %d,   distance :", u);
			display_distance(g->n);
			printf("  선택 edge : ( %d, %d) distance : %d\n", w, u, distance[u]);
		}
	}
	printf("최소 비용 : %d\n", sum);
}

int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	int start, end, weight;
	int edgeNum;
	graphType g;
	init_graph(&g);

	fscanf(fa, "%d", &edgeNum);
	g.n = 7;

	int i;
	for (i = 0;i < edgeNum;i++)
	{
		fscanf(fa, "%d %d %d", &start, &end, &weight);
		g.weight[start][end] = weight;
		g.weight[end][start] = weight;
	}

	prim(&g, 0);
}
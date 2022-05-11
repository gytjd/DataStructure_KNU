#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRAPH_SIZE 100

typedef struct graphNode {
	int data;
	struct graphNode* link;
}graphNode;

typedef struct graphType {
	graphNode *graph[MAX_GRAPH_SIZE];
	int size;
}graphType;

int visited[MAX_GRAPH_SIZE];

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_visited()
{
	int i;
	for (i = 0;i < MAX_GRAPH_SIZE;i++)
	{
		visited[i] = 0;
	}
}
void init_graph(graphType* g)
{
	g->size = 0;

	int i;
	for (i = 0;i < MAX_GRAPH_SIZE;i++)
	{
		g->graph[i] = NULL;
	}
}

void insert_vertex(graphType* g)
{
	g->size++;
}

void make_edge(graphType* g, int start, int end)
{
	graphNode* new_node = (graphNode*)malloc(sizeof(graphNode));
	new_node->data = end;
	new_node->link = NULL;

	if (g->graph[start] == NULL)
	{
		g->graph[start] = new_node;
	}
	else
	{
		new_node->link = g->graph[start];
		g->graph[start] = new_node;
	}
}

void insert_edge(graphType* g, int start, int end)
{
	make_edge(g, start, end);
	make_edge(g, end, start);
}

void display(graphType* g)
{
	int i;
	graphNode* p;

	for (i = 0;i < g->size;i++)
	{
		p = g->graph[i];
		printf("graph[%d] :",i);
		while (p != NULL)
		{
			printf("%3d", p->data);
			p = p->link;
		}
		printf("\n");
	}
}

void dfs_recur(graphType* g, int start)
{
	graphNode* p = g->graph[start];
	visited[start] = 1;
	printf("%3d", start);

	while (p != NULL)
	{
		if (!visited[p->data])
		{
			dfs_recur(g, p->data);
		}
		p = p->link;
	}
}
int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	int i;
	int verNum, edgeNum;
	int start, end;

	graphType g;
	init_graph(&g);

	fscanf(fa,"%d %d", &verNum, &edgeNum);

	for (i = 0;i < verNum;i++)
	{
		insert_vertex(&g);
	}

	for (i = 0;i < edgeNum;i++)
	{
		fscanf(fa,"%d %d", &start, &end);
		insert_edge(&g, start, end);
	}

	printf("<<<<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>>>>>\n");
	display(&g);
	printf("\n");
	printf("<<<<<<<<<<<<<<<< Depth First Search >>>>>>>>>>>>>>>>>\n");
	for (i = 0;i < g.size;i++)
	{
		init_visited();
		printf("dfs[%d] :", i);
		dfs_recur(&g, i);
		printf("\n");
	}

	return 0;
}


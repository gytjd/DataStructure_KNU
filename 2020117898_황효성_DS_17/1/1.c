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

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
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

int is_graph_empty(graphType* g)
{
	return g->size == 0;
}

int is_graph_full(graphType* g)
{
	return g->size == MAX_GRAPH_SIZE;
}

void insert_vertex(graphType* g)
{
	g->size++;
}

void insert_edge_directed(graphType* g, int start, int end)
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

void insert_edge_undirected(graphType* g, int start, int end)
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

	graphNode* new_node2 = (graphNode*)malloc(sizeof(graphNode));
	new_node2->data = start;
	new_node2->link = NULL;

	if (g->graph[end] == NULL)
	{
		g->graph[end] = new_node2;
	}
	else
	{
		new_node2->link = g->graph[end];
		g->graph[end] = new_node2;
	}
}

void display(graphType* g)
{
	int i;
	graphNode* temp;
	for (i = 0;i < g->size;i++)
	{
		temp = g->graph[i];
		printf("adjList[%d] : ", i);
		while (temp != NULL)
		{
			printf("%4d", temp->data);
			temp = temp->link;
		}
		printf("\n");
	}
}

int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");
	
	int i;
	char mode;
	int verNum, edgeNum;

	int start, end;

	graphType g;
	init_graph(&g);

	fscanf(fa, "%c %d %d", &mode, &verNum, &edgeNum);

	for (i = 0;i < verNum;i++)
	{
		insert_vertex(&g);
	}

	for (i = 0;i < edgeNum;i++)
	{
		fscanf(fa, "%d %d", &start, &end);

		if (mode == 'u')
		{
			insert_edge_undirected(&g, start, end);
		}
		else
		{
			insert_edge_directed(&g, start, end);
		}
	}

	printf("<<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>\n");
	display(&g);

	return 0;
}


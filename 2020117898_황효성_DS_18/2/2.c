#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRAPH_SIZE 100

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

typedef struct queueNode {
	int data;
	struct queueNode* link;
}queueNode;

typedef struct queueType {
	queueNode* front;
	queueNode* rear;
}queueType;

void init_queue(queueType* q)
{
	q->front = NULL;
	q->rear = NULL;
}

int is_queue_empty(queueType* q)
{
	return (q->front == NULL && q->rear == NULL);
}

void enqueue(queueType* q, int data)
{
	queueNode* new_node = (queueNode*)malloc(sizeof(queueNode));
	new_node->data = data;
	new_node->link = NULL;

	if (is_queue_empty(q))
	{
		q->front = new_node;
		q->rear = new_node;
	}
	else
	{
		q->rear->link = new_node;
		q->rear = new_node;
	}
}

int dequeue(queueType* q)
{
	queueNode* removed = q->front;
	int data = removed->data;

	q->front = removed->link;
	if (q->front == NULL)
	{
		q->rear = NULL;
	}

	free(removed);

	return data;
}

typedef struct graphNode {
	int data;
	struct graphNode* link;
}graphNode;

typedef struct graphType {
	graphNode* graph[MAX_GRAPH_SIZE];
	int size;
}graphType;

int visited[MAX_GRAPH_SIZE];


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
		printf("graph[%d] :", i);
		while (p != NULL)
		{
			printf("%3d", p->data);
			p = p->link;
		}
		printf("\n");
	}
}

void bfs_list(graphType* g, int start)
{
	queueType q;
	init_queue(&q);

	graphNode* p;

	printf("%3d", start);
	visited[start] = 1;
	enqueue(&q, start);

	while (!is_queue_empty(&q))
	{
		start = dequeue(&q);
		p = g->graph[start];

		while (p != NULL)
		{
			if (!visited[p->data])
			{
				printf("%3d", p->data);
				visited[p->data] = 1;
				enqueue(&q, p->data);
			}
			p = p->link;
		}
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

	fscanf(fa, "%d %d", &verNum, &edgeNum);

	for (i = 0;i < verNum;i++)
	{
		insert_vertex(&g);
	}

	for (i = 0;i < edgeNum;i++)
	{
		fscanf(fa, "%d %d", &start, &end);
		insert_edge(&g, start, end);
	}

	printf("<<<<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>>>>>\n");
	display(&g);
	printf("\n");


	printf("<<<<<<<<<<<<<<<< Depth First Search >>>>>>>>>>>>>>>>>\n");
	for (i = 0;i < g.size;i++)
	{
		init_visited();
		printf("bfs[%d] :", i);
		bfs_list(&g, i);
		printf("\n");
	}

	return 0;
}


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false)

typedef struct node* link;
typedef struct node {
	int num1;
	link num1_ptr;
	int num2;
	link num2_ptr;
} node;

link* graph;
node* edges;

int vertex_num, edge_num;
int tmp_from, tmp_to;

void print_graph(void)
{
	link tmp; int i;
	printf("<<<<<<<< edges incident to each vertex >>>>>>>>>>\n\n");

	printf("간선의 정점 출력 순서 - 입력데이터 순서대로\n");

	for (i = 0;i < vertex_num;i++)
	{
		printf("edges incident to vertex %d : ", i);
		for (tmp = graph[i];tmp;)
		{
			printf("(%d %d) ", tmp->num1, tmp->num2);
			tmp = (i == tmp->num1) ? tmp->num1_ptr : tmp->num2_ptr;
		}
		printf("\n");
	}
	printf("\n");

	printf("간선의 정점 출력 순서 - 헤더노드 정점이 먼저 오게\n");
	for (i = 0;i < vertex_num;i++)
	{
		printf("edges incident to vertex %d : ", i);
		for (tmp = graph[i];tmp;)
		{
			printf("(%d %d) ", i, ((i == tmp->num1) ? tmp->num2 : tmp->num1));
			tmp = (i == tmp->num1) ? tmp->num1_ptr : tmp->num2_ptr;
		}
		printf("\n");
	}
	printf("\n");
}

int main(void)
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	if (fa)
	{
		fscanf(fa, "%d %d", &vertex_num, &edge_num);

		CALLOC(link, vertex_num, graph);
		CALLOC(node, edge_num, edges);

		int i, j;
		for (i = 0;i < edge_num;i++)
		{
			fscanf_s(fa, "%d %d", &tmp_from, &tmp_to);
			edges[i].num1 = tmp_from; edges[i].num2 = tmp_to;

			for (j = 0;j < vertex_num;j++)
			{
				if (j == tmp_from && !graph[j])
					graph[j] = &edges[i];

				if (j == tmp_to && !graph[j])
					graph[j] = &edges[i];
			}

			for (j = 0;j < i;j++)
			{
				if (edges[j].num1 == tmp_from && !edges[j].num1_ptr)
					edges[j].num1_ptr = &edges[i];

				if (edges[j].num2 == tmp_from && !edges[j].num2_ptr)
					edges[j].num2_ptr = &edges[i];

				if (edges[j].num1 == tmp_to && !edges[j].num1_ptr)
					edges[j].num1_ptr = &edges[i];

				if (edges[j].num2 == tmp_to && !edges[j].num2_ptr)
					edges[j].num2_ptr = &edges[i];
			}
		}

		fclose(fa);
	}

	print_graph();

	return 0;
}

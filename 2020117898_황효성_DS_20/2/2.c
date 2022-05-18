#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICS 50

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

typedef struct StackNode {
    int data;
    struct StackNode* link;
}StackNode;

typedef struct StackType {
    StackNode* top;
}StackType;

void init_stack(StackType* s)
{
    s->top = NULL;
}

int is_stack_empty(StackType* s)
{
    return s->top == NULL;
}

void push(StackType* s, int data)
{
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    new_node->data = data;
    new_node->link = NULL;

    if (is_stack_empty(s))
    {
        s->top = new_node;
    }
    else
    {
        new_node->link = s->top;
        s->top = new_node;
    }
}

int pop(StackType* s)
{
    StackNode* removed = s->top;
    int data = removed->data;

    s->top = removed->link;

    free(removed);

    return data;
}

typedef struct GraphNode {
    int data;
    struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
    GraphNode* adj_list[MAX_VERTICS];
    int n;
}GraphType;

void init_graph(GraphType* g)
{
    g->n = 0;

    int i;
    for (i = 0; i < MAX_VERTICS; i++)
    {
        g->adj_list[i] = NULL;
    }
}

int is_graph_empty(GraphType* g)
{
    return g->n == 0;
}

int is_graph_full(GraphType* g)
{
    return g->n == MAX_VERTICS;
}

void insert_vertex(GraphType* g)
{
    if (is_graph_full(g))
    {
        error("정점 개수 초과.");
    }
    g->n++;
}

void insert_edge(GraphType* g, int start, int end)
{
    if (start >= g->n || end >= g->n)
    {
        error("간선 번호 오류.");
    }
    else
    {
        GraphNode* new_node = (GraphNode*)malloc(sizeof(GraphNode));
        new_node->data = end;
        new_node->link = NULL;

        if (g->adj_list[start] == NULL)
        {
            g->adj_list[start] = new_node;
        }
        else
        {
            new_node->link = g->adj_list[start];
            g->adj_list[start] = new_node;
        }
    }
}

void display_graph(GraphType* g)
{
    GraphNode* p;

    int i;
    for (i = 0; i < g->n; i++)
    {
        printf("%d = ", i);
        p = g->adj_list[i];

        while (p != NULL)
        {
            printf("%d ", p->data);
            p = p->link;
        }
        printf("\n");
    }
}

void topo_sort(GraphType* g)
{
    static int count = 0;

    StackType s;
    init_stack(&s);

    int i;
    GraphNode* p;

    int* in_degree = (int*)malloc(g->n * sizeof(int));

    for (i = 0; i < g->n; i++)
    {
        in_degree[i] = 0;
    }

    for (i = 0; i < g->n; i++)
    {
        p = g->adj_list[i];

        while (p != NULL)
        {
            in_degree[p->data]++;
            p = p->link;
        }
    }

    for (i = 0; i < g->n; i++)
    {
        if (in_degree[i] == 0)
        {
            push(&s, i);
        }
    }

    while (!is_stack_empty(&s))
    {
        int w;
        w = pop(&s);
        count++;

        if (count == 6)
        {
            printf("%d", w);
        }
        else
        {
            printf("%d -> ", w);
        }

        p = g->adj_list[w];

        while (p != NULL)
        {
            in_degree[p->data]--;

            if (in_degree[p->data] == 0)
            {
                push(&s, p->data);
            }
            p = p->link;
        }
    }
    free(in_degree);
    printf("\n");

}
int main()
{
    FILE* fa;
    fa = fopen("input.txt", "r");

    int verNum;
    GraphType g;
    init_graph(&g);

    fscanf(fa, "%d", &verNum);
    g.n = verNum;

    int i;
    int start, end;
    for (i = 0; i < 8; i++)
    {
        fscanf(fa, "%d %d", &start, &end);
        insert_edge(&g, start, end);
    }

    topo_sort(&g);

    return 0;
}


/* Computing the minimum spanning tree of A Garph using
 * Kruskal's Algorithm
 * Author   -   Anish Sharma
 * Date     -   14-04-2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Edge
{
    int src, dest;
    int w;
} Edge;

typedef struct Graph
{
    int V, E;
    Edge *edges;
} Graph;

typedef struct Subset
{
    int parent;
    int rank;
} Subset;

typedef struct IntList
{
    int value;
    struct IntList *next;
} IntList;

Edge *newEdge(int src, int dest, int weight)
{
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->src = src;
    edge->dest = dest;
    edge->w = weight;
    return edge;
}

IntList *newInt(int value)
{
    IntList *node = (IntList *)malloc(sizeof(IntList));
    node->value = value;
    node->next = NULL;

    return node;
}

void push(IntList **list, int value)
{
    if (*list == NULL)
    {
        *list = newInt(value);
    }
    else
    {
        IntList *node = *list;
        while (node->next)
            node = node->next;
        node->next = newInt(value);
    }
}

Graph *newGraph(int V, int E)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;

    graph->edges = (Edge *)calloc(E, sizeof(Edge));

    return graph;
}

void initializeSubsets(Subset *subsets, int V)
{
    for (int i = 0; i < V; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }
}

Subset *newSubset(int V)
{
    Subset *subsets = (Subset *)calloc(V, sizeof(Subset));
    initializeSubsets(subsets, V);
    return subsets;
}

int find(Subset *subsets, int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void makeUnion(Subset subsets[], int x, int y)
{
    int x_root = find(subsets, x);
    int y_root = find(subsets, y);

    if (subsets[x_root].rank < subsets[y_root].rank)
        subsets[x_root].parent = y_root;
    else if (subsets[y_root].rank < subsets[x_root].rank)
        subsets[y_root].parent = x_root;
    else
    {
        subsets[y_root].parent = x_root;
        subsets[x_root].rank++;
    }
}

int weightCompare(const void *a, const void *b)
{
    Edge *edge1 = (Edge *)a;
    Edge *edge2 = (Edge *)b;
    return edge1->w - edge2->w;
}

// Returns the weight of the MST using Kruskal's Algorithm
int findMSTWeight(Graph *graph)
{
    qsort(graph->edges, graph->E, sizeof(Edge), weightCompare);

    Subset *subsets = newSubset(graph->V);

    int sum = 0;
    for (int i = 0, e = 0; i < graph->E && e < graph->V; i++)
    {
        Edge next = graph->edges[i];

        int src = find(subsets, next.src);
        int dest = find(subsets, next.dest);

        if (src != dest)
        {
            sum += next.w;
            makeUnion(subsets, src, dest);
        }
    }

    return sum;
}

IntList *readNumList()
{
    IntList *list = NULL;
    char line[500];
    scanf("%[^\n]%*c", line);

    int num = 0;
    for (int i = 0; line[i] != '\0'; i++)
    {
        if (isdigit(line[i]))
        {
            num *= 10;
            num += (int)line[i] - '0';
        }
        else
        {
            push(&list, num);
            num = 0;
        }
    }

    // Last element
    push(&list, num);

    return list;
}

void printList(IntList *list)
{
    if (list)
    {
        printf("%d ", list->value);
        printList(list->next);
    }
}

int getSize(IntList *list)
{
    if (list)
        return 1 + getSize(list->next);
    return 0;
}

int undirectedExists(Graph *graph, int src, int dest)
{
    for (int i = 0; i < graph->E; i++)
        if ((graph->edges[i].src == src && graph->edges[i].dest == dest) || (graph->edges[i].src == dest && graph->edges[i].dest == src))
            return 1;
    return 0;
}

int main()
{
    int V;
    scanf("%d%*c", &V);

    IntList *edges[V];
    IntList *weights[V];

    int E = 0;

    for (int i = 0; i < V; i++)
    {
        edges[i] = readNumList();
        E += getSize(edges[i]);
    }

    for (int i = 0; i < V; i++)
    {
        weights[i] = readNumList();
    }

    // Since the graph is undirected
    E = E / 2;

    Graph *graph = newGraph(V, E);

    for (int i = 0, e = 0; i < V; i++)
    {
        IntList *list = edges[i];
        IntList *wList = weights[i];
        while (list && wList)
        {
            int src = i;
            int dest = list->value;
            int w = wList->value;
            if (!undirectedExists(graph, src, dest))
            {
                graph->edges[e] = *newEdge(src, dest, w);
                e++;
            }
            list = list->next;
            wList = wList->next;
        }
    }

    int mst = findMSTWeight(graph);
    printf("%d\n", mst);
    return 0;
}
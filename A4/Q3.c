/* Check if a directed graph contains a negative cycle
 * Author   -   Anish Sharma
 * Date     -   14-04-2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Graph
{
    int *adj;
    int V;
} Graph;

Graph *newGraph(int V)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->adj = (int *)calloc(V * V, sizeof(int));
    graph->V = V;
}

int getWeight(Graph *graph, int src, int dest)
{
    return *(graph->adj + dest + graph->V * src);
}

void setWeight(Graph *graph, int src, int dest, int weight)
{
    *(graph->adj + dest + graph->V * src) = weight;
}

int findMin(int *set, int length, int *exclude)
{
    int mini = -1, min = INT_MAX;
    for (int i = 0; i < length; i++)
        if (!exclude[i] && set[i] < min)
        {
            mini = i;
            min = set[i];
        }
    return mini;
}

int hasZero(int *set, int length)
{
    for (int i = 0; i < length; i++)
        if (!set[i])
            return 1;
    return 0;
}

int *findAllPaths(Graph *graph, int src)
{
    int V = graph->V;
    int *dist = malloc(V * sizeof(int));
    int *sptSet = calloc(V, sizeof(int));

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    while (hasZero(sptSet, V))
    {
        int u = findMin(dist, V, sptSet);
        sptSet[u] = 1;
        for (int j = 0; j < V; j++)
        {
            int w = getWeight(graph, u, j);
            if (w && dist[u] != INT_MAX)
            {
                if (dist[u] + w < dist[j])
                    dist[j] = dist[u] + w;
            }
        }
    }

    return (int *)dist;
}

int hasNegativeCycle(Graph *graph, int *dist)
{
    if (!dist)
        dist = findAllPaths(graph, 0);

    for (int i = 0; i < graph->V; i++)
        for (int j = 0; j < graph->V; j++)
        {
            int w = getWeight(graph, i, j);
            if (w && dist[j] > dist[i] + w)
                return 1;
        }

    return -1;
}

void main()
{
    int V, E;
    int src, dest, w;
    scanf("%d %d", &V, &E);
    Graph *graph = newGraph(V);
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &src, &dest, &w);
        setWeight(graph, src, dest, w);
    }

    int *dist = findAllPaths(graph, 0);
    printf("%d\n", hasNegativeCycle(graph, dist));
}
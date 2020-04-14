/* Computing the minimum spanning tree of A Garph using
 * Prim's Algorithm
 * Author   -   Anish Sharma
 * Date     -   14-04-2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

typedef struct Graph
{
    int *adj;
    int V;
} Graph;

typedef struct IntList
{
    int value;
    struct IntList *next;
} IntList;

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
    *(graph->adj + src + graph->V * dest) = weight;
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

int primMST(Graph *graph)
{
    int V = graph->V;
    int *keys = malloc(V * sizeof(int));
    int *sptSet = calloc(V, sizeof(int));

    for (int i = 0; i < V; i++)
        keys[i] = INT_MAX;
    keys[0] = 0;

    while (hasZero(sptSet, V))
    {
        int u = findMin(keys, V, sptSet);
        sptSet[u] = 1;
        for (int j = 0; j < V; j++)
        {
            int w = getWeight(graph, u, j);
            if (w && !sptSet[j])
            {
                if (w < keys[j])
                    keys[j] = w;
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < V; i++)
        sum += keys[i];
    return sum;
}

int main()
{
    int V;
    scanf("%d%*c", &V);

    IntList *edges[V];
    IntList *weights[V];

    for (int i = 0; i < V; i++)
    {
        edges[i] = readNumList();
    }

    for (int i = 0; i < V; i++)
    {
        weights[i] = readNumList();
    }

    Graph *graph = newGraph(V);

    for (int i = 0, e = 0; i < V; i++)
    {
        IntList *list = edges[i];
        IntList *wList = weights[i];
        while (list && wList)
        {
            int src = i;
            int dest = list->value;
            int w = wList->value;

            setWeight(graph, src, dest, w);

            list = list->next;
            wList = wList->next;
        }
    }

    int mst = primMST(graph);
    printf("%d\n", mst);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define INF 999999

int main()
{
    int V, E, K, R;

    printf("Enter vertices and edges: ");
    scanf("%d%d", &V, &E);

    int **graph = malloc(V * sizeof(int *));

    for (int i = 0; i < V; i++)
    {
        graph[i] = calloc(V, sizeof(int));
    }

    printf("Enter undirected edges:\n");

    int u, v;

    for (int i = 0; i < E; i++)
    {
        scanf("%d%d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    printf("Enter number of hubs: ");
    scanf("%d", &K);

    int *hub = malloc(K * sizeof(int));

    printf("Enter hub vertices in increasing order:\n");

    for (int i = 0; i < K; i++)
        scanf("%d", &hub[i]);

    printf("Enter radius: ");
    scanf("%d", &R);

    int *dist = malloc(V * sizeof(int));
    int *owner = malloc(V * sizeof(int));
    int *queue = malloc(V * sizeof(int));

    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        owner[i] = -1;
    }

    int front = 0, rear = 0;

    // Insert all hubs into the queue

    for (int i = 0; i < K; i++)
    {
        int h = hub[i];

        dist[h] = 0;
        owner[h] = i + 1;

        queue[rear++] = h;
    }

    // Multi-source BFS

    while (front < rear)
    {
        int node = queue[front++];

        for (int i = 0; i < V; i++)
        {
            if (graph[node][i] == 1 && dist[i] == INF)
            {
                dist[i] = dist[node] + 1;
                owner[i] = owner[node];

                queue[rear++] = i;
            }
        }
    }

    printf("\nVertex\tOwner\tDistance\n");

    for (int i = 0; i < V; i++)
    {
        if (dist[i] > R)
            printf("%d\t-1\t-1\n", i);
        else
            printf("%d\t%d\t%d\n", i, owner[i], dist[i]);
    }

    return 0;
}
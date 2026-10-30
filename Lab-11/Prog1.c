#include <stdio.h>
#include <stdlib.h>

#define INF 999999

int main()
{
    int V, E, S, C;
    int u, v, w;

    printf("Enter vertices and edges: ");
    scanf("%d%d", &V, &E);

    printf("Enter source vertex: ");
    scanf("%d", &S);

    printf("Enter penalty cost: ");
    scanf("%d", &C);

    int *head = malloc(V * sizeof(int));
    int *to = malloc(2 * E * sizeof(int));
    int *weight = malloc(2 * E * sizeof(int));
    int *next = malloc(2 * E * sizeof(int));

    for (int i = 0; i < V; i++)
        head[i] = -1;

    int edge = 0;

    printf("Enter directed edges (u v weight):\n");

    for (int i = 0; i < E; i++)
    {
        scanf("%d%d%d", &u, &v, &w);

        to[edge] = v;
        weight[edge] = w;
        next[edge] = head[u];
        head[u] = edge++;
    }

    int **dist = malloc(V * sizeof(int *));

    for (int i = 0; i < V; i++)
    {
        dist[i] = malloc(2 * sizeof(int));
        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    int capacity = 4 * (E + V + 1);
    int *dq = malloc(capacity * sizeof(int));

    int front = capacity / 2;
    int rear = front;

    dist[S][0] = 0;
    dq[rear++] = S * 2;

    while (front < rear)
    {
        int state = dq[front++];
        int node = state / 2;
        int parity = state % 2;

        for (int i = head[node]; i != -1; i = next[i])
        {
            int dest = to[i];
            int wt = weight[i];
            int newParity = parity ^ wt;

            if (dist[node][parity] + wt < dist[dest][newParity])
            {
                dist[dest][newParity] =
                    dist[node][parity] + wt;

                int newState = dest * 2 + newParity;

                if (wt == 0)
                    dq[--front] = newState;
                else
                    dq[rear++] = newState;
            }
        }
    }

    printf("\nMinimum Effective Costs:\n");

    for (int i = 0; i < V; i++)
    {
        int even = dist[i][0];
        int odd = dist[i][1];

        if (even == INF && odd == INF)
            printf("Vertex %d: Unreachable\n", i);
        else
        {
            if (odd != INF)
                odd += C;

            int ans = even < odd ? even : odd;

            printf("Vertex %d: %d\n", i, ans);
        }
    }

    return 0;
}
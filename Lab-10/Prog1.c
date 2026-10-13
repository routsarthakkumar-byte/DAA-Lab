#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// Queue structure for BFS coloring check
typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

bool isEmpty(Queue* q) {
    return q->front > q->rear;
}

void enqueue(Queue* q, int value) {
    if (q->rear < MAX - 1) {
        q->items[++(q->rear)] = value;
    }
}

int dequeue(Queue* q) {
    if (!isEmpty(q)) {
        return q->items[(q->front)++];
    }
    return -1;
}

// Function to check if graph remains bipartite after adding an edge (u, v)
bool isBipartiteAfterAddingEdge(int V, int adj[MAX][MAX], int u, int v) {
    // Temporary adjacency matrix to test the new edge
    int tempAdj[MAX][MAX];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            tempAdj[i][j] = adj[i][j];
        }
    }
    tempAdj[u][v] = 1;
    tempAdj[v][u] = 1;

    int color[MAX];
    for (int i = 0; i < V; i++) {
        color[i] = -1; // -1 means unvisited
    }

    // BFS to check bipartiteness across all components
    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            Queue q;
            initQueue(&q);
            color[i] = 0;
            enqueue(&q, i);

            while (!isEmpty(&q)) {
                int curr = dequeue(&q);

                for (int neighbor = 0; neighbor < V; neighbor++) {
                    if (tempAdj[curr][neighbor] == 1) {
                        if (color[neighbor] == -1) {
                            color[neighbor] = 1 - color[curr];
                            enqueue(&q, neighbor);
                        } else if (color[neighbor] == color[curr]) {
                            return false; // Same color found -> odd cycle exists
                        }
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    int V, E;
    printf("Enter number of vertices (V): ");
    scanf("%d", &V);
    printf("Enter number of edges arriving online (E): ");
    scanf("%d", &E);

    int adj[MAX][MAX] = {0};

    printf("\nEnter edges one by one (format: u v, with vertices from 0 to V-1):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        printf("\nEdge %d - Enter u and v: ", i + 1);
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= V || v < 0 || v >= V) {
            printf("Invalid vertex indices! Try again.\n");
            i--;
            continue;
        }

        // Test if adding (u, v) maintains bipartiteness
        if (isBipartiteAfterAddingEdge(V, adj, u, v)) {
            adj[u][v] = 1;
            adj[v][u] = 1;
            printf("Edge (%d, %d) added successfully. Graph remains bipartite.\n", u, v);
        } else {
            printf("Violation! Adding edge (%d, %d) introduces an odd cycle. Edge skipped.\n", u, v);
        }
    }

    return 0;
}
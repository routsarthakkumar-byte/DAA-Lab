#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int parent[MAX];
int comp_weight[MAX];
int is_active[MAX];
int max_sum = 0;

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void unite(int u, int v, int weights[]) {
    int root_u = find(u);
    int root_v = find(v);
    if (root_u != root_v) {
        parent[root_v] = root_u;
        comp_weight[root_u] += comp_weight[root_v];
        if (comp_weight[root_u] > max_sum) {
            max_sum = comp_weight[root_u];
        }
    }
}

int main() {
    int V, E;
    printf("Enter number of vertices (V): ");
    scanf("%d", &V);

    int weights[MAX];
    printf("Enter vertex weights:\n");
    for (int i = 0; i < V; i++) {
        printf("Vertex %d weight: ", i);
        scanf("%d", &weights[i]);
    }

    int adj[MAX][MAX] = {0};
    printf("Enter number of edges: ");
    scanf("%d", &E);
    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    int deletion_order[MAX];
    printf("Enter deletion order of vertices (P):\n");
    for (int i = 0; i < V; i++) {
        scanf("%d", &deletion_order[i]);
        is_active[i] = 0; // Initially all deleted, we add them back in reverse
    }

    int results[MAX];
    max_sum = 0;

    // Process deletions in reverse order (as additions)
    for (int i = V - 1; i >= 0; i--) {
        int u = deletion_order[i];
        is_active[u] = 1;
        parent[u] = u;
        comp_weight[u] = weights[u];

        if (comp_weight[u] > max_sum) {
            max_sum = comp_weight[u];
        }

        // Connect with already active neighbors
        for (int v = 0; v < V; v++) {
            if (adj[u][v] && is_active[v]) {
                unite(u, v, weights);
            }
        }
        results[i] = max_sum;
    }

    printf("\nMaximum sum of component values after each deletion step:\n");
    for (int i = 0; i < V; i++) {
        printf("After deleting vertex %d: Max Component Sum = %d\n", deletion_order[i], results[i]);
    }

    return 0;
}
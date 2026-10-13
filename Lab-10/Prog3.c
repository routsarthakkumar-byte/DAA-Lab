#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int parent[MAX];
int comp_size[MAX];
int comp_weight[MAX];
int max_weight = 0;

void init(int V, int weights[]) {
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        comp_size[i] = 1;
        comp_weight[i] = weights[i];
        if (weights[i] > max_weight) {
            max_weight = weights[i];
        }
    }
}

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void unite(int u, int v, int K) {
    int root_u = find(u);
    int root_v = find(v);

    if (root_u != root_v) {
        if (comp_size[root_u] + comp_size[root_v] <= K) {
            parent[root_v] = root_u;
            comp_size[root_u] += comp_size[root_v];
            comp_weight[root_u] += comp_weight[root_v];
            if (comp_weight[root_u] > max_weight) {
                max_weight = comp_weight[root_u];
            }
            printf("Edge added. Merged components. New max component weight <= K: %d\n", max_weight);
        } else {
            printf("Edge skipped! Combined size exceeds threshold K = %d\n", K);
        }
    } else {
        printf("Vertices already in the same component.\n");
    }
}

int main() {
    int V, E, K;
    printf("Enter number of vertices (V): ");
    scanf("%d", &V);

    int weights[MAX];
    printf("Enter vertex weights:\n");
    for (int i = 0; i < V; i++) {
        printf("Weight of vertex %d: ", i);
        scanf("%d", &weights[i]);
    }

    printf("Enter size constraint threshold (K): ");
    scanf("%d", &K);

    init(V, weights);

    printf("Enter number of edges (E): ");
    scanf("%d", &E);

    printf("Enter edges (u v) sequentially:\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        printf("Edge %d (u v): ", i + 1);
        scanf("%d %d", &u, &v);
        unite(u, v, K);
        printf("Current Maximum Component Weight: %d\n\n", max_weight);
    }
    return 0;
}
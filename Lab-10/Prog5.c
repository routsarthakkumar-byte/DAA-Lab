#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int parent[MAX];

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
    }
}

// Simple comparison function for qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, E;
    printf("Enter number of elements in permutation (n): ");
    scanf("%d", &n);

    int A[MAX];
    printf("Enter permutation elements (1-indexed or 0-indexed values):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        parent[i] = i;
    }

    printf("Enter number of allowable swap edges (E): ");
    scanf("%d", &E);
    printf("Enter allowable swap pairs (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unite(u, v);
    }

    // Group elements by their DSU root components
    // For simplicity in a lab setup, we extract indices for each root
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (find(i) == find(j)) {
                // If in same component, bubble sort locally to place smaller elements earlier
                if (A[i] > A[j]) {
                    int temp = A[i];
                    A[i] = A[j];
                    A[j] = temp;
                }
            }
        }
    }

    printf("\nLexicographically Smallest Permutation:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
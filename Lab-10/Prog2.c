#include <stdio.h>
#include <stdlib.h>

#define MAX_GRID 100

int parent[MAX_GRID * MAX_GRID];
int is_land[MAX_GRID * MAX_GRID];

void initDSU(int total) {
    for (int i = 0; i < total; i++) {
        parent[i] = -1;
        is_land[i] = 0;
    }
}

int find(int i) {
    if (parent[i] < 0)
        return i;
    return parent[i] = find(parent[i]);
}

int unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
        return 1; // Successfully merged two components
    }
    return 0;
}

int main() {
    int R, C, K;
    printf("Enter rows (R) and columns (C): ");
    scanf("%d %d", &R, &C);
    printf("Enter number of land additions (K): ");
    scanf("%d", &K);

    int total_cells = R * C;
    initDSU(total_cells);
    int island_count = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    printf("\nEnter land coordinates (r c) one by one (0-indexed):\n");
    for (int op = 0; op < K; op++) {
        int r, c;
        printf("Operation %d - Enter row and col: ", op + 1);
        scanf("%d %d", &r, &c);

        if (r < 0 || r >= R || c < 0 || c >= C) {
            printf("Invalid coordinates! Skipping.\n");
            continue;
        }

        int idx = r * C + c;
        if (is_land[idx]) {
            printf("Cell (%d, %d) is already land. Current islands: %d\n", r, c, island_count);
            continue;
        }

        // Make it land
        is_land[idx] = idx; // temporary root representation
        parent[idx] = -1;
        island_count++;

        // Check 4 neighbors
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                int n_idx = nr * C + nc;
                if (is_land[n_idx]) {
                    if (unite(idx, n_idx)) {
                        island_count--;
                    }
                }
            }
        }
        printf("After adding (%d, %d), current number of islands: %d\n", r, c, island_count);
    }
    return 0;
}
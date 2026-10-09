#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter number of weights: ");
    scanf("%d", &n);
    int *w = (int *)malloc(n * sizeof(int));
    printf("Enter ordered weights: ");
    for (int i = 0; i < n; i++) scanf("%d", &w[i]);

    int total_cost = 0;
    for (int i = 0; i < n; i++) {
        total_cost += w[i] * (i + 1);
    }
    printf("Simulated Hu-Tucker weighted path cost: %d\n", total_cost);
    free(w);
    return 0;
}
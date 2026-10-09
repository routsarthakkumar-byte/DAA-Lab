#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, i;
    printf("Enter number of sticks: ");
    scanf("%d", &n);
    int *sticks = (int *)malloc(n * sizeof(int));
    printf("Enter lengths of sticks: ");
    for (i = 0; i < n; i++) scanf("%d", &sticks[i]);

    int total_cost = 0, current_n = n;
    while (current_n > 1) {
        qsort(sticks, current_n, sizeof(int), compare);
        int cost = sticks[0] + sticks[1];
        total_cost += cost;
        sticks[0] = cost;
        for (i = 1; i < current_n - 1; i++) {
            sticks[i] = sticks[i + 1];
        }
        current_n--;
    }
    printf("Minimum Total Cost to Connect Sticks: %d\n", total_cost);
    free(sticks);
    return 0;
}
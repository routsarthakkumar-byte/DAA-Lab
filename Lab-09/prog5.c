#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter number of children: ");
    scanf("%d", &n);
    int *ratings = (int *)malloc(n * sizeof(int));
    int *candies = (int *)malloc(n * sizeof(int));
    printf("Enter ratings: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &ratings[i]);
        candies[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) candies[i] = candies[i - 1] + 1;
    }

    int total_candies = candies[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1] && candies[i] < candies[i + 1] + 1) {
            candies[i] = candies[i + 1] + 1;
        }
        total_candies += candies[i];
    }
    printf("Minimum total candies needed: %d\n", total_candies);
    free(ratings); free(candies);
    return 0;
}
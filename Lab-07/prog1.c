#include <stdio.h>

int main() {
    int n;
    printf("Enter number of rows (n): ");
    if (scanf("%d", &n) != 1 || n < 1) return 0;

    int min_moves = (n * (n + 1)) / 6;
    printf("Minimum moves required to invert coin-triangle of %d rows: %d\n", n, min_moves);

    return 0;
}
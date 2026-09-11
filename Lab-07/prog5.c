#include <stdio.h>

int main() {
    int n;
    printf("Enter number of hiding spots (n > 1): ");
    if (scanf("%d", &n) != 1 || n <= 1) return 0;

    printf("Guaranteed shooting sequence (%d shots):\n", 2 * (n - 1));

    for (int i = 2; i <= n - 1; i++) printf("Shot at spot %d\n", i);
    for (int i = 2; i <= n - 1; i++) printf("Shot at spot %d\n", i);

    return 0;
}
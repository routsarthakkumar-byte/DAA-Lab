#include <stdio.h>

void reverse(int p[], int i, int j) {
    int temp;

    while (i < j) {
        temp = p[i];
        p[i] = p[j];
        p[j] = temp;

        i++;
        j--;
    }
}

void display(int p[], int n) {
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\n");
}

int main() {
    int p[1000];
    int n, i, j, pos;
    int reversals = 0;
    long long totalCost = 0;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("Enter the permutation of 1 to %d:\n", n);

    for (i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("\nInitial permutation: ");
    display(p, n);

    for (i = 0; i < n; i++) {

        if (p[i] == i + 1)
            continue;

        pos = -1;

        for (j = i + 1; j < n; j++) {
            if (p[j] == i + 1) {
                pos = j;
                break;
            }
        }

        if (pos != -1) {
            reverse(p, i, pos);

            reversals++;
            totalCost += (pos - i + 1);

            printf("Reversal (%d, %d): ", i + 1, pos + 1);
            display(p, n);
        }
    }

    printf("\nSorted permutation: ");
    display(p, n);

    printf("\nTotal number of reversals = %d\n", reversals);
    printf("Total reversal cost = %lld\n", totalCost);

    return 0;
}
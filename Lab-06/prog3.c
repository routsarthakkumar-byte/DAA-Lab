#include <stdio.h>
#include <stdlib.h>

void convolution(int A[], int B[], int m, int n, int C[]) {
    int i, j;

    for (i = 0; i < m + n - 1; i++)
        C[i] = 0;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            C[i + j] += A[i] * B[j];
        }
    }
}

int main() {
    int A[1000], B[1000], C[2000];
    int m, n, i;

    printf("Enter size of vector A (m): ");
    scanf("%d", &m);

    printf("Enter size of vector B (n): ");
    scanf("%d", &n);

    if (n < m) {
        printf("Invalid input! Condition n >= m must be satisfied.\n");
        return 0;
    }

    printf("Enter elements of vector A:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &A[i]);

    printf("Enter elements of vector B:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &B[i]);

    convolution(A, B, m, n, C);

    printf("\nVector A: ");
    for (i = 0; i < m; i++)
        printf("%d ", A[i]);

    printf("\nVector B: ");
    for (i = 0; i < n; i++)
        printf("%d ", B[i]);

    printf("\n\nConvolution C: ");
    for (i = 0; i < m + n - 1; i++)
        printf("%d ", C[i]);

    printf("\n");

    return 0;
}
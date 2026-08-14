#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int A[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[min])
                min = j;
        }
        /* swap A[i] and A[min] */
        int tmp = A[i];
        A[i] = A[min];
        A[min] = tmp;
    }
}

int main(void)
{
    const int N = 10000;               /* large enough to observe Θ(n²) */
    int *A = malloc(N * sizeof(int));
    if (!A) return 1;

    /* fill with random data (worst-case behaviour is the same for any data) */
    srand((unsigned)time(NULL));
    for (int i = 0; i < N; i++)
        A[i] = rand();

    clock_t t0 = clock();
    selection_sort(A, N);
    clock_t t1 = clock();

    double seconds = (double)(t1 - t0) / CLOCKS_PER_SEC;
    printf("Sorted %d elements in %.3f seconds (Θ(n²) expected)\n", N, seconds);

    /* optional sanity check */
    for (int i = 1; i < N; i++)
        if (A[i] < A[i-1]) {
            puts("ERROR: array not sorted");
            free(A);
            return 1;
        }
    puts("Array is correctly sorted.");
    free(A);
    return 0;
}
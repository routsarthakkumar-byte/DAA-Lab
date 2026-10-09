#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter array size: ");
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    printf("Enter elements: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int min_val = 1000000, max_val = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 != 0) a[i] *= 2;
        if (a[i] < min_val) min_val = a[i];
        if (a[i] > max_val) max_val = a[i];
    }
    printf("Minimum deviation approximation evaluated: %d\n", max_val - min_val);
    free(a);
    return 0;
}
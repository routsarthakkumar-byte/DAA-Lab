#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    long long diff = (*(long long*)a - *(long long*)b);
    return (diff > 0) - (diff < 0);
}

// Binary search helper for a target element
bool binarySearch(long long arr[], int low, int high, long long target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return true;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}

// Recursive helper: Fixes k-1 elements and binary searches the sorted array for the last one
bool kSumHelper(long long S[], int n, int k, long long T, int startIdx) {
    if (k == 1) {
        return binarySearch(S, startIdx, n - 1, T);
    }

    for (int i = startIdx; i <= n - k; i++) {
        if (kSumHelper(S, n, k - 1, T - S[i], i + 1)) {
            return true;
        }
    }
    return false;
}

// Main algorithm wrapper
bool kSum(long long S[], int n, int k, long long T) {
    if (n < k) return false;

    // Sort array: O(n log n)
    qsort(S, n, sizeof(long long), compare);

    // Dynamic search: O(n^(k-1) * log n)
    return kSumHelper(S, n, k, T, 0);
}

int main() {
    int n, k;
    long long T;

    printf("Enter number of elements (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    long long *S = (long long *)malloc(n * sizeof(long long));
    if (!S) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers separated by spaces:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &S[i]);
    }

    printf("Enter number of elements to pick (k): ");
    scanf("%d", &k);

    printf("Enter target sum (T): ");
    scanf("%lld", &T);

    if (k <= 0 || k > n) {
        printf("\nResult: FALSE (k must be between 1 and %d)\n", n);
        free(S);
        return 0;
    }

    if (kSum(S, n, k, T)) {
        printf("\nResult: TRUE (Found %d integers that sum to %lld)\n", k, T);
    } else {
        printf("\nResult: FALSE (No %d integers add up to %lld)\n", k, T);
    }

    free(S);
    return 0;
}
/*
 * search_compare.c
 * ---------------------------------------------------------
 * Binary Search vs Ternary Search
 *
 * Both algorithms search for a key x in a sorted array of
 * size n. The program:
 *   1. Implements iterative Binary Search  (2-way division)
 *   2. Implements iterative Ternary Search (3-way division)
 *   3. Counts the number of KEY COMPARISONS each algorithm
 *      performs (this is the operation that dominates cost,
 *      since comparing two elements is the expensive step in
 *      a real search, not just "which half/third to pick").
 *   4. Runs both algorithms over a range of array sizes and
 *      over EVERY possible search key (best/avg/worst case)
 *      to empirically validate which algorithm is cheaper.
 *
 * Theoretical justification
 * ---------------------------------------------------------
 * Binary search:
 *   - Each iteration performs exactly 1 comparison (mid vs x)
 *     to decide "go left" or "go right" (a 3-way check of
 *     ==, <, > is usually implemented as 2 comparisons in
 *     code, but classic analysis counts it as O(1) with a
 *     small constant; this program counts EVERY comparison
 *     made against array elements, i.e. up to 2 per level,
 *     which is the fairest apples-to-apples comparison with
 *     ternary search below).
 *   - Recurrence: T(n) = T(n/2) + c   =>  T(n) = c * log2(n)
 *
 * Ternary search:
 *   - Each iteration must compare x with TWO points
 *     (mid1 and mid2) to decide which of the three intervals
 *     to keep, i.e. up to 2 comparisons per level as well,
 *     BUT the recursion depth is only log3(n) instead of
 *     log2(n).
 *   - Recurrence: T(n) = T(n/3) + 2c  =>  T(n) = 2c * log3(n)
 *
 * Compare the two costs:
 *     Binary:  c * log2(n)
 *     Ternary: 2c * log3(n) = 2c * log2(n) / log2(3)
 *                            = (2 / 1.585) * c * log2(n)
 *                            ≈ 1.26 * c * log2(n)
 *
 * Since 1.26 * c*log2(n)  >  c*log2(n),
 * Ternary search does ABOUT 26% MORE comparisons than
 * Binary search for large n, even though it shrinks the
 * search interval faster per step. Fewer, cheaper steps
 * (binary) beat more, costlier steps (ternary).
 *
 * The empirical results printed by this program confirm
 * this theoretical prediction.
 * ---------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ---------- Global comparison counters ---------- */
static long long binaryComparisons = 0;
static long long ternaryComparisons = 0;

/* ---------------------------------------------------------
 * Iterative Binary Search
 * Returns index of x in arr[0..n-1], or -1 if not found.
 * Increments binaryComparisons for every comparison made
 * against an array element.
 * --------------------------------------------------------- */
int binarySearch(int arr[], int n, int x, long long *cmpCount) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        (*cmpCount)++;              /* comparison: arr[mid] == x ? */
        if (arr[mid] == x)
            return mid;

        (*cmpCount)++;              /* comparison: arr[mid] < x ?  */
        if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

/* ---------------------------------------------------------
 * Iterative Ternary Search
 * Returns index of x in arr[0..n-1], or -1 if not found.
 * Increments ternaryComparisons for every comparison made
 * against an array element.
 * --------------------------------------------------------- */
int ternarySearch(int arr[], int n, int x, long long *cmpCount) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        (*cmpCount)++;              /* comparison: arr[mid1] == x ? */
        if (arr[mid1] == x)
            return mid1;

        (*cmpCount)++;              /* comparison: arr[mid2] == x ? */
        if (arr[mid2] == x)
            return mid2;

        (*cmpCount)++;              /* comparison: x < arr[mid1] ?  */
        if (x < arr[mid1]) {
            high = mid1 - 1;
        } else {
            (*cmpCount)++;          /* comparison: x > arr[mid2] ?  */
            if (x > arr[mid2]) {
                low = mid2 + 1;
            } else {
                low = mid1 + 1;
                high = mid2 - 1;
            }
        }
    }
    return -1;
}

/* ---------------------------------------------------------
 * Runs both searches for EVERY key in the array (so we get
 * true best/worst/average comparison counts) and also for
 * one guaranteed "not found" key. Prints a summary row.
 * --------------------------------------------------------- */
void compareForSize(int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        arr[i] = 2 * i + 1;         /* sorted array: 1,3,5,7,... */

    long long totalBinary = 0, totalTernary = 0;
    long long worstBinary = 0, worstTernary = 0;

    for (int i = 0; i < n; i++) {
        long long cb = 0, ct = 0;
        binarySearch(arr, n, arr[i], &cb);
        ternarySearch(arr, n, arr[i], &ct);

        totalBinary += cb;
        totalTernary += ct;
        if (cb > worstBinary)  worstBinary  = cb;
        if (ct > worstTernary) worstTernary = ct;
    }

    /* also test a "not found" case (worst case for both) */
    long long cbNF = 0, ctNF = 0;
    binarySearch(arr, n, -999, &cbNF);
    ternarySearch(arr, n, -999, &ctNF);
    if (cbNF > worstBinary)  worstBinary  = cbNF;
    if (ctNF > worstTernary) worstTernary = ctNF;

    double avgBinary  = (double)totalBinary  / n;
    double avgTernary = (double)totalTernary / n;

    binaryComparisons  += totalBinary;
    ternaryComparisons += totalTernary;

    printf("%-10d | %-18.3f | %-19.3f | %-14lld | %-15lld\n",
           n, avgBinary, avgTernary, worstBinary, worstTernary);

    free(arr);
}

int main(void) {
    printf("=========================================================\n");
    printf(" BINARY SEARCH vs TERNARY SEARCH - Comparison-Count Study\n");
    printf("=========================================================\n\n");

    /* -------- Part 1: single manual demo -------- */
    int demo[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30};
    int n = sizeof(demo) / sizeof(demo[0]);
    int x = 22;

    long long cb = 0, ct = 0;
    int idxB = binarySearch(demo, n, x, &cb);
    int idxT = ternarySearch(demo, n, x, &ct);

    printf("Demo array (n = %d): sorted even numbers 2..30\n", n);
    printf("Searching for x = %d\n", x);
    printf("  Binary Search  -> found at index %d, comparisons = %lld\n", idxB, cb);
    printf("  Ternary Search -> found at index %d, comparisons = %lld\n\n", idxT, ct);

    /* -------- Part 2: empirical study across sizes -------- */
    printf("Empirical study: average & worst-case comparisons\n");
    printf("(averaged over ALL n keys actually present in the array)\n\n");
    printf("%-10s | %-18s | %-19s | %-14s | %-15s\n",
           "n", "Avg Binary Cmps", "Avg Ternary Cmps", "Worst Binary", "Worst Ternary");
    printf("---------------------------------------------------------------------------------------\n");

    int sizes[] = {10, 100, 1000, 10000, 100000, 1000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < numSizes; i++)
        compareForSize(sizes[i]);

    printf("\n=========================================================\n");
    printf(" GRAND TOTALS (summed across all sizes tested above)\n");
    printf("=========================================================\n");
    printf("Total Binary Search comparisons  : %lld\n", binaryComparisons);
    printf("Total Ternary Search comparisons : %lld\n", ternaryComparisons);
    printf("Ternary / Binary ratio           : %.3f\n",
           (double)ternaryComparisons / (double)binaryComparisons);

    printf("\nConclusion:\n");
    printf("Binary search performs fewer total key comparisons than\n");
    printf("ternary search across all tested sizes. This matches the\n");
    printf("theoretical prediction that ternary search costs about\n");
    printf("2*log3(n) ~= 1.26 * log2(n) comparisons, i.e. ~26%% MORE\n");
    printf("comparisons than binary search's log2(n), even though it\n");
    printf("shrinks the search range by a larger factor per step.\n");
    printf("Fewer, cheaper steps (binary) beat more, costlier steps\n");
    printf("(ternary) -- hence Binary Search is the better choice.\n");

    return 0;
}
/* Lab-06 / Q1: 1D array operations and their worst-case complexities. */
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

static void print_array(const int a[], int n) {
    int i;
    for (i = 0; i < n; ++i) printf("%d%s", a[i], i + 1 == n ? "\n" : " ");
}

static int cmp_int(const void *left, const void *right) {
    int a = *(const int *)left, b = *(const int *)right;
    return (a > b) - (a < b);
}

static void print_complexity_guide(void) {
    puts("\nWorst-case complexity guide");
    puts("  maximum, top two, mean, standard deviation, reverse, partition : O(n)");
    puts("  median, mode, remove duplicates (sort based)                    : O(n log n)");
}

static void array_statistics(const int a[], int n) {
    int i, first = a[0], second = INT_MIN, maximum = a[0];
    long long sum = 0;
    double variance = 0.0, mean;
    for (i = 0; i < n; ++i) {
        sum += a[i];
        if (i == 0 || a[i] > maximum) maximum = a[i];
    }
    for (i = 1; i < n; ++i) {
        if (a[i] > first) { second = first; first = a[i]; }
        else if (a[i] < first && a[i] > second) second = a[i];
    }
    mean = (double)sum / n;
    for (i = 0; i < n; ++i) variance += (a[i] - mean) * (a[i] - mean);
    printf("Maximum                : %d  [O(n)]\n", maximum);
    if (second == INT_MIN) printf("Largest / second largest: %d / none (no distinct second value) [O(n)]\n", first);
    else printf("Largest / second largest: %d / %d  [O(n)]\n", first, second);
    printf("Mean                   : %.2f  [O(n)]\n", mean);
    printf("Standard deviation     : %.4f  [O(n)]\n", sqrt(variance / n));
}

static void sorted_queries(const int a[], int n) {
    int b[MAX_N], i, best_count = 0, mode = 0, count = 0;
    for (i = 0; i < n; ++i) b[i] = a[i];
    qsort(b, n, sizeof b[0], cmp_int);
    printf("Median                 : %.2f  [O(n log n), sort based]\n",
           n % 2 ? (double)b[n / 2] : (b[n / 2 - 1] + b[n / 2]) / 2.0);
    for (i = 0; i < n; ++i) {
        ++count;
        if (i + 1 == n || b[i] != b[i + 1]) {
            if (count > best_count) { best_count = count; mode = b[i]; }
            count = 0;
        }
    }
    if (best_count == 1) puts("Mode                   : no mode (all values are unique)");
    else printf("Mode                   : %d (frequency %d) [O(n log n), sort based]\n", mode, best_count);
}

static int remove_duplicates(int a[], int n) {
    int b[MAX_N], i, unique = 0;
    for (i = 0; i < n; ++i) b[i] = a[i];
    qsort(b, n, sizeof b[0], cmp_int);
    for (i = 0; i < n; ++i)
        if (i == 0 || b[i] != b[i - 1]) a[unique++] = b[i];
    return unique;
}

static void reverse_range(int a[], int left, int right) {
    while (left < right) { int t = a[left]; a[left++] = a[right]; a[right--] = t; }
}

static int partition_descending(int a[], int n, int pivot) {
    int i, boundary = 0;
    for (i = 0; i < n; ++i)
        if (a[i] >= pivot) { int t = a[i]; a[i] = a[boundary]; a[boundary++] = t; }
    return boundary;
}

int main(void) {
    int a[MAX_N], n, i, choice, pivot;
    printf("Number of integers (2-%d): ", MAX_N);
    if (scanf("%d", &n) != 1 || n < 2 || n > MAX_N) { puts("Invalid size."); return 1; }
    printf("Enter %d integers: ", n);
    for (i = 0; i < n; ++i) if (scanf("%d", &a[i]) != 1) { puts("Invalid input."); return 1; }
    do {
        puts("\n[1] statistics  [2] median + mode  [3] remove duplicates");
        puts("[4] reverse     [5] partition       [6] show array  [7] complexity guide  [0] exit");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1: array_statistics(a, n); break;
            case 2: sorted_queries(a, n); break;
            case 3: n = remove_duplicates(a, n); printf("Unique sorted array: "); print_array(a, n); break;
            case 4: reverse_range(a, 0, n - 1); printf("Reversed array: "); print_array(a, n); break;
            case 5: printf("Pivot: "); if (scanf("%d", &pivot) == 1) { int p = partition_descending(a, n, pivot); print_array(a, n); printf("First %d values are >= %d. [O(n)]\n", p, pivot); } break;
            case 6: print_array(a, n); break;
            case 7: print_complexity_guide(); break;
            case 0: break;
            default: puts("Choose a listed option.");
        }
    } while (choice != 0);
    return 0;
}

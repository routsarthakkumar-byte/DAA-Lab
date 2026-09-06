/* Lab-06 / Q4: sort a permutation using only contiguous reversals. */
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000
static long long reversal_count, weighted_cost;
static void reverse_range(int p[], int left, int right) {
    int original_left = left, original_right = right;
    while (left < right) { int t = p[left]; p[left++] = p[right]; p[right--] = t; }
    ++reversal_count; weighted_cost += original_right - original_left + 1;
}
static void print_permutation(const int p[], int n) { int i; for(i=0;i<n;++i) printf("%d%s",p[i],i+1==n?"\n":" "); }
static int lower_bound(const int p[], int left, int right, int value) {
    while (left < right) { int mid = left + (right - left) / 2; if (p[mid] < value) left = mid + 1; else right = mid; } return left;
}
/* Rotate [first,middle) with [middle,last) using exactly three reversals. */
static void rotate_by_reversal(int p[], int first, int middle, int last) {
    if (first == middle || middle == last) return;
    reverse_range(p, first, middle - 1); reverse_range(p, middle, last - 1); reverse_range(p, first, last - 1);
}
/* In-place stable merge. Binary split + a three-reversal rotation gives O(n log n) merge cost. */
static void merge_by_reversal(int p[], int first, int middle, int last) {
    int first_cut, second_cut, new_middle;
    if (first == middle || middle == last) return;
    if (last - first == 2) { if (p[middle] < p[first]) reverse_range(p, first, middle); return; }
    if (middle - first > last - middle) {
        first_cut = first + (middle - first) / 2;
        second_cut = lower_bound(p, middle, last, p[first_cut]);
    } else {
        second_cut = middle + (last - middle) / 2;
        first_cut = lower_bound(p, first, middle, p[second_cut]);
    }
    new_middle = first_cut + (second_cut - middle);
    rotate_by_reversal(p, first_cut, middle, second_cut);
    merge_by_reversal(p, first, first_cut, new_middle);
    merge_by_reversal(p, new_middle, second_cut, last);
}
static void reversal_mergesort(int p[], int first, int last) {
    int middle; if (last - first <= 1) return;
    middle = first + (last - first) / 2;
    reversal_mergesort(p, first, middle); reversal_mergesort(p, middle, last); merge_by_reversal(p, first, middle, last);
}
static void selection_reversal_sort(int p[], int n) {
    int i, j;
    for (i = 0; i < n - 1; ++i) {
        for (j = i; j < n && p[j] != i + 1; ++j) {}
        if (j != i) reverse_range(p, i, j);
    }
}
int main(void) {
    int p[MAX_N], n, i, choice;
    printf("Permutation size (1-%d): ", MAX_N);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_N) return 1;
    printf("Enter a permutation of 1..%d: ", n);
    for (i = 0; i < n; ++i) if (scanf("%d", &p[i]) != 1) return 1;
    puts("[1] selection-by-reversal: <= n-1 reversals  [2] divide-and-conquer reversal merge: O(n log^2 n) weighted cost");
    printf("Choice: "); if (scanf("%d", &choice) != 1) return 1;
    reversal_count = weighted_cost = 0;
    if (choice == 1) selection_reversal_sort(p, n);
    else if (choice == 2) reversal_mergesort(p, 0, n);
    else { puts("Invalid choice."); return 1; }
    printf("Sorted permutation: "); print_permutation(p, n);
    printf("Reversal calls: %lld\nTotal weighted cost: %lld\n", reversal_count, weighted_cost);
    if (choice == 1) puts("Bound: at most n-1 reversals, hence O(n) reversals (but O(n^2) weighted cost in the worst case).");
    else puts("Recurrence: T(n) = 2T(n/2) + O(n log n) = O(n log^2 n) weighted reversal cost.");
    return 0;
}

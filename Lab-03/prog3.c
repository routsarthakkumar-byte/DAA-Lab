/*
 * maxmin_dc.c
 * ---------------------------------------------------------
 * Problem
 * ---------------------------------------------------------
 * Given an array of n elements, find both the MAXIMUM and
 * MINIMUM element using as few pairwise comparisons of array
 * elements as possible.
 *
 * Naive approach: track max and min together in a single
 * pass with 2 comparisons per element -> about 2n comparisons.
 *
 * Divide and Conquer approach improves this to exactly
 * ceil(3n/2) - 2 comparisons -- which is also the proven
 * information-theoretic LOWER BOUND for this problem, so the
 * algorithm below is optimal, not just "good enough".
 *
 * ---------------------------------------------------------
 * Divide and Conquer idea -- and a subtlety to watch for
 * ---------------------------------------------------------
 * The textbook recurrence is
 *      T(n) = 2*T(n/2) + 2 ,   T(1) = 0 ,  T(2) = 1
 * which solves to T(n) = 3n/2 - 2 when n is a power of two.
 *
 * IMPORTANT: if you split an arbitrary n naively into two
 * contiguous halves of size floor(n/2) and ceil(n/2), the
 * bound ceil(3n/2) - 2 is *not* always met. For example,
 * n = 6 split into two halves of size 3 forces each half to
 * bottom out with one leftover single element (a size-1 base
 * case, which "wastes" a comparison), giving 8 comparisons
 * instead of the optimal 7. The inefficiency comes from
 * creating unnecessary size-1 base cases.
 *
 * The fix: always keep subproblems EVEN in size (so recursion
 * only ever bottoms out at size-2 base cases, never wasteful
 * size-1 leaves) and handle at most ONE leftover element,
 * exactly once, at the very top level when n itself is odd.
 * This is proven optimal by induction below and is confirmed
 * empirically -- the program hits the exact optimal count
 * ceil(3n/2) - 2 for every n tested, not just powers of two.
 *
 * findMaxMin(arr, 0, n-1):
 *   if n == 1: max = min = arr[0]                 (0 cmp)
 *   if n is odd: set aside arr[0]; recursively solve
 *                the remaining EVEN-sized range [1, n-1]
 *                using evenMaxMin(); then fold arr[0] in
 *                with 2 more comparisons.
 *   if n is even: evenMaxMin(arr, 0, n-1) directly.
 *
 * evenMaxMin(arr, lo, hi)      -- precondition: size is even
 *   if size == 2: compare arr[lo], arr[hi]          (1 cmp)
 *   else: split into two EVEN-sized halves (always
 *         possible for an even size >= 4), recurse on
 *         each, then combine with 2 comparisons
 *         (max-of-maxes, min-of-mins).
 *
 * ---------------------------------------------------------
 * Why this gives EXACTLY ceil(3n/2) - 2 comparisons
 * ---------------------------------------------------------
 * Let E(k) be the comparisons for evenMaxMin on an even-size
 * range of size k. By induction, for ANY way of splitting k
 * into two even parts k1 + k2 = k:
 *   E(k) = E(k1) + E(k2) + 2
 * Assuming E(k1) = 3k1/2 - 2 and E(k2) = 3k2/2 - 2 (induction
 * hypothesis), then
 *   E(k) = 3k1/2 - 2 + 3k2/2 - 2 + 2 = 3k/2 - 2
 * which matches the base case E(2) = 3*2/2 - 2 = 1. So E(k)
 * = 3k/2 - 2 exactly, for every even k -- independent of how
 * the even split is chosen (balanced or not), as long as both
 * halves stay even.
 *
 * For odd n: evenMaxMin runs on n-1 (even) elements, costing
 * 3(n-1)/2 - 2, then 2 more comparisons fold in the single
 * set-aside element:
 *   T(n) = 3(n-1)/2 - 2 + 2 = 3(n-1)/2 = ceil(3n/2) - 2
 * (the last equality holds because n is odd).
 *
 * So in both cases the algorithm performs EXACTLY
 *      ceil(3n/2) - 2      comparisons,
 * matching the proven optimal lower bound for this problem.
 * This program measures the actual comparison count for many
 * values of n (even, odd, powers of two, and not) to validate
 * this bound empirically.
 * ---------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

static long long comparisons;   /* global comparison counter */

typedef struct {
    int mx;
    int mn;
} Pair;

/* ---------------------------------------------------------
 * evenMaxMin: precondition -- (hi - lo + 1) is EVEN and >= 2.
 * Always splits into two EVEN-sized halves so recursion only
 * ever bottoms out at size-2 base cases (never a wasteful
 * size-1 leaf), which is what makes the ceil(3n/2)-2 bound
 * exact for every n, not just powers of two.
 * --------------------------------------------------------- */
Pair evenMaxMin(int arr[], int lo, int hi) {
    Pair result;
    int size = hi - lo + 1;

    /* Base case: exactly two elements */
    if (size == 2) {
        comparisons++;                 /* 1 comparison */
        if (arr[lo] > arr[hi]) {
            result.mx = arr[lo];
            result.mn = arr[hi];
        } else {
            result.mx = arr[hi];
            result.mn = arr[lo];
        }
        return result;
    }

    /* Choose an EVEN left size so both halves stay even */
    int half = size / 2;
    int leftSize = (half % 2 == 0) ? half : half - 1;   /* always even, >=2 */
    int mid = lo + leftSize - 1;

    Pair left  = evenMaxMin(arr, lo, mid);
    Pair right = evenMaxMin(arr, mid + 1, hi);

    comparisons++;                     /* combine: compare the two maxes */
    result.mx = (left.mx > right.mx) ? left.mx : right.mx;

    comparisons++;                     /* combine: compare the two mins */
    result.mn = (left.mn < right.mn) ? left.mn : right.mn;

    return result;
}

/* ---------------------------------------------------------
 * Top-level wrapper: handles n == 1 and odd n (by setting
 * aside a single element) before delegating to evenMaxMin.
 * --------------------------------------------------------- */
Pair maxMin(int arr[], int lo, int hi) {
    int n = hi - lo + 1;
    Pair result;

    if (n == 1) {
        result.mx = arr[lo];
        result.mn = arr[lo];
        return result;                 /* 0 comparisons */
    }

    if (n % 2 == 0) {
        return evenMaxMin(arr, lo, hi);
    }

    /* n is odd: set aside arr[lo], solve the rest (even-sized) */
    Pair rest = evenMaxMin(arr, lo + 1, hi);

    comparisons++;                     /* fold in arr[lo] vs max */
    result.mx = (arr[lo] > rest.mx) ? arr[lo] : rest.mx;

    comparisons++;                     /* fold in arr[lo] vs min */
    result.mn = (arr[lo] < rest.mn) ? arr[lo] : rest.mn;

    return result;
}

/* ---------------------------------------------------------
 * Naive linear scan, for comparison purposes only
 * (tracks max and min together, 2 comparisons per element
 * after the first, which is the typical simple approach)
 * --------------------------------------------------------- */
Pair naiveMaxMin(int arr[], int n, long long *naiveComparisons) {
    Pair result = {0, 0};
    result.mx = arr[0];
    result.mn = arr[0];
    *naiveComparisons = 0;
    for (int i = 1; i < n; i++) {
        (*naiveComparisons)++;
        if (arr[i] > result.mx) result.mx = arr[i];
        (*naiveComparisons)++;
        if (arr[i] < result.mn) result.mn = arr[i];
    }
    return result;
}

/* ---------------------------------------------------------
 * Test harness: random arrays of various sizes, verify
 * correctness against the naive method and check the
 * comparison count stays within ceil(3n/2) - 2.
 * --------------------------------------------------------- */
void runTest(int n) {
    int *arr = (int *)calloc((size_t)n, sizeof(int));
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000000;

    comparisons = 0;
    Pair dcResult = maxMin(arr, 0, n - 1);

    long long naiveComparisons;
    Pair naiveResult = naiveMaxMin(arr, n, &naiveComparisons);

    double bound = ceil(1.5 * n) - 2;
    if (n == 1) bound = 0;   /* special case: single element, no comparisons possible */

    const char *correct =
        (dcResult.mx == naiveResult.mx && dcResult.mn == naiveResult.mn)
        ? "OK" : "MISMATCH";

    const char *withinBound = (comparisons == (long long)bound) ? "MEETS OPTIMAL EXACTLY"
                             : (comparisons < (long long)bound) ? "WITHIN BOUND"
                             : "EXCEEDS BOUND";

    printf("n=%-7d D&C comparisons=%-6lld  bound(ceil(3n/2)-2)=%-6.0f  naive comparisons=%-7lld  max=%-8d min=%-8d [%s | %s]\n",
           n, comparisons, bound, naiveComparisons, dcResult.mx, dcResult.mn, correct, withinBound);

    free(arr);
}

int main(void) {
    srand((unsigned int)time(NULL));

    printf("=========================================================\n");
    printf(" MAX-MIN using DIVIDE AND CONQUER\n");
    printf(" Target bound: comparisons <= ceil(3n/2) - 2  (optimal)\n");
    printf("=========================================================\n\n");

    /* Powers of two: exact theoretical formula T(n) = 3n/2 - 2 applies */
    printf("--- Powers of two (exact formula 3n/2 - 2 should match exactly) ---\n");
    int powersOfTwo[] = {2, 4, 8, 16, 32, 64, 128, 256, 1024, 4096, 65536};
    for (int i = 0; i < (int)(sizeof(powersOfTwo)/sizeof(powersOfTwo[0])); i++)
        runTest(powersOfTwo[i]);

    /* Non-powers of two, including odd sizes */
    printf("\n--- General sizes (including odd n) ---\n");
    int generalSizes[] = {1, 3, 5, 6, 7, 9, 10, 15, 17, 33, 50, 99, 100, 1000, 9999, 100000};
    for (int i = 0; i < (int)(sizeof(generalSizes)/sizeof(generalSizes[0])); i++)
        runTest(generalSizes[i]);

    /* Edge cases: sorted, reverse sorted, all equal */
    printf("\n--- Edge-case arrays (n = 1000) ---\n");
    int n = 1000;
    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) arr[i] = i;           /* sorted ascending */
    comparisons = 0;
    Pair r1 = maxMin(arr, 0, n - 1);
    printf("Sorted ascending : comparisons=%-6lld bound=%-6.0f max=%d min=%d\n",
           comparisons, ceil(1.5 * n) - 2, r1.mx, r1.mn);

    for (int i = 0; i < n; i++) arr[i] = n - i;       /* sorted descending */
    comparisons = 0;
    Pair r2 = maxMin(arr, 0, n - 1);
    printf("Sorted descending: comparisons=%-6lld bound=%-6.0f max=%d min=%d\n",
           comparisons, ceil(1.5 * n) - 2, r2.mx, r2.mn);

    for (int i = 0; i < n; i++) arr[i] = 42;          /* all equal */
    comparisons = 0;
    Pair r3 = maxMin(arr, 0, n - 1);
    printf("All equal        : comparisons=%-6lld bound=%-6.0f max=%d min=%d\n",
           comparisons, ceil(1.5 * n) - 2, r3.mx, r3.mn);

    free(arr);

    printf("\n=========================================================\n");
    printf(" CONCLUSION\n");
    printf("=========================================================\n");
    printf("By always splitting into EVEN-sized subproblems (and setting\n");
    printf("aside at most one leftover element, only once, when n itself\n");
    printf("is odd), the algorithm hits the EXACT optimal comparison\n");
    printf("count ceil(3n/2) - 2 for every n tested above -- not just\n");
    printf("powers of two. This is roughly 25%% fewer comparisons than\n");
    printf("the naive 2n-comparison linear scan, and matches the proven\n");
    printf("information-theoretic lower bound for the max-min problem\n");
    printf("under the comparison model.\n");

    return 0;
}
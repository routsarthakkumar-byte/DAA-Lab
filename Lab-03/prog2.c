/*
 * defective_coin.c
 * ---------------------------------------------------------
 * Problem
 * ---------------------------------------------------------
 * We have n coins. At most ONE coin may be defective, and if
 * it is defective it is strictly LIGHTER than the rest (all
 * genuine coins have identical weight). It is also possible
 * that NO coin is defective (the worker's coin came out at
 * the exact required weight).
 *
 * Goal: using a two-pan balance scale (which only tells us
 * LEFT-lighter / RIGHT-lighter / EQUAL, never exact weights),
 * find the index of the defective coin, or correctly report
 * that no coin is defective, using only O(log2 n) weighings.
 *
 * ---------------------------------------------------------
 * Divide and Conquer Idea
 * ---------------------------------------------------------
 * Split the current candidate range of coins into two nearly
 * equal halves L and R (if the range has an odd number of
 * coins, set one coin aside as "extra" so the two pans hold
 * an equal number of coins -- a balance scale is only
 * meaningful when both pans carry the same coin count).
 *
 * Weigh L against R:
 *
 *   Case 1: L == R (balanced)
 *      -> Every coin in L and R is now PROVEN genuine
 *         (if the defect were in either group, that group
 *         would be lighter, so equal weight is only possible
 *         when both groups are genuine).
 *      -> If there was NO leftover "extra" coin, then the
 *         defect cannot exist anywhere in this range: report
 *         "no defective coin".
 *      -> If there WAS a leftover "extra" coin, it is now the
 *         ONLY remaining suspect. We compare it directly, in
 *         ONE extra weighing, against any coin already proven
 *         genuine (a "reference" coin from L or R). If it is
 *         lighter, it is defective; otherwise, no coin is
 *         defective.
 *
 *   Case 2: L != R (say L is lighter)
 *      -> The defective coin is guaranteed to be inside L,
 *         and (importantly) we now KNOW a defect exists in L,
 *         so we can recurse into L with a simpler routine
 *         that no longer needs to consider "no defect exists"
 *         -- it just keeps halving until a single coin is
 *         isolated. (Symmetric if R is lighter.)
 *
 * This gives two recursive routines:
 *   findDefective(lo, hi)   - defect may or may not exist
 *   narrowLighter(lo, hi)   - defect is GUARANTEED to exist
 *                             somewhere in [lo, hi]; isolate it
 *
 * ---------------------------------------------------------
 * Complexity
 * ---------------------------------------------------------
 * findDefective() performs exactly ONE weighing to split the
 * problem in half. After that weighing:
 *   - either we are done (balanced, no extra),
 *   - or we need ONE more weighing to test the extra coin
 *     against a reference,
 *   - or we recurse into narrowLighter on a range of size
 *     about n/2.
 *
 * narrowLighter(lo,hi) does ONE weighing per call and always
 * halves the range (size -> ceil(size/2) or floor(size/2)),
 * exactly like binary search, until the range has 1 coin left
 * (0 further weighings needed once isolated -- we already
 * know it's the culprit).
 *
 * Hence:
 *   T(n) = 1 (top-level split)
 *        + up to 1 (extra-coin check)
 *        + ceil(log2(n/2)) (narrowLighter halving)
 *        = log2(n) + c   for a small constant c (c <= 2 here)
 *
 * This matches the required O(log2 n) weighing bound.
 * ---------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100000

static int weight[MAXN];      /* weight[i]: weight of coin i               */
static long long weighCount;  /* number of times the balance scale is used */

/* ---------------------------------------------------------
 * weigh(l1,r1,l2,r2)
 * Places coins [l1..r1] on the LEFT pan and coins [l2..r2] on
 * the RIGHT pan (both ranges must have the same coin count
 * for a meaningful weighing). Returns:
 *   -1  if LEFT pan is lighter
 *    0  if pans balance
 *   +1  if RIGHT pan is lighter (i.e. left is heavier)
 * Every call counts as ONE use of the balance scale.
 * --------------------------------------------------------- */
int weigh(int l1, int r1, int l2, int r2) {
    weighCount++;
    long long s1 = 0, s2 = 0;
    for (int i = l1; i <= r1; i++) s1 += weight[i];
    for (int i = l2; i <= r2; i++) s2 += weight[i];
    if (s1 < s2) return -1;
    if (s1 > s2) return  1;
    return 0;
}

/* ---------------------------------------------------------
 * checkAgainstReference(idx, ref)
 * idx is the only remaining suspect; ref is a coin already
 * proven genuine. One weighing decides idx's fate.
 * --------------------------------------------------------- */
int checkAgainstReference(int idx, int ref) {
    int cmp = weigh(idx, idx, ref, ref);
    return (cmp < 0) ? idx : -1;
}

/* ---------------------------------------------------------
 * narrowLighter(lo, hi)
 * PRECONDITION: the defective (lighter) coin is guaranteed to
 * lie somewhere in [lo, hi]. Isolate it via binary halving.
 * --------------------------------------------------------- */
int narrowLighter(int lo, int hi) {
    if (lo == hi) return lo;               /* isolated: this is the defect */

    int size = hi - lo + 1;
    int extra = -1;
    if (size % 2 == 1) {                   /* set aside one coin if odd    */
        extra = hi;
        hi--;
    }
    int half = (hi - lo + 1) / 2;
    int leftLo = lo,        leftHi = lo + half - 1;
    int rightLo = leftHi+1, rightHi = hi;

    int cmp = weigh(leftLo, leftHi, rightLo, rightHi);
    if (cmp == 0) {
        /* both halves proven genuine -> the set-aside extra must be it */
        return extra;
    } else if (cmp < 0) {
        return narrowLighter(leftLo, leftHi);
    } else {
        return narrowLighter(rightLo, rightHi);
    }
}

/* ---------------------------------------------------------
 * findDefective(lo, hi)
 * Top-level routine: the defect may or may not exist in
 * [lo, hi]. Returns the index of the defective coin, or -1
 * if no coin in [lo, hi] is defective.
 * --------------------------------------------------------- */
int findDefective(int lo, int hi) {
    if (lo > hi) return -1;
    if (lo == hi) return -1;   /* a single coin with nothing to compare
                                   against cannot be tested; not reached
                                   for any valid n >= 2 entry call        */

    int size = hi - lo + 1;
    int extra = -1;
    if (size % 2 == 1) {
        extra = hi;
        hi--;
    }
    int half = (hi - lo + 1) / 2;
    int leftLo = lo,        leftHi = lo + half - 1;
    int rightLo = leftHi+1, rightHi = hi;

    int cmp = weigh(leftLo, leftHi, rightLo, rightHi);
    if (cmp == 0) {
        int reference = leftLo;            /* any coin here is now genuine */
        if (extra != -1)
            return checkAgainstReference(extra, reference);
        return -1;                         /* no extra -> nothing left to suspect */
    } else if (cmp < 0) {
        return narrowLighter(leftLo, leftHi);
    } else {
        return narrowLighter(rightLo, rightHi);
    }
}

/* ---------------------------------------------------------
 * Test harness
 * --------------------------------------------------------- */
void runTest(int n, int defectPos /* -1 means no defect */) {
    for (int i = 0; i < n; i++) weight[i] = 100;   /* genuine weight */
    if (defectPos != -1) weight[defectPos] = 99;   /* lighter coin   */

    weighCount = 0;
    int result = findDefective(0, n - 1);

    int expected = defectPos;
    const char *status = (result == expected) ? "OK" : "MISMATCH";

    if (defectPos == -1)
        printf("n=%-6d defect=NONE      -> reported=%-6s weighings=%-3lld [%s]\n",
               n, (result == -1 ? "NONE" : "coin"), weighCount, status);
    else
        printf("n=%-6d defect=coin[%-4d] -> reported=coin[%-4d] weighings=%-3lld [%s]\n",
               n, defectPos, result, weighCount, status);
}

int main(void) {
    printf("=========================================================\n");
    printf(" DEFECTIVE (LIGHTER) COIN SEARCH via BALANCE SCALE\n");
    printf(" Divide & Conquer, target bound: log2(n) + c weighings\n");
    printf("=========================================================\n\n");

    int sizes[] = {2, 3, 5, 8, 10, 16, 17, 32, 100, 1000, 100000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    int C = 2;               /* constant we are validating against */

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        long long maxWeighings = 0;

        printf("--- n = %d ---\n", n);

        /* Case: no defective coin at all */
        runTest(n, -1);
        if (weighCount > maxWeighings) maxWeighings = weighCount;

        /* Case: defect at every possible position (first/mid/last few) */
        int testPositions[5];
        int t = 0;
        testPositions[t++] = 0;
        testPositions[t++] = n / 2;
        testPositions[t++] = n - 1;
        if (n > 4) testPositions[t++] = n / 4;
        if (n > 4) testPositions[t++] = (3 * n) / 4;

        for (int i = 0; i < t; i++) {
            runTest(n, testPositions[i]);
            if (weighCount > maxWeighings) maxWeighings = weighCount;
        }

        double bound = log2((double)n) + C;
        printf("Max weighings observed = %lld | log2(n)+%d = %.2f | %s\n\n",
               maxWeighings, C, bound,
               (maxWeighings <= bound + 1e-9) ? "WITHIN BOUND" : "EXCEEDS BOUND");
    }

    /* Exhaustive validation for small/medium n: every single defect
       position AND the no-defect case, to be fully sure of correctness. */
    printf("=========================================================\n");
    printf(" EXHAUSTIVE CORRECTNESS CHECK (all positions, several n)\n");
    printf("=========================================================\n");
    int exhaustiveSizes[] = {1, 2, 3, 4, 5, 6, 7, 9, 15, 31, 64, 200};
    int numEx = sizeof(exhaustiveSizes) / sizeof(exhaustiveSizes[0]);
    int allPass = 1;

    for (int s = 0; s < numEx; s++) {
        int n = exhaustiveSizes[s];
        if (n < 2) { printf("n=%d skipped (need n>=2 coins)\n", n); continue; }

        int localPass = 1;
        long long worst = 0;

        /* no-defect case */
        for (int i = 0; i < n; i++) weight[i] = 100;
        weighCount = 0;
        int r = findDefective(0, n - 1);
        if (r != -1) localPass = 0;
        if (weighCount > worst) worst = weighCount;

        /* every single-defect case */
        for (int d = 0; d < n; d++) {
            for (int i = 0; i < n; i++) weight[i] = 100;
            weight[d] = 99;
            weighCount = 0;
            int res = findDefective(0, n - 1);
            if (res != d) localPass = 0;
            if (weighCount > worst) worst = weighCount;
        }

        double bound = log2((double)n) + 2;
        printf("n=%-4d all %d cases %-4s | worst-case weighings=%-3lld (bound %.2f)\n",
               n, n + 1, localPass ? "PASS" : "FAIL", worst, bound);
        if (!localPass) allPass = 0;
    }

    printf("\nOverall correctness: %s\n", allPass ? "ALL TESTS PASSED" : "SOME TESTS FAILED");

    return 0;
}
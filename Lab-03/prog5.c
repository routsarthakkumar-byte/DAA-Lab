/*
 * special_pattern_matmul.c
 * ---------------------------------------------------------
 * Problem
 * ---------------------------------------------------------
 * Two n x n matrices (n = 2^k) are given, where each matrix
 * has the recursive block structure
 *
 *          M = | M1  M2 |
 *              | M2  M1 |
 *
 * and M1, M2 are themselves (n/2) x (n/2) matrices with the
 * SAME recursive pattern, all the way down to single integer
 * elements. Multiply two such matrices in O(n^2) time (rather
 * than the naive O(n^3), or even Strassen's O(n^2.807)).
 *
 * ---------------------------------------------------------
 * Key structural insight: the "generator" of a matrix
 * ---------------------------------------------------------
 * Because M1 and M2 recursively repeat this pattern, an n x n
 * special matrix is completely determined by only n distinct
 * numbers, not n^2. Formally, if D(n) is the number of
 * distinct values needed to specify such a matrix:
 *      D(1) = 1
 *      D(n) = 2*D(n/2)      (need D(n/2) values for M1, and
 *                             D(n/2) more, independent, for M2)
 *   => D(n) = n
 *
 * In fact, this generator is exactly the FIRST ROW of the
 * matrix. Proof sketch (induction on n): the first row of M
 * is [first row of M1 | first row of M2] (top-left block
 * contributes the left half of row 0, top-right block M2
 * contributes the right half). By induction, the first row of
 * M1 equals M1's own generator, and likewise for M2. So the
 * first row of M equals generator(M1) ++ generator(M2), which
 * is exactly how we build M's own generator. Base case n=1 is
 * trivial (the single entry is its own generator/first row).
 *
 * So: gen(M) = row 0 of M,   and conversely, given any length
 * n array we can EXPAND it back into the unique n x n special
 * matrix that has it as a first row, by recursively building
 *   M = | expand(gen[0 .. n/2-1])   expand(gen[n/2 .. n-1]) |
 *       | expand(gen[n/2 .. n-1])   expand(gen[0 .. n/2-1]) |
 *
 * ---------------------------------------------------------
 * Multiplying two special matrices via their generators
 * ---------------------------------------------------------
 * Let A = [[A1,A2],[A2,A1]], B = [[B1,B2],[B2,B1]]. Ordinary
 * block matrix multiplication gives:
 *      C11 = A1*B1 + A2*B2
 *      C12 = A1*B2 + A2*B1
 *      C21 = A2*B1 + A1*B2 = C12
 *      C22 = A2*B2 + A1*B1 = C11
 * so C = A*B = [[C11,C12],[C12,C11]] -- the SAME special
 * pattern is preserved by the product (closed under
 * multiplication). This means we never need to materialize
 * full (n/2)x(n/2) matrices at all -- we can recurse directly
 * on the length-(n/2) generator halves:
 *
 *   combine(Agen, Bgen, n):
 *       if n == 1: return [ Agen[0] * Bgen[0] ]
 *       split Agen -> A1gen, A2gen  (each length n/2)
 *       split Bgen -> B1gen, B2gen  (each length n/2)
 *       P  = combine(A1gen, B1gen, n/2)   // represents A1*B1
 *       Q  = combine(A2gen, B2gen, n/2)   // represents A2*B2
 *       R1 = combine(A1gen, B2gen, n/2)   // represents A1*B2
 *       R2 = combine(A2gen, B1gen, n/2)   // represents A2*B1
 *       C11gen[i] = P[i] + Q[i]     for i in 0..n/2-1
 *       C12gen[i] = R1[i] + R2[i]   for i in 0..n/2-1
 *       return C11gen ++ C12gen           // length n
 *
 * ---------------------------------------------------------
 * Complexity
 * ---------------------------------------------------------
 * combine() makes 4 recursive calls on size n/2, plus O(n)
 * additions to merge results:
 *      T(n) = 4*T(n/2) + O(n)
 * By the Master Theorem: a=4, b=2, n^(log_b a) = n^2, and
 * f(n) = O(n) = O(n^(2-eps)), so this is Case 1:
 *      T(n) = Theta(n^2)
 * In fact the number of scalar multiplications performed at
 * the leaves is EXACTLY
 *      M(n) = 4*M(n/2), M(1) = 1   =>   M(n) = n^2
 * (the program below counts this directly and confirms it
 * equals n^2 exactly, for every n tested).
 *
 * Finally, expanding the length-n generator of C back into
 * the full n x n output matrix touches every one of the n^2
 * output cells exactly once: O(n^2).
 *
 * TOTAL: O(n) [read input generators] + O(n^2) [combine] +
 *        O(n^2) [expand output] = O(n^2) overall -- a full
 * asymptotic order better than naive O(n^3) and better than
 * Strassen's general-purpose O(n^2.807), by exploiting the
 * special structure of these matrices.
 * ---------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long ll;

static ll multCount;   /* scalar multiplications performed by combine() */
static ll addCount;    /* scalar additions performed by combine()       */
static ll naiveMultCount;

/* ---------------------------------------------------------
 * combine: multiply two special matrices given ONLY as their
 * length-n generators, producing the length-n generator of
 * the product (also a special matrix, per the proof above).
 * --------------------------------------------------------- */
int *combine(const int *Agen, const int *Bgen, int n) {
    if (n == 1) {
        int *C = (int *)malloc(sizeof(int));
        C[0] = Agen[0] * Bgen[0];
        multCount++;
        return C;
    }

    int half = n / 2;
    const int *A1 = Agen,        *A2 = Agen + half;
    const int *B1 = Bgen,        *B2 = Bgen + half;

    int *P  = combine(A1, B1, half);   /* A1*B1 */
    int *Q  = combine(A2, B2, half);   /* A2*B2 */
    int *R1 = combine(A1, B2, half);   /* A1*B2 */
    int *R2 = combine(A2, B1, half);   /* A2*B1 */

    int *C = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < half; i++) {
        C[i]        = P[i] + Q[i];        /* C11[i] */
        addCount++;
        C[half + i] = R1[i] + R2[i];      /* C12[i] */
        addCount++;
    }

    free(P); free(Q); free(R1); free(R2);
    return C;
}

/* ---------------------------------------------------------
 * expand: build the full n x n special matrix whose first
 * row (and recursive block pattern) matches the given
 * length-n generator.
 * --------------------------------------------------------- */
int **allocMatrix(int n) {
    int **m = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) m[i] = (int *)malloc(n * sizeof(int));
    return m;
}

void freeMatrix(int **m, int n) {
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);
}

void expandInto(const int *gen, int n, int **dst, int rowOff, int colOff) {
    if (n == 1) {
        dst[rowOff][colOff] = gen[0];
        return;
    }
    int half = n / 2;
    /* top-left = expand(gen1), bottom-right = expand(gen1)  */
    expandInto(gen,        half, dst, rowOff,        colOff);
    expandInto(gen,        half, dst, rowOff + half,  colOff + half);
    /* top-right = expand(gen2), bottom-left = expand(gen2)  */
    expandInto(gen + half,  half, dst, rowOff,        colOff + half);
    expandInto(gen + half,  half, dst, rowOff + half,  colOff);
}

int **expandMatrix(const int *gen, int n) {
    int **M = allocMatrix(n);
    expandInto(gen, n, M, 0, 0);
    return M;
}

/* ---------------------------------------------------------
 * Naive O(n^3) full matrix multiply, for correctness check
 * --------------------------------------------------------- */
int **naiveMultiply(int **A, int **B, int n) {
    int **C = allocMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * B[k][j];
                naiveMultCount++;
            }
            C[i][j] = sum;
        }
    return C;
}

/* ---------------------------------------------------------
 * Verify a full matrix actually has the required special
 * pattern (used only to sanity-check our test generator).
 * --------------------------------------------------------- */
int isSpecialPattern(int **M, int n) {
    if (n == 1) return 1;
    int half = n / 2;
    for (int i = 0; i < half; i++)
        for (int j = 0; j < half; j++) {
            if (M[i][j] != M[i + half][j + half]) return 0;              /* M1 blocks */
            if (M[i][j + half] != M[i + half][j]) return 0;              /* M2 blocks */
        }
    /* recursively verify M1 and M2 themselves */
    int **M1 = allocMatrix(half), **M2 = allocMatrix(half);
    for (int i = 0; i < half; i++)
        for (int j = 0; j < half; j++) {
            M1[i][j] = M[i][j];
            M2[i][j] = M[i][j + half];
        }
    int ok = isSpecialPattern(M1, half) && isSpecialPattern(M2, half);
    freeMatrix(M1, half); freeMatrix(M2, half);
    return ok;
}

int matricesEqual(int **A, int **B, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (A[i][j] != B[i][j]) return 0;
    return 1;
}

void printMatrix(int **M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%5d ", M[i][j]);
        printf("\n");
    }
}

/* ---------------------------------------------------------
 * Test harness
 * --------------------------------------------------------- */
void runTest(int n, int showDetails) {
    int *Agen = (int *)malloc(n * sizeof(int));
    int *Bgen = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        Agen[i] = rand() % 10;
        Bgen[i] = rand() % 10;
    }

    int **A = expandMatrix(Agen, n);
    int **B = expandMatrix(Bgen, n);

    /* sanity check that A and B truly are special-pattern matrices */
    int patternOk = isSpecialPattern(A, n) && isSpecialPattern(B, n);

    multCount = 0; addCount = 0; naiveMultCount = 0;

    int *Cgen = combine(Agen, Bgen, n);
    int **C_fast = expandMatrix(Cgen, n);

    int **C_naive = naiveMultiply(A, B, n);

    int correct = matricesEqual(C_fast, C_naive, n);
    ll nSquared = (ll)n * (ll)n;

    printf("n=%-6d pattern=%-4s combine mults=%-8lld (n^2=%-8lld exact match=%-4s) "
           "naive mults=%-9lld  [%s]\n",
           n, patternOk ? "OK" : "BAD",
           multCount, nSquared, (multCount == nSquared) ? "YES" : "no",
           naiveMultCount, correct ? "CORRECT" : "MISMATCH");

    if (showDetails) {
        printf("\nGenerator A: "); for (int i=0;i<n;i++) printf("%d ", Agen[i]); printf("\n");
        printf("Generator B: "); for (int i=0;i<n;i++) printf("%d ", Bgen[i]); printf("\n");
        printf("\nMatrix A:\n"); printMatrix(A, n);
        printf("\nMatrix B:\n"); printMatrix(B, n);
        printf("\nProduct C (via fast O(n^2) algorithm):\n"); printMatrix(C_fast, n);
        printf("\nGenerator C: "); for (int i=0;i<n;i++) printf("%d ", Cgen[i]); printf("\n\n");
    }

    free(Agen); free(Bgen); free(Cgen);
    freeMatrix(A, n); freeMatrix(B, n); freeMatrix(C_fast, n); freeMatrix(C_naive, n);
}

int main(void) {
    srand((unsigned int)time(NULL));

    printf("=========================================================\n");
    printf(" SPECIAL-PATTERN MATRIX MULTIPLICATION -- O(n^2) D&C\n");
    printf(" Pattern: M = [[M1,M2],[M2,M1]], recursive to scalars\n");
    printf("=========================================================\n\n");

    printf("--- Worked example (n = 4) ---\n");
    runTest(4, 1);

    printf("--- Correctness & multiplication-count validation ---\n\n");
    int sizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    for (int i = 0; i < (int)(sizeof(sizes)/sizeof(sizes[0])); i++)
        runTest(sizes[i], 0);

    printf("\n=========================================================\n");
    printf(" CONCLUSION\n");
    printf("=========================================================\n");
    printf("Because a special-pattern matrix is fully determined by\n");
    printf("just n numbers (its first row / generator), and that\n");
    printf("special pattern is closed under multiplication, we can\n");
    printf("multiply two such matrices by recursing directly on their\n");
    printf("length-n generators: 4 recursive combine() calls of half\n");
    printf("size plus O(n) merging work gives T(n) = 4T(n/2) + O(n),\n");
    printf("which solves to Theta(n^2) by the Master theorem. The\n");
    printf("measured scalar-multiplication count above equals n^2\n");
    printf("EXACTLY for every size tested, confirming the O(n^2) bound\n");
    printf("-- a full order better than the naive O(n^3) approach and\n");
    printf("better than general-purpose Strassen's O(n^2.807), because\n");
    printf("this algorithm exploits the redundancy in the input's\n");
    printf("special structure instead of treating it as n^2 unrelated\n");
    printf("entries. All results are verified identical to a full\n");
    printf("naive O(n^3) multiplication for every test.\n");

    return 0;
}
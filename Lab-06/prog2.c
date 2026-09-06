/* Lab-06 / Q2: square-matrix operations and their complexity. */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 30
#define EPS 1e-10

static void read_matrix(double a[MAX_N][MAX_N], int n, const char *name) {
    int i, j;
    printf("Enter %s (%d x %d), row by row:\n", name, n, n);
    for (i = 0; i < n; ++i) for (j = 0; j < n; ++j) scanf("%lf", &a[i][j]);
}
static void print_matrix(double a[MAX_N][MAX_N], int n) {
    int i, j;
    for (i = 0; i < n; ++i) { for (j = 0; j < n; ++j) printf("%9.3f ", a[i][j]); puts(""); }
}
static int is_zero(double a[MAX_N][MAX_N], int n) {
    int i, j; for (i = 0; i < n; ++i) for (j = 0; j < n; ++j) if (fabs(a[i][j]) > EPS) return 0; return 1;
}
static int is_symmetric(double a[MAX_N][MAX_N], int n) {
    int i, j; for (i = 0; i < n; ++i) for (j = i + 1; j < n; ++j) if (fabs(a[i][j] - a[j][i]) > EPS) return 0; return 1;
}
static double determinant(double a[MAX_N][MAX_N], int n) {
    double b[MAX_N][MAX_N], det = 1.0; int i, j, k, pivot, sign = 1;
    for (i = 0; i < n; ++i) for (j = 0; j < n; ++j) b[i][j] = a[i][j];
    for (i = 0; i < n; ++i) {
        pivot = i; for (j = i + 1; j < n; ++j) if (fabs(b[j][i]) > fabs(b[pivot][i])) pivot = j;
        if (fabs(b[pivot][i]) < EPS) return 0.0;
        if (pivot != i) { for (k = 0; k < n; ++k) { double t = b[i][k]; b[i][k] = b[pivot][k]; b[pivot][k] = t; } sign = -sign; }
        det *= b[i][i];
        for (j = i + 1; j < n; ++j) { double factor = b[j][i] / b[i][i]; for (k = i + 1; k < n; ++k) b[j][k] -= factor * b[i][k]; }
    }
    return sign * det;
}
static void dominant_eigenpair(double a[MAX_N][MAX_N], int n) {
    double x[MAX_N], y[MAX_N], norm, lambda = 0.0, previous = 1e100; int i, j, iteration;
    for (i = 0; i < n; ++i) x[i] = 1.0 / sqrt((double)n);
    for (iteration = 1; iteration <= 1000; ++iteration) {
        for (i = 0; i < n; ++i) { y[i] = 0; for (j = 0; j < n; ++j) y[i] += a[i][j] * x[j]; }
        norm = 0; for (i = 0; i < n; ++i) norm += y[i] * y[i]; norm = sqrt(norm);
        if (norm < EPS) { puts("The zero matrix has no unique dominant eigenvector."); return; }
        for (i = 0; i < n; ++i) x[i] = y[i] / norm;
        lambda = 0; for (i = 0; i < n; ++i) { double ax = 0; for (j = 0; j < n; ++j) ax += a[i][j] * x[j]; lambda += x[i] * ax; }
        if (fabs(lambda - previous) < EPS) break;
        previous = lambda;
    }
    printf("Dominant eigenvalue (power iteration): %.8f after %d iteration(s)\n", lambda, iteration);
    printf("Corresponding unit eigenvector: "); for (i = 0; i < n; ++i) printf("%.6f%s", x[i], i + 1 == n ? "\n" : " ");
}
int main(void) {
    double a[MAX_N][MAX_N], b[MAX_N][MAX_N], c[MAX_N][MAX_N]; int n, i, j, k, choice;
    printf("Square matrix order (1-%d): ", MAX_N); if (scanf("%d", &n) != 1 || n < 1 || n > MAX_N) return 1;
    read_matrix(a, n, "matrix A");
    do {
        puts("\n[1] A+B [2] A*B [3] zero? [4] symmetric? [5] determinant [6] in-place transpose [7] dominant eigenpair [0] exit");
        printf("Choice: "); if (scanf("%d", &choice) != 1) break;
        if (choice == 1 || choice == 2) read_matrix(b, n, "matrix B");
        if (choice == 1) { for (i=0;i<n;++i) for(j=0;j<n;++j) c[i][j]=a[i][j]+b[i][j]; print_matrix(c,n); puts("[O(n^2)]"); }
        else if (choice == 2) { for(i=0;i<n;++i) for(j=0;j<n;++j){c[i][j]=0;for(k=0;k<n;++k)c[i][j]+=a[i][k]*b[k][j];} print_matrix(c,n); puts("[O(n^3), naive multiplication]"); }
        else if (choice == 3) printf("%s [O(n^2)]\n", is_zero(a,n)?"Zero matrix.":"Not a zero matrix.");
        else if (choice == 4) printf("%s [O(n^2)]\n", is_symmetric(a,n)?"Symmetric.":"Not symmetric.");
        else if (choice == 5) printf("det(A) = %.8f [O(n^3), Gaussian elimination]\n", determinant(a,n));
        else if (choice == 6) { for(i=0;i<n;++i) for(j=i+1;j<n;++j){double t=a[i][j];a[i][j]=a[j][i];a[j][i]=t;} print_matrix(a,n); puts("[O(n^2), in place]"); }
        else if (choice == 7) { dominant_eigenpair(a,n); puts("Power iteration: O(iterations * n^2); full QR decomposition is conventionally O(n^3) per iteration."); }
    } while (choice != 0);
    return 0;
}

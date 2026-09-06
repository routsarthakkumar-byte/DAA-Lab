/* Lab-06 / Q3: convolution in O(N log N) using an iterative FFT. */
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

static int next_power_of_two(int value) { int p = 1; while (p < value) p <<= 1; return p; }
static void fft(double complex a[], int n, int inverse) {
    int i, j, len;
    for (i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) { double complex t = a[i]; a[i] = a[j]; a[j] = t; }
    }
    for (len = 2; len <= n; len <<= 1) {
        double angle = 2.0 * PI / len * (inverse ? -1.0 : 1.0);
        double complex step = cos(angle) + I * sin(angle);
        for (i = 0; i < n; i += len) {
            double complex w = 1.0;
            for (j = 0; j < len / 2; ++j) {
                double complex u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v; a[i + j + len / 2] = u - v; w *= step;
            }
        }
    }
    if (inverse) for (i = 0; i < n; ++i) a[i] /= n;
}
int main(void) {
    int m, n, size, i; double complex *a, *b;
    printf("Length of A and B (n >= m): ");
    if (scanf("%d%d", &m, &n) != 2 || m < 1 || n < m) { puts("Require 1 <= m <= n."); return 1; }
    size = next_power_of_two(m + n - 1);
    a = calloc((size_t)size, sizeof *a); b = calloc((size_t)size, sizeof *b);
    if (!a || !b) { puts("Allocation failed."); free(a); free(b); return 1; }
    printf("Enter %d coefficient(s) of A: ", m); for (i = 0; i < m; ++i) { double x; scanf("%lf", &x); a[i] = x; }
    printf("Enter %d coefficient(s) of B: ", n); for (i = 0; i < n; ++i) { double x; scanf("%lf", &x); b[i] = x; }
    fft(a, size, 0); fft(b, size, 0); for (i = 0; i < size; ++i) a[i] *= b[i]; fft(a, size, 1);
    puts("\nC[k] = sum_j A[j] * B[k-j]");
    for (i = 0; i < m + n - 1; ++i) printf("C[%d] = %.6f\n", i, creal(a[i]));
    printf("\nPadded FFT size N = %d; time = O(N log N), space = O(N).\n", size);
    free(a); free(b); return 0;
}

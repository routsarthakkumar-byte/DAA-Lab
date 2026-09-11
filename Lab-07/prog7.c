#include <stdio.h>
#include <limits.h>

void printParenthesis(int i, int j, int n, int s[n][n], char *name) {
    if (i == j) {
        printf("%c", (*name)++);
        return;
    }
    printf("(");
    printParenthesis(i, s[i][j], n, s, name);
    printParenthesis(s[i][j] + 1, j, n, s, name);
    printf(")");
}

int main() {
    int n;
    printf("Enter number of matrices: ");
    if (scanf("%d", &n) != 1 || n < 1) return 0;

    int p[n + 1];
    printf("Enter %d dimensions (p0 to p%d): ", n + 1, n);
    for (int i = 0; i <= n; i++) scanf("%d", &p[i]);

    int m[n + 1][n + 1];
    int s[n + 1][n + 1];

    for (int i = 1; i <= n; i++) m[i][i] = 0;

    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("Minimum number of scalar multiplications: %d\n", m[1][n]);
    printf("Optimal Parenthesization: ");
    char name = 'A';
    printParenthesis(1, n, n + 1, s, &name);
    printf("\n");

    return 0;
}
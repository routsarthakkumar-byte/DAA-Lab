#include <stdio.h>
#include <string.h>

int min3(int a, int b, int c) {
    int x = a;

    if (b < x)
        x = b;

    if (c < x)
        x = c;

    return x;
}

int main() {
    char A[100], B[100];

    scanf("%s", A);
    scanf("%s", B);

    int m = strlen(A);
    int n = strlen(B);

    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }

    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= m; i++) {

        for (int j = 1; j <= n; j++) {

            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = 1 + min3(
                    dp[i - 1][j],
                    dp[i][j - 1],
                    dp[i - 1][j - 1]
                );
            }
        }
    }

    printf("Edit Distance: %d\n", dp[m][n]);

    int i = m;
    int j = n;

    while (i > 0 || j > 0) {

        if (i > 0 && j > 0 && A[i - 1] == B[j - 1]) {
            printf("Keep %c\n", A[i - 1]);
            i--;
            j--;
        }

        else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            printf("Delete %c\n", A[i - 1]);
            i--;
        }

        else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            printf("Insert %c\n", B[j - 1]);
            j--;
        }

        else {
            printf("Replace %c with %c\n", A[i - 1], B[j - 1]);
            i--;
            j--;
        }
    }

    return 0;
}
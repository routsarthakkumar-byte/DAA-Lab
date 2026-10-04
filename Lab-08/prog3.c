#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int main() {
    char X[100], Y[100];

    scanf("%s", X);
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {

            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            }
            else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    printf("Length: %d\n", dp[m][n]);

    char lcs[100];
    int index = dp[m][n];

    lcs[index] = '\0';

    int i = m;
    int j = n;

    while (i > 0 && j > 0) {

        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            index--;
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    printf("LCS: %s", lcs);

    return 0;
}
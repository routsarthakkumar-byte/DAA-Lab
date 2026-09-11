#include <stdio.h>
#include <limits.h>

int max(int a, int b) { return (a > b) ? a : b; }

int main() {
    int E, F;
    printf("Enter number of eggs (E) and floors (F): ");
    if (scanf("%d %d", &E, &F) != 2 || E < 1 || F < 1) return 0;

    int dp[E + 1][F + 1];

    for (int i = 1; i <= E; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }
    for (int j = 1; j <= F; j++) dp[1][j] = j;

    for (int i = 2; i <= E; i++) {
        for (int j = 2; j <= F; j++) {
            dp[i][j] = INT_MAX;
            for (int k = 1; k <= j; k++) {
                int res = 1 + max(dp[i - 1][k - 1], dp[i][j - k]);
                if (res < dp[i][j]) dp[i][j] = res;
            }
        }
    }

    printf("Minimum drops required for %d eggs and %d floors: %d\n", E, F, dp[E][F]);
    return 0;
}
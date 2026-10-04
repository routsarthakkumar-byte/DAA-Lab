#include <stdio.h>
#include <limits.h>

int main() {
    int n, V;

    scanf("%d", &n);

    int coins[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    scanf("%d", &V);

    int dp[V + 1];

    dp[0] = 0;

    for (int i = 1; i <= V; i++) {
        dp[i] = INT_MAX;
    }

    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                if (dp[i] > dp[i - coins[j]] + 1) {
                    dp[i] = dp[i - coins[j]] + 1;
                }
            }
        }
    }

    if (dp[V] == INT_MAX)
        printf("-1");
    else
        printf("%d", dp[V]);

    return 0;
}
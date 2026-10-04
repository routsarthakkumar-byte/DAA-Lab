#include <stdio.h>

int main() {
    int n, V;

    scanf("%d", &n);

    int coins[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    scanf("%d", &V);

    long long dp[V + 1];

    for (int i = 0; i <= V; i++) {
        dp[i] = 0;
    }

    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = coins[i]; j <= V; j++) {
            dp[j] = dp[j] + dp[j - coins[i]];
        }
    }

    printf("%lld", dp[V]);

    return 0;
}
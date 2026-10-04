#include <stdio.h>

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int main() {
    int n;

    scanf("%d", &n);

    int price[n + 1];

    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }

    int dp[n + 1];
    int cut[n + 1];

    dp[0] = 0;
    cut[0] = 0;

    for (int i = 1; i <= n; i++) {

        dp[i] = 0;

        for (int j = 1; j <= i; j++) {

            if (dp[i] < price[j] + dp[i - j]) {
                dp[i] = price[j] + dp[i - j];
                cut[i] = j;
            }
        }
    }

    printf("Maximum Revenue: %d\n", dp[n]);

    printf("Pieces: ");

    int length = n;

    while (length > 0) {
        printf("%d ", cut[length]);
        length = length - cut[length];
    }

    return 0;
}
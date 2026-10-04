#include <stdio.h>

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int main() {
    int n;

    scanf("%d", &n);

    int a[n];
    int dp[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        dp[i] = a[i];
    }

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < i; j++) {

            if (a[j] < a[i]) {
                dp[i] = max(dp[i], dp[j] + a[i]);
            }
        }
    }

    int answer = dp[0];

    for (int i = 1; i < n; i++) {
        if (dp[i] > answer)
            answer = dp[i];
    }

    printf("%d", answer);

    return 0;
}
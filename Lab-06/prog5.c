/* Lab-06 / Q5: nth Fibonacci number using bottom-up dynamic programming. */
#include <stdio.h>
#include <stdint.h>
int main(void) {
    int n, i; uint64_t dp[94] = {0, 1};
    printf("Enter n (0-93): ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 93) { puts("n must be in 0..93."); return 1; }
    for (i = 2; i <= n; ++i) dp[i] = dp[i-1] + dp[i-2];
    printf("F(%d) = %llu\n", n, (unsigned long long)dp[n]);
    puts("Time: O(n) | Space: O(n) for the displayed DP table (O(1) with two variables).");
    return 0;
}

/* Lab-06 / Q6: 0/1 Knapsack via dynamic programming and backtracking. */
#include <stdio.h>
#define MAX_ITEMS 50
#define MAX_CAPACITY 500
int main(void) {
    int n, cap, w[MAX_ITEMS+1], v[MAX_ITEMS+1], dp[MAX_ITEMS+1][MAX_CAPACITY+1] = {{0}};
    int i, c;
    printf("Items (1-%d) and capacity (0-%d): ", MAX_ITEMS, MAX_CAPACITY);
    if (scanf("%d%d", &n, &cap) != 2 || n < 1 || n > MAX_ITEMS || cap < 0 || cap > MAX_CAPACITY) return 1;
    for (i=1;i<=n;++i) { printf("weight and profit for item %d: ",i); if (scanf("%d%d",&w[i],&v[i])!=2 || w[i]<0) return 1; }
    for (i=1;i<=n;++i) for (c=0;c<=cap;++c) {
        dp[i][c]=dp[i-1][c];
        if (w[i]<=c && v[i]+dp[i-1][c-w[i]]>dp[i][c]) dp[i][c]=v[i]+dp[i-1][c-w[i]];
    }
    printf("Maximum profit: %d\nSelected item(s): ",dp[n][cap]);
    for (i=n;i>=1;--i) if (dp[i][cap]!=dp[i-1][cap]) { printf("%d ",i); cap-=w[i]; }
    puts("\nTime: O(nW) | Space: O(nW), where W is capacity.");
    return 0;
}

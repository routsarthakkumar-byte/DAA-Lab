/* Lab-06 / Q7: Longest Common Subsequence, including reconstruction. */
#include <stdio.h>
#include <string.h>
#define MAX 300
int main(void) {
    char a[MAX+1], b[MAX+1], out[MAX+1]; int dp[MAX+1][MAX+1]={{0}};
    int i,j,m,n,k;
    printf("First string: "); if (!fgets(a,sizeof a,stdin)) return 1; a[strcspn(a,"\r\n")]=0;
    printf("Second string: "); if (!fgets(b,sizeof b,stdin)) return 1; b[strcspn(b,"\r\n")]=0;
    m=(int)strlen(a); n=(int)strlen(b);
    for(i=1;i<=m;++i) for(j=1;j<=n;++j) dp[i][j]=(a[i-1]==b[j-1])?dp[i-1][j-1]+1:(dp[i-1][j]>dp[i][j-1]?dp[i-1][j]:dp[i][j-1]);
    k=dp[m][n]; out[k]=0; i=m; j=n;
    while(i>0&&j>0) { if(a[i-1]==b[j-1]) out[--k]=a[--i],--j; else if(dp[i-1][j]>=dp[i][j-1]) --i; else --j; }
    printf("LCS length: %d\nLCS: %s\n",dp[m][n],out);
    puts("Time: O(mn) | Space: O(mn) (table retained to reconstruct the subsequence).");
    return 0;
}

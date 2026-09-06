/* Lab-06 / Q8: Matrix Chain Multiplication using dynamic programming. */
#include <limits.h>
#include <stdio.h>
#define MAX_DIMENSIONS 31
static void print_order(int split[MAX_DIMENSIONS][MAX_DIMENSIONS], int i, int j) {
    if(i==j) { printf("A%d",i); return; }
    putchar('('); print_order(split,i,split[i][j]); print_order(split,split[i][j]+1,j); putchar(')');
}
int main(void) {
    long d[MAX_DIMENSIONS]; long long cost[MAX_DIMENSIONS][MAX_DIMENSIONS]; int split[MAX_DIMENSIONS][MAX_DIMENSIONS];
    int count,n,i,j,len,k; printf("Number of dimensions (2-%d): ",MAX_DIMENSIONS);
    if(scanf("%d",&count)!=1||count<2||count>MAX_DIMENSIONS) return 1;
    n=count-1;
    printf("Enter %d dimensions: ",count); for(i=0;i<count;++i) if(scanf("%ld",&d[i])!=1||d[i]<=0) return 1;
    for(i=1;i<=n;++i) cost[i][i]=0;
    for(len=2;len<=n;++len) for(i=1;i<=n-len+1;++i) { j=i+len-1; cost[i][j]=LLONG_MAX;
        for(k=i;k<j;++k) { long long q=cost[i][k]+cost[k+1][j]+d[i-1]*d[k]*d[j]; if(q<cost[i][j]) {cost[i][j]=q;split[i][j]=k;} }
    }
    printf("Minimum scalar multiplications: %lld\nOptimal parenthesization: ",cost[1][n]); print_order(split,1,n); puts("\nTime: O(n^3) | Space: O(n^2).");
    return 0;
}

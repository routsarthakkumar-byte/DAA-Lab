#include <stdio.h>
#include <float.h>

int main() {
    int n;

    scanf("%d", &n);

    int keys[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &keys[i]);
    }

    double p[n + 1];
    double q[n + 1];

    for (int i = 1; i <= n; i++) {
        scanf("%lf", &p[i]);
    }

    for (int i = 0; i <= n; i++) {
        scanf("%lf", &q[i]);
    }

    double e[n + 2][n + 1];
    double w[n + 2][n + 1];

    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int length = 1; length <= n; length++) {

        for (int i = 1; i <= n - length + 1; i++) {

            int j = i + length - 1;

            e[i][j] = DBL_MAX;

            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++) {

                double cost = e[i][r - 1]
                            + e[r + 1][j]
                            + w[i][j];

                if (cost < e[i][j]) {
                    e[i][j] = cost;
                }
            }
        }
    }

    printf("Minimum Expected Search Cost: %.4lf", e[1][n]);

    return 0;
}
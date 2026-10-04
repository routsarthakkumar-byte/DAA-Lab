#include <stdio.h>
#include <limits.h>

unsigned long long nextValue(unsigned long long n) {

    if (n % 2 == 0)
        return n / 2;

    return 3 * n + 1;
}

void analyze(unsigned long long n) {

    printf("Starting value: %llu\n", n);

    printf("Trajectory: ");

    int steps = 0;

    while (n != 1) {

        printf("%llu -> ", n);

        if (n % 2 == 0)
            n = n / 2;
        else
            n = 3 * n + 1;

        steps++;
    }

    printf("1\n");

    printf("Steps: %d\n", steps);
}

int main() {

    unsigned long long a, b;

    scanf("%llu %llu", &a, &b);

    for (unsigned long long n = a; n <= b; n++) {

        analyze(n);

        printf("\n");

        if (n == ULLONG_MAX)
            break;
    }

    return 0;
}
#include <stdio.h>
#include <math.h>

int move_count = 0;

void hanoi3(int n, char src, char dst, char aux) {
    if (n == 0) return;
    hanoi3(n - 1, src, aux, dst);
    printf("Move disk %d from %c to %c\n", n, src, dst);
    move_count++;
    hanoi3(n - 1, aux, dst, src);
}

void reves4(int n, char src, char dst, char aux1, char aux2) {
    if (n == 0) return;
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", src, dst);
        move_count++;
        return;
    }

    int k = n + 1 - (int)round(sqrt(2 * n + 1));
    reves4(k, src, aux1, aux2, dst);
    hanoi3(n - k, src, dst, aux2);
    reves4(k, aux1, dst, src, aux2);
}

int main() {
    int n;
    printf("Enter number of disks (e.g., 8): ");
    if (scanf("%d", &n) != 1 || n < 1) return 0;

    move_count = 0;
    reves4(n, 'A', 'B', 'C', 'D');
    printf("Total moves: %d\n", move_count);

    return 0;
}
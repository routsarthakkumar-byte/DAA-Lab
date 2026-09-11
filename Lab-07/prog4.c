#include <stdio.h>

int moves = 0;

void turnOff(int n);
void turnOn(int n);

void turnOff(int n) {
    if (n <= 0) return;
    if (n == 1) {
        printf("Turn OFF switch 1\n");
        moves++;
        return;
    }
    turnOff(n - 2);
    printf("Turn OFF switch %d\n", n);
    moves++;
    turnOn(n - 2);
    turnOff(n - 1);
}

void turnOn(int n) {
    if (n <= 0) return;
    if (n == 1) {
        printf("Turn ON switch 1\n");
        moves++;
        return;
    }
    turnOn(n - 1);
    turnOff(n - 2);
    printf("Turn ON switch %d\n", n);
    moves++;
    turnOn(n - 2);
}

int main() {
    int n;
    printf("Enter number of switches: ");
    if (scanf("%d", &n) != 1 || n < 1) return 0;

    moves = 0;
    turnOff(n);
    printf("Total moves to turn OFF all switches: %d\n", moves);
    return 0;
}
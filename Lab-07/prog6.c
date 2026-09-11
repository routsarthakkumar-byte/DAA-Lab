#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int year;
    int type; // -1 for death transition, +1 for birth
} Event;

int compareEvents(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;
    if (e1->year != e2->year) return e1->year - e2->year;
    return e1->type - e2->type; // -1 before +1
}

int main() {
    int n;
    printf("Enter number of scientists: ");
    if (scanf("%d", &n) != 1 || n < 1) return 0;

    Event events[2 * n];
    char name[50];
    int birth, death;

    for (int i = 0; i < n; i++) {
        printf("Enter scientist %d name, birth year, death year: ", i + 1);
        scanf("%s %d %d", name, &birth, &death);
        events[2 * i] = (Event){birth, 1};
        events[2 * i + 1] = (Event){death + 1, -1};
    }

    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int max_alive = 0, current_alive = 0, best_year = -1;

    for (int i = 0; i < 2 * n; i++) {
        current_alive += events[i].type;
        if (current_alive > max_alive) {
            max_alive = current_alive;
            best_year = events[i].year;
        }
    }

    printf("Max scientists alive simultaneously: %d (in year %d)\n", max_alive, best_year);
    return 0;
}
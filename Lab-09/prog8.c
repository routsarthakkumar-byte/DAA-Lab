#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, i;
    printf("Enter number of meetings: ");
    scanf("%d", &n);
    int *start = (int *)malloc(n * sizeof(int));
    int *end = (int *)malloc(n * sizeof(int));
    printf("Enter start times: ");
    for (i = 0; i < n; i++) scanf("%d", &start[i]);
    printf("Enter end times: ");
    for (i = 0; i < n; i++) scanf("%d", &end[i]);

    qsort(start, n, sizeof(int), compare);
    qsort(end, n, sizeof(int), compare);

    int rooms = 0, max_rooms = 0, s_ptr = 0, e_ptr = 0;
    while (s_ptr < n) {
        if (start[s_ptr] < end[e_ptr]) {
            rooms++; s_ptr++;
        } else {
            rooms--; e_ptr++;
        }
        if (rooms > max_rooms) max_rooms = rooms;
    }
    printf("Minimum number of meeting rooms required: %d\n", max_rooms);
    free(start); free(end);
    return 0;
}
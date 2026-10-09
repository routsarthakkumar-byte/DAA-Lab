#include <stdio.h>
#include <stdlib.h>

int main() {
    int target, startFuel, n;
    printf("Enter target distance: ");
    scanf("%d", &target);
    printf("Enter initial fuel: ");
    scanf("%d", &startFuel);
    printf("Enter number of stations: ");
    scanf("%d", &n);

    int *pos = (int *)malloc(n * sizeof(int));
    int *fuel = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("Station %d (distance and refuel amount): ", i + 1);
        scanf("%d %d", &pos[i], &fuel[i]);
    }

    int stops = 0, current_fuel = startFuel, curr_pos = 0, i = 0;
    while (curr_pos + current_fuel < target) {
        int max_reach = curr_pos + current_fuel;
        int farthest_fuel = -1;
        while (i < n && pos[i] <= max_reach) {
            if (fuel[i] > farthest_fuel) farthest_fuel = fuel[i];
            i++;
        }
        if (farthest_fuel == -1) {
            printf("Target cannot be reached.\n");
            free(pos); free(fuel);
            return 0;
        }
        current_fuel = (current_fuel - (pos[i - 1] - curr_pos)) + farthest_fuel;
        curr_pos = pos[i - 1];
        stops++;
    }
    printf("Minimum refueling stops required: %d\n", stops);
    free(pos); free(fuel);
    return 0;
}
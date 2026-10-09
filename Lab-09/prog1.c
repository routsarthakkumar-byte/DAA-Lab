#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double v, w, lambda;
} Item;

int compare(const void *a, const void *b) {
    Item *item1 = (Item *)a;
    Item *item2 = (Item *)b;
    double d1 = item1->v / item1->w;
    double d2 = item2->v / item2->w;
    if (d1 < d2) return 1;
    if (d1 > d2) return -1;
    return 0;
}

int main() {
    int n, i;
    double W;
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter knapsack capacity: ");
    scanf("%lf", &W);

    Item *items = (Item *)malloc(n * sizeof(Item));
    for (i = 0; i < n; i++) {
        items[i].id = i + 1;
        printf("Item %d - Enter value, weight, decay rate (lambda): ", i + 1);
        scanf("%lf %lf %lf", &items[i].v, &items[i].w, &items[i].lambda);
    }

    qsort(items, n, sizeof(Item), compare);

    double total_value = 0.0;
    double current_weight = 0.0;
    double current_time = 0.0;

    printf("\n--- Fractional Knapsack Schedule ---\n");
    for (i = 0; i < n; i++) {
        if (current_weight + items[i].w <= W) {
            current_weight += items[i].w;
            double effective_val = items[i].v - items[i].lambda * current_time * items[i].w;
            if (effective_val < 0) effective_val = 0;
            total_value += effective_val;
            current_time += items[i].w;
            printf("Item %d: Taken fully. Effective Value: %.2lf\n", items[i].id, effective_val);
        } else {
            double remaining = W - current_weight;
            double fraction = remaining / items[i].w;
            double effective_val = (items[i].v - items[i].lambda * current_time * items[i].w) * fraction;
            if (effective_val < 0) effective_val = 0;
            total_value += effective_val;
            current_weight = W;
            printf("Item %d: Taken %.2lf%%\n", items[i].id, fraction * 100);
            break;
        }
    }
    printf("Maximum Total Value: %.2lf\n", total_value);
    free(items);
    return 0;
}
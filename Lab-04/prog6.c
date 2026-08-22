#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int point;
    int type;       // +1 = left endpoint, -1 = right endpoint
} Event;

// Sort by point
// If points are equal, process +1 before -1
int compare(const void *a, const void *b)
{
    Event *x = (Event *)a;
    Event *y = (Event *)b;

    if(x->point != y->point)
        return x->point - y->point;

    return y->type - x->type;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Event events[2 * n];

    printf("Enter the intervals:\n");

    for(int i = 0; i < n; i++)
    {
        int l, r;

        scanf("%d %d", &l, &r);

        // Left endpoint
        events[2 * i].point = l;
        events[2 * i].type = 1;

        // Right endpoint
        events[2 * i + 1].point = r;
        events[2 * i + 1].type = -1;
    }

    // Sort all endpoints
    qsort(events, 2 * n, sizeof(Event), compare);

    int current = 0;
    int maximum = 0;
    int answer = 0;

    // Scan events
    for(int i = 0; i < 2 * n; i++)
    {
        current += events[i].type;

        if(current > maximum)
        {
            maximum = current;
            answer = events[i].point;
        }
    }

    printf("\nPoint with maximum overlapping intervals = %d\n", answer);
    printf("Maximum number of intervals = %d\n", maximum);

    return 0;
}
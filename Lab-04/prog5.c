#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int start;
    int end;
} Interval;

// Compare intervals according to starting time
int compare(const void *a, const void *b)
{
    Interval *x = (Interval *)a;
    Interval *y = (Interval *)b;

    return x->start - y->start;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Interval intervals[n];
    Interval result[n];

    printf("Enter intervals:\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d %d", &intervals[i].start,
                       &intervals[i].end);
    }

    // Step 1: Sort intervals by starting time
    qsort(intervals, n, sizeof(Interval), compare);

    // Step 2: Merge overlapping intervals
    int count = 0;

    result[0] = intervals[0];
    count = 1;

    for(int i = 1; i < n; i++)
    {
        // Overlapping intervals
        if(intervals[i].start <= result[count - 1].end)
        {
            // Extend the ending point if necessary
            if(intervals[i].end > result[count - 1].end)
            {
                result[count - 1].end = intervals[i].end;
            }
        }
        else
        {
            // No overlap, add new interval
            result[count] = intervals[i];
            count++;
        }
    }

    // Print result
    printf("\nMerged intervals:\n");

    for(int i = 0; i < count; i++)
    {
        printf("(%d, %d) ", result[i].start,
                            result[i].end);
    }

    printf("\n");

    return 0;
}
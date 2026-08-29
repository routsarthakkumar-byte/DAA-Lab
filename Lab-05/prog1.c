#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int a[], int low, int high)
{
    int pivot = a[high];
    int i = low - 1;

    for(int j = low; j < high; j++)
    {
        if(a[j] <= pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);

    return i + 1;
}

int quickSelect(int a[], int low, int high, int k)
{
    if(low == high)
        return a[low];

    int pos = partition(a, low, high);

    int count = pos - low + 1;

    if(k == count)
        return a[pos];

    if(k < count)
        return quickSelect(a, low, pos - 1, k);

    return quickSelect(a, pos + 1, high, k - count);
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter %d elements:\n", n);

    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    if(n % 2 != 0)
    {
        int median = quickSelect(a, 0, n - 1, n / 2 + 1);

        printf("Median = %d\n", median);
    }
    else
    {
        int x = quickSelect(a, 0, n - 1, n / 2);
        int y = quickSelect(a, 0, n - 1, n / 2 + 1);

        printf("Median = %.2f\n", (x + y) / 2.0);
    }

    return 0;
}
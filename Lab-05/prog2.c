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

    int rank = pos - low + 1;

    if(rank == k)
        return a[pos];

    if(k < rank)
        return quickSelect(a, low, pos - 1, k);

    return quickSelect(a, pos + 1, high, k - rank);
}

int main()
{
    int n, k;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter %d elements:\n", n);

    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter K: ");
    scanf("%d", &k);

    if(k < 1 || k > n)
    {
        printf("Invalid value of K\n");
        return 0;
    }

    int answer = quickSelect(a, 0, n - 1, k);

    printf("%dth smallest element = %d\n", k, answer);

    return 0;
}
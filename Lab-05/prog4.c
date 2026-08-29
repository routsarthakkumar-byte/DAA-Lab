#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && a[left] > a[largest])
        largest = left;

    if(right < n && a[right] > a[largest])
        largest = right;

    if(largest != i)
    {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for(int i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
    }
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    FILE *fp;

    fp = fopen("heap_data.txt", "w");

    if(fp == NULL)
    {
        printf("File cannot be opened.\n");
        return 1;
    }

    printf("Enter %d random elements:\n", n);

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        fprintf(fp, "%d ", a[i]);
    }

    fclose(fp);

    fp = fopen("heap_data.txt", "r");

    if(fp == NULL)
    {
        printf("File cannot be opened.\n");
        return 1;
    }

    for(int i = 0; i < n; i++)
        fscanf(fp, "%d", &a[i]);

    fclose(fp);

    printf("\nElements before sorting:\n");

    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);

    heapSort(a, n);

    printf("\n\nElements after Heap Sort:\n");

    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int data;
} Element;

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

void quickSort(int a[], int low, int high)
{
    if(low < high)
    {
        int p = partition(a, low, high);

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    FILE *fp;

    fp = fopen("quick_data.txt", "w");

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

    fp = fopen("quick_data.txt", "r");

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

    quickSort(a, 0, n - 1);

    printf("\n\nElements after Quick Sort:\n");

    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    return 0;
}
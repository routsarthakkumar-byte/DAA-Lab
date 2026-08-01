#include <stdio.h>

void optimizedBubbleSort(int arr[], int n)
{
    int comparisons = 0;
    int temp;
    int swapped;

    for(int i = 0; i < n - 1; i++)
    {
        swapped = 0;

        for(int j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if(arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = 1;
            }
        }

        if(swapped == 0)
            break;
    }

    printf("\nOptimized Bubble Sort Comparisons = %d\n", comparisons);
}

void normalBubbleSort(int arr[], int n)
{
    int comparisons = 0;
    int temp;

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if(arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("Normal Bubble Sort Comparisons = %d\n", comparisons);
}

int main()
{
    int n;

    printf("Enter size of array: ");
    scanf("%d",&n);

    int arr1[n];
    int arr2[n];

    printf("Enter array elements:\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d",&arr1[i]);
        arr2[i] = arr1[i];
    }

    optimizedBubbleSort(arr1,n);
    normalBubbleSort(arr2,n);

    return 0;
}
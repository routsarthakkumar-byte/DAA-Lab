#include <stdio.h>

int main()
{
    int n;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];
    int totalSum = 0;
    int leftSum = 0;

    printf("Enter array elements:\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        totalSum += arr[i];
    }

    for(int i = 0; i < n; i++)
    {
        int rightSum = totalSum - leftSum - arr[i];

        if(leftSum == rightSum)
        {
            printf("\nPartition Point Found!\n");
            printf("Index = %d\n", i);
            printf("Element = %d\n", arr[i]);
            printf("Left Sum = %d\n", leftSum);
            printf("Right Sum = %d\n", rightSum);
            return 0;
        }

        leftSum += arr[i];
    }

    printf("\nNo Partition Point Exists.\n");

    return 0;
}
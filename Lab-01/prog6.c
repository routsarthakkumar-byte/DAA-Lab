/*
-------------------------------------------------------
Program    : Question 6
Title      : Element Uniqueness
Subject    : Design and Analysis of Algorithms
Language   : C
Author     : Sarthak Kumar Rout
Institute  : IIIT Bhubaneswar
Semester   : 3rd Semester
-------------------------------------------------------
*/

#include <stdio.h>

int main()
{
    int n;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter array elements:\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(arr[i] == arr[j])
            {
                printf("\nDuplicate Element Found: %d\n", arr[i]);
                printf("Array does NOT contain unique elements.\n");
                return 0;
            }
        }
    }

    printf("\nAll elements are unique.\n");

    return 0;
}

/*
---------------- End of Program ----------------
*/
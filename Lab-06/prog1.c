#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void display(int a[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void maximum(int a[], int n) {
    int max = a[0];
    int i;

    for (i = 1; i < n; i++) {
        if (a[i] > max)
            max = a[i];
    }

    printf("Maximum element = %d\n", max);
}

void largest_two(int a[], int n) {
    int largest, second;
    int i;

    if (n < 2) {
        printf("Need at least 2 elements.\n");
        return;
    }

    if (a[0] > a[1]) {
        largest = a[0];
        second = a[1];
    } else {
        largest = a[1];
        second = a[0];
    }

    for (i = 2; i < n; i++) {
        if (a[i] > largest) {
            second = largest;
            largest = a[i];
        } else if (a[i] > second) {
            second = a[i];
        }
    }

    printf("Largest = %d\n", largest);
    printf("Second Largest = %d\n", second);
}

void mean(int a[], int n) {
    long long sum = 0;
    int i;

    for (i = 0; i < n; i++)
        sum += a[i];

    printf("Mean = %.2f\n", (double)sum / n);
}

void median(int a[], int n) {
    int b[1000];
    int i, j, temp;

    for (i = 0; i < n; i++)
        b[i] = a[i];

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (b[j] > b[j + 1]) {
                temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }

    if (n % 2 == 1)
        printf("Median = %.2f\n", (double)b[n / 2]);
    else
        printf("Median = %.2f\n",
               (b[n / 2 - 1] + b[n / 2]) / 2.0);
}

void standard_deviation(int a[], int n) {
    double sum = 0, mean, variance = 0;
    int i;

    for (i = 0; i < n; i++)
        sum += a[i];

    mean = sum / n;

    for (i = 0; i < n; i++)
        variance += (a[i] - mean) * (a[i] - mean);

    variance = variance / n;

    printf("Standard Deviation = %.2f\n", sqrt(variance));
}

void mode(int a[], int n) {
    int i, j;
    int maxCount = 0, modeValue = a[0];

    for (i = 0; i < n; i++) {
        int count = 0;

        for (j = 0; j < n; j++) {
            if (a[j] == a[i])
                count++;
        }

        if (count > maxCount) {
            maxCount = count;
            modeValue = a[i];
        }
    }

    if (maxCount == 1)
        printf("No mode (all elements occur once).\n");
    else
        printf("Mode = %d\n", modeValue);
}

int remove_duplicates(int a[], int n) {
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                for (k = j; k < n - 1; k++)
                    a[k] = a[k + 1];

                n--;
                j--;
            }
        }
    }

    return n;
}

void reverse_array(int a[], int n) {
    int i, temp;

    for (i = 0; i < n / 2; i++) {
        temp = a[i];
        a[i] = a[n - i - 1];
        a[n - i - 1] = temp;
    }

    printf("Reversed array: ");
    display(a, n);
}

void partition_array(int a[], int n, int pivot) {
    int i, j, temp;

    /*
       Required condition:
       Elements >= pivot appear before elements < pivot
    */

    j = 0;

    for (i = 0; i < n; i++) {
        if (a[i] >= pivot) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            j++;
        }
    }

    printf("Partitioned array: ");
    display(a, n);
}

int main() {
    int a[1000];
    int n, i;
    int choice;
    int pivot;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Find Maximum\n");
        printf("2. Find First and Second Largest\n");
        printf("3. Find Mean\n");
        printf("4. Find Median\n");
        printf("5. Find Standard Deviation\n");
        printf("6. Find Mode\n");
        printf("7. Remove Duplicates\n");
        printf("8. Reverse Array\n");
        printf("9. Partition Around Pivot\n");
        printf("10. Display Array\n");
        printf("0. Exit\n");
        printf("==========================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                maximum(a, n);
                break;

            case 2:
                largest_two(a, n);
                break;

            case 3:
                mean(a, n);
                break;

            case 4:
                median(a, n);
                break;

            case 5:
                standard_deviation(a, n);
                break;

            case 6:
                mode(a, n);
                break;

            case 7:
                n = remove_duplicates(a, n);
                printf("Array after removing duplicates: ");
                display(a, n);
                break;

            case 8:
                reverse_array(a, n);
                break;

            case 9:
                printf("Enter pivot element: ");
                scanf("%d", &pivot);
                partition_array(a, n, pivot);
                break;

            case 10:
                printf("Array: ");
                display(a, n);
                break;

            case 0:
                printf("Program terminated.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}
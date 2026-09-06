#include <stdio.h>
#include <math.h>

#define MAX 100

void inputMatrix(double a[MAX][MAX], int n) {
    int i, j;

    printf("Enter matrix elements:\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &a[i][j]);
        }
    }
}

void displayMatrix(double a[MAX][MAX], int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%.2lf ", a[i][j]);

        printf("\n");
    }
}

void addition(double a[MAX][MAX], double b[MAX][MAX], int n) {
    double c[MAX][MAX];
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    printf("Matrix Addition:\n");
    displayMatrix(c, n);
}

void multiplication(double a[MAX][MAX], double b[MAX][MAX], int n) {
    double c[MAX][MAX] = {0};
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    printf("Matrix Multiplication:\n");
    displayMatrix(c, n);
}

void zeroMatrix(double a[MAX][MAX], int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (a[i][j] != 0) {
                printf("The matrix is NOT a zero matrix.\n");
                return;
            }
        }
    }

    printf("The matrix is a zero matrix.\n");
}

void symmetricMatrix(double a[MAX][MAX], int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i][j] != a[j][i]) {
                printf("The matrix is NOT symmetric.\n");
                return;
            }
        }
    }

    printf("The matrix is symmetric.\n");
}

double determinant(double a[MAX][MAX], int n) {
    double temp[MAX][MAX];
    double det = 1;
    double factor;
    int i, j, k;
    int sign = 1;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            temp[i][j] = a[i][j];
    }

    for (i = 0; i < n; i++) {

        if (fabs(temp[i][i]) < 1e-9) {
            int swapRow = -1;

            for (j = i + 1; j < n; j++) {
                if (fabs(temp[j][i]) > 1e-9) {
                    swapRow = j;
                    break;
                }
            }

            if (swapRow == -1)
                return 0;

            for (k = 0; k < n; k++) {
                double t = temp[i][k];
                temp[i][k] = temp[swapRow][k];
                temp[swapRow][k] = t;
            }

            sign = -sign;
        }

        for (j = i + 1; j < n; j++) {
            factor = temp[j][i] / temp[i][i];

            for (k = i; k < n; k++)
                temp[j][k] -= factor * temp[i][k];
        }
    }

    for (i = 0; i < n; i++)
        det *= temp[i][i];

    return det * sign;
}

void transposeInPlace(double a[MAX][MAX], int n) {
    int i, j;
    double temp;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            temp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = temp;
        }
    }

    printf("Transpose of matrix:\n");
    displayMatrix(a, n);
}

void eigenPowerIteration(double a[MAX][MAX], int n) {
    double x[MAX], y[MAX];
    double eigenvalue = 0;
    double newEigenvalue;
    double norm;
    int i, j, k;
    int iterations;

    printf("Enter number of iterations: ");
    scanf("%d", &iterations);

    for (i = 0; i < n; i++)
        x[i] = 1.0;

    for (k = 0; k < iterations; k++) {

        for (i = 0; i < n; i++) {
            y[i] = 0;

            for (j = 0; j < n; j++)
                y[i] += a[i][j] * x[j];
        }

        norm = 0;

        for (i = 0; i < n; i++)
            norm += y[i] * y[i];

        norm = sqrt(norm);

        for (i = 0; i < n; i++)
            x[i] = y[i] / norm;

        newEigenvalue = 0;

        for (i = 0; i < n; i++)
            newEigenvalue += x[i] * y[i];

        eigenvalue = newEigenvalue;
    }

    printf("Dominant Eigenvalue = %.6lf\n", eigenvalue);

    printf("Corresponding Eigenvector:\n");

    for (i = 0; i < n; i++)
        printf("%.6lf\n", x[i]);
}

int main() {

    double a[MAX][MAX];
    double b[MAX][MAX];

    int n;
    int choice;

    printf("Enter size of square matrix: ");
    scanf("%d", &n);

    printf("\nEnter Matrix A\n");
    inputMatrix(a, n);

    do {

        printf("\n========== MENU ==========\n");
        printf("1. Matrix Addition\n");
        printf("2. Matrix Multiplication\n");
        printf("3. Check Zero Matrix\n");
        printf("4. Check Symmetric Matrix\n");
        printf("5. Find Determinant\n");
        printf("6. Transpose Matrix In-Place\n");
        printf("7. Find Eigenvalue and Eigenvector\n");
        printf("8. Display Matrix A\n");
        printf("0. Exit\n");
        printf("==========================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("\nEnter Matrix B\n");
                inputMatrix(b, n);
                addition(a, b, n);
                break;

            case 2:
                printf("\nEnter Matrix B\n");
                inputMatrix(b, n);
                multiplication(a, b, n);
                break;

            case 3:
                zeroMatrix(a, n);
                break;

            case 4:
                symmetricMatrix(a, n);
                break;

            case 5:
                printf("Determinant = %.2lf\n",
                       determinant(a, n));
                break;

            case 6:
                transposeInPlace(a, n);
                break;

            case 7:
                eigenPowerIteration(a, n);
                break;

            case 8:
                printf("Matrix A:\n");
                displayMatrix(a, n);
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
#include <stdio.h>

int main() {
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int red[n], blue[n], yellow[n];
    int r = 0, b = 0, y = 0;

    printf("Enter number and colour (R/B/Y):\n");

    for (int i = 0; i < n; i++) {
        int num;
        char colour;

        scanf("%d %c", &num, &colour);

        if (colour == 'R') {
            red[r++] = num;
        }
        else if (colour == 'B') {
            blue[b++] = num;
        }
        else if (colour == 'Y') {
            yellow[y++] = num;
        }
    }

    printf("\nSorted by colour:\n");

    for (int i = 0; i < r; i++)
        printf("(%d, R) ", red[i]);

    for (int i = 0; i < b; i++)
        printf("(%d, B) ", blue[i]);

    for (int i = 0; i < y; i++)
        printf("(%d, Y) ", yellow[i]);

    return 0;
}
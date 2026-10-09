#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate maximum overlap (suffix of a matches prefix of b)
int find_overlap(char *a, char *b, char *merged) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int max_overlap = 0;
    int type = 0; // 1 means b appended to a, 2 means a appended to b

    // Check overlap of a's suffix with b's prefix
    for (int i = 1; i <= len_a && i <= len_b; i++) {
        if (strncmp(a + len_a - i, b, i) == 0) {
            max_overlap = i;
            type = 1;
        }
    }

    // Check overlap of b's suffix with a's prefix
    for (int i = 1; i <= len_a && i <= len_b; i++) {
        if (strncmp(b + len_b - i, a, i) == 0) {
            if (i > max_overlap) {
                max_overlap = i;
                type = 2;
            }
        }
    }

    if (type == 1) {
        strcpy(merged, a);
        strcat(merged, b + max_overlap);
    } else if (type == 2) {
        strcpy(merged, b);
        strcat(merged, a + max_overlap);
    } else {
        strcpy(merged, a);
        strcat(merged, b);
    }

    return max_overlap;
}

int main() {
    int n;
    printf("Enter number of strings: ");
    scanf("%d", &n);

    char **strings = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        strings[i] = (char *)malloc(200 * sizeof(char));
        printf("Enter string %d: ", i + 1);
        scanf("%s", strings[i]);
    }

    int current_n = n;
    while (current_n > 1) {
        int max_ov = -1;
        int best_i = -1, best_j = -1;
        char best_merged[400];
        char temp_merged[400];

        // Find the pair with the maximum overlap
        for (int i = 0; i < current_n; i++) {
            for (int j = i + 1; j < current_n; j++) {
                int ov = find_overlap(strings[i], strings[j], temp_merged);
                if (ov > max_ov) {
                    max_ov = ov;
                    best_i = i;
                    best_j = j;
                    strcpy(best_merged, temp_merged);
                }
            }
        }

        // Replace best_i with the merged string and remove best_j
        strcpy(strings[best_i], best_merged);
        free(strings[best_j]);
        strings[best_j] = strings[current_n - 1];
        current_n--;
    }

    printf("\nShortest Superstring Result: %s\n", strings[0]);

    free(strings[0]);
    free(strings);
    return 0;
}
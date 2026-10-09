#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char s[100];
    int k;
    printf("Enter string: ");
    scanf("%s", s);
    printf("Enter distance K: ");
    scanf("%d", &k);

    int len = strlen(s);
    int count[26] = {0}, valid[26] = {0};
    char *result = (char *)malloc((len + 1) * sizeof(char));

    for (int i = 0; i < len; i++) count[s[i] - 'a']++;

    for (int i = 0; i < len; i++) {
        int best_char = -1, max_val = 0;
        for (int c = 0; c < 26; c++) {
            if (count[c] > max_val && valid[c] <= i) {
                max_val = count[c];
                best_char = c;
            }
        }
        if (best_char == -1) {
            printf("Result: \"\"\n");
            free(result); return 0;
        }
        result[i] = best_char + 'a';
        count[best_char]--;
        valid[best_char] = i + k;
    }
    result[len] = '\0';
    printf("Reorganized String: %s\n", result);
    free(result);
    return 0;
}
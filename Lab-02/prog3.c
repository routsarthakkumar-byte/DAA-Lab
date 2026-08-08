#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Standard 2-array merge subroutine
void merge_two_arrays(int arr1[], int size1, int arr2[], int size2, int result[]) {
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) result[k++] = arr1[i++];
        else                   result[k++] = arr2[j++];
    }
    while (i < size1) result[k++] = arr1[i++];
    while (j < size2) result[k++] = arr2[j++];
}

// ============================================================================
// METHOD 1: ITERATIVE / SEQUENTIAL MERGE - O(n * k^2)
// ============================================================================
int* merge_k_method1(int** arrays, int k, int n) {
    int current_size = n;
    int* result = (int*)malloc(n * sizeof(int));
    memcpy(result, arrays[0], n * sizeof(int));

    for (int i = 1; i < k; i++) {
        int* temp = (int*)malloc((current_size + n) * sizeof(int));
        merge_two_arrays(result, current_size, arrays[i], n, temp);
        free(result);
        result = temp;
        current_size += n;
    }
    return result;
}

// ============================================================================
// METHOD 2: DIVIDE & CONQUER (PAIRWISE) MERGE - O(n * k * log k)
// ============================================================================
int* merge_k_method2(int** arrays, int k, int n) {
    // Make copy of original arrays pointers
    int** temp_arrays = (int**)malloc(k * sizeof(int*));
    int* sizes = (int*)malloc(k * sizeof(int));

    for (int i = 0; i < k; i++) {
        temp_arrays[i] = (int*)malloc(n * sizeof(int));
        memcpy(temp_arrays[i], arrays[i], n * sizeof(int));
        sizes[i] = n;
    }

    int active_k = k;
    while (active_k > 1) {
        int new_k = 0;
        for (int i = 0; i < active_k; i += 2) {
            if (i + 1 < active_k) {
                int new_size = sizes[i] + sizes[i + 1];
                int* merged = (int*)malloc(new_size * sizeof(int));
                merge_two_arrays(temp_arrays[i], sizes[i], temp_arrays[i + 1], sizes[i + 1], merged);

                free(temp_arrays[i]);
                free(temp_arrays[i + 1]);

                temp_arrays[new_k] = merged;
                sizes[new_k] = new_size;
                new_k++;
            } else {
                temp_arrays[new_k] = temp_arrays[i];
                sizes[new_k] = sizes[i];
                new_k++;
            }
        }
        active_k = new_k;
    }

    int* final_result = temp_arrays[0];
    free(temp_arrays);
    free(sizes);
    return final_result;
}

// ============================================================================
// SVG GRAPH GENERATOR FUNCTION
// ============================================================================
void generate_kmerge_svg(const char* filename, int k_values[], double times_m1[], double times_m2[], int num_tests) {
    FILE *f = fopen(filename, "w");
    if (!f) return;

    double max_time = 0.0;
    for (int i = 0; i < num_tests; i++) {
        if (times_m1[i] > max_time) max_time = times_m1[i];
        if (times_m2[i] > max_time) max_time = times_m2[i];
    }
    if (max_time == 0) max_time = 1.0;

    int max_K = k_values[num_tests - 1];

    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"900\" height=\"600\">\n");
    fprintf(f, "  <rect width=\"100%%\" height=\"100%%\" fill=\"#111827\"/>\n");

    // Grid lines
    for (int y = 100; y <= 500; y += 100) {
        fprintf(f, "  <line x1=\"80\" y1=\"%d\" x2=\"820\" y2=\"%d\" stroke=\"#374151\" stroke-width=\"1\" stroke-dasharray=\"4\"/>\n", y, y);
    }

    // Axes
    fprintf(f, "  <line x1=\"80\" y1=\"500\" x2=\"830\" y2=\"500\" stroke=\"white\" stroke-width=\"2\"/>\n"); 
    fprintf(f, "  <line x1=\"80\" y1=\"500\" x2=\"80\" y2=\"70\" stroke=\"white\" stroke-width=\"2\"/>\n");   

    // Titles
    fprintf(f, "  <text x=\"450\" y=\"40\" fill=\"white\" font-family=\"sans-serif\" font-size=\"20\" font-weight=\"bold\" text-anchor=\"middle\">K-Way Merge: Method 1 O(N*K^2) vs Method 2 O(N*K log K)</text>\n");
    fprintf(f, "  <text x=\"450\" y=\"555\" fill=\"#d1d5db\" font-family=\"sans-serif\" font-size=\"14\" text-anchor=\"middle\">Number of Arrays (k)</text>\n");
    fprintf(f, "  <text x=\"25\" y=\"290\" fill=\"#d1d5db\" font-family=\"sans-serif\" font-size=\"14\" transform=\"rotate(-90 25,290)\" text-anchor=\"middle\">Execution Time (ms)</text>\n");

    // Method 1 Line (Red)
    fprintf(f, "  <polyline fill=\"none\" stroke=\"#f87171\" stroke-width=\"3\" points=\"");
    for (int i = 0; i < num_tests; i++) {
        int cx = 80 + (int)(((double)k_values[i] / max_K) * 740);
        int cy = 500 - (int)(((double)times_m1[i] / max_time) * 400);
        fprintf(f, "%d,%d ", cx, cy);
    }
    fprintf(f, "\"/>\n");

    // Method 2 Line (Green)
    fprintf(f, "  <polyline fill=\"none\" stroke=\"#4ade80\" stroke-width=\"3\" points=\"");
    for (int i = 0; i < num_tests; i++) {
        int cx = 80 + (int)(((double)k_values[i] / max_K) * 740);
        int cy = 500 - (int)(((double)times_m2[i] / max_time) * 400);
        fprintf(f, "%d,%d ", cx, cy);
    }
    fprintf(f, "\"/>\n");

    // Points & Labels
    for (int i = 0; i < num_tests; i++) {
        int cx = 80 + (int)(((double)k_values[i] / max_K) * 740);
        int cy1 = 500 - (int)(((double)times_m1[i] / max_time) * 400);
        int cy2 = 500 - (int)(((double)times_m2[i] / max_time) * 400);

        fprintf(f, "  <circle cx=\"%d\" cy=\"%d\" r=\"5\" fill=\"#f87171\"/>\n", cx, cy1);
        fprintf(f, "  <circle cx=\"%d\" cy=\"%d\" r=\"5\" fill=\"#4ade80\"/>\n", cx, cy2);
        fprintf(f, "  <text x=\"%d\" y=\"525\" fill=\"#9ca3af\" font-family=\"sans-serif\" font-size=\"11\" text-anchor=\"middle\">k=%d</text>\n", cx, k_values[i]);
    }

    // Legend
    fprintf(f, "  <rect x=\"100\" y=\"80\" width=\"360\" height=\"75\" fill=\"#1f2937\" stroke=\"#4b5563\" rx=\"6\"/>\n");
    fprintf(f, "  <line x1=\"115\" y1=\"105\" x2=\"145\" y2=\"105\" stroke=\"#f87171\" stroke-width=\"3\"/>\n");
    fprintf(f, "  <text x=\"155\" y=\"109\" fill=\"white\" font-family=\"sans-serif\" font-size=\"13\">Method 1: Sequential Merge O(n * k^2)</text>\n");
    fprintf(f, "  <line x1=\"115\" y1=\"132\" x2=\"145\" y2=\"132\" stroke=\"#4ade80\" stroke-width=\"3\"/>\n");
    fprintf(f, "  <text x=\"155\" y=\"136\" fill=\"white\" font-family=\"sans-serif\" font-size=\"13\">Method 2: Pairwise Merge O(n * k log k)</text>\n");

    fprintf(f, "</svg>\n");
    fclose(f);
    printf("\n[SUCCESS] Benchmark Graph saved as 'k_merge_complexity.svg'. Open it in any browser!\n");
}

// Helper function to compare int for qsort
int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    srand(42);

    int k_values[] = {4, 16, 32, 64, 128, 256, 512};
    int num_tests = sizeof(k_values) / sizeof(k_values[0]);
    int n = 2000; // Fixed size per array
    int trials = 3;

    double times_m1[7], times_m2[7];

    printf("=====================================================\n");
    printf("     MERGING K SORTED ARRAYS BENCHMARK RUNNER        \n");
    printf("     (Array size per k, n = %d)                      \n", n);
    printf("=====================================================\n\n");
    printf("%-10s | %-18s | %-18s\n", "k (Arrays)", "Method 1 Time(ms)", "Method 2 Time(ms)");
    printf("-----------------------------------------------------\n");

    for (int t_idx = 0; t_idx < num_tests; t_idx++) {
        int k = k_values[t_idx];
        double t1_sum = 0.0, t2_sum = 0.0;

        for (int tr = 0; tr < trials; tr++) {
            // Allocate k sorted arrays
            int** arrays = (int**)malloc(k * sizeof(int*));
            for (int i = 0; i < k; i++) {
                arrays[i] = (int*)malloc(n * sizeof(int));
                for (int j = 0; j < n; j++) arrays[i][j] = rand() % 100000;
                qsort(arrays[i], n, sizeof(int), compare_ints);
            }

            // Benchmark Method 1
            clock_t start = clock();
            int* res1 = merge_k_method1(arrays, k, n);
            t1_sum += ((double)(clock() - start)) / CLOCKS_PER_SEC * 1000.0;

            // Benchmark Method 2
            start = clock();
            int* res2 = merge_k_method2(arrays, k, n);
            t2_sum += ((double)(clock() - start)) / CLOCKS_PER_SEC * 1000.0;

            // Free allocated memory
            for (int i = 0; i < k; i++) free(arrays[i]);
            free(arrays);
            free(res1);
            free(res2);
        }

        times_m1[t_idx] = t1_sum / trials;
        times_m2[t_idx] = t2_sum / trials;

        printf("k = %-6d | %-18.3f | %-18.3f\n", k, times_m1[t_idx], times_m2[t_idx]);
    }

    printf("=====================================================\n");

    // Generate graph
    generate_kmerge_svg("k_merge_complexity.svg", k_values, times_m1, times_m2, num_tests);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================================================
// 1. STANDARD 2-WAY MERGE SORT
// ============================================================================

void merge_2way(int arr[], int temp[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else                  temp[k++] = arr[j++];
    }
    while (i <= mid)   temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

void merge_sort_2way_rec(int arr[], int temp[], int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_2way_rec(arr, temp, left, mid);
    merge_sort_2way_rec(arr, temp, mid + 1, right);
    merge_2way(arr, temp, left, mid, right);
}

void merge_sort_2way(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    merge_sort_2way_rec(arr, temp, 0, n - 1);
    free(temp);
}

// ============================================================================
// 2. MODIFIED 3-WAY MERGE SORT
// ============================================================================

void merge_3way(int arr[], int temp[], int low, int mid1, int mid2, int high) {
    int i = low, j = mid1, k = mid2, l = low;

    // Pick minimum among 3 active heads
    while ((i < mid1) && (j < mid2) && (k < high)) {
        if (arr[i] <= arr[j]) {
            if (arr[i] <= arr[k]) temp[l++] = arr[i++];
            else                  temp[l++] = arr[k++];
        } else {
            if (arr[j] <= arr[k]) temp[l++] = arr[j++];
            else                  temp[l++] = arr[k++];
        }
    }

    // Merge remaining 2 active ranges
    while ((i < mid1) && (j < mid2)) {
        if (arr[i] <= arr[j]) temp[l++] = arr[i++];
        else                  temp[l++] = arr[j++];
    }
    while ((j < mid2) && (k < high)) {
        if (arr[j] <= arr[k]) temp[l++] = arr[j++];
        else                  temp[l++] = arr[k++];
    }
    while ((i < mid1) && (k < high)) {
        if (arr[i] <= arr[k]) temp[l++] = arr[i++];
        else                  temp[l++] = arr[k++];
    }

    // Copy remaining single range
    while (i < mid1) temp[l++] = arr[i++];
    while (j < mid2) temp[l++] = arr[j++];
    while (k < high) temp[l++] = arr[k++];

    for (i = low; i < high; i++) {
        arr[i] = temp[i];
    }
}

void merge_sort_3way_rec(int arr[], int temp[], int low, int high) {
    if (high - low < 2) return;

    int len = high - low;
    int mid1 = low + len / 3;
    int mid2 = low + 2 * len / 3;

    merge_sort_3way_rec(arr, temp, low, mid1);
    merge_sort_3way_rec(arr, temp, mid1, mid2);
    merge_sort_3way_rec(arr, temp, mid2, high);

    merge_3way(arr, temp, low, mid1, mid2, high);
}

void merge_sort_3way(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    merge_sort_3way_rec(arr, temp, 0, n);
    free(temp);
}

// ============================================================================
// 3. SVG GRAPH GENERATOR FUNCTION
// ============================================================================

void generate_merge_svg(const char* filename, int sizes[], double times_2way[], double times_3way[], int num_sizes) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Error creating SVG file!\n");
        return;
    }

    // Dynamic maximum finding for proper Y-axis scaling
    double max_time = 0.0;
    for (int i = 0; i < num_sizes; i++) {
        if (times_2way[i] > max_time) max_time = times_2way[i];
        if (times_3way[i] > max_time) max_time = times_3way[i];
    }
    if (max_time == 0) max_time = 1.0;

    int max_N = sizes[num_sizes - 1];

    // SVG Canvas Initialization
    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"900\" height=\"600\">\n");
    fprintf(f, "  <rect width=\"100%%\" height=\"100%%\" fill=\"#111827\"/>\n"); // Dark background

    // Grid lines
    for (int y = 100; y <= 500; y += 100) {
        fprintf(f, "  <line x1=\"80\" y1=\"%d\" x2=\"820\" y2=\"%d\" stroke=\"#374151\" stroke-width=\"1\" stroke-dasharray=\"4\"/>\n", y, y);
    }
    for (int x = 80; x <= 820; x += 148) {
        fprintf(f, "  <line x1=\"%d\" y1=\"80\" x2=\"%d\" y2=\"500\" stroke=\"#374151\" stroke-width=\"1\" stroke-dasharray=\"4\"/>\n", x, x);
    }

    // Axes
    fprintf(f, "  <line x1=\"80\" y1=\"500\" x2=\"830\" y2=\"500\" stroke=\"white\" stroke-width=\"2\"/>\n"); // X-Axis
    fprintf(f, "  <line x1=\"80\" y1=\"500\" x2=\"80\" y2=\"70\" stroke=\"white\" stroke-width=\"2\"/>\n");   // Y-Axis

    // Title & Labels
    fprintf(f, "  <text x=\"450\" y=\"40\" fill=\"white\" font-family=\"sans-serif\" font-size=\"20\" font-weight=\"bold\" text-anchor=\"middle\">Order of Growth: 2-Way vs. 3-Way Merge Sort</text>\n");
    fprintf(f, "  <text x=\"450\" y=\"555\" fill=\"#d1d5db\" font-family=\"sans-serif\" font-size=\"14\" text-anchor=\"middle\">Array Size (N)</text>\n");
    fprintf(f, "  <text x=\"25\" y=\"290\" fill=\"#d1d5db\" font-family=\"sans-serif\" font-size=\"14\" transform=\"rotate(-90 25,290)\" text-anchor=\"middle\">Execution Time (ms)</text>\n");

    // Plotting 2-Way Merge Sort Line (Blue)
    fprintf(f, "  <polyline fill=\"none\" stroke=\"#38bdf8\" stroke-width=\"3\" points=\"");
    for (int i = 0; i < num_sizes; i++) {
        int cx = 80 + (int)(((double)sizes[i] / max_N) * 740);
        int cy = 500 - (int)(((double)times_2way[i] / max_time) * 400);
        fprintf(f, "%d,%d ", cx, cy);
    }
    fprintf(f, "\"/>\n");

    // Plotting 3-Way Merge Sort Line (Green)
    fprintf(f, "  <polyline fill=\"none\" stroke=\"#4ade80\" stroke-width=\"3\" points=\"");
    for (int i = 0; i < num_sizes; i++) {
        int cx = 80 + (int)(((double)sizes[i] / max_N) * 740);
        int cy = 500 - (int)(((double)times_3way[i] / max_time) * 400);
        fprintf(f, "%d,%d ", cx, cy);
    }
    fprintf(f, "\"/>\n");

    // Adding Data Points & Tooltips
    for (int i = 0; i < num_sizes; i++) {
        int cx = 80 + (int)(((double)sizes[i] / max_N) * 740);
        int cy2 = 500 - (int)(((double)times_2way[i] / max_time) * 400);
        int cy3 = 500 - (int)(((double)times_3way[i] / max_time) * 400);

        // 2-Way Points
        fprintf(f, "  <circle cx=\"%d\" cy=\"%d\" r=\"5\" fill=\"#38bdf8\"/>\n", cx, cy2);
        // 3-Way Points
        fprintf(f, "  <circle cx=\"%d\" cy=\"%d\" r=\"5\" fill=\"#4ade80\"/>\n", cx, cy3);

        // X-Axis tick labels
        fprintf(f, "  <text x=\"%d\" y=\"520\" fill=\"#9ca3af\" font-family=\"sans-serif\" font-size=\"11\" text-anchor=\"middle\">%d</text>\n", cx, sizes[i]);
    }

    // Legend Panel
    fprintf(f, "  <rect x=\"100\" y=\"80\" width=\"340\" height=\"75\" fill=\"#1f2937\" stroke=\"#4b5563\" rx=\"6\"/>\n");
    
    fprintf(f, "  <line x1=\"115\" y1=\"105\" x2=\"145\" y2=\"105\" stroke=\"#38bdf8\" stroke-width=\"3\"/>\n");
    fprintf(f, "  <circle cx=\"130\" cy=\"105\" r=\"4\" fill=\"#38bdf8\"/>\n");
    fprintf(f, "  <text x=\"155\" y=\"109\" fill=\"white\" font-family=\"sans-serif\" font-size=\"13\">Standard 2-Way Merge Sort O(N log N)</text>\n");

    fprintf(f, "  <line x1=\"115\" y1=\"132\" x2=\"145\" y2=\"132\" stroke=\"#4ade80\" stroke-width=\"3\"/>\n");
    fprintf(f, "  <circle cx=\"130\" cy=\"132\" r=\"4\" fill=\"#4ade80\"/>\n");
    fprintf(f, "  <text x=\"155\" y=\"136\" fill=\"white\" font-family=\"sans-serif\" font-size=\"13\">Modified 3-Way Merge Sort O(N log N)</text>\n");

    fprintf(f, "</svg>\n");
    fclose(f);
    printf("\n[SUCCESS] Graph generated as '%s'. Open it in Chrome/Firefox or any browser!\n", filename);
}

// ============================================================================
// 4. MAIN BENCHMARK DRIVER
// ============================================================================

int main() {
    srand(42);

    int sizes[] = {10000, 50000, 100000, 250000, 500000, 750000, 1000000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int trials = 3;

    double times_2way[7];
    double times_3way[7];

    printf("=====================================================\n");
    printf("     2-WAY VS 3-WAY MERGE SORT BENCHMARK RUNNER      \n");
    printf("=====================================================\n\n");
    printf("%-10s | %-18s | %-18s\n", "Size (N)", "2-Way Time (ms)", "3-Way Time (ms)");
    printf("-----------------------------------------------------\n");

    for (int s = 0; s < num_sizes; s++) {
        int N = sizes[s];

        int *orig = (int *)malloc(N * sizeof(int));
        int *arr1 = (int *)malloc(N * sizeof(int));
        int *arr2 = (int *)malloc(N * sizeof(int));

        double time_2way = 0.0, time_3way = 0.0;

        for (int t = 0; t < trials; t++) {
            for (int i = 0; i < N; i++) orig[i] = rand();

            // Measure 2-Way Merge Sort
            memcpy(arr1, orig, N * sizeof(int));
            clock_t start = clock();
            merge_sort_2way(arr1, N);
            time_2way += ((double)(clock() - start)) / CLOCKS_PER_SEC * 1000.0;

            // Measure 3-Way Merge Sort
            memcpy(arr2, orig, N * sizeof(int));
            start = clock();
            merge_sort_3way(arr2, N);
            time_3way += ((double)(clock() - start)) / CLOCKS_PER_SEC * 1000.0;
        }

        time_2way /= trials;
        time_3way /= trials;

        times_2way[s] = time_2way;
        times_3way[s] = time_3way;

        printf("%-10d | %-18.3f | %-18.3f\n", N, time_2way, time_3way);

        free(orig);
        free(arr1);
        free(arr2);
    }

    printf("=====================================================\n");

    // Generate Graph automatically without external software
    generate_merge_svg("merge_sort_complexity.svg", sizes, times_2way, times_3way, num_sizes);

    return 0;
}
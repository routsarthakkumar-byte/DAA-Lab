#include <stdio.h>
#include <stdlib.h>

struct MinHNode {
    char item;
    unsigned freq;
    struct MinHNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHNode **array;
};

struct MinHNode *newNode(char item, unsigned freq) {
    struct MinHNode *temp = (struct MinHNode *)malloc(sizeof(struct MinHNode));
    temp->left = temp->right = NULL;
    temp->item = item;
    temp->freq = freq;
    return temp;
}

struct MinHeap *createMinHeap(unsigned capacity) {
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHNode **)malloc(minHeap->capacity * sizeof(struct MinHNode *));
    return minHeap;
}

void swapMinHNode(struct MinHNode **a, struct MinHNode **b) {
    struct MinHNode *t = *a; *a = *b; *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx) {
    int smallest = idx, left = 2 * idx + 1, right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq) smallest = left;
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq) smallest = right;
    if (smallest != idx) {
        swapMinHNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

struct MinHNode *extractMin(struct MinHeap *minHeap) {
    struct MinHNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap *minHeap, struct MinHNode *minHNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHNode;
}

struct MinHNode *buildHuffmanTree(char item[], int freq[], int size) {
    struct MinHNode *left, *right, *top;
    struct MinHeap *minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i) minHeap->array[i] = newNode(item[i], freq[i]);
    minHeap->size = size;
    for (int i = (minHeap->size - 1) / 2; i >= 0; --i) minHeapify(minHeap, i);

    while (minHeap->size > 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left; top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void printCodes(struct MinHNode *root, int arr[], int top) {
    if (root->left) { arr[top] = 0; printCodes(root->left, arr, top + 1); }
    if (root->right) { arr[top] = 1; printCodes(root->right, arr, top + 1); }
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->item);
        for (int i = 0; i < top; ++i) printf("%d", arr[i]);
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter number of symbols: ");
    scanf("%d", &n);
    char *arr = (char *)malloc(n * sizeof(char));
    int *freq = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("Enter symbol and frequency %d: ", i + 1);
        scanf(" %c %d", &arr[i], &freq[i]);
    }
    struct MinHNode *root = buildHuffmanTree(arr, freq, n);
    int code[100], top = 0;
    printf("\nHuffman Codes:\n");
    printCodes(root, code, top);
    free(arr); free(freq);
    return 0;
}
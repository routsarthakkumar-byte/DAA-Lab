#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// ============================================================================
// DATA STRUCTURE DEFINITIONS
// ============================================================================

typedef struct {
    int *data;
    int size;
    int capacity;
} Array;

typedef struct SNode {
    int key;
    struct SNode *next;
} SNode;

typedef struct DNode {
    int key;
    struct DNode *prev;
    struct DNode *next;
} DNode;

typedef struct {
    DNode *head;
    DNode *tail;
} DList;

// Helper: Node allocation
SNode* create_snode(int k) {
    SNode *n = (SNode*)malloc(sizeof(SNode));
    n->key = k;
    n->next = NULL;
    return n;
}

DNode* create_dnode(int k) {
    DNode *n = (DNode*)malloc(sizeof(DNode));
    n->key = k;
    n->prev = n->next = NULL;
    return n;
}

// ============================================================================
// 1. UNSORTED ARRAY
// ============================================================================
int UA_Search(Array *A, int k) {
    for (int i = 0; i < A->size; i++) if (A->data[i] == k) return i;
    return -1;
}
void UA_Insert(Array *A, int x) { A->data[A->size++] = x; }
void UA_Delete(Array *A, int idx) {
    if (idx < 0 || idx >= A->size) return;
    A->data[idx] = A->data[--A->size];
}
int UA_Min(Array *A) {
    if (!A->size) return INT_MAX;
    int min = A->data[0];
    for (int i = 1; i < A->size; i++) if (A->data[i] < min) min = A->data[i];
    return min;
}
int UA_Max(Array *A) {
    if (!A->size) return INT_MIN;
    int max = A->data[0];
    for (int i = 1; i < A->size; i++) if (A->data[i] > max) max = A->data[i];
    return max;
}
int UA_Predecessor(Array *A, int val) {
    int pred = INT_MIN;
    for (int i = 0; i < A->size; i++) {
        if (A->data[i] < val && A->data[i] > pred) pred = A->data[i];
    }
    return pred;
}
int UA_Successor(Array *A, int val) {
    int succ = INT_MAX;
    for (int i = 0; i < A->size; i++) {
        if (A->data[i] > val && A->data[i] < succ) succ = A->data[i];
    }
    return succ;
}

// ============================================================================
// 2. SORTED ARRAY
// ============================================================================
int SA_Search(Array *A, int k) {
    int low = 0, high = A->size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (A->data[mid] == k) return mid;
        if (A->data[mid] < k) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
void SA_Insert(Array *A, int x) {
    int i = A->size - 1;
    while (i >= 0 && A->data[i] > x) {
        A->data[i + 1] = A->data[i];
        i--;
    }
    A->data[i + 1] = x;
    A->size++;
}
void SA_Delete(Array *A, int idx) {
    if (idx < 0 || idx >= A->size) return;
    for (int i = idx; i < A->size - 1; i++) A->data[i] = A->data[i + 1];
    A->size--;
}
int SA_Min(Array *A) { return A->size ? A->data[0] : INT_MAX; }
int SA_Max(Array *A) { return A->size ? A->data[A->size - 1] : INT_MIN; }
int SA_Predecessor(Array *A, int val) {
    int idx = SA_Search(A, val);
    return (idx > 0) ? A->data[idx - 1] : INT_MIN;
}
int SA_Successor(Array *A, int val) {
    int idx = SA_Search(A, val);
    return (idx >= 0 && idx < A->size - 1) ? A->data[idx + 1] : INT_MAX;
}

// ============================================================================
// 3. SINGLY LINKED LIST (UNSORTED)
// ============================================================================
SNode* SLLU_Search(SNode *head, int k) {
    while (head && head->key != k) head = head->next;
    return head;
}
void SLLU_Insert(SNode **head, int x) {
    SNode *n = create_snode(x);
    n->next = *head;
    *head = n;
}
void SLLU_Delete(SNode **head, int x) {
    if (!*head) return;
    if ((*head)->key == x) {
        SNode *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    SNode *curr = *head;
    while (curr->next && curr->next->key != x) curr = curr->next;
    if (curr->next) {
        SNode *temp = curr->next;
        curr->next = temp->next;
        free(temp);
    }
}
int SLLU_Min(SNode *head) {
    if (!head) return INT_MAX;
    int min = head->key;
    while (head) {
        if (head->key < min) min = head->key;
        head = head->next;
    }
    return min;
}
int SLLU_Max(SNode *head) {
    if (!head) return INT_MIN;
    int max = head->key;
    while (head) {
        if (head->key > max) max = head->key;
        head = head->next;
    }
    return max;
}

// ============================================================================
// 4. SINGLY LINKED LIST (SORTED)
// ============================================================================
SNode* SLLS_Search(SNode *head, int k) {
    while (head && head->key < k) head = head->next;
    return (head && head->key == k) ? head : NULL;
}
void SLLS_Insert(SNode **head, int x) {
    SNode *n = create_snode(x);
    if (!*head || (*head)->key >= x) {
        n->next = *head;
        *head = n;
        return;
    }
    SNode *curr = *head;
    while (curr->next && curr->next->key < x) curr = curr->next;
    n->next = curr->next;
    curr->next = n;
}

// ============================================================================
// 5. DOUBLY LINKED LIST (UNSORTED)
// ============================================================================
DNode* DLLU_Search(DList *L, int k) {
    DNode *curr = L->head;
    while (curr && curr->key != k) curr = curr->next;
    return curr;
}
void DLLU_Insert(DList *L, int x) {
    DNode *n = create_dnode(x);
    n->next = L->head;
    if (L->head) L->head->prev = n;
    else L->tail = n;
    L->head = n;
}
void DLLU_Delete(DList *L, DNode *x) {
    if (!x) return;
    if (x->prev) x->prev->next = x->next;
    else L->head = x->next;
    if (x->next) x->next->prev = x->prev;
    else L->tail = x->prev;
    free(x);
}

// ============================================================================
// 6. DOUBLY LINKED LIST (SORTED)
// ============================================================================
void DLLS_Insert(DList *L, int x) {
    DNode *n = create_dnode(x);
    if (!L->head) {
        L->head = L->tail = n;
        return;
    }
    if (L->head->key >= x) {
        n->next = L->head;
        L->head->prev = n;
        L->head = n;
        return;
    }
    DNode *curr = L->head;
    while (curr->next && curr->next->key < x) curr = curr->next;
    n->next = curr->next;
    n->prev = curr;
    if (curr->next) curr->next->prev = n;
    else L->tail = n;
    curr->next = n;
}
int DLLS_Min(DList *L) { return L->head ? L->head->key : INT_MAX; }
int DLLS_Max(DList *L) { return L->tail ? L->tail->key : INT_MIN; }

// ============================================================================
// GRAPH GENERATOR FUNCTION
// ============================================================================
void generate_complexity_svg(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) return;

    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"900\" height=\"650\">\n");
    fprintf(f, "  <rect width=\"100%%\" height=\"100%%\" fill=\"#121212\"/>\n");

    for (int i = 50; i <= 800; i += 50) {
        fprintf(f, "  <line x1=\"%d\" y1=\"50\" x2=\"%d\" y2=\"550\" stroke=\"#2a2a2a\" stroke-width=\"1\"/>\n", i, i);
        fprintf(f, "  <line x1=\"50\" y1=\"%d\" x2=\"800\" y2=\"%d\" stroke=\"#2a2a2a\" stroke-width=\"1\"/>\n", i, i);
    }

    fprintf(f, "  <line x1=\"50\" y1=\"550\" x2=\"820\" y2=\"550\" stroke=\"white\" stroke-width=\"2\"/>\n"); 
    fprintf(f, "  <line x1=\"50\" y1=\"550\" x2=\"50\" y2=\"30\" stroke=\"white\" stroke-width=\"2\"/>\n"); 
    fprintf(f, "  <text x=\"400\" y=\"595\" fill=\"white\" font-family=\"Arial\" font-size=\"14\" font-weight=\"bold\">Number of Elements (N)</text>\n");
    fprintf(f, "  <text x=\"20\" y=\"300\" fill=\"white\" font-family=\"Arial\" font-size=\"14\" font-weight=\"bold\" transform=\"rotate(-90 20,300)\">Time Taken</text>\n");
    fprintf(f, "  <text x=\"50\" y=\"30\" fill=\"white\" font-family=\"Arial\" font-size=\"16\" font-weight=\"bold\">Asymptotic Time Complexity Comparison</text>\n");

    // O(1) Lime Line
    fprintf(f, "  <polyline fill=\"none\" stroke=\"#00FF66\" stroke-width=\"3\" points=\"");
    for (int x = 50; x <= 800; x += 10) fprintf(f, "%d,%d ", x, 520);
    fprintf(f, "\"/>\n");

    // O(log N) Cyan Line
    fprintf(f, "  <polyline fill=\"none\" stroke=\"#00E5FF\" stroke-width=\"3\" points=\"");
    for (int x = 50; x <= 800; x += 5) {
        double n = (x - 50);
        double y = 550 - (n > 0 ? 45 * log2(n + 1) : 0);
        fprintf(f, "%d,%d ", x, (int)y);
    }
    fprintf(f, "\"/>\n");

    // O(N) Red Line
    fprintf(f, "  <polyline fill=\"none\" stroke=\"#FF3366\" stroke-width=\"3\" points=\"");
    for (int x = 50; x <= 800; x += 10) {
        double y = 550 - 0.6 * (x - 50);
        if (y > 40) fprintf(f, "%d,%d ", x, (int)y);
    }
    fprintf(f, "\"/>\n");

    fprintf(f, "  <text x=\"810\" y=\"525\" fill=\"#00FF66\" font-family=\"Arial\" font-size=\"14\" font-weight=\"bold\">O(1)</text>\n");
    fprintf(f, "  <text x=\"810\" y=\"110\" fill=\"#00E5FF\" font-family=\"Arial\" font-size=\"14\" font-weight=\"bold\">O(log N)</text>\n");
    fprintf(f, "  <text x=\"810\" y=\"80\" fill=\"#FF3366\" font-family=\"Arial\" font-size=\"14\" font-weight=\"bold\">O(N)</text>\n");

    // Legend Panel
    fprintf(f, "  <rect x=\"80\" y=\"60\" width=\"460\" height=\"160\" fill=\"#1e1e1e\" stroke=\"#444\" rx=\"5\"/>\n");
    fprintf(f, "  <text x=\"95\" y=\"82\" fill=\"white\" font-family=\"Arial\" font-size=\"13\" font-weight=\"bold\">Performance by Data Structure:</text>\n");

    const char* legend[] = {
        "<tspan fill=\"#FF3366\">O(N)</tspan> Search, <tspan fill=\"#00FF66\">O(1)</tspan> Insert : Unsorted Array, DLL (Unsorted)",
        "<tspan fill=\"#00E5FF\">O(log N)</tspan> Search, <tspan fill=\"#FF3366\">O(N)</tspan> Insert : Sorted Array",
        "<tspan fill=\"#FF3366\">O(N)</tspan> Search, <tspan fill=\"#FF3366\">O(N)</tspan> Insert : SLL (Sorted), DLL (Sorted)",
        "<tspan fill=\"#FF3366\">O(N)</tspan> Search, <tspan fill=\"#00FF66\">O(1)</tspan> Delete : DLL (Sorted &amp; Unsorted)",
        "<tspan fill=\"#FF3366\">O(N)</tspan> Search, <tspan fill=\"#00FF66\">O(1)</tspan> Insert : SLL (Unsorted)"
    };

    for (int i = 0; i < 5; i++) {
        fprintf(f, "  <text x=\"95\" y=\"%d\" fill=\"#ccc\" font-family=\"Arial\" font-size=\"12\">%s</text>\n", 105 + (i * 22), legend[i]);
    }

    fprintf(f, "</svg>\n");
    fclose(f);
    printf("\n[SUCCESS] Interactive SVG graph exported as 'prog1.svg'. Open it in Chrome/Edge!\n");
}

// ============================================================================
// MAIN FUNCTION & COMPLETE OPERATIONS BENCHMARK
// ============================================================================
int main() {
    int n, val, searchKey;

    printf("=========================================================\n");
    printf("     DICTIONARY ADT COMPLETE OPERATIONAL BENCHMARK      \n");
    printf("=========================================================\n\n");

    printf("How Many elements do you want to insert? (e.g., 5): ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    // Initialize Structures
    Array UA = {(int*)malloc(n * sizeof(int)), 0, n};
    Array SA = {(int*)malloc(n * sizeof(int)), 0, n};
    SNode *SLLU = NULL, *SLLS = NULL;
    DList DLLU = {NULL, NULL}, DLLS = {NULL, NULL};

    printf("\n%d Numbers Enter:\n", n);
    for (int i = 0; i < n; i++) {
        printf(" Element [%d]: ", i + 1);
        scanf("%d", &val);

        // 1. Insert across ALL 6 Data Structures
        UA_Insert(&UA, val);
        SA_Insert(&SA, val);
        SLLU_Insert(&SLLU, val);
        SLLS_Insert(&SLLS, val);
        DLLU_Insert(&DLLU, val);
        DLLS_Insert(&DLLS, val);
    }

    // 2. Display States
    printf("\n---------------------------------------------------------\n");
    printf("                 DATA STRUCTURE STATES                   \n");
    printf("---------------------------------------------------------\n");
    printf("1. Unsorted Array : ");
    for (int i = 0; i < UA.size; i++) printf("%d ", UA.data[i]);
    printf("\n2. Sorted Array   : ");
    for (int i = 0; i < SA.size; i++) printf("%d ", SA.data[i]);
    printf("\n3. Sorted DLL     : ");
    for (DNode *c = DLLS.head; c; c = c->next) printf("%d <-> ", c->key);
    printf("NULL\n");

    // 3. Min/Max Operations Test across Structures
    printf("\n---------------------------------------------------------\n");
    printf("                   MIN / MAX TESTS                       \n");
    printf("---------------------------------------------------------\n");
    printf("Unsorted Array -> Min: %d | Max: %d\n", UA_Min(&UA), UA_Max(&UA));
    printf("Sorted Array   -> Min: %d | Max: %d\n", SA_Min(&SA), SA_Max(&SA));
    printf("Sorted DLL     -> Min: %d | Max: %d\n", DLLS_Min(&DLLS), DLLS_Max(&DLLS));

    // 4. Search, Predecessor & Successor Operations Test
    printf("\n---------------------------------------------------------\n");
    printf("Enter Element to Search & Find Pred/Succ: ");
    scanf("%d", &searchKey);

    int idxUA = UA_Search(&UA, searchKey);
    int idxSA = SA_Search(&SA, searchKey);

    printf("\n[Linear Search]   Unsorted Array Index : %d\n", idxUA);
    printf("[Binary Search]   Sorted Array Index   : %d\n", idxSA);

    printf("Predecessor of %d (Sorted Array) : %d\n", searchKey, SA_Predecessor(&SA, searchKey));
    printf("Successor of %d   (Sorted Array) : %d\n", searchKey, SA_Successor(&SA, searchKey));

    // Generate Visual Complexity Graph
    generate_complexity_svg("prog1.svg");

    // Free Allocated Memory
    free(UA.data);
    free(SA.data);

    return 0;
}
#include <stdio.h>

#define MAX 10

/* ================= 1D ARRAY OPERATIONS (1-10) ================= */

/* 1. Array display */
void displayArray(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

/* 2. Array traversal (visit every element with its index) */
void traverseArray(int a[], int n) {
    for (int i = 0; i < n; i++) printf("a[%d] = %d\n", i, a[i]);
}

/* 3. Accessing an element */
int accessElement(int a[], int n, int index) {
    if (index < 0 || index >= n) { printf("Invalid index!\n"); return -1; }
    return a[index];
}

/* 4. Update an element */
void updateElement(int a[], int n, int index, int value) {
    if (index < 0 || index >= n) { printf("Invalid index!\n"); return; }
    a[index] = value;
}

/* 5. Sum of all elements */
int arraySum(int a[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum;
}

/* 6. Average */
float arrayAverage(int a[], int n) {
    return (float)arraySum(a, n) / n;
}

/* 7. Find maximum */
int findMax(int a[], int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) if (a[i] > max) max = a[i];
    return max;
}

/* 8. Find minimum */
int findMin(int a[], int n) {
    int min = a[0];
    for (int i = 1; i < n; i++) if (a[i] < min) min = a[i];
    return min;
}

/* 9. Searching (linear search) - returns index or -1 */
int linearSearch(int a[], int n, int key) {
    for (int i = 0; i < n; i++) if (a[i] == key) return i;
    return -1;
}

/* 10. Count elements (total count, and count of a specific value) */
int countElements(int a[], int n) { return n; }
int countOccurrences(int a[], int n, int key) {
    int c = 0;
    for (int i = 0; i < n; i++) if (a[i] == key) c++;
    return c;
}

/* ================= MATRIX OPERATIONS (11-25) ================= */

void displayMatrix(int m[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) printf("%4d", m[i][j]);
        printf("\n");
    }
}

/* 11. Sum of each row */
void rowSums(int m[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++) {
        int s = 0;
        for (int j = 0; j < c; j++) s += m[i][j];
        printf("Sum of row %d = %d\n", i, s);
    }
}

/* 12. Sum of each column */
void colSums(int m[MAX][MAX], int r, int c) {
    for (int j = 0; j < c; j++) {
        int s = 0;
        for (int i = 0; i < r; i++) s += m[i][j];
        printf("Sum of column %d = %d\n", j, s);
    }
}

/* 13. Row maximum / minimum */
void rowMaxMin(int m[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++) {
        int max = m[i][0], min = m[i][0];
        for (int j = 1; j < c; j++) {
            if (m[i][j] > max) max = m[i][j];
            if (m[i][j] < min) min = m[i][j];
        }
        printf("Row %d: max = %d, min = %d\n", i, max, min);
    }
}

/* 14. Column maximum / minimum */
void colMaxMin(int m[MAX][MAX], int r, int c) {
    for (int j = 0; j < c; j++) {
        int max = m[0][j], min = m[0][j];
        for (int i = 1; i < r; i++) {
            if (m[i][j] > max) max = m[i][j];
            if (m[i][j] < min) min = m[i][j];
        }
        printf("Column %d: max = %d, min = %d\n", j, max, min);
    }
}

/* 15. Matrix addition */
void matAdd(int a[MAX][MAX], int b[MAX][MAX], int res[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) res[i][j] = a[i][j] + b[i][j];
}

/* 16. Matrix subtraction */
void matSub(int a[MAX][MAX], int b[MAX][MAX], int res[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) res[i][j] = a[i][j] - b[i][j];
}

/* 17. Matrix multiplication (a: r1 x c1, b: c1 x c2) */
void matMul(int a[MAX][MAX], int b[MAX][MAX], int res[MAX][MAX], int r1, int c1, int c2) {
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < c1; k++) res[i][j] += a[i][k] * b[k][j];
        }
}

/* 18. Transpose */
void transpose(int m[MAX][MAX], int t[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) t[j][i] = m[i][j];
}

/* 19. Main diagonal (square matrix) */
void mainDiagonal(int m[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) printf("%d ", m[i][i]);
    printf("\n");
}

/* 20. Secondary diagonal (square matrix) */
void secondaryDiagonal(int m[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) printf("%d ", m[i][n - 1 - i]);
    printf("\n");
}

/* 21. Sum of diagonal elements */
void diagonalSums(int m[MAX][MAX], int n) {
    int main_sum = 0, sec_sum = 0;
    for (int i = 0; i < n; i++) {
        main_sum += m[i][i];
        sec_sum += m[i][n - 1 - i];
    }
    printf("Main diagonal sum      = %d\n", main_sum);
    printf("Secondary diagonal sum = %d\n", sec_sum);
}

/* 22. Upper triangular matrix (zero out elements below main diagonal) */
void upperTriangular(int m[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%4d", (j >= i) ? m[i][j] : 0);
        printf("\n");
    }
}

/* 23. Lower triangular matrix (zero out elements above main diagonal) */
void lowerTriangular(int m[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%4d", (j <= i) ? m[i][j] : 0);
        printf("\n");
    }
}

/* 24. Symmetric matrix check (A == A^T) */
int isSymmetric(int m[MAX][MAX], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (m[i][j] != m[j][i]) return 0;
    return 1;
}

/* 25. Identity matrix check (1 on diagonal, 0 elsewhere) */
int isIdentity(int m[MAX][MAX], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (i == j && m[i][j] != 1) return 0;
            if (i != j && m[i][j] != 0) return 0;
        }
    return 1;
}

/* ===================== MAIN (demo) ===================== */
int main(void) {
    int arr[] = {12, 5, 8, 20, 5, 17};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("===== 1D ARRAY OPERATIONS =====\n");
    printf("1. Display: ");              displayArray(arr, n);
    printf("2. Traversal:\n");           traverseArray(arr, n);
    printf("3. Element at index 2: %d\n", accessElement(arr, n, 2));
    updateElement(arr, n, 2, 99);
    printf("4. After updating index 2 to 99: "); displayArray(arr, n);
    printf("5. Sum: %d\n", arraySum(arr, n));
    printf("6. Average: %.2f\n", arrayAverage(arr, n));
    printf("7. Maximum: %d\n", findMax(arr, n));
    printf("8. Minimum: %d\n", findMin(arr, n));
    int pos = linearSearch(arr, n, 20);
    if (pos != -1) printf("9. Search 20: found at index %d\n", pos);
    else           printf("9. Search 20: not found\n");
    printf("10. Total elements: %d, occurrences of 5: %d\n",
           countElements(arr, n), countOccurrences(arr, n, 5));

    int A[MAX][MAX] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int B[MAX][MAX] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int R[MAX][MAX];
    int N = 3;

    printf("\n===== MATRIX OPERATIONS =====\nMatrix A:\n");
    displayMatrix(A, N, N);
    printf("Matrix B:\n");
    displayMatrix(B, N, N);

    printf("\n11. Row sums:\n");        rowSums(A, N, N);
    printf("\n12. Column sums:\n");      colSums(A, N, N);
    printf("\n13. Row max/min:\n");      rowMaxMin(A, N, N);
    printf("\n14. Column max/min:\n");   colMaxMin(A, N, N);

    printf("\n15. A + B:\n");  matAdd(A, B, R, N, N);  displayMatrix(R, N, N);
    printf("\n16. A - B:\n");  matSub(A, B, R, N, N);  displayMatrix(R, N, N);
    printf("\n17. A x B:\n");  matMul(A, B, R, N, N, N); displayMatrix(R, N, N);
    printf("\n18. Transpose of A:\n"); transpose(A, R, N, N); displayMatrix(R, N, N);

    printf("\n19. Main diagonal: ");       mainDiagonal(A, N);
    printf("20. Secondary diagonal: ");    secondaryDiagonal(A, N);
    printf("21. Diagonal sums:\n");        diagonalSums(A, N);

    printf("\n22. Upper triangular matrix:\n"); upperTriangular(A, N);
    printf("\n23. Lower triangular matrix:\n"); lowerTriangular(A, N);

    int S[MAX][MAX] = {{1, 2, 3}, {2, 4, 5}, {3, 5, 6}};
    int I[MAX][MAX] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    printf("\n24. Is A symmetric? %s\n", isSymmetric(A, N) ? "Yes" : "No");
    printf("    Is S symmetric? %s\n", isSymmetric(S, N) ? "Yes" : "No");
    printf("25. Is A identity? %s\n", isIdentity(A, N) ? "Yes" : "No");
    printf("    Is I identity? %s\n", isIdentity(I, N) ? "Yes" : "No");

    return 0;
}
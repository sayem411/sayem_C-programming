#include <stdio.h>

// Function to swap two rows
void rowswap(int n, int a[n][n], int x, int y) {
    for (int i = 0; i < n; i++) {
        int temp = a[x][i];
        a[x][i] = a[y][i];
        a[y][i] = temp;
    }
}

// Function to swap two columns
void colswap(int n, int a[n][n], int x, int y) {
    for (int i = 0; i < n; i++) {
        int temp = a[i][x];
        a[i][x] = a[i][y];
        a[i][y] = temp;
    }
}

int main() {
    int n, x, y;
    int a[1000][1000];

    // Input
    scanf("%d %d %d", &n, &x, &y);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // Convert to 0-based index
    x--;
    y--;

    // Call functions
    rowswap(n, a, x, y);
    colswap(n, a, x, y);

    // Output result
    printf("After swapping rows and columns:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}
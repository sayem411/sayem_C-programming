#include <stdio.h>

int main() {
    int a[100][100];
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    int identity = 1;
    if (rows != cols) {
        identity = 0; 
    } else {
        for (int i = 0; i < rows && identity; i++) {
            for (int j = 0; j < cols; j++) {
                if (i == j && a[i][j] != 1) {
                    identity = 0;
                    break;
                }
                if (i != j && a[i][j] != 0) {
                    identity = 0;
                    break;
                }
            }
        }
    }

    if (identity)
        printf("The matrix is an identity matrix.\n");
    else
        printf("The matrix is NOT an identity matrix.\n");

    return 0;
}
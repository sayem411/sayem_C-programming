#include <stdio.h>

int main() {
    int m[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    printf("Lower triangular matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j <= i)
                printf("%4d", m[i][j]);
            else
                printf("%4d", 0);
        }
        printf("\n");
    }
    return 0;
}

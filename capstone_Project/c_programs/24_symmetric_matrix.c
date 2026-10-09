#include <stdio.h>

int main() {
    int m[3][3] = {{1, 2, 3}, {2, 4, 5}, {3, 5, 6}};
    int symmetric = 1;

    for (int i = 0; i < 3 && symmetric; i++)
        for (int j = 0; j < 3; j++)
            if (m[i][j] != m[j][i]) {
                symmetric = 0;
                break;
            }

    if (symmetric)
        printf("The matrix is symmetric.\n");
    else
        printf("The matrix is NOT symmetric.\n");
    return 0;
}

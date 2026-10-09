#include <stdio.h>

int main() {
    int m[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int t[3][2];

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            t[j][i] = m[i][j];

    printf("Transpose =\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++)
            printf("%4d", t[i][j]);
        printf("\n");
    }
    return 0;
}

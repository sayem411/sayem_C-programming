#include <stdio.h>

int main() {
    int m[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    printf("Main diagonal: ");
    for (int i = 0; i < 3; i++)
        printf("%d ", m[i][i]);
    printf("\n");
    return 0;
}

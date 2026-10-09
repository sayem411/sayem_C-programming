#include <stdio.h>

int main() {
    int m[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    printf("Secondary diagonal: ");
    for (int i = 0; i < 3; i++)
        printf("%d ", m[i][3 - 1 - i]);
    printf("\n");
    return 0;
}

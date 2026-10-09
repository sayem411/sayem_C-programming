#include <stdio.h>

int main() {
    int m[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int mainSum = 0, secSum = 0;

    for (int i = 0; i < 3; i++) {
        mainSum += m[i][i];
        secSum += m[i][3 - 1 - i];
    }

    printf("Sum of main diagonal      = %d\n", mainSum);
    printf("Sum of secondary diagonal = %d\n", secSum);
    return 0;
}

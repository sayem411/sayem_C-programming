#include <stdio.h>

int main() {
    int m[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    int identity = 1;

    for (int i = 0; i < 3 && identity; i++)
        for (int j = 0; j < 3; j++) {
            if (i == j && m[i][j] != 1) { identity = 0; break; }
            if (i != j && m[i][j] != 0) { identity = 0; break; }
        }

    if (identity)
        printf("The matrix is an identity matrix.\n");
    else
        printf("The matrix is NOT an identity matrix.\n");
    return 0;
}

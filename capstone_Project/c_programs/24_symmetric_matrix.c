#include <stdio.h>

int main() {
     int a[100][100];
    int rows,cols;
 
    printf("Enter rows and columns: ");
    scanf("%d %d",&rows,&cols);
 
    printf("Enter matrix elements:\n");
    for (int i=0;i<rows;i++) {
        for(int j=0;j<cols;j++) {
            scanf("%d",&a[i][j]);
        }
    }
    int symmetric = 1;

    for (int i = 0; i < 3 && symmetric; i++)
        for (int j = 0; j < 3; j++)
            if (a[i][j] != a[j][i]) {
                symmetric = 0;
                break;
            }

    if (symmetric)
        printf("The matrix is symmetric.\n");
    else
        printf("The matrix is NOT symmetric.\n");
    return 0;
}

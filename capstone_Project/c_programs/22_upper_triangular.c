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

    printf("Upper triangular matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j >= i)
                printf("%4d", a[i][j]);
            else
                printf("%4d", 0);
        }
        printf("\n");
    }
    return 0;
}

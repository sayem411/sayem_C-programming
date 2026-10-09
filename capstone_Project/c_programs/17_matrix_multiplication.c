
#include <stdio.h>
 
int main() {
    int a[100][100],b[100][100],mul[100][100];
    int rows,cols;
 
    printf("Enter rows and columns: ");
    scanf("%d %d",&rows,&cols);
 
    printf("Enter First matrix elements:\n");
    for (int i=0;i<rows;i++) {
        for(int j=0;j<cols;j++) {
            scanf("%d",&a[i][j]);
        }
    }
 
       printf("Enter Second matrix elements:\n");
    for (int i=0;i<rows;i++) {
        for(int j=0;j<cols;j++) {
            scanf("%d",&b[i][j]);
        }
    }
     for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mul[i][j] = 0;
            for (int k = 0; k < cols; k++)
                mul[i][j] += a[i][k] * b[k][j];
        }
    }

    printf("A x B =\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%5d", mul[i][j]);
        printf("\n");
    }
 

    return 0;
}
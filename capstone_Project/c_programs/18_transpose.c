
#include <stdio.h>
 
int main() {
    int a[100][100],b[100][100],tr[100][100];
    int rows,cols;
 
    printf("Enter rows and columns: ");
    scanf("%d %d",&rows,&cols);
 
    printf("Enter matrix elements:\n");
    for (int i=0;i<rows;i++) {
        for(int j=0;j<cols;j++) {
            scanf("%d",&a[i][j]);
        }
    }
 
     for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tr[j][i] = a[i][j];
        }
    }

    printf("Transpose\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
        printf("%d ", tr[i][j]);
        printf("\n");
    }

    return 0;
}
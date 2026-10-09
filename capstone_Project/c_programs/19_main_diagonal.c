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

    printf("Main diagonal: ");
    for (int i = 0; i < 3; i++)
        printf("%d ", a[i][i]);
    printf("\n");
    return 0;
}

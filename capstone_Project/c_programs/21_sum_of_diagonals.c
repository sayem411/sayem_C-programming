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

    int mainSum = 0, secSum = 0;

    for (int i = 0; i < 3; i++) {
        mainSum += a[i][i];
        secSum += a[i][rows - 1 - i];
    }

    printf("Sum of main diagonal      = %d\n", mainSum);
    printf("Sum of secondary diagonal = %d\n", secSum);
    return 0;
}

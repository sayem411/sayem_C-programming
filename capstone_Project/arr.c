#include <stdio.h>

int main() {
    int row, col;
    
    printf("number of rows: ");
    scanf("%d", &row);

    printf("number of columns: ");
    scanf("%d", &col);

    int arr[row][col];

    printf("Enter  element:\n");

    for (int i = 0; i <row; i++) {
        for (int j = 0; j <col; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    //Update elements: Second row, Second column
    int u;
    printf("enter value: ");
    scanf("%d",&u);
   arr[2][2]=u;
    printf("array is:\n");
    

    for (int i = 0; i < row; i++) {
        for (int j = 0; j <col; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
  
    return 0;
}

#include <stdio.h>

int main() {
    int row, col;
    
    printf("Enter number of rows and columns: ");
    scanf("%d %d",&row,&col);
    int arr[row][col];

    printf("Enter array elements:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d",&arr[i][j]);
        }
    }

    printf("\nArray elements:\n");
    for (int j = 0; j < col; j++) {
     int max = arr[0][j];
    int min = arr[0][j];
        for (int i = 0; i < row; i++) {

            if (arr[i][j] > max)
                max = arr[i][j];

            if (arr[i][j] < min)
                min = arr[i][j];
        }
       printf("Column %d: max = %d, min = %d\n", j, max, min);
    }

    return 0;
}

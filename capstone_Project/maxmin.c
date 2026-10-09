#include <stdio.h>

int main() {
    int row, col,sum = 0;
    
    printf("Enter number of rows and columns: ");
    scanf("%d %d",&row,&col);
    int arr[row][col];

    printf("Enter array elements:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d",&arr[i][j]);
        }
    }
    int max = arr[0][0];
    int min = arr[0][0];

    printf("\nArray elements:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%4d", arr[i][j]);
            sum += arr[i][j];

            if (arr[i][j] > max)
                max = arr[i][j];

            if (arr[i][j] < min)
                min = arr[i][j];
        }
        printf("\n");
    }

    printf("\nSum   = %d\n", sum);
    printf("Maximum = %d\n", max);
    printf("Minimum = %d\n", min);

    return 0;
}
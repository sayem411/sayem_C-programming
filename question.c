#include <stdio.h>

int main() {
    int N;
    
    // Input the size of the matrix
    printf("Enter the size of the matrix (odd number): ");
    scanf("%d", &N);

    // Validate if N is an odd number
    if (N % 2 == 0) {
        printf("N must be an odd number.\n");
        return 0;
    }

    int matrix[N][N];
    
    // Input the elements of the matrix
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int mid = N / 2;
    int sum_row = 0;
    int sum_col = 0;

    // Calculate sum of the middle row and middle column
    for (int i = 0; i < N; i++) {
        sum_row += matrix[mid][i];
        sum_col += matrix[i][mid];
    }

    // Print the results matching the sample output
    printf("Summation of the row's elements: %d\n", sum_row);
    printf("Summation of the column's elements: %d\n", sum_col);
    
    // Total score calculation ensuring the middle element isn't counted twice
    int total_score = sum_row + sum_col - matrix[mid][mid];
    printf("Total score of central parts: %d\n", total_score);

    return 0;
}
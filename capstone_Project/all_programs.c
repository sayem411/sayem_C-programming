#include <stdio.h>

/* 01: Array display */
void array_display(void) {
    int n, a[100];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("Invalid size!\n");
        return;
    }

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Array elements:\n");
    for (int i = 0; i < n; i++)
        printf("%d\n", a[i]);
}

/* 02: Array traversal */
void array_traversal(void) {
    int n, a[100];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("Invalid size!\n");
        return;
    }

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Array elements:\n");
    for (int i = 0; i < n; i++) {
        printf("a[%d] = %d\n", i, a[i]);
    }
}

/* 03: Accessing elements */
void accessing_elements(void) {
    int n, a[100];
    while (1) {
        printf("Enter number of elements: ");
        scanf("%d", &n);

        if (n <= 0 || n > 100) {
            printf("Invalid size!please try again\n");
        } else {
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("Element at index %d = %d\n", i, a[i]);
    }
}

/* 04: Update elements */
void update_elements(void) {
    int a[100], n, index, value;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Array elements:\n");
    for (int i = 0; i < n; i++)
        printf("%d\n", a[i]);

    printf("Enter index and new value: ");
    scanf("%d %d", &index, &value);

    if (index < 0 || index >= n) {
        printf("Invalid index!\n");
        return;
    }
    a[index] = value;

    printf("Updated array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

/* 05: Sum of elements */
void sum_of_elements(void) {
    int a[100], n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    printf("Sum = %d\n", sum);
}

/* 06: Average */
void average(void) {
    int a[100], n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }

    printf("Sum = %d\n", sum);
    printf("Average = %.2f\n", (float)sum / n);
}

/* 07 & 08: Sum, max and min of a 2D array */
void max_min(void) {
    int row, col, sum = 0;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &row, &col);
    int arr[row][col];

    printf("Enter array elements:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    int max = arr[0][0];
    int min = arr[0][0];

    printf("\nArray elements:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", arr[i][j]);
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
}

/* 09: Searching */
void searching(void) {
    int a[100], n;
    int key, found = -1;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    printf("%d elements are: ", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    printf("\nEnter element to search: ");
    scanf("%d", &key);

    for (int i = 0; i < n; i++) {
        if (a[i] == key) {
            found = i;
            break;
        }
    }

    if (found != -1)
        printf("%d found at index %d\n", key, found);
    else
        printf("%d not found\n", key);
}

/* 10: Count elements */
void count_elements(void) {
    int a[100], n;
    int key, count = 0;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    printf("%d elements are: ", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    printf("\nTotal number of elements = %d\n", n);

    printf("Enter value to count its occurrences: ");
    scanf("%d", &key);

    for (int i = 0; i < n; i++)
        if (a[i] == key)
            count++;

    printf("%d appears %d time(s)\n", key, count);
}

/* 11: Sum of each row */
void sum_of_each_row(void) {
    int a[100][100], n;
    printf("Enter matrix dimention: ");
    scanf("%d", &n);

    printf("Enter %d X %d Matrix:\n ", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        int rowsum = 0;
        for (int j = 0; j < n; j++)
            rowsum += a[i][j];
        printf("Sum of row %d = %d\n", i, rowsum);
    }
}

/* 12: Sum of each column */
void sum_of_each_column(void) {
    int a[100][100], n;
    printf("Enter matrix dimention: ");
    scanf("%d", &n);

    printf("Enter %d X %d Matrix:\n ", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        int colsum = 0;
        for (int j = 0; j < n; j++)
            colsum += a[j][i];
        printf("Sum of column %d = %d\n", i, colsum);
    }
}

/* 13: Row-wise max and min */
void row_max_min(void) {
    int row, col;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &row, &col);
    int arr[row][col];

    printf("Enter array elements:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    printf("\nArray elements:\n");
    for (int i = 0; i < row; i++) {
        int max = arr[i][0];
        int min = arr[i][0];
        for (int j = 0; j < col; j++) {
            if (arr[i][j] > max)
                max = arr[i][j];

            if (arr[i][j] < min)
                min = arr[i][j];
        }
        printf("Row %d: max = %d, min = %d\n", i, max, min);
    }
}

/* 14: Column-wise max and min */
void column_max_min(void) {
    int row, col;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &row, &col);
    int arr[row][col];

    printf("Enter array elements:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &arr[i][j]);
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
}

/* 15: Matrix addition */
void matrix_addition(void) {
    int a[100][100], b[100][100], sum[100][100];
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter First matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("Enter Second matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum[i][j] = a[i][j] + b[i][j];
        }
    }
    printf("sum of matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", sum[i][j]);
        }
        printf("\n");
    }
}

/* 16: Matrix subtraction */
void matrix_subtraction(void) {
    int a[100][100], b[100][100], sub[100][100];
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter First matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("Enter Second matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sub[i][j] = a[i][j] - b[i][j];
        }
    }
    printf("Difference of matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", sub[i][j]);
        }
        printf("\n");
    }
}

/* 17: Matrix multiplication */
void matrix_multiplication(void) {
    int a[100][100], b[100][100], mul[100][100];
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter First matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("Enter Second matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &b[i][j]);
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
}

/* 18: Transpose */
void transpose(void) {
    int a[100][100], tr[100][100];
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tr[j][i] = a[i][j];
        }
    }

    printf("Transpose\n");
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++)
            printf("%d ", tr[i][j]);
        printf("\n");
    }
}

/* 19: Main diagonal */
void main_diagonal(void) {
    int a[100][100];
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("Main diagonal: ");
    for (int i = 0; i < rows; i++)
        printf("%d ", a[i][i]);
    printf("\n");
}

/* 20: Secondary diagonal */
void secondary_diagonal(void) {
    int a[100][100];
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("Secondary diagonal: ");
    for (int i = 0; i < rows; i++)
        printf("%d ", a[i][rows - 1 - i]);
    printf("\n");
}

/* 21: Sum of diagonals */
void sum_of_diagonals(void) {
    int a[100][100];
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int mainSum = 0, secSum = 0;

    for (int i = 0; i < rows; i++) {
        mainSum += a[i][i];
        secSum += a[i][rows - 1 - i];
    }

    printf("Sum of main diagonal      = %d\n", mainSum);
    printf("Sum of secondary diagonal = %d\n", secSum);
}

/* 22: Upper triangular */
void upper_triangular(void) {
    int a[100][100];
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("Upper triangular matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j >= i)
                printf("%d ", a[i][j]);
            else
                printf("%d ", 0);
        }
        printf("\n");
    }
}

/* 23: Lower triangular */
void lower_triangular(void) {
    int a[100][100];
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("Lower triangular matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j <= i)
                printf("%d ", a[i][j]);
            else
                printf("%d ", 0);
        }
        printf("\n");
    }
}

/* 24: Symmetric matrix */
void symmetric_matrix(void) {
    int a[100][100];
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    int symmetric = (rows == cols);

    for (int i = 0; i < rows && symmetric; i++)
        for (int j = 0; j < cols; j++)
            if (a[i][j] != a[j][i]) {
                symmetric = 0;
                break;
            }

    if (symmetric)
        printf("The matrix is symmetric.\n");
    else
        printf("The matrix is NOT symmetric.\n");
}

/* 25: Identity matrix */
void identity_matrix(void) {
    int a[100][100];
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    int identity = 1;
    if (rows != cols) {
        identity = 0;
    } else {
        for (int i = 0; i < rows && identity; i++) {
            for (int j = 0; j < cols; j++) {
                if (i == j && a[i][j] != 1) {
                    identity = 0;
                    break;
                }
                if (i != j && a[i][j] != 0) {
                    identity = 0;
                    break;
                }
            }
        }
    }

    if (identity)
        printf("The matrix is an identity matrix.\n");
    else
        printf("The matrix is NOT an identity matrix.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n===== Array & Matrix Programs =====\n");
        printf(" 1. Array display\n");
        printf(" 2. Array traversal\n");
        printf(" 3. Accessing elements\n");
        printf(" 4. Update elements\n");
        printf(" 5. Sum of elements\n");
        printf(" 6. Average\n");
        printf(" 7. Sum, max & min (2D array)\n");
        printf(" 8. Searching\n");
        printf(" 9. Count elements\n");
        printf("10. Sum of each row\n");
        printf("11. Sum of each column\n");
        printf("12. Row max & min\n");
        printf("13. Column max & min\n");
        printf("14. Matrix addition\n");
        printf("15. Matrix subtraction\n");
        printf("16. Matrix multiplication\n");
        printf("17. Transpose\n");
        printf("18. Main diagonal\n");
        printf("19. Secondary diagonal\n");
        printf("20. Sum of diagonals\n");
        printf("21. Upper triangular\n");
        printf("22. Lower triangular\n");
        printf("23. Symmetric matrix check\n");
        printf("24. Identity matrix check\n");
        printf(" 0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
            break;

        printf("\n");
        switch (choice) {
            case 1:  array_display();        break;
            case 2:  array_traversal();      break;
            case 3:  accessing_elements();   break;
            case 4:  update_elements();      break;
            case 5:  sum_of_elements();      break;
            case 6:  average();              break;
            case 7:  max_min();              break;
            case 8:  searching();            break;
            case 9:  count_elements();       break;
            case 10: sum_of_each_row();      break;
            case 11: sum_of_each_column();   break;
            case 12: row_max_min();          break;
            case 13: column_max_min();       break;
            case 14: matrix_addition();      break;
            case 15: matrix_subtraction();   break;
            case 16: matrix_multiplication();break;
            case 17: transpose();            break;
            case 18: main_diagonal();        break;
            case 19: secondary_diagonal();   break;
            case 20: sum_of_diagonals();     break;
            case 21: upper_triangular();     break;
            case 22: lower_triangular();     break;
            case 23: symmetric_matrix();     break;
            case 24: identity_matrix();      break;
            case 0:  printf("Goodbye!\n");   return 0;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

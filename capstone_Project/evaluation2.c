#include <stdio.h>
#include <math.h>

void addition(int *a, int *b, int *result){
    *result = *a + *b;
}

void subtraction(int *a, int *b, int *result){
    *result = *a - *b;
}

void multiplication(int *a, int *b, int *result){
    *result = *a * *b;
}

void division(int *a, int *b, float *result){
    if (*b != 0)
        *result = (float)*a / *b;
}

void square(int *a, int *result){
    *result = *a * *a;
}

void root(int *a, float *result){
    if (*a >= 0)
        *result = sqrt(*a);
}

int main(){
    int a, b, choice, result;
    float answer;

    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    printf("\n===== BASIC CALCULATOR =====\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Square\n");
    printf("6. Square Root\n");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            addition(&a, &b, &result);
            printf("Addition = %d\n", result);
            break;

        case 2:
            subtraction(&a, &b, &result);
            printf("Subtraction = %d\n", result);
            break;

        case 3:
            multiplication(&a, &b, &result);
            printf("Multiplication = %d\n", result);
            break;

        case 4:
            if (b != 0)
            {
                division(&a, &b, &answer);
                printf("Division = %.2f\n", answer);
            }
            else
            {
                printf("Syntax Error: Division by Zero!\n");
            }
            break;

        case 5:
            square(&a, &result);
            printf("Square = %d\n", result);
            break;

        case 6:
            if (a >= 0)
            {
                root(&a, &answer);
                printf("Square Root = %.2f\n", answer);
            }
            else
            {
                printf("Math Error: Invalid Square Root!\n");
            }
            break;

        default:
            printf("Syntax Error: Invalid Choice!\n");
    }

    return 0;
}
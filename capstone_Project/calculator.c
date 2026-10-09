#include <stdio.h>

void operation(float x,float y, int n){
    switch (n)
    {
    case 1:
    {
        float result = x + y;
        printf("Summation: %.2f\n", result);
        break;
    }
    case 2:
    {
        float result = x - y;
        printf("Subtraction: %.2f\n", result);
        break;
    }
    case 3:
    {
        float result = x * y;
        printf("Multiplication: %.2f\n", result);
        break;
    }
    case 4:
    {
        if (y == 0){
            printf("Math Error: Division by zero is not allowed.\n");
            break;
        }
        else
        {
            float result = x / y;
            printf("Division: %.2f\n", result);
            break;
        }
    }
    }
}

int main()
{
    float x, y;
    int n;

    while (1)
    {
        printf("\n--------- Operation ---------\n");
        printf("1. Summation\n2. Subtraction\n3. Multiplication\n4. Division\n5. Exit\n");
        printf("Enter your operation: ");
        scanf("%d", &n);

        if (n == 5){
            printf("Shutting down...\n");
            return 0;
        }

        while (n > 5 || n < 1){
            printf("Invalid operation, please enter a valid operation: ");
            scanf("%d", &n);
        }

        printf("Enter your first number: ");
        scanf("%f", &x);
        printf("Enter your second number: ");
        scanf("%f", &y);

        operation(x, y, n);
    }

    return 0;
}
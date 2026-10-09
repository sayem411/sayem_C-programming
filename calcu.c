#include <stdio.h>

void performCalculation(float num1, float num2, int choice)
{
    switch (choice)
    {
        case 1:
        {
            float result = num1 + num2;
            printf("Summation    : %.2f\n", result);
            break;
        }

        case 2:
        {
            float result = num1 - num2;
            printf("Subtraction    : %.2f\n", result);
            break;
        }

        case 3:
        {
            float result = num1 * num2;
            printf("Multiplication : %.2f\n", result);
            break;
        }

        case 4:
        {
            if (num2 == 0)
            {
                printf("Math Error     : Division by zero is not allowed.\n");
            }
            else
            {
                float result = num1 / num2;
                printf("Division       : %.2f\n", result);
            }
            break;
        }
    }
}


/* ================================
 *   Function: getValidChoice
 *   Purpose : Take menu input and
 *             validate the range
 * ================================
 */
int getValidChoice()
{
    int choice;

    printf("Enter your operation: ");
    scanf("%d", &choice);

    while (choice < 1 || choice > 5)
    {
        printf("Invalid operation, please enter a valid operation: ");
        scanf("%d", &choice);
    }

    return choice;
}


/* ================================
 *   Function: showMenu
 *   Purpose : Display the menu
 * ================================
 */
void showMenu()
{
    printf("\n--------- Operation ---------\n");
    printf("1. Summation\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Exit\n");
}


/* ================================
 *   Function: main
 * ================================
 */
int main()
{
    float num1, num2;
    int choice;

    while (1)
    {
        showMenu();
        choice = getValidChoice();

        if (choice == 5)
        {
            printf("Shutting down...\n");
            break;
        }

        printf("Enter your first number  : ");
        scanf("%f", &num1);

        printf("Enter your second number : ");
        scanf("%f", &num2);

        performCalculation(num1, num2, choice);
    }

    return 0;
}
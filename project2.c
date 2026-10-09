#include <stdio.h>

int main() {
    int starting_balance, monthly_savings, months;

    // Taking inputs
    printf("Enter starting balance: ");
    scanf("%d", &starting_balance);
    printf("Enter monthly savings amount: ");
    scanf("%d", &monthly_savings);
    printf("Enter the number of months: ");
    scanf("%d", &months);
    
    printf("\n"); // Formatting line break

    // Loop to calculate and display savings for each month
    for (int i = 1; i <= months; i++) {
        starting_balance += monthly_savings;
        printf("Month %d: Total Savings = %d\n", i, starting_balance);
    }

    return 0;
}
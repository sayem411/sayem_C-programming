#include <stdio.h>
// Function to calculate the square of a number
int calculateSquare(int num) {
return num * num;
}
int main() {
// Declare variables
int number1, number2, result;
// Prompt user for input
printf("Enter the first number: ");
scanf("%d", &number1);
// Call the function to calculate the square
result = calculateSquare(number1);
// Display the result
printf("Square of %d is: %d\n", number1,result);
return 0;
} 
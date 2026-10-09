#include <stdio.h>

void add(int a, int b) { 
    printf("Addition:%d\n",a + b);
 }
void subtract(int a, int b) { 
    printf("Subtraction:%d\n",a - b);
 }
void multiply(int a, int b) { 
    printf("Multiplication: %d\n", a * b); 
}
void divide(int a,int b) {
    if (b == 0) {
        printf("Error: Division by zero!\n");
    }
    printf("Division: %.2f\n", (float)a / b);
}

int main() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    add(a, b);
    subtract(a, b);
    multiply(a, b);
    divide(a, b);

    return 0;
}
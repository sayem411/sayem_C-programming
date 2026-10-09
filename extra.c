#include <stdio.h>
int main() {
    int x = 5;
    float y = 3.14; // Added semicolon here
    y = x * y;
    printf("Multiplication: %.2f\n", y);
    return 0;
}
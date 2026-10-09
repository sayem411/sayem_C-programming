#include <stdio.h>

struct distance {
    int feet, inches;
};
int main() {
    struct distance d1, d2, result;
    printf("Enter Distance 1 (feet inches): ");
     scanf("%d %d", &d1.feet, &d1.inches);

    printf("Enter Distance 2 (feet inches): ");
     scanf("%d %d", &d2.feet, &d2.inches);

    result.inches = d1.inches + d2.inches;
    result.feet   = d1.feet + d2.feet + result.inches / 12;
    result.inches = result.inches % 12;

    printf("Total Distance: %d feet %d inches\n", result.feet, result.inches);

    return 0;
}
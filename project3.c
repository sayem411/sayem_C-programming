#include <stdio.h>
#define PI 3.14159

int main() {
    int choice;
    float radius, side, length, width, area;

    printf("1 = Circle, 2 = Square, 3 = Rectangle\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("Enter Radius: ");
            scanf("%f", &radius);
            area = PI * radius * radius;
            printf("Area of Circle: %.3f\n", area);
            break;
        case 2:
            printf("Enter One Side: ");
            scanf("%f", &side);
            area = side * side;
            printf("Area of Square: %.0f\n", area);
            break;
        case 3:
            printf("Enter Length: ");
            scanf("%f", &length);
            printf("Enter Width: ");
            scanf("%f", &width);
            area = length * width;
            printf("Area of Rectangle: %.0f\n", area);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
#include <stdio.h>

int main() {
    int n, a[100];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("Invalid size!\n");
        return 0;
    }

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Array elements:\n");
    for (int i = 0; i < n; i++)
        printf("%d\n", a[i]);

    return 0;
}
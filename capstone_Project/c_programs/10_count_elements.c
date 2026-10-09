#include <stdio.h>

int main() {
    int a[] = {5, 8, 5, 12, 5, 9};
    int n = sizeof(a) / sizeof(a[0]);
    int key, count = 0;

    printf("Total number of elements = %d\n", n);

    printf("Enter value to count its occurrences: ");
    scanf("%d", &key);

    for (int i = 0; i < n; i++)
        if (a[i] == key)
            count++;

    printf("%d appears %d time(s)\n", key, count);
    return 0;
}

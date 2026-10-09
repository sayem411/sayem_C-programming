#include <stdio.h>

int main() {
   int a[100],n,index,value;

     printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Array elements:\n");
    for (int i = 0; i < n; i++)
        printf("%d\n", a[i]);


    printf("Enter index and new value: ");
    scanf("%d %d", &index, &value);

    if (index < 0 || index >= n) {
        printf("Invalid index!\n");
        return 0;
    }
    a[index] = value;

    printf("Updated array: ");
    for (int i = 0; i < n; i++)
    printf("%d ", a[i]);
    printf("\n");
    return 0;
}

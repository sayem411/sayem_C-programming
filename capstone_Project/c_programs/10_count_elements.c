#include <stdio.h>

int main() {
         int a[100],n;
         int key, found = -1, count = 0;
     printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++){
         scanf("%d", &a[i]);
    }

      printf("%d elements are: ", n);
    for (int i = 0; i < n; i++){
         printf("%d ",a[i]);
    }
   
    printf("\nTotal number of elements = %d\n", n);

    printf("Enter value to count its occurrences: ");
    scanf("%d", &key);

    for (int i = 0; i < n; i++)
        if (a[i] == key)
            count++;

    printf("%d appears %d time(s)\n", key, count);
    return 0;
}

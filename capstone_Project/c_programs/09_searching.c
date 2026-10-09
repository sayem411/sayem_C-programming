#include <stdio.h>

int main() {
        int a[100],n;
         int key, found = -1;
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

    printf("\nEnter element to search: ");
    scanf("%d", &key);

    for (int i = 0; i < n; i++) {
        if (a[i] == key) {
            found = i;
            break;
        }
    }

    if (found != -1)
        printf("%d found at index %d\n", key, found);
    else
        printf("%d not found\n", key);
    return 0;
}

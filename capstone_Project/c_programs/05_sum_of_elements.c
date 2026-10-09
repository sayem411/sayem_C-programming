#include <stdio.h>

int main() {
      int a[100],n;
     printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++){
         scanf("%d", &a[i]);
    }
    
    int sum = 0;
    for (int i = 0; i < n; i++)
    sum += a[i];
    printf("Sum = %d\n", sum);
    return 0;
}

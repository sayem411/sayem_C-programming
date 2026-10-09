#include <stdio.h>
void sumArray(int arr[], int n);
int main() {
    int arr[100], n, i;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
   sumArray(arr, n);
    return 0;
}
void sumArray(int arr[], int n) {
    int sum = 0, i;
    for (i = 0; i < n; i++) {
        sum += arr[i];
    }
    printf("Sum = %d\n", sum);
}
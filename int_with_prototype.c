#include <stdio.h>
int sumArray(int arr[], int n);
int main() {
    int arr[100], n, i;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Sum = %d\n", sumArray(arr, n));
    return 0;
}
int sumArray(int arr[], int n) {
    int sum = 0, i;
    for (i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}
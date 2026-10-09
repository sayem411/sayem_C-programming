#include <stdio.h>
void maxmin(int arr[], int n);
int main() {
    int arr[100], n, i;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
   maxmin(arr, n);
    return 0;
}
void maxmin(int arr[], int n) {
    int max= arr[0],min=arr[0], i;
    for (i = 0; i < n; i++) {
     if(arr[i]>max){
        max=arr[i];
     }else if(arr[i]<min){
        min=arr[i];
     }
    }
    printf("Max = %d\n", max);
     printf("Min = %d\n", min);
}
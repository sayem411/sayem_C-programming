#include<stdio.h>
int main(){
    int n;
    int arr[100];
    int evensum =0;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    for(int i =0;i<n;i++){
        if(arr[i]%2==0){
          evensum+=arr[i];
        }
    }
    printf("Sum of even =%d\n",evensum);
    return 0;
}
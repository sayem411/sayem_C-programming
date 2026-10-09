#include <stdio.h>
int main() {
    int n;
    int arr[100];
    int freq[256]={0};
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    for(int i=0;i<n;i++){
       freq[arr[i]]++;
    }
    for(int i=0;i<256;i++){
        if(freq[i]!=0){
        printf("%d=%d\n",i,freq[i]);
        }
    }
    printf("\n");
    return 0;
}
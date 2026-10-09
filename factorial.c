#include<stdio.h>
void factorial(int n);
int main(){
    int n;
    scanf("%d",&n);
factorial(n);
    return 0;
}
void factorial(int n){
    int fact=1;
    for(int i=1;i<=n;i++){
        fact*=i;
    }
printf("%d",fact);
}
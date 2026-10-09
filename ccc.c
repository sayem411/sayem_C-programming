#include<stdio.h>
int main(){
    int a,b;
    printf("Enter two number :");
    scanf("%d%d",&a,&b);
    if(a>b){
    printf("%d is greater\n",a);
    }
    else if (b>a){
        printf("%d is greater \n",b);
    }
        else {
            printf("Both are equal\n");
           }
           return 0;
        }
#include<stdio.h>
int main(){
    int i;
    scanf("%d",&i);
    do{
        printf("Value:%d\n",i);
        i++;
    }while(i<20);
    return 0;
}
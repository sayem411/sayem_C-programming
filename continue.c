#include<stdio.h>
int main(){
    int i;
    for(i=0;i<6;i++){
    if(i==3){
        continue;
    }
    printf("Value: %d\n",i);
    }
    return 0;
}
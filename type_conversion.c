#include<stdio.h>
int main(){
    float a;
    scanf("%f",&a);
    if(a-(int)a>0.000){
        printf("int-%d float%.3f\n",(int)a,a-(int)a);
    }else{
        printf("int %d\n",(int)a);
        }
    return 0;
}
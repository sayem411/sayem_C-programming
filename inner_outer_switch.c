#include<stdio.h>
int main(){
    int a;
    int b;
    scanf("%d%d",&a,&b);
    switch(a){
        case 100:
        printf("Outer\n");
        switch(b){
            case 200:
            printf("Inner\n");
           
        }
         default:
            printf("Invalid");
    }
   
    return 0;
}
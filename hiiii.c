#include<stdio.h>
int main(){
    int a=10,b=5,c,d;
    c=a++;
    d=--b;
    b=--c;
    c=++b;
    b=d--;
    printf("%d\n%d\n%d\n%d\n",a,b,c,d);
    return 0;
}
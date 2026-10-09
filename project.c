#include<stdio.h>
int main(){
    int f,m,b,p_a,paym,dis,total;
    printf("Enter Money from father: ");
    scanf("%d",&f);

    printf("Enter Money from mother: ");
    scanf("%d",&m);

    printf("Enter Money from brother: ");
    scanf("%d",&b);

    printf("Enter purchase amount: ");
    scanf("%d",&p_a);

    printf("Enter payment method(1 for mobile banking,0 for cash: )");
    scanf("%d",&paym);

    total = f+m+b;
    printf("Total money Available of able = %d\n",total);

   
if(paym==1){
     dis =p_a-p_a*0.15;
    printf("Final purchase amount after 15 persent discount: %d\n",dis);
}

printf("Remaining money: %d\n",total-dis);

    return 0;
}
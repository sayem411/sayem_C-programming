//Variable definition vs declaration #1
#include <stdio.h>
int main(){
int var;
printf("Enter the value of var: ");
scanf("%d",&var);
printf("var + 5 = %d\n",var + 5);
printf("var - 5 = %d\n",var - 5);
printf("var * 5 = %d\n",var * 5);
printf("var / 5 = %d\n",var / 5);
printf("var = %d\n",var);
return 0;
}
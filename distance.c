//Type Conversion in c #16

#include <stdio.h>
int main(void){
char ch ='T';
int r = (int)ch+100;
printf("%c %d %x\n",ch,ch,ch);
printf("result: %d\n",r);
float f=r;
printf("Float: %f\n",f);
float a=4.5f;
float b=5.3;
float c=6.2;
int result=a+b+c;
printf("Total(No convention):%d\n",result);

int result2=(int)a+(int)b+(int)c;
printf("Total:%d\n",result2);
return 0;
}
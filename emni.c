#include<stdio.h>
#include<string.h>
int main(){

char str1[]="Ritu";
char str2[]="Shaha";
char str3[20];
int length,compare;

length=strlen(str1);
printf("The length of string 1: %d\n",length);

strcpy(str3,str1);
printf("After copying, string 3: %s\n",str3);

compare=strcmp(str1,str2);
printf("Comparing string 1 and string 2: %d\n",compare);

compare=strcmp(str1,str3);
printf("Comparing string 1 and string 3: %d\n",compare);

strcat(str3,str1);
printf("After concatenating string 1 and string 2: %s\n",str1);
return 0;
}
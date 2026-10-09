#include<stdio.h>
int main(){
char grade;
scanf("%c",&grade);
switch(grade){
    case 'A':
        printf("Excellent\n");
    break;

    case 'B':
    printf("Best\n");
    break;

    case 'C':
    printf("Bettar\n");
    break;

    case 'D':
    printf("Good\n");
    break;

    case 'E':
    printf("Satisfied\n");
    break;

    case 'F':
    printf("Fail\n");
    break;

   default:
    printf("Invalid\n");
}
printf("Your grade is %c\n",grade);

return 0;
}
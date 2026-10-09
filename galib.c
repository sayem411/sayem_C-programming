#include<stdio.h>
struct employee{
char name[100];
int id;
int basic;
float HRA,MA,total;
};
int main(){
int n,i;
printf("Enter number of Employee:\n");
scanf("%d",&n);
struct employee e[n];
for(i=0;i<n;i++){
    printf("----employee %d----\n",i+1);
    printf("Name:");
    scanf("%s",e[i].name);
     printf("ID:");
    scanf("%d",&e[i].id);
     printf("Basic salary:");
    scanf("%d",&e[i].basic);
e[i].HRA=e[i].basic*0.2;
e[i].MA=e[i].basic*0.1;
e[i].total=e[i].basic+e[i].HRA+e[i].MA;
}
for(i=0;i<n;i++){
    printf("Name                 : %s\n",e[i].name);
    printf("ID                   : %d\n",e[i].id);
    printf("Basic Salary         : %d\n",e[i].basic);
    printf("House Rent Allowance : %.2f\n",e[i].HRA);
    printf("Medical Allowance    : %.2f\n",e[i].MA);
    printf("Total Salary         : %.2f\n",e[i].total);
}

    return 0;
}
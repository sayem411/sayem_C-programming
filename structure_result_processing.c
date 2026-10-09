#include<stdio.h>
struct student{
char name[50];//char name[]="Sayem";
int ID;
float physics,chemistry,mathematics;
float total,average;
};
int main(){ 
int n;
printf("Enter number of student: ");
scanf("%d",&n);
struct student s[n];
for(int i=0;i<n;i++){
    printf("Name:");
    scanf("%s",s[i].name);
     printf("ID:");
    scanf("%d",&s[i].ID);
    printf("physics chemistry mathematics: ");
    scanf("%f%f%f",&s[i].physics,&s[i].chemistry,&s[i].mathematics);
    s[i].total=s[i].physics+s[i].chemistry+s[i].mathematics;
    s[i].average=s[i].total/3;
}
printf("Name\tID\ttotal\taverage\n");
printf("---\t---\t---\t----\n");

for(int i=0;i<n;i++){
printf("%s\t%d\t%.2f\t%.2f\n",s[i].name,s[i].ID,s[i].total,s[i].average);
}
return 0;
}
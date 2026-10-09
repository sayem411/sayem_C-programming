#include<stdio.h>
struct student{
char name[50];
int roll;
float math,science,english,total;
};
int main(){
    struct student s;
    printf("Enter student name:");
    scanf("%s",s.name);
    printf("Enter roll number:");
    scanf("%d",&s.roll);

    printf("Enter marks in Math:");
    scanf("%f",&s.math);
    printf("Enter marks in Science:");
    scanf("%f",&s.science);
    printf("Enter marks in English:");
    scanf("%f",&s.english);
    s.total=s.math+s.science+s.english;
    printf("Student Information:\n");
    printf("Name:%s\n",s.name);
    printf("Roll Number:%d\n",s.roll);
    printf("Marks in Math:%.2f\n",s.math);
   printf("Marks in Science:%.2f\n",s.science);
   printf("Marks in English:%.2f\n",s.english);
    printf("Total Marks:%.2f\n",s.total);

    return 0;
}
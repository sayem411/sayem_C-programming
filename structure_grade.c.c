#include<stdio.h>
struct student{
char name[50];
int ID;
float physics,mathematics,chemistry;
};

int main(){
  struct student s;
  char grade;

  printf("Name: ");
  scanf("%s",s.name);

   printf("ID: ");
  scanf("%d",&s.ID);

   printf("Physics Mathematics Chemistry marks:");
  scanf("%f%f%f",&s.physics,&s.mathematics,&s.chemistry);

  float total=s.physics+s.mathematics+s.chemistry;
  float average=total/3;
  if(average>=80 && average<=100)
  grade='A';
  else if(average>=70 && average<80)
    grade='B';
     else if(average>=60 && average<70)
    grade='C';
     else if(average>=50 && average<60)
    grade='D';
     else 
      grade='F';

      printf("Name          : %s\n",s.name);
      printf("ID            : %d\n",s.ID);
      printf("Total Marks   : %.2f\n",total);
      printf("Average Marks : %.2f\n",average);
      printf("Grade         : %c\n",grade);

  return 0;
}
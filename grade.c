#include<stdio.h>
int main(){
    int physics,chemistry,math,total,average;
    scanf("%d%d%d",&physics,&chemistry,&math);
    total=physics+chemistry+math;
    average=total/3;

      printf("Total:%d\n",total);
    printf("Average:%d\n",average);

    if(average>=80&&average<=100){
        printf("The grade is:A+");
    }else if(average>=70&&average<=79){
        printf("The grade is:A");
    }else if(average>=60&&average<=69){
        printf("The grade is:A-");
    }else if(average>=50&&average<=59){
        printf("The grade is:B");
    }else if(average>=40&&average<=49){
        printf("The grade is:C");
    }else if(average>=33&&average<=39){
        printf("The grade is:D");
    }else {
        printf("The grade is:F");   
    }
  
    return 0;
}
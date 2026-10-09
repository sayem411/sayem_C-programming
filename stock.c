#include<stdio.h>
int main(){
    int num,count=0,total=0;
    printf("Enter number of products:");
    scanf("%d",&num);
    int s[100];
      printf("Enter stock for %d products:\n",num);
    for(int i =0;i<num;i++){
        scanf("%d",&s[i]);
    }
    printf("Products needing restock (stock < 10):\n");
    for(int i =0;i<num;i++){
        total+=s[i];
        if(s[i]<10){
        printf("%d",s[i]);
        count++;
        }
    }
    printf("\n");
    printf("Total number of products needing restock = %d\n",count);
   printf("Total stock =%d\n",total);

    return 0;
}
#include<stdio.h>
int main(){
   int row,col,sum=0,a[100][100],key,foundrow=-1,foundcol=-1;
   printf("Enter number of rows and columns:");
   scanf("%d %d",&row,&col);

   if (row <= 0 || col <= 0 || row > 100 || col > 100) {
    printf("Invalid size.\n");
    return 1;
}

   printf("\nEnter matrix elements:\n");
   for(int i =0;i<row;i++){
    for(int j=0;j<col;j++){
        scanf("%d",&a[i][j]);
    }
   }
int max=a[0][0];
int min =a[0][0];

   printf("Matrix Element are:\n");
   for(int i =0;i<row;i++){
    for(int j=0;j<col;j++){
        printf("%d ",a[i][j]);
      
        sum+=a[i][j];

        if(max<a[i][j]){
            max=a[i][j];
        }
         if(min>a[i][j]){
            min=a[i][j];
        }
    }
      printf("\n");
   }

   printf("Enter searching element:");
   scanf("%d",&key);

   for(int i=0;i<row && foundrow==-1;i++){
    for(int j=0;j<col;j++){
        if(a[i][j]==key){
            foundrow=i;
            foundcol=j;
            break;
        }
    }
   }
   if(foundrow!=-1){
    printf("%d element found at index [%d][%d]",key,foundrow,foundcol);
   }else{
    printf(" %d Element not found",key);
   }

   printf("\nSum = %d\n",sum);
   printf("Max = %d\n",max);
   printf("Min = %d\n",min);
}
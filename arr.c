#include<stdio.h>
int main(){
 int matrix1[2][2]={{1,2},{3,4}};
 int matrix2[2][2]={{5,6},{7,8}};
int add[2][2],sub[2][2],mult[2][2];
int i,j;
for(i=0;i<2;i++){
    for(j=0;j<2;j++){
        add[i][j]=matrix1[i][j]+matrix2[i][j];
        sub[i][j]=matrix1[i][j]-matrix2[i][j];
    }
}
for(i=0;i<2;i++){
    for(j=0;j<2;j++){
        mult[i][j]=0;
        for(int k=0;k<2;k++){
            mult[i][j]+=matrix1[i][k]*matrix2[k][j];
        }
    }
    }
    printf("Addition:\n");
   for(i=0;i<2;i++){
    for(j=0;j<2;j++){
        printf("%d\t",add[i][j]);
    }
    printf("\n");
    } 
    printf("Substraction:\n");
     for(i=0;i<2;i++){
    for(j=0;j<2;j++){
        printf("%d\t",sub[i][j]);
    }
    printf("\n");
    } 
    printf("Multiplication:\n");
     for(i=0;i<2;i++){
    for(j=0;j<2;j++){
        printf("%d\t",mult[i][j]);
    }
    printf("\n");
    } 

return 0;
}






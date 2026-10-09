#include <stdio.h>
int main()
{
int m,n,i,j;

printf("Enter the number of rows and column of the matrics:\n");
scanf("%d%d",&m,&n);
//Declare the matrics
int matrix1[m][n],matrix2[m][n],result[m][n];
//Get the elements of the matrics from the user
printf("Enter the elements of first matrics:\n");
for(i=0;i<m;i++){
for(j=0;j<n;j++){
scanf("%d",&matrix1[i][j]);

}
}
printf("Enter the elements of second matrics:\n");
for(i=0;i<m;i++){
for(j=0;j<n;j++){
scanf("%d",&matrix2[i][j]);

}
}
//Calculate the sum
for(i=0;i<m;i++){
for(j=0;j<n;j++){
result[i][j] = matrix1[i][j]+matrix2[i][j];

}
}
//print the result
printf("The sum of the matrics:\n");
for(i=0;i<m;i++){
for(j=0;j<n;j++){
printf("%d\t",result[i][j]);

}
printf("\n");
}

return 0;
}
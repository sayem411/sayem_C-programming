#include <stdio.h>
int main(void){
int i,j,rows=5;
int stars,spaces;
stars =1;
spaces = rows-1;
for(i =1;i<rows;i++){
for(j=1;j<=spaces;j++){
printf(" ");
}
for(j=1;j<stars;j++){
printf("* ");
}
printf("\n");
if(i<rows){
spaces--;
stars++;
}else{
spaces++;
stars--;
}
}
return 0;
}
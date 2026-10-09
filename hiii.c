//Max,min using array
#include <stdio.h>
int main() {
    int i,j,m,n;
    scanf("%d%d",&m,&n);
    int a[m][n];

for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }    
int max=a[0][0],min=a[0][0];
for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(a[i][j]>max){
                max=a[i][j];
            }else if(a[i][j]<min){
                min=a[i][j];
            }
          
        }
   
    }
printf("maximum=%d\n",max);
printf("minimum=%d\n",min);
          
    return 0;
}
#include<stdio.h>
int main(){
    int n;
    printf("Enter matrix:\n");
    scanf("%d",&n);

    int i,j,a[n+5][n+5];
    printf("Enter the element:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(i=1;i<=n;i++){
        int rs=0,cs=0;
        for(j=0;j<n;j++){
            rs+=a[i][j];
            cs+=a[j][i];
        }
      
            printf("rs =%d\n",rs);
              printf("cs =%d\n",cs);
        
    }
    return 0;
}
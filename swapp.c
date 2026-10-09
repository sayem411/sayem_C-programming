#include <stdio.h>

int main() {
    int n,x,y;
    int a[1000][1000];
    scanf("%d",&n);
    scanf("%d%d",&x,&y);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    x--,y--;
     for(int i=0;i<n;i++){
   
           int temp=a[x][i];
           a[x][i]=a[y][i];
           a[y][i]=temp;
        }
    
    for(int i=0;i<n;i++){
           int temp=a[i][x];
           a[i][x]=a[i][y];
           a[i][y]=temp;
        }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}
#include<stdio.h>
int main(){
    int nums[5];
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&nums[i]);
    }
    int target;
    scanf("%d",&target);

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){   
            if(target == nums[i] + nums[j]){
                printf("%d %d\n",i,j);
            }
        }
    }
    return 0;
}
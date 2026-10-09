#include<stdio.h>
int a(int arr[],int n,int key){
    int position=-1;
    int i;

    for(i=0;i<n;i++)
    {
        if(key==arr[i])
        {
            position=i;
        }
    }
    
    if(position == -1)
    {
        printf("Sorry not found");
    }
    
    else
    {
        printf("Position = %d",position);
    }
    
    return position;
}

int main()
{
    int n;
    scanf("%d",&n);
    int arr[n],i;
    for(i=1;i<=n;i++)
    {
        scanf("%d",&arr[i]);
    }
    
    int key;
    scanf("%d",&key);
    
    a(arr,n,key);
    return 0;
}



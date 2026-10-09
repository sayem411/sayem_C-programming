#include <stdio.h>

int main() {
     int n, a[100];
while(1){
      printf("Enter number of elements: ");
    scanf("%d", &n);

     if (n <= 0 || n > 100) {
        printf("Invalid size!please try again\n");
    }else{
        break;
    }
}
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }

    for(int i=0;i<n;i++){
        printf("Element at index %d = %d\n",i, a[i]);
    }
    return 0;
}

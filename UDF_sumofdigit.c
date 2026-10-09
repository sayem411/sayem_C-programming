#include <stdio.h>
int sumofdigit(int n){
    int sum=0;
 for(int i=n;i>0;i/=10){
    sum+=i%10;
   }
   return sum;
}
int main() {
   int n;
   scanf("%d",&n);
  printf("%d\n",sumofdigit(n));
    return 0;
}

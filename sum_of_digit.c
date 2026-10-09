#include <stdio.h>
void summation(int n){
    int sum=0;
  for (int i = n; i > 0; i /=10) {//12345
        sum +=i % 10; //sum=0+5+4+3+2+1=15
    }
    printf(" Sum of digit %d\n",sum);
}
int main() {
    int n;
    scanf("%d", &n);
  summation(n);

    return 0;
}

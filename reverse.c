#include <stdio.h>

int main() {
    int n, reverse = 0, i;

    scanf("%d", &n);

    for (i = n; i > 0; i /=10) {
        reverse = reverse*10 +(i % 10); 
    }
   
    printf(" %d\n", reverse);

     if (n == reverse)
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}

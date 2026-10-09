#include <stdio.h>

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    int fib[100];
    fib[0] = 0;
    fib[1] = 1;

    if (n == 0) {
        printf("%dth Fibonacci number: 0\n", n);
        return 0;
    }

    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    printf("%dth Fibonacci number: %d\n", n, fib[n]);
    return 0;
}
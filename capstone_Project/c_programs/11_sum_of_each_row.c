#include <stdio.h>

int main() {
    int a[100][100],n;
    printf("Enter matrix dimention: ");
    scanf("%d", &n);

    printf("Enter %d X %d Matrix:\n ",n,n);
    for (int i = 0; i < n; i++){
        for(int j=0;j<n;j++){
              scanf("%d", &a[i][j]);
        }
       
    }
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++)
            sum += a[i][j];
        printf("Sum of row %d = %d\n", i, sum);
    }
    return 0;
}

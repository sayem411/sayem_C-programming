#include <stdio.h>
void Payment(int w, int b) {
    if (b < 200 && w>=b) {
        printf("Minimum order amount is 200 Tk.\n");
        printf("Remaining Wallet Balance = %d\n",w);
    } else if (w< b) {
        printf("Insufficient Balance.\n");
        printf("Remaining Wallet Balance = %d\n", w);
    } else {
        w -= b;
        printf("Payment Successful.\n");
        printf("Remaining Wallet Balance = %d\n", w);
    }
}
int main() {
    int wallet, bill;
    
    printf("Enter wallet balance: ");
    scanf("%d", &wallet);

    printf("Enter bill amount: ");
    scanf("%d", &bill);

    Payment(wallet, bill);

    return 0;
}
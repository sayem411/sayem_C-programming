#include<stdio.h>
int main(){
    float wallet, bill;

    printf("Enter wallet balance: ");
    scanf("%f", &wallet);

    printf("Enter bill amount: ");
    scanf("%f", &bill);

     if(bill < 200){
        printf("Minimum order amount is 200 Tk.\n");
        printf("Remaining Wallet Balance = %.0f\n", wallet);
    }
    else if(wallet < bill){
        printf("Insufficient Balance.\n");
        printf("Remaining Wallet Balance = %.0f\n", wallet);
    }
    else{
        wallet -= bill;
        printf("Payment Successful.\n");
        printf("Remaining Wallet Balance = %.0f\n", wallet);

    return 0;
}
#include<stdio.h>

struct Account{
    int accNo;
    char holder[31];   
    float balance;
};

void deposit(struct Account *a, float amount){
    a->balance = a->balance + amount;
}

int withdraw(struct Account *a, float amount){
    if(a->balance >= amount){      
        a->balance = a->balance - amount;
        return 1;                
    }
    return 0;         
}

void wrongDeposit(struct Account a, float amount){
    a.balance = a.balance + amount; // shudhu copy-te change hobe
}

int main(){
    struct Account acc = {101, "Sayem", 1000};

    printf("Initial = %.2f\n", acc.balance);

    wrongDeposit(acc, 500);
    printf("After wrongDeposit(500): %.2f\n", acc.balance);

    deposit(&acc, 500);
    printf("After deposit(500): %.2f\n", acc.balance);

    int result = withdraw(&acc, 2000);
    printf("withdraw(2000) returned: %d\n", result);
    printf("Balance after withdraw: %.2f\n", acc.balance);

    return 0;
}
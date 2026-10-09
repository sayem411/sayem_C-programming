#include <stdio.h>
void sendMoney();
void cashOut();
void recharge();

void loan(); 
int main() {
    int choice;
    while(1){
    printf("    Carrier info    \n");
    printf("bKash\n");
    printf("1.Send Money\n");
    printf("2.Send Money to Non-Bkash User\n");
    printf("3.mobile Recharge\n");
    printf("4.Payment\n");
    printf("5.Cash Out\n");
    printf("6.Pay Bill\n");
    printf("7.Microfinance\n");
    printf("8.Download bKash App\n");
    printf("9.My bKash\n");
    printf("10.Reset PIN\n");

    printf("Enter your choice:");
    scanf("%d",&choice);
    if(choice<1 || 7<choice){
        printf("Invalid! please try again\n");
        continue;
    }
    break;

    }
 
     switch(choice){
         case 1:
         printf("Enter your number for send money:\n");
         break;
         case 2:
         printf("Enter your number for Cash out:\n");
         break;
         case 3:
         printf("Enter your number for mobile recharge:\n");
         break;
         case 4:
         printf("Enter your number for payment:\n");
         break;
         case 5:
         printf("Enter your number for bank to bkash:\n");
         break;
         case 6:
         printf("Enter your number for donate:\n");
         break;
         case 7:
         printf("View my bkash for balance equepty:\n");
         break;
     }
 
 
 
    return 0;
}
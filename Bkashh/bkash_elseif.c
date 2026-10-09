#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===== bKash USSD Menu Simulator =====
   Dial: *247#
   ====================================== */

#define MAX_PIN_LEN     5
#define MAX_PHONE_LEN   12
#define MAX_AMOUNT_LEN  10
#define BALANCE         1500.00   /* Demo balance */

/* --- Utility --- */
void clear_screen() {
    printf("\033[2J\033[H");
}

void print_header() {
    printf("=============================\n");
    printf("        bKash *247#          \n");
    printf("=============================\n");
}

void get_input(const char *prompt, char *buf, int maxlen) {
    printf("%s: ", prompt);
    fgets(buf, maxlen, stdin);
    /* strip newline */
    buf[strcspn(buf, "\n")] = '\0';
}

/* --- PIN validation (demo: PIN = 1234) --- */
int verify_pin() {
    char pin[MAX_PIN_LEN + 2];
    get_input("PIN Number", pin, sizeof(pin));
    if (strcmp(pin, "1234") == 0) {
        return 1;
    }
    printf("\n❌ Voul PIN! Aborting.\n");
    return 0;
}

/* --- Menu handlers --- */

void send_money() {
    char phone[MAX_PHONE_LEN];
    char amount_str[MAX_AMOUNT_LEN];
    double amount;

    clear_screen();
    print_header();
    printf("Send Money\n");
    printf("-----------------------------\n");

    get_input("Receiver Number (01XXXXXXXXX)", phone, sizeof(phone));

    if (strlen(phone) != 11 || phone[0] != '0' || phone[1] != '1') {
        printf("\n❌ Invalid number format!\n");
        return;
    }

    get_input("Amount (Taka)", amount_str, sizeof(amount_str));
    amount = atof(amount_str);

    if (amount <= 0 || amount > BALANCE) {
        printf("\n❌ Invalid amount or insufficient balance!\n");
        return;
    }

    printf("\n--- Confirm ---\n");
    printf("To  : %s\n", phone);
    printf("Amt : %.2f Tk\n", amount);
    printf("Charge: 5.00 Tk\n");

    if (!verify_pin()) return;

    printf("\n✅ Send Successful!\n");
    printf("Transaction ID: TXN%08d\n", rand() % 99999999);
    printf("Remaining Bal : %.2f Tk\n", BALANCE - amount - 5.0);
}

void mobile_recharge() {
    char phone[MAX_PHONE_LEN];
    char amount_str[MAX_AMOUNT_LEN];
    double amount;

    clear_screen();
    print_header();
    printf("Mobile Recharge\n");
    printf("-----------------------------\n");
    printf("1. Nij Number\n");
    printf("2. Onyo Number\n");
    printf("0. Back\n");
    printf("-----------------------------\n");

    char choice[4];
    get_input("Option", choice, sizeof(choice));

    if (strcmp(choice, "1") == 0) {
        strcpy(phone, "01XXXXXXXXX");
    } else if (strcmp(choice, "2") == 0) {
        get_input("Receiver Number (01XXXXXXXXX)", phone, sizeof(phone));
    } else {
        return;
    }

    get_input("Recharge Amount", amount_str, sizeof(amount_str));
    amount = atof(amount_str);

    if (amount <= 0 || amount > BALANCE) {
        printf("\n❌ Invalid amount or insufficient balance!\n");
        return;
    }

    printf("\n--- Confirm Recharge ---\n");
    printf("Number : %s\n", phone);
    printf("Amount : %.2f Tk\n", amount);

    if (!verify_pin()) return;

    printf("\n✅ Recharge Successful!\n");
    printf("Remaining Bal : %.2f Tk\n", BALANCE - amount);
}

void check_balance() {
    clear_screen();
    print_header();
    printf("Balance Inquiry\n");
    printf("-----------------------------\n");

    if (!verify_pin()) return;

    printf("\n✅ Balance: %.2f Tk\n", BALANCE);
}

void cash_out() {
    char agent[MAX_PHONE_LEN];
    char amount_str[MAX_AMOUNT_LEN];
    double amount;

    clear_screen();
    print_header();
    printf("Cash Out\n");
    printf("-----------------------------\n");

    get_input("Agent/ATM Number (01XXXXXXXXX)", agent, sizeof(agent));
    get_input("Amount (Taka)", amount_str, sizeof(amount_str));
    amount = atof(amount_str);

    if (amount <= 0 || amount > BALANCE) {
        printf("\n❌ Invalid amount or insufficient balance!\n");
        return;
    }

    double charge = amount * 0.015; /* 1.5% charge */

    printf("\n--- Confirm Cash Out ---\n");
    printf("Agent : %s\n", agent);
    printf("Amt   : %.2f Tk\n", amount);
    printf("Charge: %.2f Tk\n", charge);

    if (!verify_pin()) return;

    printf("\n✅ Cash Out Successful!\n");
    printf("Transaction ID: TXN%08d\n", rand() % 99999999);
    printf("Remaining Bal : %.2f Tk\n", BALANCE - amount);
}

void payment() {
    char merchant[MAX_PHONE_LEN];
    char amount_str[MAX_AMOUNT_LEN];
    double amount;

    clear_screen();
    print_header();
    printf("Payment\n");
    printf("-----------------------------\n");

    get_input("Merchant Number", merchant, sizeof(merchant));
    get_input("Amount (Taka)", amount_str, sizeof(amount_str));
    amount = atof(amount_str);

    if (amount <= 0 || amount > BALANCE) {
        printf("\n❌ Invalid amount or insufficient balance!\n");
        return;
    }

    printf("\n--- Confirm Payment ---\n");
    printf("Merchant : %s\n", merchant);
    printf("Amount   : %.2f Tk\n", amount);
    printf("Charge   : 0.00 Tk (free)\n");

    if (!verify_pin()) return;

    printf("\n✅ Payment Successful!\n");
    printf("Transaction ID: TXN%08d\n", rand() % 99999999);
    printf("Remaining Bal : %.2f Tk\n", BALANCE - amount);
}

void my_bkash() {
    clear_screen();
    print_header();
    printf("My bKash\n");
    printf("-----------------------------\n");
    printf("1. Statement\n");
    printf("2. Change PIN\n");
    printf("0. Back\n");
    printf("-----------------------------\n");

    char choice[4];
    get_input("Option", choice, sizeof(choice));

    if (strcmp(choice, "1") == 0) {
        if (!verify_pin()) return;
        printf("\n--- Last 3 Transactions ---\n");
        printf("1. Send  -> 01711XXXXXX  200.00 Tk\n");
        printf("2. CashIn<- Agent        500.00 Tk\n");
        printf("3. Pay   -> Merchant     150.00 Tk\n");
    } else if (strcmp(choice, "2") == 0) {
        printf("\nEnter current PIN:\n");
        if (!verify_pin()) return;
        char new_pin[MAX_PIN_LEN + 2];
        get_input("New PIN (4 digit)", new_pin, sizeof(new_pin));
        printf("\n✅ PIN changed successfully!\n");
    }
}

/* --- Main Menu --- */
void main_menu() {
    char choice[4];

    while (1) {
        clear_screen();
        print_header();
        printf("1. Send Money\n");
        printf("2. Mobile Recharge\n");
        printf("3. Cash Out\n");
        printf("4. Payment\n");
        printf("5. Balance\n");
        printf("6. My bKash\n");
        printf("-----------------------------\n");
        printf("0. Exit\n");
        printf("=============================\n");

        get_input("Option select korun", choice, sizeof(choice));

        if      (strcmp(choice, "1") == 0) send_money();
        else if (strcmp(choice, "2") == 0) mobile_recharge();
        else if (strcmp(choice, "3") == 0) cash_out();
        else if (strcmp(choice, "4") == 0) payment();
        else if (strcmp(choice, "5") == 0) check_balance();
        else if (strcmp(choice, "6") == 0) my_bkash();
        else if (strcmp(choice, "0") == 0) {
            printf("\nbKash theke beriye aschhen...\n");
            break;
        } else {
            printf("\n❌ Invalid option!\n");
        }

        printf("\nEnter chapon continue korun...");
        getchar();
    }
}

/* --- Entry Point --- */
int main() {
    srand(42);

    clear_screen();
    print_header();
    printf("\n*247# dial kora hoyeche\n");
    printf("bKash-e swagatom!\n\n");
    printf("Continue korun...");
    getchar();

    main_menu();

    printf("Dhonyabad bKash use korar jonyo.\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===== bKash USSD Menu Simulator =====
   Dial: *247#
   ====================================== */

#define MAX_PIN_LEN     6
#define MAX_PHONE_LEN   13
#define MAX_AMOUNT_LEN  10
#define BALANCE         1500.00

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
    buf[strcspn(buf, "\n")] = '\0';
}

int get_choice(const char *prompt) {
    char buf[8];
    get_input(prompt, buf, sizeof(buf));
    return atoi(buf);
}

int verify_pin() {
    char pin[MAX_PIN_LEN + 2];
    get_input("PIN Number", pin, sizeof(pin));
    if (strcmp(pin, "1234") == 0) return 1;
    printf("\n❌ Voul PIN! Aborting.\n");
    return 0;
}

/* ================================================
   1. Send Money
   ================================================ */
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
    printf("To    : %s\n", phone);
    printf("Amt   : %.2f Tk\n", amount);
    printf("Charge: 5.00 Tk\n");
    printf("-----------------------------\n");
    printf("1. Confirm\n2. Cancel\n");

    switch (get_choice("Option")) {
        case 1:
            if (!verify_pin()) return;
            printf("\n✅ Send Successful!\n");
            printf("Transaction ID: TXN%08d\n", rand() % 99999999);
            printf("Remaining Bal : %.2f Tk\n", BALANCE - amount - 5.0);
            break;
        case 2:
            printf("\nCancel kora hoyeche.\n");
            break;
        default:
            printf("\n❌ Invalid option!\n");
            break;
    }
}

/* ================================================
   2. Mobile Recharge
   ================================================ */
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

    switch (get_choice("Option")) {
        case 1:
            strcpy(phone, "01700000000");
            break;
        case 2:
            get_input("Receiver Number (01XXXXXXXXX)", phone, sizeof(phone));
            break;
        case 0:
            return;
        default:
            printf("\n❌ Invalid option!\n");
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
    printf("-----------------------------\n");
    printf("1. Confirm\n2. Cancel\n");

    switch (get_choice("Option")) {
        case 1:
            if (!verify_pin()) return;
            printf("\n✅ Recharge Successful!\n");
            printf("Remaining Bal : %.2f Tk\n", BALANCE - amount);
            break;
        case 2:
            printf("\nCancel kora hoyeche.\n");
            break;
        default:
            printf("\n❌ Invalid option!\n");
            break;
    }
}

/* ================================================
   3. Cash Out
   ================================================ */
void cash_out() {
    char agent[MAX_PHONE_LEN];
    char amount_str[MAX_AMOUNT_LEN];
    double amount, charge;

    clear_screen();
    print_header();
    printf("Cash Out\n");
    printf("-----------------------------\n");
    printf("1. Agent\n");
    printf("2. ATM\n");
    printf("0. Back\n");
    printf("-----------------------------\n");

    switch (get_choice("Option")) {
        case 1:
            get_input("Agent Number (01XXXXXXXXX)", agent, sizeof(agent));
            break;
        case 2:
            get_input("ATM Number", agent, sizeof(agent));
            break;
        case 0:
            return;
        default:
            printf("\n❌ Invalid option!\n");
            return;
    }

    get_input("Amount (Taka)", amount_str, sizeof(amount_str));
    amount = atof(amount_str);

    if (amount <= 0 || amount > BALANCE) {
        printf("\n❌ Invalid amount or insufficient balance!\n");
        return;
    }

    charge = amount * 0.015;

    printf("\n--- Confirm Cash Out ---\n");
    printf("To    : %s\n", agent);
    printf("Amt   : %.2f Tk\n", amount);
    printf("Charge: %.2f Tk\n", charge);
    printf("-----------------------------\n");
    printf("1. Confirm\n2. Cancel\n");

    switch (get_choice("Option")) {
        case 1:
            if (!verify_pin()) return;
            printf("\n✅ Cash Out Successful!\n");
            printf("Transaction ID: TXN%08d\n", rand() % 99999999);
            printf("Remaining Bal : %.2f Tk\n", BALANCE - amount);
            break;
        case 2:
            printf("\nCancel kora hoyeche.\n");
            break;
        default:
            printf("\n❌ Invalid option!\n");
            break;
    }
}

/* ================================================
   4. Payment
   ================================================ */
void payment() {
    char merchant[MAX_PHONE_LEN];
    char amount_str[MAX_AMOUNT_LEN];
    double amount;

    clear_screen();
    print_header();
    printf("Payment\n");
    printf("-----------------------------\n");
    printf("1. Merchant Number diye\n");
    printf("2. Merchant ID diye\n");
    printf("0. Back\n");
    printf("-----------------------------\n");

    switch (get_choice("Option")) {
        case 1:
            get_input("Merchant Number", merchant, sizeof(merchant));
            break;
        case 2:
            get_input("Merchant ID", merchant, sizeof(merchant));
            break;
        case 0:
            return;
        default:
            printf("\n❌ Invalid option!\n");
            return;
    }

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
    printf("-----------------------------\n");
    printf("1. Confirm\n2. Cancel\n");

    switch (get_choice("Option")) {
        case 1:
            if (!verify_pin()) return;
            printf("\n✅ Payment Successful!\n");
            printf("Transaction ID: TXN%08d\n", rand() % 99999999);
            printf("Remaining Bal : %.2f Tk\n", BALANCE - amount);
            break;
        case 2:
            printf("\nCancel kora hoyeche.\n");
            break;
        default:
            printf("\n❌ Invalid option!\n");
            break;
    }
}

/* ================================================
   5. Balance Inquiry
   ================================================ */
void check_balance() {
    clear_screen();
    print_header();
    printf("Balance Inquiry\n");
    printf("-----------------------------\n");
    if (!verify_pin()) return;
    printf("\n✅ Balance: %.2f Tk\n", BALANCE);
}

/* ================================================
   6. My bKash
   ================================================ */
void my_bkash() {
    clear_screen();
    print_header();
    printf("My bKash\n");
    printf("-----------------------------\n");
    printf("1. Statement\n");
    printf("2. Change PIN\n");
    printf("3. Profile\n");
    printf("0. Back\n");
    printf("-----------------------------\n");

    switch (get_choice("Option")) {
        case 1:
            if (!verify_pin()) return;
            printf("\n--- Last 3 Transactions ---\n");
            printf("1. Send  -> 01711XXXXXX  200.00 Tk\n");
            printf("2. CashIn<- Agent        500.00 Tk\n");
            printf("3. Pay   -> Merchant     150.00 Tk\n");
            break;

        case 2: {
            char new_pin[MAX_PIN_LEN + 2];
            printf("\nCurrent PIN verify:\n");
            if (!verify_pin()) return;
            get_input("New PIN (4 digit)", new_pin, sizeof(new_pin));
            printf("\n✅ PIN successfully changed!\n");
            break;
        }

        case 3:
            printf("\n--- Profile ---\n");
            printf("Name    : Demo User\n");
            printf("Number  : 01700000000\n");
            printf("Account : Personal\n");
            break;

        case 0:
            break;

        default:
            printf("\n❌ Invalid option!\n");
            break;
    }
}

/* ================================================
   Main Menu
   ================================================ */
void main_menu() {
    int running = 1;

    while (running) {
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

        switch (get_choice("Option select korun")) {
            case 1: send_money();      break;
            case 2: mobile_recharge(); break;
            case 3: cash_out();        break;
            case 4: payment();         break;
            case 5: check_balance();   break;
            case 6: my_bkash();        break;
            case 0:
                printf("\nbKash theke beriye aschhen...\n");
                running = 0;
                break;
            default:
                printf("\n❌ Invalid option! Abar try korun.\n");
                break;
        }

        if (running) {
            printf("\nEnter chapon continue korun...");
            getchar();
        }
    }
}

/* ================================================
   Entry Point
   ================================================ */
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
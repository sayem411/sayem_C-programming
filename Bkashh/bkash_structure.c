#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ===== bKash USSD Menu Simulator =====
   Dial: *247#
   ====================================== */

#define MAX_PIN_LEN      5
#define MAX_PHONE_LEN    12
#define MAX_AMOUNT_LEN   10
#define MAX_NAME_LEN     30
#define MAX_TXN_ID_LEN   15
#define MAX_HISTORY      10

/* ================================================
   Structures
   ================================================ */

/* Account — bKash user-er info */
typedef struct {
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
    char pin[MAX_PIN_LEN];
    double balance;
    char account_type[15];    /* Personal / Merchant */
} Account;

/* Transaction — ekta transaction-er poripurno record */
typedef struct {
    char txn_id[MAX_TXN_ID_LEN];
    char type[12];            /* Send / CashOut / Recharge / Payment / CashIn */
    char counterpart[MAX_PHONE_LEN];
    double amount;
    double charge;
    double balance_after;
} Transaction;

/* TransactionHistory — shob transaction dharar container */
typedef struct {
    Transaction list[MAX_HISTORY];
    int count;
} TransactionHistory;

/* SendMoneyReq — Send Money-r input data */
typedef struct {
    char receiver[MAX_PHONE_LEN];
    double amount;
    double charge;
} SendMoneyReq;

/* RechargeReq — Recharge-r input data */
typedef struct {
    char phone[MAX_PHONE_LEN];
    double amount;
    int self;                 /* 1 = nij number, 0 = onyo number */
} RechargeReq;

/* CashOutReq — Cash Out-r input data */
typedef struct {
    char agent[MAX_PHONE_LEN];
    int via_atm;              /* 0 = Agent, 1 = ATM */
    double amount;
    double charge;
} CashOutReq;

/* PaymentReq — Payment-r input data */
typedef struct {
    char merchant[MAX_PHONE_LEN];
    int via_id;               /* 0 = number, 1 = merchant ID */
    double amount;
} PaymentReq;

/* ================================================
   Global State
   ================================================ */
Account         g_account;
TransactionHistory g_history;

/* ================================================
   Utility Functions
   ================================================ */

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

void generate_txn_id(char *buf) {
    sprintf(buf, "TXN%08d", rand() % 99999999);
}

/* ================================================
   Account Functions
   ================================================ */

void account_init(Account *acc) {
    strcpy(acc->name,         "Demo User");
    strcpy(acc->phone,        "01700000000");
    strcpy(acc->pin,          "1234");
    acc->balance = 1500.00;
    strcpy(acc->account_type, "Personal");
}

int account_verify_pin(const Account *acc) {
    char pin[MAX_PIN_LEN + 2];
    get_input("PIN Number", pin, sizeof(pin));
    if (strcmp(pin, acc->pin) == 0) return 1;
    printf("\n❌ Voul PIN! Aborting.\n");
    return 0;
}

int account_change_pin(Account *acc) {
    char new_pin[MAX_PIN_LEN + 2];
    printf("\nCurrent PIN verify:\n");
    if (!account_verify_pin(acc)) return 0;
    get_input("New PIN (4 digit)", new_pin, sizeof(new_pin));
    strncpy(acc->pin, new_pin, MAX_PIN_LEN);
    acc->pin[MAX_PIN_LEN - 1] = '\0';
    return 1;
}

void account_print_profile(const Account *acc) {
    printf("\n--- Profile ---\n");
    printf("Name    : %s\n",  acc->name);
    printf("Number  : %s\n",  acc->phone);
    printf("Account : %s\n",  acc->account_type);
    printf("Balance : %.2f Tk\n", acc->balance);
}

/* ================================================
   Transaction History Functions
   ================================================ */

void history_init(TransactionHistory *h) {
    h->count = 0;
}

void history_add(TransactionHistory *h, const Transaction *txn) {
    if (h->count >= MAX_HISTORY) {
        /* oldest sorate nao (shift left) */
        int i;
        for (i = 0; i < MAX_HISTORY - 1; i++)
            h->list[i] = h->list[i + 1];
        h->list[MAX_HISTORY - 1] = *txn;
    } else {
        h->list[h->count++] = *txn;
    }
}

void history_print(const TransactionHistory *h) {
    if (h->count == 0) {
        printf("\nKono transaction nei.\n");
        return;
    }
    printf("\n--- Last %d Transaction(s) ---\n", h->count);
    int i;
    for (i = 0; i < h->count; i++) {
        const Transaction *t = &h->list[i];
        printf("%d. [%s] %s | %.2f Tk | Bal: %.2f Tk\n",
               i + 1, t->txn_id, t->type, t->amount, t->balance_after);
    }
}

/* ================================================
   Send Money
   ================================================ */

int send_money_input(SendMoneyReq *req, const Account *acc) {
    get_input("Receiver Number (01XXXXXXXXX)", req->receiver, MAX_PHONE_LEN);

    if (strlen(req->receiver) != 11 ||
        req->receiver[0] != '0' || req->receiver[1] != '1') {
        printf("\n❌ Invalid number format!\n");
        return 0;
    }

    char buf[MAX_AMOUNT_LEN];
    get_input("Amount (Taka)", buf, MAX_AMOUNT_LEN);
    req->amount = atof(buf);
    req->charge = 5.00;

    if (req->amount <= 0 || req->amount + req->charge > acc->balance) {
        printf("\n❌ Invalid amount or insufficient balance!\n");
        return 0;
    }
    return 1;
}

void send_money_confirm_print(const SendMoneyReq *req) {
    printf("\n--- Confirm Send Money ---\n");
    printf("To    : %s\n",       req->receiver);
    printf("Amt   : %.2f Tk\n",  req->amount);
    printf("Charge: %.2f Tk\n",  req->charge);
    printf("Total : %.2f Tk\n",  req->amount + req->charge);
    printf("-----------------------------\n");
    printf("1. Confirm\n2. Cancel\n");
}

void send_money(Account *acc, TransactionHistory *h) {
    SendMoneyReq req;
    clear_screen(); print_header();
    printf("Send Money\n");
    printf("-----------------------------\n");

    if (!send_money_input(&req, acc)) return;
    send_money_confirm_print(&req);

    switch (get_choice("Option")) {
        case 1:
            if (!account_verify_pin(acc)) return;
            acc->balance -= (req.amount + req.charge);
            {
                Transaction t;
                generate_txn_id(t.txn_id);
                strcpy(t.type, "Send");
                strcpy(t.counterpart, req.receiver);
                t.amount       = req.amount;
                t.charge       = req.charge;
                t.balance_after = acc->balance;
                history_add(h, &t);
                printf("\n✅ Send Successful!\n");
                printf("TXN ID       : %s\n",    t.txn_id);
                printf("Remaining Bal: %.2f Tk\n", acc->balance);
            }
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
   Mobile Recharge
   ================================================ */

int recharge_input(RechargeReq *req, const Account *acc) {
    printf("1. Nij Number\n2. Onyo Number\n0. Back\n");
    printf("-----------------------------\n");

    switch (get_choice("Option")) {
        case 1:
            strcpy(req->phone, acc->phone);
            req->self = 1;
            break;
        case 2:
            get_input("Receiver Number (01XXXXXXXXX)", req->phone, MAX_PHONE_LEN);
            req->self = 0;
            break;
        case 0:
            return -1; /* back */
        default:
            printf("\n❌ Invalid option!\n");
            return 0;
    }

    char buf[MAX_AMOUNT_LEN];
    get_input("Recharge Amount", buf, MAX_AMOUNT_LEN);
    req->amount = atof(buf);

    if (req->amount <= 0 || req->amount > acc->balance) {
        printf("\n❌ Invalid amount or insufficient balance!\n");
        return 0;
    }
    return 1;
}

void mobile_recharge(Account *acc, TransactionHistory *h) {
    RechargeReq req;
    clear_screen(); print_header();
    printf("Mobile Recharge\n");
    printf("-----------------------------\n");

    int r = recharge_input(&req, acc);
    if (r <= 0) return;

    printf("\n--- Confirm Recharge ---\n");
    printf("Number : %s\n",      req.phone);
    printf("Amount : %.2f Tk\n", req.amount);
    printf("-----------------------------\n");
    printf("1. Confirm\n2. Cancel\n");

    switch (get_choice("Option")) {
        case 1:
            if (!account_verify_pin(acc)) return;
            acc->balance -= req.amount;
            {
                Transaction t;
                generate_txn_id(t.txn_id);
                strcpy(t.type, "Recharge");
                strcpy(t.counterpart, req.phone);
                t.amount       = req.amount;
                t.charge       = 0;
                t.balance_after = acc->balance;
                history_add(h, &t);
                printf("\n✅ Recharge Successful!\n");
                printf("TXN ID       : %s\n",    t.txn_id);
                printf("Remaining Bal: %.2f Tk\n", acc->balance);
            }
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
   Cash Out
   ================================================ */

int cashout_input(CashOutReq *req, const Account *acc) {
    printf("1. Agent\n2. ATM\n0. Back\n");
    printf("-----------------------------\n");

    switch (get_choice("Option")) {
        case 1:
            get_input("Agent Number (01XXXXXXXXX)", req->agent, MAX_PHONE_LEN);
            req->via_atm = 0;
            break;
        case 2:
            get_input("ATM Number", req->agent, MAX_PHONE_LEN);
            req->via_atm = 1;
            break;
        case 0:
            return -1;
        default:
            printf("\n❌ Invalid option!\n");
            return 0;
    }

    char buf[MAX_AMOUNT_LEN];
    get_input("Amount (Taka)", buf, MAX_AMOUNT_LEN);
    req->amount = atof(buf);
    req->charge = req->amount * 0.015; /* 1.5% */

    if (req->amount <= 0 || req->amount + req->charge > acc->balance) {
        printf("\n❌ Invalid amount or insufficient balance!\n");
        return 0;
    }
    return 1;
}

void cash_out(Account *acc, TransactionHistory *h) {
    CashOutReq req;
    clear_screen(); print_header();
    printf("Cash Out\n");
    printf("-----------------------------\n");

    int r = cashout_input(&req, acc);
    if (r <= 0) return;

    printf("\n--- Confirm Cash Out ---\n");
    printf("To    : %s\n",       req.agent);
    printf("Via   : %s\n",       req.via_atm ? "ATM" : "Agent");
    printf("Amt   : %.2f Tk\n",  req.amount);
    printf("Charge: %.2f Tk\n",  req.charge);
    printf("Total : %.2f Tk\n",  req.amount + req.charge);
    printf("-----------------------------\n");
    printf("1. Confirm\n2. Cancel\n");

    switch (get_choice("Option")) {
        case 1:
            if (!account_verify_pin(acc)) return;
            acc->balance -= (req.amount + req.charge);
            {
                Transaction t;
                generate_txn_id(t.txn_id);
                strcpy(t.type, "CashOut");
                strcpy(t.counterpart, req.agent);
                t.amount       = req.amount;
                t.charge       = req.charge;
                t.balance_after = acc->balance;
                history_add(h, &t);
                printf("\n✅ Cash Out Successful!\n");
                printf("TXN ID       : %s\n",    t.txn_id);
                printf("Remaining Bal: %.2f Tk\n", acc->balance);
            }
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
   Payment
   ================================================ */

int payment_input(PaymentReq *req, const Account *acc) {
    printf("1. Merchant Number diye\n2. Merchant ID diye\n0. Back\n");
    printf("-----------------------------\n");

    switch (get_choice("Option")) {
        case 1:
            get_input("Merchant Number", req->merchant, MAX_PHONE_LEN);
            req->via_id = 0;
            break;
        case 2:
            get_input("Merchant ID", req->merchant, MAX_PHONE_LEN);
            req->via_id = 1;
            break;
        case 0:
            return -1;
        default:
            printf("\n❌ Invalid option!\n");
            return 0;
    }

    char buf[MAX_AMOUNT_LEN];
    get_input("Amount (Taka)", buf, MAX_AMOUNT_LEN);
    req->amount = atof(buf);

    if (req->amount <= 0 || req->amount > acc->balance) {
        printf("\n❌ Invalid amount or insufficient balance!\n");
        return 0;
    }
    return 1;
}

void payment(Account *acc, TransactionHistory *h) {
    PaymentReq req;
    clear_screen(); print_header();
    printf("Payment\n");
    printf("-----------------------------\n");

    int r = payment_input(&req, acc);
    if (r <= 0) return;

    printf("\n--- Confirm Payment ---\n");
    printf("Merchant : %s\n",     req.merchant);
    printf("Amount   : %.2f Tk\n", req.amount);
    printf("Charge   : 0.00 Tk (free)\n");
    printf("-----------------------------\n");
    printf("1. Confirm\n2. Cancel\n");

    switch (get_choice("Option")) {
        case 1:
            if (!account_verify_pin(acc)) return;
            acc->balance -= req.amount;
            {
                Transaction t;
                generate_txn_id(t.txn_id);
                strcpy(t.type, "Payment");
                strcpy(t.counterpart, req.merchant);
                t.amount       = req.amount;
                t.charge       = 0;
                t.balance_after = acc->balance;
                history_add(h, &t);
                printf("\n✅ Payment Successful!\n");
                printf("TXN ID       : %s\n",    t.txn_id);
                printf("Remaining Bal: %.2f Tk\n", acc->balance);
            }
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
   Balance Inquiry
   ================================================ */

void check_balance(const Account *acc) {
    clear_screen(); print_header();
    printf("Balance Inquiry\n");
    printf("-----------------------------\n");
    if (!account_verify_pin(acc)) return;
    printf("\n✅ Balance: %.2f Tk\n", acc->balance);
}

/* ================================================
   My bKash
   ================================================ */

void my_bkash(Account *acc, TransactionHistory *h) {
    clear_screen(); print_header();
    printf("My bKash\n");
    printf("-----------------------------\n");
    printf("1. Statement\n");
    printf("2. Change PIN\n");
    printf("3. Profile\n");
    printf("0. Back\n");
    printf("-----------------------------\n");

    switch (get_choice("Option")) {
        case 1:
            if (!account_verify_pin(acc)) return;
            history_print(h);
            break;
        case 2:
            if (account_change_pin(acc))
                printf("\n✅ PIN successfully changed!\n");
            break;
        case 3:
            account_print_profile(acc);
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

void main_menu(Account *acc, TransactionHistory *h) {
    int running = 1;

    while (running) {
        clear_screen(); print_header();
        printf("Name: %s | Bal: %.2f Tk\n", acc->name, acc->balance);
        printf("-----------------------------\n");
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
            case 1: send_money(acc, h);      break;
            case 2: mobile_recharge(acc, h); break;
            case 3: cash_out(acc, h);        break;
            case 4: payment(acc, h);         break;
            case 5: check_balance(acc);      break;
            case 6: my_bkash(acc, h);        break;
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
    srand((unsigned int)time(NULL));

    /* Global state initialize */
    account_init(&g_account);
    history_init(&g_history);

    clear_screen(); print_header();
    printf("\n*247# dial kora hoyeche\n");
    printf("bKash-e swagatom!\n\n");
    printf("Continue korun...");
    getchar();

    main_menu(&g_account, &g_history);

    printf("Dhonyabad bKash use korar jonyo.\n");
    return 0;
}
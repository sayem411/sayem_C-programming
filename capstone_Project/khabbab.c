#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
    char expiryDate[15];
} Medicine;


typedef struct {
    int id;
    int quantity;
} CartItem;

CartItem cart[50];
int cartCount = 0;

Medicine medicines [100];
int medicineCount = 0;

//Functions
void displayManu();
void adminLogin();
void adminPanel();
void clearInputBuffer();
void viewMedicine();
void searchMedicine();
int isDuplicateId(int id);
void addMedicine();
void customerPanel();
void addToCart(int id, int qty);
float processPayment(float totalAmount);
void checkout();
void printReceipt(float total, float tax, float finalAmount);
void saveReceiptToFile(float total, float tax, float finalAmount);
void customerCart();
void viewSales();
void saveMedicines();
void updateMedicine();
void lowStockAlert();
void loadMedicines();
void deleteMedicine();


int main() 
{   
    loadMedicines();
    displayManu();
    
    return 0;
}

void displayManu() {
    while(1) {
        // Design for Medical Store Title
        printf("\n");
        printf("************************************************\n");
        printf("*                                              *\n");
        printf("*            WELCOME TO MediTrack              *\n");
        printf("*                                              *\n");
        printf("************************************************\n");

        printf("\n1. Admin Login\n");
        printf("2. Customer Panel\n");
        printf("3. Exit\n");

        int choice;
        printf("Enter Choice : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: adminLogin(); break;
            case 2: customerPanel(); break;
            case 3: exit(0);

            default: printf("Invalid choice!\n"); break;
        }
    }
}


void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void adminLogin() {
    char username[20], password[20];

    // Predefined usernames and passwords
    char *validUsers[] = {"Khabbab", "Rafi", "Bishal"};
    char *validPasswords[] = {"851", "452", "474"};

    printf("\n--- Admin Login ---\n");
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    // Check if username and password match any valid credentials
    int authenticated = 0;
    for (int i = 0; i < 3; i++) {
        if ((strcasecmp(username, validUsers[i]) == 0) && (strcmp(password, validPasswords[i]) == 0)) {
            authenticated = 1;
            printf("\nLogin successful! Welcome, %s.\n", validUsers[i]);
            adminPanel();  // Proceed to admin panel if login is successful
            break;
        }
    }

    if (!authenticated) {
        printf("\nInvalid credentials! Returning to main menu...\n");
    }
}


void adminPanel() {
    while (1) {
        printf ("\nAdmin Panel\n");
        printf ("1. View Medicines\n");
        printf ("2. Add Medicine\n");
        printf ("3. Update Medicine\n");
        printf ("4. Delete Medicine\n");
        printf ("5. Search Medicine\n");
        printf ("6. View Sales\n"); 
        printf ("7. Back to Main\n");

        int choice;
        printf ("Enter Choice : ");
        scanf ("%d", &choice);

        switch (choice) {
            case 1: 
            viewMedicine();
             break;
            case 2: addMedicine(); break;
            case 3: updateMedicine(); break;
            case 4: deleteMedicine(); break;
            case 5: searchMedicine(); break;
            case 6: viewSales(); break;
            case 7: return;
            default: printf("Invalid choice!\n"); break;
        }
    }
}

void viewMedicine() {
    if (medicineCount == 0) {
        printf("No medicine in stock!\n");
        return;
    }

    // Print the medicines in a formatted way
    printf("\nID    Name                  Price   Qty   Expiry\n");
    printf("----------------------------------------------\n");

    for (int i = 0; i < medicineCount; i++) {
        printf("%-5d %-20s %-8.2f %-5d %-12s\n", 
               medicines[i].id, 
               medicines[i].name, 
               medicines[i].price, 
               medicines[i].quantity,
               medicines[i].expiryDate);
    }

    printf("----------------------------------------------\n");
}


void searchMedicine() {
    if (medicineCount == 0) {
        printf("No medicine in stock!\n");
        return;
    }

    int choice;
    printf("\n--- Search Medicine ---\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int found = 0;

    if (choice == 1) {
        int id;
        printf("Enter Medicine ID: ");
        scanf("%d", &id);

        for (int i = 0; i < medicineCount; i++) {
            if (medicines[i].id == id) {
                printf("\nID\tName\t\tPrice\tQty\tExpiry\n");
                printf("----------------------------------------------\n");
                printf("%d\t%s\t\t%.2f\t%d\t%s\n",
                       medicines[i].id, medicines[i].name,
                       medicines[i].price, medicines[i].quantity,
                       medicines[i].expiryDate);
                found = 1;
                break;
            }
        }

    } else if (choice == 2) {
        char name[50];
        printf("Enter Medicine Name: ");
        clearInputBuffer();
        fgets(name, sizeof(name), stdin);
        size_t len = strlen(name);
        if (len > 0 && name[len - 1] == '\n') {
            name[len - 1] = '\0';
        }

        for (int i = 0; i < medicineCount; i++) {
            if (strcasecmp(medicines[i].name, name) == 0) { // case-insensitive comparison
                printf("\nID\tName\t\tPrice\tQty\tExpiry\n");
                printf("----------------------------------------------\n");
                printf("%d\t%s\t\t%.2f\t%d\t%s\n",
                       medicines[i].id, medicines[i].name,
                       medicines[i].price, medicines[i].quantity,
                       medicines[i].expiryDate);
                found = 1;
            }
        }

    } else {
        printf("Invalid choice!\n");
        return;
    }

    if (!found) {
        printf("Medicine not found!\n");
    }
}

int isDuplicateId(int id) {
    for (int i = 0; i < medicineCount; i++) {
        if (medicines[i].id == id) {
            return 1; // duplicate found
        }
    }
    return 0; // no duplicate
}

void addMedicine() {
    if (medicineCount >= 100) {
        printf("Inventory is full!\n");
        return;
    }

    Medicine m;
    while (1) {
        printf("Enter Medicine Id : ");
        scanf("%d", &m.id);

        if (isDuplicateId(m.id)) {
            printf("Medicine ID already exists! Please enter a unique ID.\n");
        } else {
            break;
        }
    }

    printf("Enter Medicine Name: ");
    clearInputBuffer();
    fgets(m.name, sizeof(m.name), stdin);
    size_t len = strlen(m.name);
    if (len > 0 && m.name[len - 1] == '\n') {
        m.name[len - 1] = '\0';
    }

    printf("Enter Medicine Price : ");
    scanf("%f", &m.price);

    printf("Enter Medicine Quantity : ");
    scanf("%d", &m.quantity);

    printf("Enter Expiry Date (DD/MM/YYYY): ");
    clearInputBuffer();
    fgets(m.expiryDate, sizeof(m.expiryDate), stdin);
    len = strlen(m.expiryDate);
    if (len > 0 && m.expiryDate[len - 1] == '\n') {
        m.expiryDate[len - 1] = '\0';
    }

    medicines[medicineCount] = m;
    medicineCount++;
    saveMedicines(); // Save to file

    printf("%s added to inventory successfully!\n", m.name);
}

void customerPanel() {
    while (1) {
        printf("\nCustomer Panel\n");
        printf("1. View Medicines\n");
        printf("2. Search Medicines\n");
        printf("3. Buy Medicines (Cart)\n");
        printf("4. Back to Main\n");

        int choice;
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewMedicine(); break;
            case 2: searchMedicine(); break;
            case 3: customerCart(); break;
            case 4: return;
            default: printf("Invalid choice!\n"); break;
        }
    }
}

void addToCart(int id, int qty) {
    cart[cartCount].id = id;
    cart[cartCount].quantity = qty;
    cartCount++;
}

float processPayment(float totalAmount) {
    float payment = 0.0;

    printf("\n--- Payment Section ---\n");
    printf("Total Amount to Pay: %.2f\n", totalAmount);

    while (1) {
        printf("Enter payment amount: ");
        scanf("%f", &payment);

        if (payment < totalAmount) {
            printf("Insufficient payment! You still owe %.2f\n", totalAmount - payment);
        } else {
            float change = payment - totalAmount;
            printf("Payment successful!\n");
            printf("Change to return: %.2f\n", change);
            return payment; // returns amount paid
        }
    }
}

void checkout() {
    if (cartCount == 0) {
        printf("Your cart is empty!\n");
        return;
    }

    float total = 0;
    printf("\n--- Purchase Summary ---\n");
    printf("ID\tName\t\tPrice\tQty\tTotal\n");
    printf("----------------------------------------------\n");

    for (int i = 0; i < cartCount; i++) {
        for (int j = 0; j < medicineCount; j++) {
            if (medicines[j].id == cart[i].id) {
                float cost = medicines[j].price * cart[i].quantity;
                total += cost;
                printf("%d\t%s\t\t%.2f\t%d\t%.2f\n",
                       medicines[j].id,
                       medicines[j].name,
                       medicines[j].price,
                       cart[i].quantity,
                       cost);

                medicines[j].quantity -= cart[i].quantity; // reduce stock
            }
        }
    }

    float taxRate = 0.05; // 5% tax
    float tax = total * taxRate;
    float finalAmount = total + tax;

    printf("----------------------------------------------\n");
    printf("Subtotal: %.2f\n", total);
    printf("Tax (5%%): %.2f\n", tax);
    printf("Total Payable: %.2f\n", finalAmount);

    float payment;
    printf("Enter payment amount: ");
    scanf("%f", &payment);

    if (payment < finalAmount) {
    printf("Insufficient payment! Transaction cancelled.\n");
    return;
    }

    printf("Payment successful! Change: %.2f\n", payment - finalAmount);


    // Save sales record
    FILE *salesFile = fopen("sales.txt", "a");
    if (salesFile != NULL) {
        fprintf(salesFile, "New Purchase:\n");
        for (int i = 0; i < cartCount; i++) {
            for (int j = 0; j < medicineCount; j++) {
                if (medicines[j].id == cart[i].id) {
                    fprintf(salesFile, "%d\t%s\t%.2f\t%d\t%.2f\n",
                            medicines[j].id,
                            medicines[j].name,
                            medicines[j].price,
                            cart[i].quantity,
                            medicines[j].price * cart[i].quantity);
                }
            }
        }
        fprintf(salesFile, "Total Paid: %.2f\n\n", finalAmount);
        fclose(salesFile);
    }

    saveMedicines(); // save updated inventory
    lowStockAlert(); // show low stock warning
    cartCount = 0;   // clear cart

}

void printReceipt(float total, float tax, float finalAmount) {
    printf("\n\n===== Purchase Receipt =====\n");
    printf("ID\tName\t\tPrice\tQty\tTotal\n");
    printf("----------------------------------------------\n");

    for (int i = 0; i < cartCount; i++) {
        for (int j = 0; j < medicineCount; j++) {
            if (medicines[j].id == cart[i].id) {
                float cost = medicines[j].price * cart[i].quantity;
                printf("%d\t%s\t\t%.2f\t%d\t%.2f\n",
                       medicines[j].id,
                       medicines[j].name,
                       medicines[j].price,
                       cart[i].quantity,
                       cost);
            }
        }
    }

    printf("----------------------------------------------\n");
    printf("Subtotal: %.2f\n", total);
    printf("Tax (5%%): %.2f\n", tax);
    printf("Total Paid: %.2f\n", finalAmount);
    printf("=============================\n\n");
}

void saveReceiptToFile(float total, float tax, float finalAmount) {
    FILE *file = fopen("purchase_receipts.txt", "a");
    if (file == NULL) {
        printf("Error saving receipt to file.\n");
        return;
    }

    fprintf(file, "===== Purchase Receipt =====\n");
    fprintf(file, "ID\tName\t\tPrice\tQty\tTotal\n");
    fprintf(file, "----------------------------------------------\n");

    for (int i = 0; i < cartCount; i++) {
        for (int j = 0; j < medicineCount; j++) {
            if (medicines[j].id == cart[i].id) {
                float cost = medicines[j].price * cart[i].quantity;
                fprintf(file, "%d\t%s\t\t%.2f\t%d\t%.2f\n",
                        medicines[j].id,
                        medicines[j].name,
                        medicines[j].price,
                        cart[i].quantity,
                        cost);
            }
        }
    }

    fprintf(file, "----------------------------------------------\n");
    fprintf(file, "Subtotal: %.2f\n", total);
    fprintf(file, "Tax (5%%): %.2f\n", tax);
    fprintf(file, "Total Paid: %.2f\n", finalAmount);
    fprintf(file, "=============================\n\n");

    fclose(file);
}

void customerCart() {
    int id, qty;
    char more;

    while (1) {
        viewMedicine();
        printf("Enter Medicine ID to add to cart: ");
        scanf("%d", &id);

        int found = 0;
        for (int i = 0; i < medicineCount; i++) {
            if (medicines[i].id == id) {
                found = 1;
                printf("Enter quantity: ");
                scanf("%d", &qty);

                if (qty <= 0) {
                    printf("Invalid quantity!\n");
                    break;
                }

                if (qty > medicines[i].quantity) {
                    printf("Not enough stock! Available: %d\n", medicines[i].quantity);
                    break;
                }

                addToCart(id, qty);
                printf("Added to cart.\n");
                break;
            }
        }

        if (!found) {
            printf("Medicine not found!\n");
        }

        printf("Add more items? (y/n): ");
        scanf(" %c", &more);

        if (more != 'y' && more != 'Y') {
            checkout();
            break;
        }
    }
}

void viewSales() {
    FILE *file = fopen("sales.txt", "r");
    if (file == NULL) {
        printf("No sales records found.\n");
        return;
    }

    char line[256];  // Buffer to hold each line from the file
    printf("\n--- Sales History ---\n\n");
    
    int fileEmpty = 1;  // Flag to check if the file is empty
    float totalPaid = 0.0;

    // Read each line from the file and print it
    while (fgets(line, sizeof(line), file)) {
        fileEmpty = 0;  // Found some content

        // Remove the trailing newline if it exists
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
        // Print the line (display in the same format as written)
        printf("%s\n", line);

        // If the line contains "Total Paid", parse the total amount
        if (strstr(line, "Total Paid:") != NULL) {
            sscanf(line, "Total Paid: %f", &totalPaid);
        }
    }

    if (fileEmpty) {
        printf("Sales file is empty!\n");
    }

    fclose(file);  // Close the file

    // Print total sales summary
    if (!fileEmpty) {
        printf("\nTotal Paid: %.2f\n", totalPaid);
    }

    printf("\n--- End of Sales History ---\n");
}

void saveMedicines() {
    FILE *file = fopen("medicines.txt", "w");
    if(file == NULL) {
        printf("Error saving data!\n");
        return;
    }
    fprintf(file, "ID\tName\t\tPrice\tQty\tExpiry\n");
    fprintf(file, "----------------------------------------------\n");

    // all medicine data
    for (int i = 0; i < medicineCount; i++) {
        fprintf(file, "%d\t%s\t\t%.2f\t%d\t%s\n",
                medicines[i].id,
                medicines[i].name,
                medicines[i].price,
                medicines[i].quantity,
                medicines[i].expiryDate);
    }

    fclose(file);
}

void updateMedicine() {
    int id;
    printf("Enter Medicine ID to update: ");
    scanf("%d", &id);

    int found = 0;

    for (int i = 0; i < medicineCount; i++) {
        if (medicines[i].id == id) {
            found = 1;

            printf("Current Name: %s\n", medicines[i].name);
            printf("Enter new Name: ");
            clearInputBuffer();
            fgets(medicines[i].name, sizeof(medicines[i].name), stdin);
            size_t len = strlen(medicines[i].name);
            if (len > 0 && medicines[i].name[len - 1] == '\n') {
                medicines[i].name[len - 1] = '\0';
            }

            printf("Current Price: %.2f\n", medicines[i].price);
            printf("Enter new Price: ");
            scanf("%f", &medicines[i].price);

            printf("Current Quantity: %d\n", medicines[i].quantity);
            printf("Enter new Quantity: ");
            scanf("%d", &medicines[i].quantity);

            printf("Current Expiry: %s\n", medicines[i].expiryDate);
            printf("Enter new Expiry (dd-mm-yyyy): ");
            clearInputBuffer();
            fgets(medicines[i].expiryDate, sizeof(medicines[i].expiryDate), stdin);
            len = strlen(medicines[i].expiryDate);
            if (len > 0 && medicines[i].expiryDate[len - 1] == '\n') {
                medicines[i].expiryDate[len - 1] = '\0';
            }

            saveMedicines();
            printf("Medicine updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Medicine with ID %d not found.\n", id);
    }
}

void lowStockAlert() {
    int alertCount = 0;
    printf("\n*** Low Stock Alert ***\n");
    for (int i = 0; i < medicineCount; i++) {
        if (medicines[i].quantity < 5) {      // will notify when stock = 5
            printf("Medicine '%s' (ID: %d) is low on stock: %d units left!\n",
                   medicines[i].name, medicines[i].id, medicines[i].quantity);
            alertCount++;
        }
    }
    if (alertCount == 0) {
        printf("No medicines are low on stock.\n");
    }
}

void deleteMedicine() {
    if (medicineCount == 0) {
        printf("No medicine to delete!\n");
        return;
    }

    // Show current medicines
    viewMedicine();

    int id;
    printf("\nEnter Medicine ID to delete: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < medicineCount; i++) {
        if (medicines[i].id == id) {
            found = 1;

            // Optional confirmation
            char confirm;
            printf("Are you sure you want to delete '%s'? (y/n): ", medicines[i].name);
            scanf(" %c", &confirm);  // note the space before %c to ignore previous newline

            if (confirm != 'y' && confirm != 'Y') {
                printf("Deletion cancelled.\n");
                return;
            }

            // Shift remaining elements left
            for (int j = i; j < medicineCount - 1; j++) {
                medicines[j] = medicines[j + 1];
            }

            medicineCount--;
            saveMedicines();
            printf("Medicine with ID %d deleted successfully!\n", id);
            return;
        }
    }

    if (!found) {
        printf("Medicine with ID %d not found.\n", id);
    }
}

void loadMedicines() {
    FILE *file = fopen("medicines.txt", "r");
    if(file == NULL) return; // File doesn't exist yet

    medicineCount = 0;

    char line[200];
    // Skip the first two lines (header and separator)
    fgets(line, sizeof(line), file); // Header
    fgets(line, sizeof(line), file); // Separator

    // Now read actual medicine data
    while (fscanf(file, "%d %s %f %d %s",
                  &medicines[medicineCount].id,
                  medicines[medicineCount].name,
                  &medicines[medicineCount].price,
                  &medicines[medicineCount].quantity,
                  medicines[medicineCount].expiryDate) == 5) {
        medicineCount++;
    }

    fclose(file);
}


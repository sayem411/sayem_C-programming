/*
 * MediTrack - Integrated Healthcare Management System (Capstone Project)
 * Language : C (text-file storage, no database needed)
 *
 * Modules  : Login & roles, Patients, Doctors, Appointments,
 *            Prescriptions, Pharmacy (your old medicine store), Billing, Audit log
 * Roles    : Admin, Doctor, Pharmacist
 *
 * IMPORTANT: Use DUMMY data only. Never enter real patient information.
 *
 * Compile  : gcc healthcare.c -o healthcare
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>

#define MAX_USERS 20
#define MAX_MED   100
#define MAX_PAT   200
#define MAX_DOC   30
#define MAX_APPT  300
#define MAX_RX    500
#define LOW_STOCK 5
#define TAX_RATE  0.05f

enum { ROLE_ADMIN = 1, ROLE_DOCTOR = 2, ROLE_PHARMACIST = 3 };
enum { ST_SCHEDULED = 0, ST_COMPLETED = 1, ST_BILLED = 2, ST_CANCELLED = 3 };

static const char *roleNames[] = {"", "Admin", "Doctor", "Pharmacist"};
static const char *statusNames[] = {"Scheduled", "Completed", "Billed", "Cancelled"};

/* ------------------------- Data structures ------------------------- */
typedef struct { char username[30]; unsigned long hash; int role; int doctorId; } User;
typedef struct { int id; char name[50]; float price; int quantity; char expiry[15]; } Medicine;
typedef struct { int id; char name[50]; int age; char gender[10]; char problem[80]; } Patient;
typedef struct { int id; char name[50]; char specialty[40]; float fee; } Doctor;
typedef struct { int id; int patientId; int doctorId; char date[15]; int status; char notes[100]; } Appointment;
typedef struct { int id; int appointmentId; int patientId; int medicineId; int quantity; int dispensed; } Prescription;

User users[MAX_USERS];              int userCount = 0;
Medicine medicines[MAX_MED];        int medicineCount = 0;
Patient patients[MAX_PAT];          int patientCount = 0;
Doctor doctors[MAX_DOC];            int doctorCount = 0;
Appointment appts[MAX_APPT];        int apptCount = 0;
Prescription rxs[MAX_RX];           int rxCount = 0;
User *current = NULL;               /* who is logged in right now */

/* ------------------------- Input helpers ------------------------- */
/* Reads one non-empty line safely. '|' is replaced because it is our file separator. */
void readLine(const char *prompt, char *buf, int size) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buf, size, stdin) == NULL) { printf("\nInput closed. Goodbye.\n"); exit(0); }
        char *nl = strchr(buf, '\n');
        if (nl) *nl = '\0';
        else { int c; while ((c = getchar()) != '\n' && c != EOF); }  /* discard overflow */
        for (char *p = buf; *p; p++) if (*p == '|') *p = '/';
        if (buf[0] != '\0') return;
        printf("Input cannot be empty.\n");
    }
}

int readInt(const char *prompt, int min, int max) {
    char buf[40], *end;
    while (1) {
        readLine(prompt, buf, sizeof buf);
        long v = strtol(buf, &end, 10);
        if (*end == '\0' && v >= min && v <= max) return (int)v;
        printf("Please enter a whole number from %d to %d.\n", min, max);
    }
}

float readFloat(const char *prompt, float min) {
    char buf[40], *end;
    while (1) {
        readLine(prompt, buf, sizeof buf);
        float v = strtof(buf, &end);
        if (*end == '\0' && v >= min) return v;
        printf("Please enter a number of at least %.2f.\n", min);
    }
}

int confirm(const char *prompt) {
    char b[10];
    readLine(prompt, b, sizeof b);
    return b[0] == 'y' || b[0] == 'Y';
}

int equalsIgnoreCase(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++; b++;
    }
    return *a == *b;
}

int containsIgnoreCase(const char *text, const char *key) {
    for (; *text; text++) {
        const char *a = text, *b = key;
        while (*a && *b && tolower((unsigned char)*a) == tolower((unsigned char)*b)) { a++; b++; }
        if (*b == '\0') return 1;
    }
    return 0;
}

/* ------------------------- Date helpers ------------------------- */
/* "DD/MM/YYYY" -> YYYYMMDD number (easy to compare), or -1 if invalid */
int dateToNum(const char *d) {
    int dd, mm, yy; char extra;
    if (sscanf(d, "%d/%d/%d%c", &dd, &mm, &yy, &extra) != 3) return -1;
    if (yy < 2000 || yy > 2100 || mm < 1 || mm > 12 || dd < 1 || dd > 31) return -1;
    return yy * 10000 + mm * 100 + dd;
}

int todayNum(void) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return (tm->tm_year + 1900) * 10000 + (tm->tm_mon + 1) * 100 + tm->tm_mday;
}

void readDate(const char *prompt, char *buf, int size) {
    while (1) {
        readLine(prompt, buf, size);
        if (dateToNum(buf) != -1) return;
        printf("Invalid date. Use DD/MM/YYYY.\n");
    }
}

/* ------------------------- Security helpers ------------------------- */
/* Simple salted hash (username is the salt). Good enough for a class project;
   real systems should use bcrypt/argon2. */
unsigned long hashPassword(const char *user, const char *pass) {
    char tmp[100];
    snprintf(tmp, sizeof tmp, "%s:%s", user, pass);
    unsigned long h = 5381;
    for (const char *p = tmp; *p; p++) h = h * 33 + (unsigned char)*p;
    return h;
}

/* Audit log: records who did what and when (sensitive data needs accountability) */
void logAction(const char *fmt, ...) {
    char msg[200];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(msg, sizeof msg, fmt, ap);
    va_end(ap);

    FILE *f = fopen("audit.txt", "a");
    if (!f) return;
    time_t t = time(NULL);
    char ts[30];
    strftime(ts, sizeof ts, "%Y-%m-%d %H:%M:%S", localtime(&t));
    fprintf(f, "%s | %-12s | %s\n", ts, current ? current->username : "-", msg);
    fclose(f);
}

/* ------------------------- File storage ------------------------- */
void saveUsers(void) {
    FILE *f = fopen("users.txt", "w");
    if (!f) { printf("Error saving users!\n"); return; }
    for (int i = 0; i < userCount; i++)
        fprintf(f, "%s|%lu|%d|%d\n", users[i].username, users[i].hash, users[i].role, users[i].doctorId);
    fclose(f);
}

void saveMedicines(void) {
    FILE *f = fopen("medicines.txt", "w");
    if (!f) { printf("Error saving medicines!\n"); return; }
    for (int i = 0; i < medicineCount; i++)
        fprintf(f, "%d|%s|%.2f|%d|%s\n", medicines[i].id, medicines[i].name,
                medicines[i].price, medicines[i].quantity, medicines[i].expiry);
    fclose(f);
}

void savePatients(void) {
    FILE *f = fopen("patients.txt", "w");
    if (!f) { printf("Error saving patients!\n"); return; }
    for (int i = 0; i < patientCount; i++)
        fprintf(f, "%d|%s|%d|%s|%s\n", patients[i].id, patients[i].name, patients[i].age,
                patients[i].gender, patients[i].problem);
    fclose(f);
}

void saveDoctors(void) {
    FILE *f = fopen("doctors.txt", "w");
    if (!f) { printf("Error saving doctors!\n"); return; }
    for (int i = 0; i < doctorCount; i++)
        fprintf(f, "%d|%s|%s|%.2f\n", doctors[i].id, doctors[i].name, doctors[i].specialty, doctors[i].fee);
    fclose(f);
}

void saveAppts(void) {
    FILE *f = fopen("appointments.txt", "w");
    if (!f) { printf("Error saving appointments!\n"); return; }
    for (int i = 0; i < apptCount; i++)
        fprintf(f, "%d|%d|%d|%s|%d|%s\n", appts[i].id, appts[i].patientId, appts[i].doctorId,
                appts[i].date, appts[i].status, appts[i].notes);
    fclose(f);
}

void saveRx(void) {
    FILE *f = fopen("prescriptions.txt", "w");
    if (!f) { printf("Error saving prescriptions!\n"); return; }
    for (int i = 0; i < rxCount; i++)
        fprintf(f, "%d|%d|%d|%d|%d|%d\n", rxs[i].id, rxs[i].appointmentId, rxs[i].patientId,
                rxs[i].medicineId, rxs[i].quantity, rxs[i].dispensed);
    fclose(f);
}

void loadAll(void) {
    char line[300];
    FILE *f;

    if ((f = fopen("users.txt", "r"))) {
        while (userCount < MAX_USERS && fgets(line, sizeof line, f))
            if (sscanf(line, "%29[^|]|%lu|%d|%d", users[userCount].username, &users[userCount].hash,
                       &users[userCount].role, &users[userCount].doctorId) == 4) userCount++;
        fclose(f);
    }
    if ((f = fopen("medicines.txt", "r"))) {
        while (medicineCount < MAX_MED && fgets(line, sizeof line, f))
            if (sscanf(line, "%d|%49[^|]|%f|%d|%14[^\n]", &medicines[medicineCount].id,
                       medicines[medicineCount].name, &medicines[medicineCount].price,
                       &medicines[medicineCount].quantity, medicines[medicineCount].expiry) == 5) medicineCount++;
        fclose(f);
    }
    if ((f = fopen("patients.txt", "r"))) {
        while (patientCount < MAX_PAT && fgets(line, sizeof line, f))
            if (sscanf(line, "%d|%49[^|]|%d|%9[^|]|%79[^\n]", &patients[patientCount].id,
                       patients[patientCount].name, &patients[patientCount].age,
                       patients[patientCount].gender, patients[patientCount].problem) == 5) patientCount++;
        fclose(f);
    }
    if ((f = fopen("doctors.txt", "r"))) {
        while (doctorCount < MAX_DOC && fgets(line, sizeof line, f))
            if (sscanf(line, "%d|%49[^|]|%39[^|]|%f", &doctors[doctorCount].id, doctors[doctorCount].name,
                       doctors[doctorCount].specialty, &doctors[doctorCount].fee) == 4) doctorCount++;
        fclose(f);
    }
    if ((f = fopen("appointments.txt", "r"))) {
        while (apptCount < MAX_APPT && fgets(line, sizeof line, f))
            if (sscanf(line, "%d|%d|%d|%14[^|]|%d|%99[^\n]", &appts[apptCount].id, &appts[apptCount].patientId,
                       &appts[apptCount].doctorId, appts[apptCount].date, &appts[apptCount].status,
                       appts[apptCount].notes) == 6) apptCount++;
        fclose(f);
    }
    if ((f = fopen("prescriptions.txt", "r"))) {
        while (rxCount < MAX_RX && fgets(line, sizeof line, f))
            if (sscanf(line, "%d|%d|%d|%d|%d|%d", &rxs[rxCount].id, &rxs[rxCount].appointmentId,
                       &rxs[rxCount].patientId, &rxs[rxCount].medicineId, &rxs[rxCount].quantity,
                       &rxs[rxCount].dispensed) == 6) rxCount++;
        fclose(f);
    }
}

/* ------------------------- Lookup helpers ------------------------- */
/* Generates the next free ID: highest existing ID + 1 */
#define DEFINE_NEXT_ID(fn, arr, count) \
    int fn(void) { int m = 0; for (int i = 0; i < count; i++) if (arr[i].id > m) m = arr[i].id; return m + 1; }
DEFINE_NEXT_ID(nextPatientId, patients, patientCount)
DEFINE_NEXT_ID(nextDoctorId, doctors, doctorCount)
DEFINE_NEXT_ID(nextApptId, appts, apptCount)
DEFINE_NEXT_ID(nextRxId, rxs, rxCount)

int findMedicine(int id) { for (int i = 0; i < medicineCount; i++) if (medicines[i].id == id) return i; return -1; }
int findPatient(int id)  { for (int i = 0; i < patientCount; i++)  if (patients[i].id == id)  return i; return -1; }
int findDoctor(int id)   { for (int i = 0; i < doctorCount; i++)   if (doctors[i].id == id)   return i; return -1; }
int findAppt(int id)     { for (int i = 0; i < apptCount; i++)     if (appts[i].id == id)     return i; return -1; }
int findUser(const char *name) {
    for (int i = 0; i < userCount; i++) if (equalsIgnoreCase(users[i].username, name)) return i;
    return -1;
}

/* ========================= PHARMACY MODULE =========================
   (your original medicine store code, improved) */
void viewMedicines(void) {
    if (medicineCount == 0) { printf("No medicine in stock!\n"); return; }
    int today = todayNum();
    printf("\n%-5s %-24s %-9s %-6s %-12s\n", "ID", "Name", "Price", "Qty", "Expiry");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < medicineCount; i++) {
        int e = dateToNum(medicines[i].expiry);
        printf("%-5d %-24.24s %-9.2f %-6d %-12s%s\n", medicines[i].id, medicines[i].name,
               medicines[i].price, medicines[i].quantity, medicines[i].expiry,
               (e != -1 && e < today) ? " EXPIRED" : "");
    }
    printf("-----------------------------------------------------------\n");
}

void printMedicineRow(int i) {
    printf("%-5d %-24.24s %-9.2f %-6d %-12s\n", medicines[i].id, medicines[i].name,
           medicines[i].price, medicines[i].quantity, medicines[i].expiry);
}

void searchMedicine(void) {
    if (medicineCount == 0) { printf("No medicine in stock!\n"); return; }
    printf("\n--- Search Medicine ---\n1. By ID\n2. By Name\n");
    int choice = readInt("Enter choice: ", 1, 2);
    int found = 0;

    if (choice == 1) {
        int i = findMedicine(readInt("Enter Medicine ID: ", 1, 999999));
        if (i >= 0) { printMedicineRow(i); found = 1; }
    } else {
        char name[50];
        readLine("Enter name (or part of it): ", name, sizeof name);
        for (int i = 0; i < medicineCount; i++)
            if (containsIgnoreCase(medicines[i].name, name)) { printMedicineRow(i); found = 1; }
    }
    if (!found) printf("Medicine not found!\n");
}

void addMedicine(void) {
    if (medicineCount >= MAX_MED) { printf("Inventory is full!\n"); return; }
    Medicine m;
    while (1) {
        m.id = readInt("Enter Medicine ID: ", 1, 999999);
        if (findMedicine(m.id) >= 0) printf("Medicine ID already exists! Enter a unique ID.\n");
        else break;
    }
    readLine("Enter Medicine Name: ", m.name, sizeof m.name);
    m.price = readFloat("Enter Price: ", 0);
    m.quantity = readInt("Enter Quantity: ", 0, 100000);
    readDate("Enter Expiry Date (DD/MM/YYYY): ", m.expiry, sizeof m.expiry);

    medicines[medicineCount++] = m;
    saveMedicines();
    logAction("added medicine %d (%s)", m.id, m.name);
    printf("%s added to inventory successfully!\n", m.name);
}

void updateMedicine(void) {
    int i = findMedicine(readInt("Enter Medicine ID to update: ", 1, 999999));
    if (i < 0) { printf("Medicine not found.\n"); return; }

    printf("Current Name: %s\n", medicines[i].name);
    readLine("Enter new Name: ", medicines[i].name, sizeof medicines[i].name);
    printf("Current Price: %.2f\n", medicines[i].price);
    medicines[i].price = readFloat("Enter new Price: ", 0);
    printf("Current Quantity: %d\n", medicines[i].quantity);
    medicines[i].quantity = readInt("Enter new Quantity: ", 0, 100000);
    printf("Current Expiry: %s\n", medicines[i].expiry);
    readDate("Enter new Expiry (DD/MM/YYYY): ", medicines[i].expiry, sizeof medicines[i].expiry);

    saveMedicines();
    logAction("updated medicine %d", medicines[i].id);
    printf("Medicine updated successfully!\n");
}

void deleteMedicine(void) {
    if (medicineCount == 0) { printf("No medicine to delete!\n"); return; }
    viewMedicines();
    int id = readInt("\nEnter Medicine ID to delete: ", 1, 999999);
    int i = findMedicine(id);
    if (i < 0) { printf("Medicine with ID %d not found.\n", id); return; }

    for (int r = 0; r < rxCount; r++)   /* do not break pending prescriptions */
        if (rxs[r].medicineId == id && !rxs[r].dispensed) {
            printf("Cannot delete: it is used in a pending prescription.\n");
            return;
        }
    char msg[100];
    snprintf(msg, sizeof msg, "Are you sure you want to delete '%s'? (y/n): ", medicines[i].name);
    if (!confirm(msg)) { printf("Deletion cancelled.\n"); return; }

    for (int j = i; j < medicineCount - 1; j++) medicines[j] = medicines[j + 1];
    medicineCount--;
    saveMedicines();
    logAction("deleted medicine %d", id);
    printf("Medicine deleted successfully!\n");
}

void stockAlerts(void) {
    int count = 0, today = todayNum();
    printf("\n*** Stock Alerts ***\n");
    for (int i = 0; i < medicineCount; i++) {
        int e = dateToNum(medicines[i].expiry);
        if (medicines[i].quantity < LOW_STOCK) {
            printf("LOW STOCK: '%s' (ID %d) has %d unit(s) left.\n", medicines[i].name,
                   medicines[i].id, medicines[i].quantity);
            count++;
        }
        if (e != -1 && e < today) {
            printf("EXPIRED  : '%s' (ID %d) expired on %s.\n", medicines[i].name,
                   medicines[i].id, medicines[i].expiry);
            count++;
        }
    }
    if (count == 0) printf("No alerts. Stock looks fine.\n");
}

/* ========================= PATIENT MODULE ========================= */
void registerPatient(void) {
    if (patientCount >= MAX_PAT) { printf("Patient storage is full!\n"); return; }
    Patient p;
    p.id = nextPatientId();
    readLine("Patient name (use a dummy name): ", p.name, sizeof p.name);
    p.age = readInt("Age: ", 0, 120);
    readLine("Gender (M/F/Other): ", p.gender, sizeof p.gender);
    readLine("Reason for visit: ", p.problem, sizeof p.problem);

    patients[patientCount++] = p;
    savePatients();
    logAction("registered patient %d", p.id);
    printf("Patient registered with ID %d.\n", p.id);
}

void viewPatients(void) {
    if (patientCount == 0) { printf("No patients registered.\n"); return; }
    printf("\n%-5s %-24s %-5s %-8s %-30s\n", "ID", "Name", "Age", "Gender", "Reason for visit");
    printf("------------------------------------------------------------------------\n");
    for (int i = 0; i < patientCount; i++)
        printf("%-5d %-24.24s %-5d %-8s %-30.30s\n", patients[i].id, patients[i].name,
               patients[i].age, patients[i].gender, patients[i].problem);
}

void searchPatient(void) {
    char key[50];
    readLine("Enter patient name (or part of it): ", key, sizeof key);
    int found = 0;
    for (int i = 0; i < patientCount; i++)
        if (containsIgnoreCase(patients[i].name, key)) {
            printf("ID %d | %s | age %d | %s | %s\n", patients[i].id, patients[i].name,
                   patients[i].age, patients[i].gender, patients[i].problem);
            found = 1;
        }
    if (!found) printf("No matching patient.\n");
}

void showPatientHistory(void) {
    int id = readInt("Patient ID: ", 1, 999999);
    int p = findPatient(id);
    if (p < 0) { printf("Patient not found!\n"); return; }

    printf("\nPatient #%d: %s, age %d, %s\nReason for visit: %s\n", id, patients[p].name,
           patients[p].age, patients[p].gender, patients[p].problem);

    printf("\nAppointments:\n");
    int n = 0;
    for (int i = 0; i < apptCount; i++)
        if (appts[i].patientId == id) {
            int d = findDoctor(appts[i].doctorId);
            printf("  #%d  %s  Dr. %s  [%s]\n      Notes: %s\n", appts[i].id, appts[i].date,
                   d >= 0 ? doctors[d].name : "(unknown)", statusNames[appts[i].status], appts[i].notes);
            n++;
        }
    if (!n) printf("  none\n");

    printf("\nPrescriptions:\n");
    n = 0;
    for (int i = 0; i < rxCount; i++)
        if (rxs[i].patientId == id) {
            int m = findMedicine(rxs[i].medicineId);
            printf("  #%d  %s x%d  [%s]\n", rxs[i].id, m >= 0 ? medicines[m].name : "(deleted medicine)",
                   rxs[i].quantity, rxs[i].dispensed ? "Dispensed" : "Pending");
            n++;
        }
    if (!n) printf("  none\n");
    logAction("viewed history of patient %d", id);
}

/* ========================= DOCTOR MODULE ========================= */
void addDoctor(void) {
    if (doctorCount >= MAX_DOC) { printf("Doctor storage is full!\n"); return; }
    Doctor d;
    d.id = nextDoctorId();
    readLine("Doctor name: ", d.name, sizeof d.name);
    readLine("Specialty: ", d.specialty, sizeof d.specialty);
    d.fee = readFloat("Consultation fee: ", 0);

    doctors[doctorCount++] = d;
    saveDoctors();
    logAction("added doctor %d", d.id);
    printf("Doctor added with ID %d.\n", d.id);
}

void viewDoctors(void) {
    if (doctorCount == 0) { printf("No doctors added yet.\n"); return; }
    printf("\n%-5s %-24s %-20s %-8s\n", "ID", "Name", "Specialty", "Fee");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < doctorCount; i++)
        printf("%-5d %-24.24s %-20.20s %-8.2f\n", doctors[i].id, doctors[i].name,
               doctors[i].specialty, doctors[i].fee);
}

/* ========================= PRESCRIPTION MODULE ========================= */
/* Doctor picks medicines from the pharmacy inventory for appointment index a */
void prescribeLoop(int a) {
    viewMedicines();
    int added = 0;
    while (1) {
        int mid = readInt("Medicine ID to prescribe (0 = finish): ", 0, 999999);
        if (mid == 0) break;
        int m = findMedicine(mid);
        if (m < 0) { printf("Medicine not found!\n"); continue; }
        if (rxCount >= MAX_RX) { printf("Prescription storage is full!\n"); break; }
        int qty = readInt("Quantity: ", 1, 1000);
        if (qty > medicines[m].quantity)
            printf("Warning: only %d in stock. The pharmacist may not be able to dispense all.\n",
                   medicines[m].quantity);

        Prescription p;
        p.id = nextRxId();
        p.appointmentId = appts[a].id;
        p.patientId = appts[a].patientId;
        p.medicineId = mid;
        p.quantity = qty;
        p.dispensed = 0;
        rxs[rxCount++] = p;
        added++;
        printf("Added %d x %s.\n", qty, medicines[m].name);
    }
    if (added) {
        saveRx();
        logAction("prescribed %d item(s) for appointment %d", added, appts[a].id);
    }
}

void viewPendingPrescriptions(void) {
    int n = 0;
    printf("\n%-5s %-20s %-24s %-5s %-6s\n", "Rx", "Patient", "Medicine", "Qty", "Stock");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < rxCount; i++) {
        if (rxs[i].dispensed) continue;
        int p = findPatient(rxs[i].patientId), m = findMedicine(rxs[i].medicineId);
        printf("%-5d %-20.20s %-24.24s %-5d %-6d\n", rxs[i].id, p >= 0 ? patients[p].name : "?",
               m >= 0 ? medicines[m].name : "(deleted)", rxs[i].quantity, m >= 0 ? medicines[m].quantity : 0);
        n++;
    }
    if (!n) printf("No pending prescriptions.\n");
}

/* ========================= APPOINTMENT MODULE ========================= */
void bookAppointment(void) {
    if (apptCount >= MAX_APPT) { printf("Appointment storage is full!\n"); return; }
    if (patientCount == 0 || doctorCount == 0) { printf("Register a patient and add a doctor first.\n"); return; }

    Appointment a;
    viewPatients();
    while (1) {
        a.patientId = readInt("Patient ID: ", 1, 999999);
        if (findPatient(a.patientId) >= 0) break;
        printf("Patient not found.\n");
    }
    viewDoctors();
    while (1) {
        a.doctorId = readInt("Doctor ID: ", 1, 999999);
        if (findDoctor(a.doctorId) >= 0) break;
        printf("Doctor not found.\n");
    }
    while (1) {
        readDate("Appointment date (DD/MM/YYYY): ", a.date, sizeof a.date);
        if (dateToNum(a.date) < todayNum()) { printf("Date cannot be in the past.\n"); continue; }
        int dup = 0;
        for (int i = 0; i < apptCount; i++)
            if (appts[i].patientId == a.patientId && appts[i].doctorId == a.doctorId &&
                appts[i].status == ST_SCHEDULED && strcmp(appts[i].date, a.date) == 0) dup = 1;
        if (dup) { printf("This patient already has that appointment.\n"); continue; }
        break;
    }
    a.id = nextApptId();
    a.status = ST_SCHEDULED;
    strcpy(a.notes, "-");
    appts[apptCount++] = a;
    saveAppts();
    logAction("booked appointment %d", a.id);
    printf("Appointment booked with ID %d.\n", a.id);
}

void viewAppointments(int doctorId) {   /* doctorId 0 = show everyone's */
    int shown = 0;
    for (int i = 0; i < apptCount; i++) {
        if (doctorId && appts[i].doctorId != doctorId) continue;
        if (!shown) {
            printf("\n%-5s %-20s %-20s %-12s %-10s\n", "ID", "Patient", "Doctor", "Date", "Status");
            printf("----------------------------------------------------------------------\n");
        }
        int p = findPatient(appts[i].patientId), d = findDoctor(appts[i].doctorId);
        printf("%-5d %-20.20s %-20.20s %-12s %-10s\n", appts[i].id, p >= 0 ? patients[p].name : "?",
               d >= 0 ? doctors[d].name : "?", appts[i].date, statusNames[appts[i].status]);
        shown++;
    }
    if (!shown) printf("No appointments found.\n");
}

void cancelAppointment(void) {
    viewAppointments(0);
    int a = findAppt(readInt("Appointment ID to cancel (0 = back): ", 0, 999999));
    if (a < 0 || appts[a].status != ST_SCHEDULED) { printf("Only scheduled appointments can be cancelled.\n"); return; }
    appts[a].status = ST_CANCELLED;
    saveAppts();
    logAction("cancelled appointment %d", appts[a].id);
    printf("Appointment cancelled.\n");
}

void completeAppointment(int doctorId) {
    viewAppointments(doctorId);
    int id = readInt("Appointment ID to complete (0 = back): ", 0, 999999);
    if (id == 0) return;
    int a = findAppt(id);
    if (a < 0 || appts[a].doctorId != doctorId || appts[a].status != ST_SCHEDULED) {
        printf("That is not one of your scheduled appointments.\n");
        return;
    }
    readLine("Diagnosis / notes: ", appts[a].notes, sizeof appts[a].notes);
    appts[a].status = ST_COMPLETED;
    saveAppts();
    logAction("completed appointment %d", id);
    printf("Appointment completed.\n");
    if (confirm("Add a prescription now? (y/n): ")) prescribeLoop(a);
}

void prescribeForCompleted(int doctorId) {
    viewAppointments(doctorId);
    int a = findAppt(readInt("Completed appointment ID (0 = back): ", 0, 999999));
    if (a < 0 || appts[a].doctorId != doctorId || appts[a].status != ST_COMPLETED) {
        printf("Choose one of your completed, not-yet-billed appointments.\n");
        return;
    }
    prescribeLoop(a);
}

/* ========================= BILLING MODULE ========================= */
int nextBillId(void) {
    int n = 0;
    char line[200];
    FILE *f = fopen("bills.txt", "r");
    if (f) { while (fgets(line, sizeof line, f)) n++; fclose(f); }
    return n + 1;
}

/* Prints to the screen (stdout) or to receipts.txt (a file) with the same code */
void printReceipt(FILE *out, int billId, int p, const int *incl, float consult, float meds,
                  float tax, float total) {
    int pid = patients[p].id;
    fprintf(out, "\n===== MediTrack Receipt #%d =====\n", billId);
    fprintf(out, "Patient: %s (ID %d)\n", patients[p].name, pid);
    fprintf(out, "%-28s %-8s %-4s %-9s\n", "Item", "Price", "Qty", "Total");
    fprintf(out, "-----------------------------------------------------\n");

    for (int i = 0; i < apptCount; i++)
        if (appts[i].patientId == pid && appts[i].status == ST_COMPLETED) {
            int d = findDoctor(appts[i].doctorId);
            char label[80];
            snprintf(label, sizeof label, "Consult: Dr. %s", d >= 0 ? doctors[d].name : "?");
            float fee = d >= 0 ? doctors[d].fee : 0;
            fprintf(out, "%-28.28s %-8.2f %-4d %-9.2f\n", label, fee, 1, fee);
        }
    for (int i = 0; i < rxCount; i++)
        if (incl[i]) {
            int m = findMedicine(rxs[i].medicineId);
            fprintf(out, "%-28.28s %-8.2f %-4d %-9.2f\n", medicines[m].name, medicines[m].price,
                    rxs[i].quantity, medicines[m].price * rxs[i].quantity);
        }
    fprintf(out, "-----------------------------------------------------\n");
    fprintf(out, "Consultation fees: %.2f\n", consult);
    fprintf(out, "Medicines        : %.2f\n", meds);
    fprintf(out, "Tax (%.0f%%)         : %.2f\n", TAX_RATE * 100, tax);
    fprintf(out, "Total Payable    : %.2f\n", total);
    fprintf(out, "=====================================================\n");
}

/* Bills consultation fees + pending prescriptions, then dispenses the medicines */
void billPatient(void) {
    int pid = readInt("Patient ID to bill: ", 1, 999999);
    int p = findPatient(pid);
    if (p < 0) { printf("Patient not found!\n"); return; }

    int incl[MAX_RX] = {0};          /* which prescriptions go on this bill */
    int tmpStock[MAX_MED];           /* temporary stock so we never oversell */
    for (int i = 0; i < medicineCount; i++) tmpStock[i] = medicines[i].quantity;
    int today = todayNum(), items = 0;
    float consult = 0, meds = 0;

    for (int i = 0; i < apptCount; i++)
        if (appts[i].patientId == pid && appts[i].status == ST_COMPLETED) {
            int d = findDoctor(appts[i].doctorId);
            if (d >= 0) consult += doctors[d].fee;
            items++;
        }
    for (int i = 0; i < rxCount; i++) {
        if (rxs[i].patientId != pid || rxs[i].dispensed) continue;
        int m = findMedicine(rxs[i].medicineId);
        if (m < 0) { printf("Rx #%d skipped: medicine no longer exists.\n", rxs[i].id); continue; }
        int e = dateToNum(medicines[m].expiry);
        if (e != -1 && e < today) { printf("Rx #%d skipped: %s is expired.\n", rxs[i].id, medicines[m].name); continue; }
        if (tmpStock[m] < rxs[i].quantity) {
            printf("Rx #%d skipped: not enough %s (need %d, have %d).\n", rxs[i].id,
                   medicines[m].name, rxs[i].quantity, tmpStock[m]);
            continue;
        }
        tmpStock[m] -= rxs[i].quantity;
        incl[i] = 1;
        meds += medicines[m].price * rxs[i].quantity;
        items++;
    }
    if (items == 0) { printf("Nothing to bill for this patient.\n"); return; }

    float subtotal = consult + meds, tax = subtotal * TAX_RATE, total = subtotal + tax;
    int billId = nextBillId();
    printReceipt(stdout, billId, p, incl, consult, meds, tax, total);

    float pay = readFloat("Enter payment amount (0 to cancel): ", 0);
    if (pay < total) { printf("Insufficient payment! Transaction cancelled, nothing was changed.\n"); return; }
    printf("Payment successful! Change: %.2f\n", pay - total);

    /* Payment confirmed: only now do we save the receipt and change stock */
    FILE *rf = fopen("receipts.txt", "a");
    if (rf) { printReceipt(rf, billId, p, incl, consult, meds, tax, total); fclose(rf); }

    for (int i = 0; i < rxCount; i++)
        if (incl[i]) {
            medicines[findMedicine(rxs[i].medicineId)].quantity -= rxs[i].quantity;
            rxs[i].dispensed = 1;
        }
    for (int i = 0; i < apptCount; i++)
        if (appts[i].patientId == pid && appts[i].status == ST_COMPLETED) appts[i].status = ST_BILLED;

    int t = todayNum();
    FILE *bf = fopen("bills.txt", "a");
    if (bf) {
        fprintf(bf, "%d|%d|%.2f|%.2f|%.2f|%.2f|%02d/%02d/%04d\n", billId, pid, consult, meds, tax,
                total, t % 100, (t / 100) % 100, t / 10000);
        fclose(bf);
    }
    saveMedicines(); saveRx(); saveAppts();
    logAction("billed patient %d, bill %d, total %.2f", pid, billId, total);
    stockAlerts();
}

void viewBills(void) {
    FILE *f = fopen("bills.txt", "r");
    if (!f) { printf("No bills found.\n"); return; }
    char line[200];
    int id, pid;
    float c, m, t, tot, revenue = 0;
    char date[15];
    printf("\n%-6s %-8s %-10s %-10s %-8s %-10s %-12s\n", "Bill", "Patient", "Consult", "Medicine", "Tax", "Total", "Date");
    printf("----------------------------------------------------------------------\n");
    while (fgets(line, sizeof line, f))
        if (sscanf(line, "%d|%d|%f|%f|%f|%f|%14s", &id, &pid, &c, &m, &t, &tot, date) == 7) {
            printf("%-6d %-8d %-10.2f %-10.2f %-8.2f %-10.2f %-12s\n", id, pid, c, m, t, tot, date);
            revenue += tot;
        }
    fclose(f);
    printf("----------------------------------------------------------------------\n");
    printf("Total revenue: %.2f\n", revenue);
}

/* ========================= USERS & LOGIN ========================= */
void readNewPassword(char *out, int size) {
    char again[40];
    while (1) {
        readLine("Password (min 6 characters): ", out, size);
        if (strlen(out) < 6) { printf("Too short.\n"); continue; }
        readLine("Confirm password: ", again, sizeof again);
        if (strcmp(out, again) == 0) return;
        printf("Passwords do not match.\n");
    }
}

void addUser(void) {
    if (userCount >= MAX_USERS) { printf("User limit reached!\n"); return; }
    User u;
    char pass[40];
    while (1) {
        readLine("New username: ", u.username, sizeof u.username);
        if (findUser(u.username) >= 0) printf("Username already exists.\n"); else break;
    }
    printf("1. Admin  2. Doctor  3. Pharmacist\n");
    u.role = readInt("Role: ", 1, 3);
    u.doctorId = 0;
    if (u.role == ROLE_DOCTOR) {
        if (doctorCount == 0) { printf("Add a doctor profile first.\n"); return; }
        viewDoctors();
        while (1) {
            u.doctorId = readInt("Link to doctor ID: ", 1, 999999);
            if (findDoctor(u.doctorId) >= 0) break;
            printf("Doctor not found.\n");
        }
    }
    readNewPassword(pass, sizeof pass);
    u.hash = hashPassword(u.username, pass);
    users[userCount++] = u;
    saveUsers();
    logAction("created user %s (%s)", u.username, roleNames[u.role]);
    printf("User created.\n");
}

void listUsers(void) {
    printf("\n%-20s %-12s %-10s\n", "Username", "Role", "Doctor ID");
    for (int i = 0; i < userCount; i++)
        printf("%-20s %-12s %-10d\n", users[i].username, roleNames[users[i].role], users[i].doctorId);
}

void changePassword(void) {
    char old[40], pass[40];
    readLine("Current password: ", old, sizeof old);
    if (hashPassword(current->username, old) != current->hash) { printf("Wrong password.\n"); return; }
    readNewPassword(pass, sizeof pass);
    current->hash = hashPassword(current->username, pass);
    saveUsers();
    logAction("changed own password");
    printf("Password changed.\n");
}

void viewAudit(void) {
    FILE *f = fopen("audit.txt", "r");
    if (!f) { printf("Audit log is empty.\n"); return; }
    char line[300];
    printf("\n--- Audit Log ---\n");
    while (fgets(line, sizeof line, f)) printf("%s", line);
    fclose(f);
}

int login(void) {
    for (int attempt = 0; attempt < 3; attempt++) {
        char name[30], pass[40];
        readLine("Username: ", name, sizeof name);
        readLine("Password: ", pass, sizeof pass);
        int u = findUser(name);
        if (u >= 0 && users[u].hash == hashPassword(users[u].username, pass)) {
            current = &users[u];
            printf("\nLogin successful! Welcome, %s (%s).\n", current->username, roleNames[current->role]);
            logAction("login");
            return 1;
        }
        printf("Invalid credentials (%d attempt(s) left).\n", 2 - attempt);
    }
    return 0;
}

/* First time the program runs there are no users, so we create the admin here
   instead of hard-coding a password in the source code. */
void firstRunSetup(void) {
    if (userCount > 0) return;
    char pass[40];
    printf("\nFirst run: create the administrator account.\n");
    readLine("Admin username: ", users[0].username, sizeof users[0].username);
    readNewPassword(pass, sizeof pass);
    users[0].hash = hashPassword(users[0].username, pass);
    users[0].role = ROLE_ADMIN;
    users[0].doctorId = 0;
    userCount = 1;
    saveUsers();
    printf("Admin account created.\n");
}

/* ========================= ROLE MENUS ========================= */
void adminMenu(void) {
    while (1) {
        printf("\n--- Admin Panel ---\n");
        printf(" 1. Register Patient       2. View Patients      3. Search Patient\n");
        printf(" 4. Add Doctor             5. View Doctors       6. Book Appointment\n");
        printf(" 7. View Appointments      8. Cancel Appointment 9. Patient History\n");
        printf("10. Add User              11. View Users        12. View Bills\n");
        printf("13. View Audit Log        14. Change Password   15. Logout\n");
        switch (readInt("Enter choice: ", 1, 15)) {
            case 1: registerPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: addDoctor(); break;
            case 5: viewDoctors(); break;
            case 6: bookAppointment(); break;
            case 7: viewAppointments(0); break;
            case 8: cancelAppointment(); break;
            case 9: showPatientHistory(); break;
            case 10: addUser(); break;
            case 11: listUsers(); break;
            case 12: viewBills(); break;
            case 13: viewAudit(); break;
            case 14: changePassword(); break;
            case 15: return;
        }
    }
}

void doctorMenu(void) {
    int doc = findDoctor(current->doctorId);
    if (doc < 0) { printf("Your account is not linked to a doctor profile. Ask the admin.\n"); return; }
    printf("Dr. %s (%s)\n", doctors[doc].name, doctors[doc].specialty);
    while (1) {
        printf("\n--- Doctor Panel ---\n");
        printf("1. My Appointments\n2. Complete Appointment (notes + prescription)\n");
        printf("3. Prescribe for Completed Appointment\n4. Patient History\n");
        printf("5. View Medicines\n6. Change Password\n7. Logout\n");
        switch (readInt("Enter choice: ", 1, 7)) {
            case 1: viewAppointments(current->doctorId); break;
            case 2: completeAppointment(current->doctorId); break;
            case 3: prescribeForCompleted(current->doctorId); break;
            case 4: showPatientHistory(); break;
            case 5: viewMedicines(); break;
            case 6: changePassword(); break;
            case 7: return;
        }
    }
}

void pharmacistMenu(void) {
    stockAlerts();
    while (1) {
        printf("\n--- Pharmacist Panel ---\n");
        printf(" 1. View Medicines          2. Search Medicine      3. Add Medicine\n");
        printf(" 4. Update Medicine         5. Delete Medicine      6. Stock Alerts\n");
        printf(" 7. Pending Prescriptions   8. Bill & Dispense      9. View Bills\n");
        printf("10. Change Password        11. Logout\n");
        switch (readInt("Enter choice: ", 1, 11)) {
            case 1: viewMedicines(); break;
            case 2: searchMedicine(); break;
            case 3: addMedicine(); break;
            case 4: updateMedicine(); break;
            case 5: deleteMedicine(); break;
            case 6: stockAlerts(); break;
            case 7: viewPendingPrescriptions(); break;
            case 8: billPatient(); break;
            case 9: viewBills(); break;
            case 10: changePassword(); break;
            case 11: return;
        }
    }
}

/* ========================= MAIN ========================= */
int main(void) {
    loadAll();
    printf("****************************************************\n");
    printf("*      MediTrack Integrated Healthcare System      *\n");
    printf("****************************************************\n");
    printf("Reminder: use dummy data only, never real patient details.\n");

    firstRunSetup();
    while (1) {
        printf("\n1. Login\n2. Exit\n");
        if (readInt("Enter choice: ", 1, 2) == 2) break;
        if (!login()) { printf("Too many failed attempts.\n"); continue; }

        switch (current->role) {
            case ROLE_ADMIN: adminMenu(); break;
            case ROLE_DOCTOR: doctorMenu(); break;
            case ROLE_PHARMACIST: pharmacistMenu(); break;
        }
        logAction("logout");
        current = NULL;
    }
    printf("Goodbye!\n");
    return 0;
}
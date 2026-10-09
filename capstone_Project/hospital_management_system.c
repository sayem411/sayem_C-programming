#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==========================================
// 1. DATA STRUCTURE DEFINITIONS
// ==========================================

// ১. রোগী
typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    int roomNumber;
    float billAmount;
} Patient;

// ২. ডাক্তার
typedef struct {
    int id;
    char name[50];
    char specialization[50];
    float fee;
} Doctor;

// ৩. অ্যাপয়েন্টমেন্ট
typedef struct {
    int appointmentId;
    int patientId;
    int doctorId;
    char date[15];
} Appointment;

// ৪. ফার্মেসি (ওষুধ)
typedef struct {
    int id;
    char name[50];
    float price;
    int stock;
} Medicine;

// ৫. স্টাফ
typedef struct {
    int id;
    char name[50];
    char role[30];
    float salary;
} Staff;

// ৬. ব্লাড ব্যাংক
typedef struct {
    char bloodGroup[10];
    int unitsAvailable;
} BloodBank;

// ৭. অ্যাম্বুলেন্স
typedef struct {
    int vehicleId;
    char driverName[50];
    char driverPhone[15];
    int isAvailable;
} Ambulance;

// ৮. ল্যাব টেস্ট
typedef struct {
    int testId;
    int patientId;
    char testName[50];
    float cost;
} LabTest;

// ৯. বেড ও ওয়ার্ড ম্যানেজমেন্ট (নতুন)
typedef struct {
    int bedId;
    char wardType[30]; // ICU, CCU, Cabin, General
    int isOccupied;    // 0 = Empty, 1 = Occupied
    int patientId;
} BedWard;

// ১০. হেলথ ইনস্যুরেন্স (নতুন)
typedef struct {
    int policyId;
    int patientId;
    char companyName[50];
    float discountPercent; // e.g. 20.0 for 20%
} Insurance;

// ১১. ভ্যাকসিনেশন ট্র্যাকার (নতুন)
typedef struct {
    int recordId;
    int patientId;
    char vaccineName[50];
    int doseNumber;
    char date[15];
} Vaccination;

// ১২. পেশেন্ট ফিডব্যাক (নতুন)
typedef struct {
    int feedbackId;
    int patientId;
    int rating; // 1 to 5
    char comments[100];
} Feedback;

// ==========================================
// 2. FUNCTION DECLARATIONS
// ==========================================
void clearBuffer();
int loginSystem();

// Existing Modules
void addPatient(); 
void displayPatients(); 
void searchPatient();
 void updatePatient(); 
 void dischargePatient();
void addDoctor();
 void displayDoctors(); 
void searchDoctorBySpecialization();
void bookAppointment(); 
void displayAppointments();
void addMedicine(); 
void displayMedicines(); 
void sellMedicine();
void addLabTest();
 void displayLabTests();
void addOrUpdateBlood();
 void displayBloodBank();
void addAmbulance();
 void displayAmbulances();
void bookAmbulance();
void addStaff();
 void displayStaff();

// New Modules
void addBed();
 void displayBeds(); 
 void assignBed();
void addInsurance();
 void displayInsurances();
void recordVaccination();
 void displayVaccinations();
void addFeedback(); 
void displayFeedbacks();

// Billing with Insurance Integration
void generateBill();

// ==========================================
// 3. MAIN FUNCTION & MENU SYSTEM
// ==========================================
int main() {
    int choice;

    if (loginSystem() == 0) {
        printf("\nAccess Denied! Exiting program...\n");
        return 0;
    }

    while (1) {
        printf("\n==================================================\n");
        printf("       SMART HOSPITAL MANAGEMENT SYSTEM           \n");
        printf("==================================================\n");
        printf("[ PATIENT & BED MANAGEMENT ]\n");
        printf(" 1. Add Patient              2. Display Patients\n");
        printf(" 3. Search Patient           4. Update Patient\n");
        printf(" 5. Discharge Patient        6. Manage Beds/Wards (ICU/Cabin)\n");
        printf("\n[ DOCTORS & APPOINTMENTS ]\n");
        printf(" 7. Add Doctor               8. Display Doctors\n");
        printf(" 9. Search Doctor by Dept    10. Book Appointment\n");
        printf("11. View Appointments\n");
        printf("\n[ PHARMACY & LAB DIAGNOSTICS ]\n");
        printf("12. Add Medicine Stock       13. View Pharmacy\n");
        printf("14. Sell Medicine            15. Add Lab Test\n");
        printf("16. View Lab Records\n");
        printf("\n[ EMERGENCY, BLOOD & STAFF ]\n");
        printf("17. Blood Bank Stock         18. Ambulance Service\n");
        printf("19. Hospital Staff List\n");
        printf("\n[ INSURANCES, VACCINE & FEEDBACK ]\n");
        printf("20. Add Patient Insurance    21. Record Vaccination\n");
        printf("22. Patient Feedback/Review  23. View Feedbacks\n");
        printf("\n[ BILLING & EXIT ]\n");
        printf("24. Generate Final Bill      25. Exit Application\n");
        printf("--------------------------------------------------\n");
        printf("Select Option (1-25): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
             addPatient(); 
             break;
            case 2:
             displayPatients(); 
             break;
            case 3:
             searchPatient();
              break;
            case 4:
             updatePatient();
              break;
            case 5: 
            dischargePatient();
             break;
            case 6: 
                printf("\n1. Add New Bed\n2. View Beds\n3. Assign Bed to Patient\nChoice: ");
                int bChoice; scanf("%d", &bChoice);
                if (bChoice == 1) 
                addBed();
                else if (bChoice == 2) 
                displayBeds();
                else if (bChoice == 3) 
                assignBed();
                break;
            case 7:
             addDoctor();
              break;
            case 8: 
            displayDoctors(); 
            break;
            case 9: 
            searchDoctorBySpecialization();
             break;
            case 10:
             bookAppointment(); 
             break;
            case 11: 
            displayAppointments();
             break;
            case 12:
             addMedicine();
              break;
            case 13: 
            displayMedicines(); 
            break;
            case 14: 
            sellMedicine(); 
            break;
            case 15:
             addLabTest();
              break;
            case 16:
             displayLabTests();
              break;
            case 17: 
                printf("\n1. Update Stock\n2. View Stock\nChoice: ");
                int blChoice; scanf("%d", &blChoice);
                if (blChoice == 1) 
                addOrUpdateBlood(); 
                else displayBloodBank();
                break;
            case 18: 
                printf("\n1. Register Ambulance\n2. View Ambulances\n3. Book Ambulance\nChoice: ");
                int ambChoice; 
                scanf("%d", &ambChoice);
                if (ambChoice == 1)
                 addAmbulance();
                else if (ambChoice == 2) 
                displayAmbulances();
                else if (ambChoice == 3) 
                bookAmbulance();
                break;
            case 19: 
                printf("\n1. Add Staff\n2. View Staff\nChoice: ");
                int stChoice; scanf("%d", &stChoice);
                if (stChoice == 1) addStaff(); else displayStaff();
                break;
            case 20:
             addInsurance();
              break;
            case 21: 
            recordVaccination();
             break;
            case 22: 
            addFeedback();
             break;
            case 23: 
            displayFeedbacks();
             break;
            case 24: 
            generateBill();
             break;
            case 25:
                printf("\nSaving Data & Closing System. Goodbye!\n");
                exit(0);
            default:
                printf("\nInvalid Selection! Please choose 1-25.\n");
        }
    }
    return 0;
}

// ==========================================
// 4. UTILITIES & LOGIN
// ==========================================
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int loginSystem() {
    char username[20], password[20];
    printf("\n=========================================\n");
    printf("         HOSPITAL SYSTEM LOGIN           \n");
    printf("=========================================\n");
    printf("Username: ");
     scanf("%s", username);
    printf("Password: ");
     scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        printf("\nLogin Successful!\n");
        return 1;
    } else {
        printf("\nInvalid Credentials!\n");
        return 0;
    }
}

// ==========================================
// 5. PATIENT MODULE
// ==========================================
void addPatient() {
    FILE *fp = fopen("patients.dat", "ab");
    if (!fp) return;
    Patient p;
    printf("\n--- Add Patient ---\n");
    printf("Patient ID: "); 
    scanf("%d", &p.id); 
    clearBuffer();
    printf("Name: ");
     fgets(p.name, sizeof(p.name), stdin); 
     p.name[strcspn(p.name, "\n")] = 0;
    printf("Age: "); 
    scanf("%d", &p.age);
     clearBuffer();
    printf("Gender: ");
     fgets(p.gender, sizeof(p.gender), stdin);
      p.gender[strcspn(p.gender, "\n")] = 0;
    printf("Disease: ");
     fgets(p.disease, sizeof(p.disease), stdin);
      p.disease[strcspn(p.disease, "\n")] = 0;
    printf("Room Number: "); scanf("%d", &p.roomNumber);
    p.billAmount = 0.0;

    fwrite(&p, sizeof(Patient), 1, fp);
    fclose(fp);
    printf("Patient record saved!\n");
}

void displayPatients() {
    FILE *fp = fopen("patients.dat", "rb");
    if (!fp) { printf("\nNo patient data found!\n"); return; }
    Patient p;
    printf("\n%-5s %-20s %-5s %-8s %-15s %-8s\n", "ID", "Name", "Age", "Gender", "Disease", "Room");
    printf("------------------------------------------------------------------\n");
    while (fread(&p, sizeof(Patient), 1, fp)) {
        printf("%-5d %-20s %-5d %-8s %-15s %-8d\n", p.id, p.name, p.age, p.gender, p.disease, p.roomNumber);
    }
    fclose(fp);
}

void searchPatient() {
    FILE *fp = fopen("patients.dat", "rb");
    if (!fp) return;
    int id, found = 0;
    Patient p;
    printf("Enter Patient ID: "); scanf("%d", &id);
    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == id) {
            printf("\nFound: %s | Age: %d | Room: %d | Disease: %s | Bill: $%.2f\n", 
                    p.name, p.age, p.roomNumber, p.disease, p.billAmount);
            found = 1; break;
        }
    }
    if (!found) printf("Patient not found.\n");
    fclose(fp);
}

void updatePatient() {
    FILE *fp = fopen("patients.dat", "rb+");
    if (!fp) return;
    int id, found = 0;
    Patient p;
    printf("Enter Patient ID to Update: "); 
    scanf("%d", &id);
    clearBuffer();
    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == id) {
            printf("Enter New Disease: ");
             fgets(p.disease, sizeof(p.disease), stdin); 
             p.disease[strcspn(p.disease, "\n")] = 0;
            printf("Enter New Room: ");
             scanf("%d", &p.roomNumber);
            fseek(fp, -sizeof(Patient), SEEK_CUR);
            fwrite(&p, sizeof(Patient), 1, fp);
            printf("Patient details updated!\n");
            found = 1; break;
        }
    }
    if (!found) printf("Patient ID not found.\n");
    fclose(fp);
}

void dischargePatient() {
    FILE *fp = fopen("patients.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp || !temp) return;
    int id, found = 0;
    Patient p;
    printf("Enter Patient ID to Discharge: "); 
    scanf("%d", &id);
    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == id) found = 1;
        else fwrite(&p, sizeof(Patient), 1, temp);
    }
    fclose(fp); fclose(temp);
    remove("patients.dat");
    rename("temp.dat", "patients.dat");
    if (found) printf("Patient Discharged successfully!\n");
    else printf("Patient not found.\n");
}

// ==========================================
// 6. BED & WARD MANAGEMENT MODULE (NEW)
// ==========================================
void addBed() {
    FILE *fp = fopen("beds.dat", "ab");
    BedWard b;
    printf("\n--- Add Bed/Ward Slot ---\n");
    printf("Bed ID: ");
     scanf("%d", &b.bedId);
      clearBuffer();
    printf("Ward Type (ICU / CCU / Cabin / General): "); 
    fgets(b.wardType, sizeof(b.wardType), stdin);
     b.wardType[strcspn(b.wardType, "\n")] = 0;
    b.isOccupied = 0;
    b.patientId = -1;

    fwrite(&b, sizeof(BedWard), 1, fp);
    fclose(fp);
    printf("Bed Slot Registered!\n");
}

void displayBeds() {
    FILE *fp = fopen("beds.dat", "rb");
    if (!fp) { printf("\nNo bed records found.\n"); return; }
    BedWard b;
    printf("\n%-10s %-15s %-12s %-12s\n", "Bed ID", "Ward Type", "Status", "Patient ID");
    printf("----------------------------------------------------\n");
    while (fread(&b, sizeof(BedWard), 1, fp)) {
        printf("%-10d %-15s %-12s %-12d\n", 
                b.bedId, b.wardType, b.isOccupied ? "Occupied" : "Free", b.patientId);
    }
    fclose(fp);
}

void assignBed() {
    FILE *fp = fopen("beds.dat", "rb+");
    if (!fp) return;
    int bedId, pId, found = 0;
    BedWard b;
    printf("Enter Bed ID to Assign: ");
     scanf("%d", &bedId);
    printf("Enter Patient ID: "); 
    scanf("%d", &pId);

    while (fread(&b, sizeof(BedWard), 1, fp)) {
        if (b.bedId == bedId) {
            found = 1;
            if (!b.isOccupied) {
                b.isOccupied = 1;
                b.patientId = pId;
                fseek(fp, -sizeof(BedWard), SEEK_CUR);
                fwrite(&b, sizeof(BedWard), 1, fp);
                printf("Bed %d successfully assigned to Patient %d!\n", bedId, pId);
            } else {
                printf("Bed %d is already occupied!\n", bedId);
            }
            break;
        }
    }
    if (!found) printf("Bed ID not found.\n");
    fclose(fp);
}

// ==========================================
// 7. INSURANCE MODULE (NEW)
// ==========================================
void addInsurance() {
    FILE *fp = fopen("insurance.dat", "ab");
    Insurance ins;
    printf("\n--- Register Patient Insurance ---\n");
    printf("Policy ID: ");
     scanf("%d", &ins.policyId);
    printf("Patient ID: "); 
    scanf("%d", &ins.patientId); 
    clearBuffer();
    printf("Insurance Company Name: "); 
    fgets(ins.companyName, sizeof(ins.companyName), stdin);
     ins.companyName[strcspn(ins.companyName, "\n")] = 0;
    printf("Discount Percentage (e.g. 15.0 for 15%%): "); 
    scanf("%f", &ins.discountPercent);

    fwrite(&ins, sizeof(Insurance), 1, fp);
    fclose(fp);
    printf("Insurance Policy Added Successfully!\n");
}

// ==========================================
// 8. VACCINATION MODULE (NEW)
// ==========================================
void recordVaccination() {
    FILE *fp = fopen("vaccine.dat", "ab");
    Vaccination v;
    printf("\n--- Record Patient Vaccination ---\n");
    printf("Record ID: "); scanf("%d", &v.recordId);
    printf("Patient ID: "); scanf("%d", &v.patientId); clearBuffer();
    printf("Vaccine Name (e.g. COVID-19 / HepB): "); 
    fgets(v.vaccineName, sizeof(v.vaccineName), stdin); 
    v.vaccineName[strcspn(v.vaccineName, "\n")] = 0;
    printf("Dose Number: "); 
    scanf("%d", &v.doseNumber);
     clearBuffer();
    printf("Date (DD/MM/YYYY): "); 
    fgets(v.date, sizeof(v.date), stdin); v.date[strcspn(v.date, "\n")] = 0;

    fwrite(&v, sizeof(Vaccination), 1, fp);
    fclose(fp);
    printf("Vaccination Record Saved!\n");
}

// ==========================================
// 9. FEEDBACK MODULE (NEW)
// ==========================================
void addFeedback() {
    FILE *fp = fopen("feedback.dat", "ab");
    Feedback f;
    printf("\n--- Patient Feedback System ---\n");
    printf("Feedback ID: "); scanf("%d", &f.feedbackId);
    printf("Patient ID: "); scanf("%d", &f.patientId);
    printf("Rating (1 to 5 Stars): "); scanf("%d", &f.rating); clearBuffer();
    printf("Comments/Suggestions: "); 
    fgets(f.comments, sizeof(f.comments), stdin); f.comments[strcspn(f.comments, "\n")] = 0;

    fwrite(&f, sizeof(Feedback), 1, fp);
    fclose(fp);
    printf("Thank you for your feedback!\n");
}

void displayFeedbacks() {
    FILE *fp = fopen("feedback.dat", "rb");
    if (!fp) { printf("\nNo feedback available.\n"); return; }
    Feedback f;
    printf("\n%-10s %-12s %-8s %-30s\n", "FB ID", "Patient ID", "Rating", "Comments");
    printf("--------------------------------------------------------------\n");
    while (fread(&f, sizeof(Feedback), 1, fp)) {
        printf("%-10d %-12d %-8d %-30s\n", f.feedbackId, f.patientId, f.rating, f.comments);
    }
    fclose(fp);
}

// ==========================================
// 10. DOCTOR, APPOINTMENT, PHARMACY & LAB (STANDARD)
// ==========================================
void addDoctor() {
    FILE *fp = fopen("doctors.dat", "ab");
    Doctor d;
    printf("\n--- Add Doctor ---\n");
    printf("Doctor ID: "); scanf("%d", &d.id); clearBuffer();
    printf("Name: "); fgets(d.name, sizeof(d.name), stdin); d.name[strcspn(d.name, "\n")] = 0;
    printf("Specialization: "); fgets(d.specialization, sizeof(d.specialization), stdin); d.specialization[strcspn(d.specialization, "\n")] = 0;
    printf("Fee: "); scanf("%f", &d.fee);
    fwrite(&d, sizeof(Doctor), 1, fp);
    fclose(fp);
    printf("Doctor registered!\n");
}

void displayDoctors() {
    FILE *fp = fopen("doctors.dat", "rb");
    if (!fp) return;
    Doctor d;
    printf("\n%-5s %-20s %-20s %-10s\n", "ID", "Name", "Specialization", "Fee");
    printf("--------------------------------------------------------------\n");
    while (fread(&d, sizeof(Doctor), 1, fp)) {
        printf("%-5d %-20s %-20s $%.2f\n", d.id, d.name, d.specialization, d.fee);
    }
    fclose(fp);
}

void searchDoctorBySpecialization() {
    FILE *fp = fopen("doctors.dat", "rb");
    if (!fp) return;
    char spec[50]; Doctor d; int found = 0; clearBuffer();
    printf("Enter Specialization: "); fgets(spec, sizeof(spec), stdin); spec[strcspn(spec, "\n")] = 0;
    while (fread(&d, sizeof(Doctor), 1, fp)) {
        if (strcasecmp(d.specialization, spec) == 0) {
            printf("ID: %d | Name: %s | Fee: $%.2f\n", d.id, d.name, d.fee);
            found = 1;
        }
    }
    if (!found) printf("No doctor found.\n");
    fclose(fp);
}

void bookAppointment() {
    FILE *fp = fopen("appointments.dat", "ab");
    Appointment app;
    printf("\nAppt ID: "); scanf("%d", &app.appointmentId);
    printf("Patient ID: "); scanf("%d", &app.patientId);
    printf("Doctor ID: "); scanf("%d", &app.doctorId); clearBuffer();
    printf("Date: "); fgets(app.date, sizeof(app.date), stdin); app.date[strcspn(app.date, "\n")] = 0;
    fwrite(&app, sizeof(Appointment), 1, fp);
    fclose(fp);
    printf("Appointment confirmed!\n");
}

void displayAppointments() {
    FILE *fp = fopen("appointments.dat", "rb");
    if (!fp) return;
    Appointment app;
    printf("\n%-10s %-12s %-12s %-15s\n", "Appt ID", "Patient ID", "Doctor ID", "Date");
    printf("-----------------------------------------------------\n");
    while (fread(&app, sizeof(Appointment), 1, fp)) {
        printf("%-10d %-12d %-12d %-15s\n", app.appointmentId, app.patientId, app.doctorId, app.date);
    }
    fclose(fp);
}

void addMedicine() {
    FILE *fp = fopen("medicine.dat", "ab");
    Medicine m;
    printf("\nMedicine ID: "); scanf("%d", &m.id); clearBuffer();
    printf("Name: "); fgets(m.name, sizeof(m.name), stdin); m.name[strcspn(m.name, "\n")] = 0;
    printf("Price: "); scanf("%f", &m.price);
    printf("Stock: "); scanf("%d", &m.stock);
    fwrite(&m, sizeof(Medicine), 1, fp);
    fclose(fp);
}

void displayMedicines() {
    FILE *fp = fopen("medicine.dat", "rb");
    if (!fp) return;
    Medicine m;
    printf("\n%-5s %-20s %-10s %-10s\n", "ID", "Name", "Price", "Stock");
    while (fread(&m, sizeof(Medicine), 1, fp)) {
        printf("%-5d %-20s $%-9.2f %-10d\n", m.id, m.name, m.price, m.stock);
    }
    fclose(fp);
}

void sellMedicine() {
    FILE *fp = fopen("medicine.dat", "rb+");
    if (!fp) return;
    int id, qty; Medicine m;
    printf("Medicine ID: "); scanf("%d", &id);
    printf("Quantity: "); scanf("%d", &qty);
    while (fread(&m, sizeof(Medicine), 1, fp)) {
        if (m.id == id && m.stock >= qty) {
            m.stock -= qty;
            fseek(fp, -sizeof(Medicine), SEEK_CUR);
            fwrite(&m, sizeof(Medicine), 1, fp);
            printf("Sold! Total: $%.2f\n", m.price * qty);
            break;
        }
    }
    fclose(fp);
}

void addLabTest() {
    FILE *fp = fopen("labtests.dat", "ab");
    LabTest lt;
    printf("\nTest ID: "); scanf("%d", &lt.testId);
    printf("Patient ID: "); scanf("%d", &lt.patientId); clearBuffer();
    printf("Test Name: "); fgets(lt.testName, sizeof(lt.testName), stdin); lt.testName[strcspn(lt.testName, "\n")] = 0;
    printf("Cost: "); scanf("%f", &lt.cost);
    fwrite(&lt, sizeof(LabTest), 1, fp);
    fclose(fp);
}

void displayLabTests() {
    FILE *fp = fopen("labtests.dat", "rb");
    if (!fp) return;
    LabTest lt;
    while (fread(&lt, sizeof(LabTest), 1, fp)) {
        printf("Test ID: %d | Patient ID: %d | Name: %s | Cost: $%.2f\n", lt.testId, lt.patientId, lt.testName, lt.cost);
    }
    fclose(fp);
}

void addOrUpdateBlood() {
    FILE *fp = fopen("bloodbank.dat", "rb+");
    if (!fp) fp = fopen("bloodbank.dat", "wb+");
    char bg[10]; int units, found = 0; BloodBank b; clearBuffer();
    printf("Blood Group: "); fgets(bg, sizeof(bg), stdin); bg[strcspn(bg, "\n")] = 0;
    printf("Units: "); scanf("%d", &units);
    while (fread(&b, sizeof(BloodBank), 1, fp)) {
        if (strcasecmp(b.bloodGroup, bg) == 0) {
            b.unitsAvailable += units;
            fseek(fp, -sizeof(BloodBank), SEEK_CUR);
            fwrite(&b, sizeof(BloodBank), 1, fp);
            found = 1; break;
        }
    }
    if (!found) { strcpy(b.bloodGroup, bg); b.unitsAvailable = units; fwrite(&b, sizeof(BloodBank), 1, fp); }
    fclose(fp);
}

void displayBloodBank() {
    FILE *fp = fopen("bloodbank.dat", "rb");
    if (!fp) return;
    BloodBank b;
    while (fread(&b, sizeof(BloodBank), 1, fp)) printf("Group: %s | Units: %d\n", b.bloodGroup, b.unitsAvailable);
    fclose(fp);
}

void addAmbulance() {
    FILE *fp = fopen("ambulance.dat", "ab");
    Ambulance a;
    printf("Vehicle ID: "); scanf("%d", &a.vehicleId); clearBuffer();
    printf("Driver: "); fgets(a.driverName, sizeof(a.driverName), stdin); a.driverName[strcspn(a.driverName, "\n")] = 0;
    printf("Phone: "); fgets(a.driverPhone, sizeof(a.driverPhone), stdin); a.driverPhone[strcspn(a.driverPhone, "\n")] = 0;
    a.isAvailable = 1;
    fwrite(&a, sizeof(Ambulance), 1, fp);
    fclose(fp);
}

void displayAmbulances() {
    FILE *fp = fopen("ambulance.dat", "rb");
    if (!fp) return;
    Ambulance a;
    while (fread(&a, sizeof(Ambulance), 1, fp)) {
        printf("Vehicle ID: %d | Driver: %s | Phone: %s | Status: %s\n", 
                a.vehicleId, a.driverName, a.driverPhone, a.isAvailable ? "Available" : "Booked");
    }
    fclose(fp);
}

void bookAmbulance() {
    FILE *fp = fopen("ambulance.dat", "rb+");
    if (!fp) return;
    int id; Ambulance a;
    printf("Vehicle ID: "); scanf("%d", &id);
    while (fread(&a, sizeof(Ambulance), 1, fp)) {
        if (a.vehicleId == id && a.isAvailable) {
            a.isAvailable = 0;
            fseek(fp, -sizeof(Ambulance), SEEK_CUR);
            fwrite(&a, sizeof(Ambulance), 1, fp);
            printf("Ambulance Booked!\n"); break;
        }
    }
    fclose(fp);
}

void addStaff() {
    FILE *fp = fopen("staff.dat", "ab");
    Staff s;
    printf("Staff ID: "); scanf("%d", &s.id); clearBuffer();
    printf("Name: "); fgets(s.name, sizeof(s.name), stdin); s.name[strcspn(s.name, "\n")] = 0;
    printf("Role: "); fgets(s.role, sizeof(s.role), stdin); s.role[strcspn(s.role, "\n")] = 0;
    printf("Salary: "); scanf("%f", &s.salary);
    fwrite(&s, sizeof(Staff), 1, fp);
    fclose(fp);
}

void displayStaff() {
    FILE *fp = fopen("staff.dat", "rb");
    if (!fp) return;
    Staff s;
    while (fread(&s, sizeof(Staff), 1, fp)) printf("ID: %d | Name: %s | Role: %s | Salary: $%.2f\n", s.id, s.name, s.role, s.salary);
    fclose(fp);
}

// ==========================================
// 11. ENHANCED BILLING WITH INSURANCE DISCOUNT
// ==========================================
void generateBill() {
    FILE *fp = fopen("patients.dat", "rb+");
    FILE *fIns = fopen("insurance.dat", "rb");
    if (!fp) return;

    int id, found = 0;
    Patient p;
    Insurance ins;
    float days, grossTotal, discount = 0.0, netTotal;

    printf("\nEnter Patient ID for Discharge Bill: "); scanf("%d", &id);

    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == id) {
            printf("Total days in hospital: "); scanf("%f", &days);
            grossTotal = (days * 50.0) + 100.0; // Base rate + daily room charge

            // চেক করা হচ্ছে রোগীর কোনো ইনস্যুরেন্স ডিসকাউন্ট আছে কিনা
            if (fIns) {
                while (fread(&ins, sizeof(Insurance), 1, fIns)) {
                    if (ins.patientId == id) {
                        discount = (grossTotal * ins.discountPercent) / 100.0;
                        printf("\nInsurance Found! Provider: %s (%.1f%% Discount Applied)\n", 
                                ins.companyName, ins.discountPercent);
                        break;
                    }
                }
            }

            netTotal = grossTotal - discount;
            p.billAmount = netTotal;

            fseek(fp, -sizeof(Patient), SEEK_CUR);
            fwrite(&p, sizeof(Patient), 1, fp);

            printf("\n==========================================\n");
            printf("         FINAL ITEMIZED INVOICE           \n");
            printf("==========================================\n");
            printf("Patient ID     : %d\n", p.id);
            printf("Patient Name   : %s\n", p.name);
            printf("Stay Duration  : %.0f days\n", days);
            printf("Gross Total    : $%.2f\n", grossTotal);
            printf("Insurance Disc : -$%.2f\n", discount);
            printf("------------------------------------------\n");
            printf("NET PAYABLE    : $%.2f\n", netTotal);
            printf("==========================================\n");
            found = 1; break;
        }
    }
    if (!found) printf("Patient ID not found!\n");
    fclose(fp);
    if (fIns) fclose(fIns);
}
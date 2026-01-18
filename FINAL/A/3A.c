#include <stdio.h>
#include <string.h>
 
// ========== Structure Definition [2 marks] ==========
// Nested structure: 1 mark | All members correct: 1 mark
typedef struct {
    int day, month, year, hour;         // Appointment details (24-hour format)
} Appointment;
 
typedef struct {
    int patientID;
    char name[50];
    int age;
    float bill;
    Appointment appt;                   // Nested structure
    char doctor[50];
} Patient;
 
// ========== Input/Display Functions [2 marks] ==========
 
// registerPatient [1 mark] - Validation for hospital hours (8-17)
void registerPatient(Patient *p) {
    printf("Enter ID: "); scanf("%d", &p->patientID);
    printf("Enter Name: "); scanf(" %[^\n]", p->name);
    printf("Enter Age: "); scanf("%d", &p->age);
    printf("Enter Bill: "); scanf("%f", &p->bill);
    printf("Enter Doctor: "); scanf(" %[^\n]", p->doctor);
 
    printf("Enter Appointment (day month year hour): ");
    scanf("%d %d %d %d", &p->appt.day, &p->appt.month, &p->appt.year, &p->appt.hour);
 
    while (p->appt.hour < 8 || p->appt.hour > 17) {     // Validation
        printf("Invalid! Hour must be 8-17: ");
        scanf("%d", &p->appt.hour);
    }
}
 
// displayPatientInfo [1 mark] - Pass by value
void displayPatientInfo(Patient p) {
    printf("\n--- Patient Info ---\n");
    printf("ID: %d | Name: %s | Age: %d\n", p.patientID, p.name, p.age);
    printf("Doctor: %s | Bill: %.2f\n", p.doctor, p.bill);
    printf("Appointment: %02d/%02d/%d at %02d:00\n",
           p.appt.day, p.appt.month, p.appt.year, p.appt.hour);
}
 
// ========== Processing Functions [2 marks] ==========
 
// calculateDiscount [1 mark] - Age-based discount
float calculateDiscount(Patient p) {
    if (p.age > 60) return p.bill * 0.20;           // 20% for seniors
    if (p.age < 12) return p.bill * 0.10;           // 10% for children
    return 0;
}
 
// findEarliestAppointment [1 mark] - Compare year, month, day, hour
Patient findEarliestAppointment(Patient patients[], int size) {
    int earliest = 0;
    for (int i = 1; i < size; i++) {
        Patient *e = &patients[earliest], *c = &patients[i];
        if (c->appt.year < e->appt.year ||
           (c->appt.year == e->appt.year && c->appt.month < e->appt.month) ||
           (c->appt.year == e->appt.year && c->appt.month == e->appt.month && c->appt.day < e->appt.day) ||
           (c->appt.year == e->appt.year && c->appt.month == e->appt.month && c->appt.day == e->appt.day && c->appt.hour < e->appt.hour))
            earliest = i;
    }
    return patients[earliest];
}
 
// ========== Modification Functions [2 marks] ==========
 
// updateBilling [1 mark] - Apply discount via pointer
void updateBilling(Patient *p) {
    float discount = calculateDiscount(*p);
    p->bill -= discount;
}
 
// rescheduleAppointment [1 mark] - Update via pointer
void rescheduleAppointment(Patient *p, int day, int month, int year, int hour) {
    p->appt.day = day;
    p->appt.month = month;
    p->appt.year = year;
    p->appt.hour = hour;
}
 
// ========== Main Function [2 marks] ==========
int main() {
    Patient patients[3] = {
        {101, "Ali Khan", 65, 5000, {15, 12, 2025, 10}, "Dr. Ahmed"},
        {102, "Sara", 8, 3000, {14, 12, 2025, 9}, "Dr. Fatima"},
        {103, "Omar", 30, 4000, {16, 12, 2025, 14}, "Dr. Hassan"}
    };
 
    // Display all patients
    for (int i = 0; i < 3; i++)
        displayPatientInfo(patients[i]);
 
    // Find earliest appointment
    Patient earliest = findEarliestAppointment(patients, 3);
    printf("\nEarliest Appointment: %s\n", earliest.name);
 
    // Apply discounts
    for (int i = 0; i < 3; i++)
        updateBilling(&patients[i]);
 
    printf("\n--- After Discounts ---\n");
    for (int i = 0; i < 3; i++)
        printf("%s: Bill = %.2f\n", patients[i].name, patients[i].bill);
 
    // Reschedule demonstration
    rescheduleAppointment(&patients[0], 20, 12, 2025, 11);
    printf("\nRescheduled %s to %02d/%02d/%d at %02d:00\n",
           patients[0].name, patients[0].appt.day, patients[0].appt.month,
           patients[0].appt.year, patients[0].appt.hour);
 
    return 0;
}

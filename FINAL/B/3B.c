#include <stdio.h>
#include <string.h>
 
// ========== Structure Definition [2 marks] ==========
// Nested structure: 1 mark | All members correct: 1 mark
typedef struct {
    int day, month, year, hour;         // Delivery details (24-hour format)
} Delivery;
 
typedef struct {
    int orderID;
    char customerName[50];
    int tableNumber;
    float totalAmount;
    Delivery deliv;                     // Nested structure
    char deliveryPerson[50];
} Order;
 
// ========== Input/Display Functions [2 marks] ==========
 
// recordOrder [1 mark] - Validation for restaurant hours (10-22)
void recordOrder(Order *o) {
    printf("Enter Order ID: "); scanf("%d", &o->orderID);
    printf("Enter Customer Name: "); scanf(" %[^\n]", o->customerName);
    printf("Enter Table Number: "); scanf("%d", &o->tableNumber);
    printf("Enter Total Amount: "); scanf("%f", &o->totalAmount);
    printf("Enter Delivery Person: "); scanf(" %[^\n]", o->deliveryPerson);
 
    printf("Enter Delivery (day month year hour): ");
    scanf("%d %d %d %d", &o->deliv.day, &o->deliv.month, &o->deliv.year, &o->deliv.hour);
 
    while (o->deliv.hour < 10 || o->deliv.hour > 22) {    // Validation
        printf("Invalid! Hour must be 10-22: ");
        scanf("%d", &o->deliv.hour);
    }
}
 
// displayOrderInfo [1 mark] - Pass by value
void displayOrderInfo(Order o) {
    printf("\n--- Order Info ---\n");
    printf("ID: %d | Customer: %s | Table: %d\n", o.orderID, o.customerName, o.tableNumber);
    printf("Delivery Person: %s | Amount: %.2f\n", o.deliveryPerson, o.totalAmount);
    printf("Delivery: %02d/%02d/%d at %02d:00\n",
           o.deliv.day, o.deliv.month, o.deliv.year, o.deliv.hour);
}
 
// ========== Processing Functions [2 marks] ==========
 
// calculateTip [1 mark] - Amount-based tip
float calculateTip(Order o) {
    if (o.totalAmount > 500) return o.totalAmount * 0.15;    // 15% for >500
    if (o.totalAmount > 200) return o.totalAmount * 0.10;    // 10% for >200
    return o.totalAmount * 0.05;                              // 5% otherwise
}
 
// findUrgentDelivery [1 mark] - Compare year, month, day, hour
Order findUrgentDelivery(Order orders[], int size) {
    int urgent = 0;
    for (int i = 1; i < size; i++) {
        Order *u = &orders[urgent], *c = &orders[i];
        if (c->deliv.year < u->deliv.year ||
           (c->deliv.year == u->deliv.year && c->deliv.month < u->deliv.month) ||
           (c->deliv.year == u->deliv.year && c->deliv.month == u->deliv.month && c->deliv.day < u->deliv.day) ||
           (c->deliv.year == u->deliv.year && c->deliv.month == u->deliv.month && c->deliv.day == u->deliv.day && c->deliv.hour < u->deliv.hour))
            urgent = i;
    }
    return orders[urgent];
}
 
// ========== Modification Functions [2 marks] ==========
 
// updateBilling [1 mark] - Apply tip via pointer
void updateBilling(Order *o) {
    float tip = calculateTip(*o);
    o->totalAmount += tip;                          // Add tip to total
}
 
// rescheduleDelivery [1 mark] - Update via pointer
void rescheduleDelivery(Order *o, int day, int month, int year, int hour) {
    o->deliv.day = day;
    o->deliv.month = month;
    o->deliv.year = year;
    o->deliv.hour = hour;
}
 
// ========== Main Function [2 marks] ==========
int main() {
    Order orders[3] = {
        {201, "Ali Khan", 5, 600, {15, 12, 2025, 14}, "Kamran"},
        {202, "Sara Ahmed", 3, 250, {14, 12, 2025, 12}, "Bilal"},
        {203, "Omar Farooq", 7, 150, {16, 12, 2025, 18}, "Hassan"}
    };
 
    // Display all orders
    for (int i = 0; i < 3; i++)
        displayOrderInfo(orders[i]);
 
    // Find urgent delivery
    Order urgent = findUrgentDelivery(orders, 3);
    printf("\nMost Urgent Delivery: Order %d for %s\n", urgent.orderID, urgent.customerName);
 
    // Apply tips
    for (int i = 0; i < 3; i++)
        updateBilling(&orders[i]);
 
    printf("\n--- After Adding Tips ---\n");
    for (int i = 0; i < 3; i++)
        printf("Order %d: Total = %.2f\n", orders[i].orderID, orders[i].totalAmount);
 
    // Reschedule demonstration
    rescheduleDelivery(&orders[0], 20, 12, 2025, 16);
    printf("\nRescheduled Order %d to %02d/%02d/%d at %02d:00\n",
           orders[0].orderID, orders[0].deliv.day, orders[0].deliv.month,
           orders[0].deliv.year, orders[0].deliv.hour);
 
    return 0;
}

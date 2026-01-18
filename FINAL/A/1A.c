#include <stdio.h>
 
// ========== PART (a): Recursive Function [3 marks] ==========
// Base case: 1 mark | Recursive logic with +2 units: 1 mark | Return total: 1 mark
int calculateMonthlyBill(int baseCost, int days, int currentUnits) {
    if (days == 0) {                    // Base case
        return 0;
    }
    // Current day cost + recursive call (consumption increases by 2 each day)
    return (currentUnits * baseCost) + calculateMonthlyBill(baseCost, days - 1, currentUnits + 2);
}
 
// ========== PART (b): Pointer Functions [5 marks] ==========
 
// swapPriority [1.5 marks] - Pointer dereferencing & swap
void swapPriority(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
// findMaxConsumer [1.5 marks] - Returns pointer to max element
int* findMaxConsumer(int arr[], int size) {
    int *maxPtr = &arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > *maxPtr) {
            maxPtr = &arr[i];
        }
    }
    return maxPtr;
}
 
// optimizePower [2 marks] - Two-pointer in-place reverse
void optimizePower(int arr[], int size) {
    int *left = arr;
    int *right = arr + size - 1;
    while (left < right) {
        int temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}
 
// ========== PART (c): Function Pointer System [4 marks] ==========
// typedef: 1 mark | Three billing functions: 1.5 marks | calculateBill: 1.5 marks
 
typedef int (*BillingFunc)(int units, int rate);    // Function pointer type
 
int residentialRate(int units, int rate) {
    return units * rate;                             // Standard rate
}
 
int commercialRate(int units, int rate) {
    return (int)(units * rate * 1.5);                // 1.5x multiplier
}
 
int industrialRate(int units, int rate) {
    return units * rate * 2;                         // 2x multiplier
}
 
int calculateBill(BillingFunc calcFunc, int units, int rate) {
    return calcFunc(units, rate);                    // Call via function pointer
}
 
// ========== PART (d): Main Function [3 marks] ==========
// Array declaration: 0.5 | Function calls: 1.5 | Output: 1 mark
int main() {
    int appliances[5] = {100, 250, 75, 300, 150};
    int baseCost = 5;
 
    // (a) Recursive bill calculation for 7 days starting at 10 units
    int totalBill = calculateMonthlyBill(baseCost, 7, 10);
    printf("Monthly Bill for 7 days: %d\n", totalBill);
 
    // (b) Pointer functions demonstration
    int *maxConsumer = findMaxConsumer(appliances, 5);
    printf("Max Consumer: %d watts\n", *maxConsumer);
 
    printf("Before swap: [0]=%d, [1]=%d\n", appliances[0], appliances[1]);
    swapPriority(&appliances[0], &appliances[1]);
    printf("After swap: [0]=%d, [1]=%d\n", appliances[0], appliances[1]);
 
    printf("Before optimize: ");
    for (int i = 0; i < 5; i++) printf("%d ", appliances[i]);
    optimizePower(appliances, 5);
    printf("\nAfter optimize: ");
    for (int i = 0; i < 5; i++) printf("%d ", appliances[i]);
 
    // (c) Function pointer demonstrations
    int units = 100, rate = 10;
    printf("\n\nResidential: %d", calculateBill(residentialRate, units, rate));
    printf("\nCommercial: %d", calculateBill(commercialRate, units, rate));
    printf("\nIndustrial: %d\n", calculateBill(industrialRate, units, rate));
 
    return 0;
}

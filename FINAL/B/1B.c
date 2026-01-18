#include <stdio.h>
 
// ========== PART (a): Recursive Function [3 marks] ==========
// Base case: 1 mark | Recursive logic with +3 units: 1 mark | Return total: 1 mark
int calculateTotalFine(int baseFine, int days, int currentFine) {
    if (days == 0) {                    // Base case
        return 0;
    }
    // Current day fine + recursive call (fine increases by 3 each day)
    return (currentFine * baseFine) + calculateTotalFine(baseFine, days - 1, currentFine + 3);
}
 
// ========== PART (b): Pointer Functions [5 marks] ==========
 
// swapPosition [1.5 marks] - Pointer dereferencing & swap
void swapPosition(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
// findOldestBook [1.5 marks] - Returns pointer to minimum (oldest year)
int* findOldestBook(int years[], int size) {
    int *oldestPtr = &years[0];
    for (int i = 1; i < size; i++) {
        if (years[i] < *oldestPtr) {            // Older = smaller year
            oldestPtr = &years[i];
        }
    }
    return oldestPtr;
}
 
// reorganizeShelf [2 marks] - Two-pointer in-place reverse
void reorganizeShelf(int bookIDs[], int size) {
    int *left = bookIDs;
    int *right = bookIDs + size - 1;
    while (left < right) {
        int temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}
 
// ========== PART (c): Function Pointer System [4 marks] ==========
// typedef: 1 mark | Three membership functions: 1.5 marks | calculateMembershipFee: 1.5 marks
 
typedef int (*MembershipFunc)(int months, int baseFee);    // Function pointer type
 
int studentMembership(int months, int baseFee) {
    return (int)(months * baseFee * 0.5);           // 50% discount for students
}
 
int regularMembership(int months, int baseFee) {
    return months * baseFee;                         // Standard rate
}
 
int premiumMembership(int months, int baseFee) {
    return (int)(months * baseFee * 1.5);           // 1.5x for premium
}
 
int calculateMembershipFee(MembershipFunc calcFunc, int months, int baseFee) {
    return calcFunc(months, baseFee);               // Call via function pointer
}
 
// ========== PART (d): Main Function [3 marks] ==========
// Array declaration: 0.5 | Function calls: 1.5 | Output: 1 mark
int main() {
    int publicationYears[5] = {2010, 1995, 2020, 1988, 2015};
    int bookIDs[5] = {101, 102, 103, 104, 105};
    int baseFine = 2;
 
    // (a) Recursive fine calculation for 10 days starting at 5 units
    int totalFine = calculateTotalFine(baseFine, 10, 5);
    printf("Total Fine for 10 days: %d\n", totalFine);
 
    // (b) Pointer functions demonstration
    int *oldestBook = findOldestBook(publicationYears, 5);
    printf("Oldest Book Year: %d\n", *oldestBook);
 
    printf("Before swap: ID[0]=%d, ID[1]=%d\n", bookIDs[0], bookIDs[1]);
    swapPosition(&bookIDs[0], &bookIDs[1]);
    printf("After swap: ID[0]=%d, ID[1]=%d\n", bookIDs[0], bookIDs[1]);
 
    printf("Before reorganize: ");
    for (int i = 0; i < 5; i++) printf("%d ", bookIDs[i]);
    reorganizeShelf(bookIDs, 5);
    printf("\nAfter reorganize: ");
    for (int i = 0; i < 5; i++) printf("%d ", bookIDs[i]);
 
    // (c) Function pointer demonstrations
    int months = 12, baseFee = 100;
    printf("\n\nStudent Fee: %d", calculateMembershipFee(studentMembership, months, baseFee));
    printf("\nRegular Fee: %d", calculateMembershipFee(regularMembership, months, baseFee));
    printf("\nPremium Fee: %d\n", calculateMembershipFee(premiumMembership, months, baseFee));
 
    return 0;
}

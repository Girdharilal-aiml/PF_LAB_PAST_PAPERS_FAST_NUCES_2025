#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
#define MAX_STUDENTS 30
#define MAX_NAME 50
#define COURSE_LEN 7
 
// ========== PART (a): 2D Array Management [2 marks] ==========
// fgets usage: 1 mark | Buffer overflow prevention: 1 mark
void inputRegistrations(char names[][MAX_NAME], char courses[][COURSE_LEN], int count) {
    for (int i = 0; i < count; i++) {
        printf("Enter student %d name: ", i + 1);
        fgets(names[i], MAX_NAME, stdin);           // Prevents buffer overflow
        names[i][strcspn(names[i], "\n")] = '\0';   // Remove newline
 
        printf("Enter course code: ");
        fgets(courses[i], COURSE_LEN, stdin);
        courses[i][strcspn(courses[i], "\n")] = '\0';
    }
}
 
// ========== PART (b): String Processing Functions [3 marks] ==========
 
// countStudentsInCourse [1 mark] - Using strcmp
int countStudentsInCourse(char courses[][COURSE_LEN], int count, const char *target) {
    int studentCount = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(courses[i], target) == 0) {      // strcmp returns 0 if equal
            studentCount++;
        }
    }
    return studentCount;
}
 
// validateCourseCode [1 mark] - Pattern: 3 letters + 3 digits
int validateCourseCode(const char *code) {
    if (strlen(code) != 6) return 0;
    for (int i = 0; i < 3; i++)
        if (!isalpha(code[i])) return 0;            // First 3 must be letters
    for (int i = 3; i < 6; i++)
        if (!isdigit(code[i])) return 0;            // Last 3 must be digits
    return 1;
}
 
// isPalindromeName [1 mark] - Case-insensitive, ignore spaces
int isPalindromeName(const char *name) {
    char clean[MAX_NAME];
    int j = 0;
    for (int i = 0; name[i]; i++) {
        if (name[i] != ' ')
            clean[j++] = tolower(name[i]);          // Remove spaces, lowercase
    }
    clean[j] = '\0';
 
    int len = strlen(clean);
    for (int i = 0; i < len / 2; i++) {
        if (clean[i] != clean[len - 1 - i])
            return 0;
    }
    return 1;
}
 
// ========== PART (c): String Manipulation [3 marks] ==========
 
// generateUsername [1.5 marks] - strncat with overflow prevention
void generateUsername(const char *first, const char *last, char *user, int maxLen) {
    user[0] = '\0';
    strncat(user, first, maxLen - 2);
    strncat(user, "_", 1);
    strncat(user, last, maxLen - strlen(user) - 1);
    for (int i = 0; user[i]; i++)
        user[i] = tolower(user[i]);                 // Convert to lowercase
}
 
// sortStudentNames [1.5 marks] - Bubble sort with strcmp
void sortStudentNames(char names[][MAX_NAME], int count) {
    char temp[MAX_NAME];
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(names[j], names[j + 1]) > 0) {
                strcpy(temp, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], temp);
            }
        }
    }
}
 
// ========== PART (d): Main Function [2 marks] ==========
int main() {
    char names[5][MAX_NAME] = {"John Smith", "Anna", "Bob Wilson", "Eve Davis", "Tom Brown"};
    char courses[5][COURSE_LEN] = {"CSE101", "MTH202", "CSE101", "PHY303", "CSE101"};
    char username[MAX_NAME];
 
    int count = countStudentsInCourse(courses, 5, "CSE101");
    printf("Students in CSE101: %d\n", count);
 
    generateUsername("John", "Smith", username, MAX_NAME);
    printf("Username: %s\n", username);
 
    sortStudentNames(names, 5);
    printf("\nSorted List:\n");
    for (int i = 0; i < 5; i++)
        printf("%d. %s\n", i + 1, names[i]);
 
    printf("\nPalindrome Check:\n");
    for (int i = 0; i < 5; i++)
        if (isPalindromeName(names[i]))
            printf("%s is palindrome\n", names[i]);
 
    return 0;
}

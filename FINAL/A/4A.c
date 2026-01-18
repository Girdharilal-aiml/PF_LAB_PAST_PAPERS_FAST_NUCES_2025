#include <stdio.h>
#include <stdlib.h>
 
// ========== Dynamic Array Creation [3 marks] ==========
 
// createGradeSheet [1.5 marks] - Allocate & initialize to -1
float* createGradeSheet(int n) {
    float *grades = (float*)malloc(n * sizeof(float));
    if (grades == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    for (int i = 0; i < n; i++)
        grades[i] = -1;                             // -1 = not graded
    return grades;
}
 
// createAttendanceMatrix [1.5 marks] - 2D dynamic allocation
int** createAttendanceMatrix(int students, int days) {
    int **matrix = (int**)malloc(students * sizeof(int*));
    if (matrix == NULL) return NULL;
 
    for (int i = 0; i < students; i++) {
        matrix[i] = (int*)malloc(days * sizeof(int));
        if (matrix[i] == NULL) return NULL;
        for (int j = 0; j < days; j++)
            matrix[i][j] = 0;                       // Initialize to 0
    }
    return matrix;
}
 
// ========== Memory Management [3 marks] ==========
 
// expandClass [1.5 marks] - Reallocate preserving data
float* expandClass(float *grades, int oldSize, int newSize) {
    float *newGrades = (float*)realloc(grades, newSize * sizeof(float));
    if (newGrades == NULL) {
        printf("Reallocation failed!\n");
        return grades;                              // Return original on failure
    }
    for (int i = oldSize; i < newSize; i++)
        newGrades[i] = -1;                          // Initialize new slots
    return newGrades;
}
 
// free2DAttendance [1.5 marks] - Free rows first, then row pointers
void free2DAttendance(int **matrix, int rows) {
    for (int i = 0; i < rows; i++)
        free(matrix[i]);                            // Free each row first
    free(matrix);                                   // Then free row pointers
}
 
// ========== Statistical Analysis [3 marks] ==========
 
// calculateStatistics [1.5 marks] - Exclude -1, use pointers for results
void calculateStatistics(float *grades, int size, float *avg, float *max, float *min) {
    float sum = 0;
    int count = 0;
    *max = -1; *min = 101;
 
    for (int i = 0; i < size; i++) {
        if (grades[i] != -1) {                      // Exclude ungraded
            sum += grades[i];
            count++;
            if (grades[i] > *max) *max = grades[i];
            if (grades[i] < *min) *min = grades[i];
        }
    }
    *avg = (count > 0) ? sum / count : 0;
}
 
// findPassingStudents [1.5 marks] - Dynamic array of indices
int* findPassingStudents(float *grades, int size, int *passCount) {
    *passCount = 0;
    for (int i = 0; i < size; i++)
        if (grades[i] >= 50) (*passCount)++;
 
    int *passing = (int*)malloc(*passCount * sizeof(int));
    if (passing == NULL) return NULL;
 
    int idx = 0;
    for (int i = 0; i < size; i++)
        if (grades[i] >= 50)
            passing[idx++] = i;
    return passing;
}
 
// ========== Grade Processing [3 marks] ==========
 
// inputGrades [1.5 marks] - Validation 0-100
void inputGrades(float *grades, int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter grade for student %d (0-100): ", i + 1);
        scanf("%f", &grades[i]);
        while (grades[i] < 0 || grades[i] > 100) {
            printf("Invalid! Enter 0-100: ");
            scanf("%f", &grades[i]);
        }
    }
}
 
// adjustGrades [1.5 marks] - Add 5 to grades below 40, max 100
void adjustGrades(float *grades, int size) {
    for (int i = 0; i < size; i++) {
        if (grades[i] != -1 && grades[i] < 40) {
            grades[i] += 5;
            if (grades[i] > 100) grades[i] = 100;
        }
    }
}
 
// ========== Main Function [3 marks] ==========
int main() {
    int initialSize = 20, expandedSize = 30, days = 30;
 
    // Allocate initial arrays
    float *grades = createGradeSheet(initialSize);
    int **attendance = createAttendanceMatrix(initialSize, days);
 
    if (grades == NULL || attendance == NULL) {
        printf("Allocation failed!\n");
        return 1;
    }
 
    // Simulate: Set grades for first 20 students
    for (int i = 0; i < initialSize; i++)
        grades[i] = 45 + (i % 50);                  // Sample grades
 
    // Expand class by 10 students
    grades = expandClass(grades, initialSize, expandedSize);
    printf("Class expanded from %d to %d students\n", initialSize, expandedSize);
 
    // Set grades for new students
    for (int i = initialSize; i < expandedSize; i++)
        grades[i] = 35 + (i % 40);
 
    // Calculate statistics
    float avg, max, min;
    calculateStatistics(grades, expandedSize, &avg, &max, &min);
    printf("\nStatistics: Avg=%.2f, Max=%.2f, Min=%.2f\n", avg, max, min);
 
    // Find passing students
    int passCount;
    int *passing = findPassingStudents(grades, expandedSize, &passCount);
    printf("\nPassing students (%d): ", passCount);
    for (int i = 0; i < passCount; i++)
        printf("%d ", passing[i]);
    printf("\n");
 
    // Apply grade curve
    printf("\nApplying grade curve...\n");
    adjustGrades(grades, expandedSize);
 
    // Recalculate after curve
    calculateStatistics(grades, expandedSize, &avg, &max, &min);
    printf("After curve: Avg=%.2f, Max=%.2f, Min=%.2f\n", avg, max, min);
 
    // Free all memory (reverse order)
    free(passing);
    free2DAttendance(attendance, initialSize);      // Use initial rows allocated
    free(grades);
 
    printf("\nAll memory freed successfully!\n");
    return 0;
}

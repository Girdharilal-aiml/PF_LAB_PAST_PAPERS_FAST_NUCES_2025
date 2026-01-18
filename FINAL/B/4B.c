#include <stdio.h>
#include <stdlib.h>
 
// ========== Dynamic Array Creation [3 marks] ==========
 
// createPerformanceSheet [1.5 marks] - Allocate & initialize to -1
float* createPerformanceSheet(int n) {
    float *ratings = (float*)malloc(n * sizeof(float));
    if (ratings == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    for (int i = 0; i < n; i++)
        ratings[i] = -1;                            // -1 = not evaluated
    return ratings;
}
 
// createProjectMatrix [1.5 marks] - 2D dynamic allocation
int** createProjectMatrix(int employees, int projects) {
    int **matrix = (int**)malloc(employees * sizeof(int*));
    if (matrix == NULL) return NULL;
 
    for (int i = 0; i < employees; i++) {
        matrix[i] = (int*)malloc(projects * sizeof(int));
        if (matrix[i] == NULL) return NULL;
        for (int j = 0; j < projects; j++)
            matrix[i][j] = 0;                       // Initialize to 0
    }
    return matrix;
}
 
// ========== Memory Management [3 marks] ==========
 
// expandTeam [1.5 marks] - Reallocate preserving data
float* expandTeam(float *ratings, int oldSize, int newSize) {
    float *newRatings = (float*)realloc(ratings, newSize * sizeof(float));
    if (newRatings == NULL) {
        printf("Reallocation failed!\n");
        return ratings;                             // Return original on failure
    }
    for (int i = oldSize; i < newSize; i++)
        newRatings[i] = -1;                         // Initialize new slots
    return newRatings;
}
 
// free2DProjects [1.5 marks] - Free rows first, then row pointers
void free2DProjects(int **matrix, int rows) {
    for (int i = 0; i < rows; i++)
        free(matrix[i]);                            // Free each row first
    free(matrix);                                   // Then free row pointers
}
 
// ========== Statistical Analysis [3 marks] ==========
 
// calculateMetrics [1.5 marks] - Exclude -1, use pointers for results
void calculateMetrics(float *ratings, int size, float *avg, float *highest, float *lowest) {
    float sum = 0;
    int count = 0;
    *highest = -1; *lowest = 101;
 
    for (int i = 0; i < size; i++) {
        if (ratings[i] != -1) {                     // Exclude unevaluated
            sum += ratings[i];
            count++;
            if (ratings[i] > *highest) *highest = ratings[i];
            if (ratings[i] < *lowest) *lowest = ratings[i];
        }
    }
    *avg = (count > 0) ? sum / count : 0;
}
 
// findTopPerformers [1.5 marks] - Dynamic array of indices (rating >= 75)
int* findTopPerformers(float *ratings, int size, int *topCount) {
    *topCount = 0;
    for (int i = 0; i < size; i++)
        if (ratings[i] >= 75) (*topCount)++;
 
    int *topPerformers = (int*)malloc(*topCount * sizeof(int));
    if (topPerformers == NULL) return NULL;
 
    int idx = 0;
    for (int i = 0; i < size; i++)
        if (ratings[i] >= 75)
            topPerformers[idx++] = i;
    return topPerformers;
}
 
// ========== Performance Processing [3 marks] ==========
 
// inputRatings [1.5 marks] - Validation 0-100
void inputRatings(float *ratings, int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter rating for employee %d (0-100): ", i + 1);
        scanf("%f", &ratings[i]);
        while (ratings[i] < 0 || ratings[i] > 100) {
            printf("Invalid! Enter 0-100: ");
            scanf("%f", &ratings[i]);
        }
    }
}
 
// adjustRatings [1.5 marks] - Add 10 to ratings below 50, max 100
void adjustRatings(float *ratings, int size) {
    for (int i = 0; i < size; i++) {
        if (ratings[i] != -1 && ratings[i] < 50) {
            ratings[i] += 10;
            if (ratings[i] > 100) ratings[i] = 100;
        }
    }
}
 
// ========== Main Function [3 marks] ==========
int main() {
    int initialSize = 15, expandedSize = 23, projects = 20;
 
    // Allocate initial arrays
    float *ratings = createPerformanceSheet(initialSize);
    int **projectMatrix = createProjectMatrix(initialSize, projects);
 
    if (ratings == NULL || projectMatrix == NULL) {
        printf("Allocation failed!\n");
        return 1;
    }
 
    // Simulate: Set ratings for first 15 employees
    for (int i = 0; i < initialSize; i++)
        ratings[i] = 55 + (i % 45);                 // Sample ratings
 
    // Expand team by 8 employees
    ratings = expandTeam(ratings, initialSize, expandedSize);
    printf("Team expanded from %d to %d employees\n", initialSize, expandedSize);
 
    // Set ratings for new employees
    for (int i = initialSize; i < expandedSize; i++)
        ratings[i] = 40 + (i % 50);
 
    // Calculate metrics
    float avg, highest, lowest;
    calculateMetrics(ratings, expandedSize, &avg, &highest, &lowest);
    printf("\nMetrics: Avg=%.2f, Highest=%.2f, Lowest=%.2f\n", avg, highest, lowest);
 
    // Find top performers
    int topCount;
    int *topPerformers = findTopPerformers(ratings, expandedSize, &topCount);
    printf("\nTop Performers (%d): ", topCount);
    for (int i = 0; i < topCount; i++)
        printf("%d ", topPerformers[i]);
    printf("\n");
 
    // Apply rating adjustments
    printf("\nApplying rating bonus...\n");
    adjustRatings(ratings, expandedSize);
 
    // Recalculate after adjustment
    calculateMetrics(ratings, expandedSize, &avg, &highest, &lowest);
    printf("After bonus: Avg=%.2f, Highest=%.2f, Lowest=%.2f\n", avg, highest, lowest);
 
    // Free all memory (reverse order)
    free(topPerformers);
    free2DProjects(projectMatrix, initialSize);     // Use initial rows allocated
    free(ratings);
 
    printf("\nAll memory freed successfully!\n");
    return 0;
}

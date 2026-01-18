#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
#define MAX_PLAYERS 25
#define MAX_NAME 50
#define TEAM_LEN 6
 
// ========== PART (a): 2D Array Management [2 marks] ==========
// fgets usage: 1 mark | Buffer overflow prevention: 1 mark
void inputPlayers(char names[][MAX_NAME], char teams[][TEAM_LEN], int count) {
    for (int i = 0; i < count; i++) {
        printf("Enter player %d name: ", i + 1);
        fgets(names[i], MAX_NAME, stdin);           // Prevents buffer overflow
        names[i][strcspn(names[i], "\n")] = '\0';   // Remove newline
 
        printf("Enter team code: ");
        fgets(teams[i], TEAM_LEN, stdin);
        teams[i][strcspn(teams[i], "\n")] = '\0';
    }
}
 
// ========== PART (b): String Processing Functions [3 marks] ==========
 
// countPlayersInTeam [1 mark] - Using strcmp
int countPlayersInTeam(char teams[][TEAM_LEN], int count, const char *target) {
    int playerCount = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(teams[i], target) == 0) {        // strcmp returns 0 if equal
            playerCount++;
        }
    }
    return playerCount;
}
 
// validateTeamCode [1 mark] - Pattern: 2 letters + 3 digits
int validateTeamCode(const char *code) {
    if (strlen(code) != 5) return 0;
    for (int i = 0; i < 2; i++)
        if (!isalpha(code[i])) return 0;            // First 2 must be letters
    for (int i = 2; i < 5; i++)
        if (!isdigit(code[i])) return 0;            // Last 3 must be digits
    return 1;
}
 
// isAnagramName [1 mark] - Character counting method
int isAnagramName(const char *name1, const char *name2) {
    int count[26] = {0};
 
    // Count characters from first name (ignore spaces, case-insensitive)
    for (int i = 0; name1[i]; i++) {
        if (name1[i] != ' ')
            count[tolower(name1[i]) - 'a']++;
    }
 
    // Subtract characters from second name
    for (int i = 0; name2[i]; i++) {
        if (name2[i] != ' ')
            count[tolower(name2[i]) - 'a']--;
    }
 
    // Check if all counts are zero
    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) return 0;
    }
    return 1;
}
 
// ========== PART (c): String Manipulation [3 marks] ==========
 
// generateJerseyName [1.5 marks] - strncat with overflow prevention, uppercase
void generateJerseyName(const char *first, const char *last, char *jersey, int maxLen) {
    jersey[0] = '\0';
    strncat(jersey, first, maxLen - 2);
    strncat(jersey, "-", 1);
    strncat(jersey, last, maxLen - strlen(jersey) - 1);
    for (int i = 0; jersey[i]; i++)
        jersey[i] = toupper(jersey[i]);             // Convert to uppercase
}
 
// sortPlayerNames [1.5 marks] - Bubble sort with strcmp
void sortPlayerNames(char names[][MAX_NAME], int count) {
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
    char names[5][MAX_NAME] = {"John Smith", "Mary Jane", "Bob Wilson", "Amy Ray", "Tom Brown"};
    char teams[5][TEAM_LEN] = {"TM001", "FB202", "TM001", "TM001", "FB202"};
    char jersey[MAX_NAME];
 
    int count = countPlayersInTeam(teams, 5, "TM001");
    printf("Players in TM001: %d\n", count);
 
    // Generate jersey names
    printf("\n=== Jersey Names ===\n");
    generateJerseyName("John", "Smith", jersey, MAX_NAME);
    printf("Jersey: %s\n", jersey);
 
    // Sort and display
    sortPlayerNames(names, 5);
    printf("\nSorted List:\n");
    for (int i = 0; i < 5; i++)
        printf("%d. %s\n", i + 1, names[i]);
 
    // Check for anagrams
    printf("\nAnagram Check:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (isAnagramName(names[i], names[j]))
                printf("%s and %s are anagrams\n", names[i], names[j]);
        }
    }
 
    return 0;
}

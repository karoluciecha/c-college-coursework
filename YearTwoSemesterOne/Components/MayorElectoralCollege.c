#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char countiesList[32][50] = {
    "Antrim",
    "Armagh",
    "Carlow",
    "Cavan",
    "Clare",
    "Cork",
    "Derry",
    "Donegal",
    "Down",
    "Dublin",
    "Fermanagh",
    "Galway",
    "Kerry",
    "Kildare",
    "Kilkenny",
    "Laois",
    "Leitrim",
    "Limerick",
    "Longford",
    "Louth",
    "Mayo",
    "Meath",
    "Monaghan",
    "Offaly",
    "Roscommon",
    "Sligo",
    "Tipperary",
    "Tyrone",
    "Waterford",
    "Westmeath",
    "Wexford",
    "Wicklow"
};

char candidatesList[50][50];

int countiesNuber, candidatesNumber, votesTable[32][100], electoralVotes[50], leader;

void getStringInput(const char* prompt, char* buffer, size_t bufferSize);

int getPositiveIntInput(const char* prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf_s("%d", &value) == 1) {
            if (value >= 0) break;
            {
                printf("Please enter a positive integer.\n");
                while (getchar() != '\n');
            }
        }
        else {
            printf("Invalid input. Please enter a valid integer.\n");
            while (getchar() != '\n');
        }
    }
    while (getchar() != '\n');
    return value;
}

void runMayorElectoralCollegeProgram() {

    countiesNuber = getPositiveIntInput("Please enter the number of participating counties: ");
    candidatesNumber = getPositiveIntInput("Please ener the number of participating candidates: ");

    for (int i = 0; i < candidatesNumber; i++) {
        char prompt[100];
        snprintf(prompt, sizeof(prompt), "Please enter the name of the %d. candidate: ", i + 1);
        getStringInput(prompt, candidatesList[i], 50);
    }

    for (int i = 0; i < countiesNuber; i++) {
        int votes = 0, candidateNumber = 0;
        printf("\nVotes for county %s:\n", countiesList[i]);
        for (int j = 0; j < candidatesNumber; j++) {
            char prompt[100];
            snprintf(prompt, sizeof(prompt), "\tPlease enter the number of votes for % s: ", candidatesList[j]);
            votesTable[i][j] = getPositiveIntInput(prompt);
            if (votes < votesTable[i][j]) {
                votes = votesTable[i][j];
                candidateNumber = j;
            }
        }
        printf("The winner in county %s is %s with %d votes!\n", countiesList[i], candidatesList[candidateNumber], votes);
        electoralVotes[candidateNumber]++;
    }

    printf("\n%-20s", "Candidate");
    for (int i = 0; i < countiesNuber; i++) {
        printf("%-15s", countiesList[i]);
    }
    printf("\n");

    for (int i = 0; i < candidatesNumber; i++) {
        printf("%-20s", candidatesList[i]);
        for (int j = 0; j < countiesNuber; j++) {
            printf("%-15d", votesTable[j][i]);
        }
        printf("\n");
    }

    for (int i = 0; i < candidatesNumber; i++) if (leader < electoralVotes[i]) leader = i;

    printf("The winner is %s with %d electoral votes!\n", candidatesList[leader], electoralVotes[leader]);
    system("pause");
    system("cls");
}
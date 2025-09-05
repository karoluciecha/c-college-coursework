#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define SIZE 3

void stringOperations();
void averageLess();
void matrixAdd();
void threeAverageFile();
void Instructions();
float Average(int num1, int num2, int num3);
void Display(float result);
static char buffer[100];
static int number;

void runArraysAndFilesProgram() {
    int choice = -1;

    do {
        printf("==== ARRAYS & FILES PROGRAM MENU ====\n");
        printf("1. Strings program\n");
        printf("2. 1D Arrays program\n");
        printf("3. 2D Arrays program\n");
        printf("4. Functions & File Access program\n");
        printf("0. Exit to Main Menu\n");
        printf("Enter your choice: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error while reading input. Please try again.\n");
        }
        else if (sscanf(buffer, "%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n\n");
            choice = -1;
        }
        else {
            switch (choice) {
                case 1:
                    stringOperations();
                    break;
                case 2:
                    averageLess();
                    break;
                case 3:
                    matrixAdd();
                    break;
                case 4:
                    threeAverageFile();
                    break;
                case 0:
                    printf("Exiting Arrays & Files Program...\n\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n\n");
                    break;
            }
        }
    } while (choice != 0);
}

// Function to perform various string operations
void stringOperations() {
    char stringOne[100], stringTwo[100];
    int charToLookFor;


    do {
        printf("Please enter the first string: ");
        fgets(stringOne, sizeof(stringOne), stdin);

        // Check if the input is just a newline character
        if (stringOne[0] == '\n') {
            printf("No input entered.\n");
        }
        else {
            if (strlen(stringOne) > 0 && stringOne[strlen(stringOne) - 1] == '\n') stringOne[strlen(stringOne) - 1] = '\0';
            printf("You entered: %s\n", stringOne);
            break;
        }
    } while (1);

    do {
        printf("Please enter the second string: ");
        fgets(stringTwo, sizeof(stringTwo), stdin);

        // Check if the input is just a newline character
        if (stringTwo[0] == '\n') {
            printf("No input entered.\n");
        }
        else {
            if (strlen(stringTwo) > 0 && stringTwo[strlen(stringTwo) - 1] == '\n') stringTwo[strlen(stringTwo) - 1] = '\0';
            printf("You entered: %s\n", stringTwo);
            break;
        }
    } while (1);

    do {
        printf("Enter the number of characters to compare: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error while reading input. Please try again.\n");
            return;
        }
        else if (sscanf(buffer, "%d", &charToLookFor) != 1) {
            printf("Invalid input. Please enter an integer.\n");
        }
        else {
            printf("You entered: %d\n", charToLookFor);
            break;
        }
    } while (1);

    // Display both strings & length
    printf("\nFirst string: \"%s\", length: %llu\n", stringOne, (unsigned long long)strlen(stringOne));
    printf("Second string: \"%s\", length: %llu\n", stringTwo, (unsigned long long)strlen(stringTwo));

    // Compare both strings & display the bigger string
    if (strcmp(stringOne, stringTwo) > 0) {
        printf("\nBigger string: %s\n", stringOne);
    }
    else if (strcmp(stringOne, stringTwo) < 0) {
        printf("\nBigger string: %s\n", stringTwo);
    }
    else {
        printf("\nBoth strings are equal.\n");
    }

    // Compare a number of characters of both strings & display the bigger sub-string
    if (strncmp(stringOne, stringTwo, charToLookFor) > 0) {
        printf("\nBigger substring (first %d chars): %.*s\n", charToLookFor, charToLookFor, stringOne);
    }
    else if (strncmp(stringOne, stringTwo, charToLookFor) < 0) {
        printf("\nBigger substring (first %d chars): %.*s\n", charToLookFor, charToLookFor, stringTwo);
    }
    else {
        printf("\nThe first %d characters of both strings are equal.\n", charToLookFor);
    }

    // Concatenate stringTwo to stringOne
    strcat(stringOne, stringTwo);
    printf("\nAfter concatenating stringTwo to stringOne:\n");
    printf("First string: %s\n", stringOne);
    printf("Second string: %s\n", stringTwo);

    // Concatenate the first three characters of stringTwo to stringOne
    strncat(stringOne, stringTwo, 3);
    printf("\nAfter concatenating first three characters of stringTwo to stringOne:\n");
    printf("First string: %s\n", stringOne);
    printf("Second string: %s\n", stringTwo);

    // Copy stringTwo to stringOne
    strcpy(stringOne, stringTwo);
    printf("\nAfter copying stringTwo to stringOne:\n");
    printf("First string: %s\n", stringOne);
    printf("Second string: %s\n", stringTwo);

    // Copy the first three characters of stringOne to stringTwo
    strncpy(stringTwo, stringOne, 3);
    stringTwo[3] = '\0'; // Null-terminate stringTwo
    printf("\nAfter copying first three characters of stringOne to stringTwo:\n");
    printf("First string: %s\n", stringOne);
    printf("Second string: %s\n\n\n", stringTwo);

    return;
}

// Function to calculate and display average and numbers less than average
void averageLess() {
    int numbers[20];
    int sum = 0;
    float average;

    // Reading 20 integers from the user
    printf("Enter 20 integers:\n");
    for (int i = 0; i < 20; i++) {
        do {
            printf("Number %d: ", i + 1);
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                printf("Error while reading input. Please try again.\n");
                return;
            }
            else if (sscanf(buffer, "%d", &numbers[i]) != 1) {
                printf("Invalid input. Please enter an integer.\n");
            }
            else {
                printf("You entered: %d\n", numbers[i]);
                sum += numbers[i];
                break;
            }
    } while (1);
    }

    // Average
    average = sum / 20.0f;
    printf("\nAverage of the numbers: %.2f\n", average);

    // Displaying numbers less than the average
    printf("Numbers less than the average:\n");
    for (int i = 0; i < 20; i++) {
        if (numbers[i] < average) {
            printf("%d ", numbers[i]);
        }
    }
    printf("\n\n\n");
    return;
}

// Function to add two 3x3 matrices
void matrixAdd() {
    int matrixOne[SIZE][SIZE];
    int matrixTwo[SIZE][SIZE];
    int result[SIZE][SIZE];

    // Input elements for the first matrix
    printf("Enter elements for the First matrix (%dx%d):\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            do {
                printf("Element [%d][%d]: ", i + 1, j + 1);
                if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                    printf("Error while reading input. Please try again.\n");
                    return;
                }
                else if (sscanf(buffer, "%d", &matrixOne[i][j]) != 1) {
                    printf("Invalid input. Please enter an integer.\n");
                }
                else {
                    printf("You entered: %d\n", matrixOne[i][j]);
                    break;
                }
            } while (1);
        }
    }

    // Input elements for the second matrix
    printf("Enter elements for the Second matrix (3x3):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            do {
                printf("Element [%d][%d]: ", i + 1, j + 1);
                if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                    printf("Error while reading input. Please try again.\n");
                    return;
                }
                else if (sscanf(buffer, "%d", &matrixTwo[i][j]) != 1) {
                    printf("Invalid input. Please enter an integer.\n");
                }
                else {
                    printf("You entered: %d\n", matrixTwo[i][j]);
                    break;
                }
            } while (1);
        }
    }

    // Add the two matrices
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = matrixOne[i][j] + matrixTwo[i][j];
        }
    }

    // Display the first matrix
    printf("\nFirst Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrixOne[i][j]);
        }
        printf("\n");
    }

    // Display the second matrix
    printf("\nSecond Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrixTwo[i][j]);
        }
        printf("\n");
    }

    // Display the result matrix
    printf("\nResult Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

    return;
}

// Function to calculate the average of three integers and write to a file
void threeAverageFile() {
    int numberOne, numberTwo, numberThree;
    float average;

    Instructions();

    // Taking in user input
    do {
     
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error while reading input. Please try again.\n");
            return;
        }
        else if (sscanf(buffer, "%d %d %d", &numberOne, &numberTwo, &numberThree) != 3) {
            printf("Invalid input.\nPlease enter exactly three integers: ");
        }
        else {
            printf("You entered: %d, %d, %d\n", numberOne, numberTwo, numberThree);
            break;
        }
    } while (1);

    average = Average(numberOne, numberTwo, numberThree);

    Display(average);

    return;

}

void Instructions() {
    // Printing out the instructions
    printf("\nThis program takes three integers as input and calculates their average.\n");
    printf("It will then display the average on the screen and write it to a file called threeAverageFileResult.txt.\n");
    printf("Please proceed by entering three integers separated by space: ");
    return;
}

float Average(int num1, int num2, int num3) {
    // Calculate and return
    return (num1 + num2 + num3) / 3.0;
}

void Display(float result) {
    // Dismplay the result
    printf("The average is: %.2f\n", result);

    // Write the result to a file
    FILE* file = fopen("ResourceFiles/threeAverageFileResult.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "The average is: %.2f.", result);
    fclose(file);
    printf("The result has been saved to threeAverageFileResult.txt.\n\n");
    return;
}
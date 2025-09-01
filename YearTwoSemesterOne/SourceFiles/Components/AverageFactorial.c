#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>

void average();
unsigned long long partTwo(int);
static char buffer[100];
static int number;

void runAverageFactorialProgram() {
    int choice = -1;
    int number;

    do {
        printf("==== AVERAGE & FACTORIAL MENU ====\n");
        printf("1. Average & Calculations program\n");
        printf("2. Factorial program\n");
        printf("0. Exit to Main Menu\n");
        printf("Enter your choice: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error while reading input. Please try again.\n\n");
            continue;
        }

        if (sscanf(buffer, "%d", &choice) != 1) {
            printf("Invalid choice. Please enter a number.\n\n");
            continue;
        }

        switch (choice) {
            case 1:
                average();
                break;

            case 2:
                do {
                    printf("\nEnter a positive integer to calculate the factorial: ");
                    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                        printf("Error while reading input. Please try again.\n");
                        continue;
                    }
                    if (sscanf(buffer, "%d", &number) != 1) {
                        printf("Invalid input. Please enter a number.\n");
                        continue;
                    }
                    if (number < 0) {
                        printf("Factorial of negative numbers does not exist. Please try again.\n");
                        continue;
                    }
                    printf("Factorial of %d is: %llu.\n\n", number, partTwo(number));
                    break;
                } while (1);
                break;

            case 0:
                printf("Exiting Average & Factorial Program...\n\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n\n");
                break;
        }
    } while (choice != 0);
}

void average() {

    int anotherNumber, sumNumbers = 0, smallestNumber = INT_MAX, largestNumber = INT_MIN, totalNumbers = 0;
    double averageNumbers = 0.0;
    do {
        printf("\nPlease enter an integer (-1 to exit): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error while reading input. Please try again.\n");
            return;
        }
        else if (sscanf(buffer, "%d", &anotherNumber) != 1) {
            printf("Invalid input. Please enter an integer.\n");
        }
        else if (anotherNumber == -1) {
            printf("Thank you. Calculating...\n");
            if(totalNumbers != 0) averageNumbers = sumNumbers / totalNumbers;
            printf("The total sum of the numbers entered: %d.\n", sumNumbers);
            printf("The average of the numbers entered: %.2lf.\n", averageNumbers);
            printf("The largest number is: %d and the smallest number is: %d.\n", largestNumber, smallestNumber);
            printf("The total number of valid integers entered is: %d.\n\n", totalNumbers);
            return;
        }
        else {
            printf("You entered: %d\n", anotherNumber);
            sumNumbers += anotherNumber;
            if (smallestNumber > anotherNumber) smallestNumber = anotherNumber;
            if (largestNumber < anotherNumber) largestNumber = anotherNumber;
            totalNumbers++;
        }
    } while (1);
}

unsigned long long partTwo(int number) {
    if (number == 0 || number == 1)
        return 1;
    else
        return (unsigned long long)number * partTwo(number - 1);
}

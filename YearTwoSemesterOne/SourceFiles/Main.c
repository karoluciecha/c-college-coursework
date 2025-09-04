#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayMainMenu();
void runVariablesIOProgram();
void runLightCalculationsProgram();
void runDayCalculatorProgram();
void runAverageFactorialProgram();
void runMonthlyPayrollProgram();
void runArraysAndFilesProgram();
void runStudendGradingSystemProgram();
void runEmployeeRecordsProgram();
void runMayorElectoralCollegeProgram();
void runMonthlySalesProgram();
double getDoubleInput(const char* prompt);
int getIntInput(const char* prompt);
void getStringInput(const char* prompt, char* buffer, size_t bufferSize);

int main() {
int choice;
printf("==== WELCOME TO THE C PROGRAM COLLECTION ====\n\n");

	do {
		displayMainMenu();
        scanf_s("%d", &choice);
		system("cls");

        // For input Clearing buffer
        while ((getchar()) != '\n');

		switch (choice) {
		case 1:
			runVariablesIOProgram();
			break;
		case 2:
            runLightCalculationsProgram();
			break;
		case 3:
            runDayCalculatorProgram();
			break;
		case 4:
            runAverageFactorialProgram();
			break;
		case 5:
            runMonthlyPayrollProgram();
			break;
        case 6:
            runArraysAndFilesProgram();
            break;
		case 7:
			runStudendGradingSystemProgram();
			break;
        case 8:
            runEmployeeRecordsProgram();
            break;
        case 9:
            runMayorElectoralCollegeProgram();
            break;
        case 10:
            runMonthlySalesProgram();
            break;
		case 0:
			printf("Program terminated.\n\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n\n");
			break;
		}
	} while (choice != 0);
	return 0;
}

void displayMainMenu() {
    printf("==== MAIN MENU ====\n\n");
    printf("1. Variables Input/Output\n");
    printf("2. Light Calculations\n");
    printf("3. Day Calculator\n");
    printf("4. Average & Factorial\n");
    printf("5. Monthly Payroll\n");
    printf("6. Arrays & Files\n");
	printf("7. Student Grading System\n");
    printf("8. Employee Records\n");
    printf("9. Mayor Electoral College System\n");
    printf("10. (Exam One) Monthly Sales System\n");
    printf("0. Exit\n");
    printf("\nSelect an option: ");
}

int getIntInput(const char* prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf_s("%d", &value) == 1) {
            break;
        }
        else {
            printf("Invalid input. Please enter a valid integer.\n");
            while (getchar() != '\n');
        }
    }
    while (getchar() != '\n');
    return value;
}

double getDoubleInput(const char* prompt) {
    double value;
    while (1) {
        printf("%s", prompt);
        if (scanf_s("%lf", &value) == 1) {
            break;
        }
        else {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');
        }
    }
    return value;
}

void getStringInput(const char* prompt, char* buffer, size_t bufferSize) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, bufferSize, stdin) != NULL) {
            // Remove the newline character if it's in the buffer
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }

            // Check if the string is not empty
            if (strlen(buffer) > 0) {
                return; // Valid input, exit the loop
            }
            else {
                printf("Input cannot be empty. Please try again.\n");
            }
        }
        else {
            printf("Invalid input. Please enter a valid string.\n");

            // Clear the input buffer if an error occurred
            while (getchar() != '\n');
        }
    }
}
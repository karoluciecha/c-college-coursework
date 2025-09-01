#include <stdio.h>
#include <stdlib.h>

void displayMainMenu();
void runVariablesIOProgram();
void runLightCalculationsProgram();
void runDayCalculatorProgram();
void runAverageFactorialProgram();
void runMonthlyPayrollProgram();
void runArraysAndFilesProgram();
void runStudendGradingSystemProgram();
double getDoubleInput(const char* prompt);

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
    printf("0. Exit\n");
    printf("\nSelect an option: ");
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
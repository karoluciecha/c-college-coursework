#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayMainMenu();
void runDailySalesProgram();
void runEmployeeRecordsProgram();
void runLibraryProgram();
double getDoubleInput(const char* prompt);
int getIntInput(const char* prompt);
void getStringInput(const char* prompt, char* buffer, size_t bufferSize);

int main() {
int choice;
printf("==== WELCOME TO THE C PROGRAM COLLECTION ====\n");
printf("=========== YEAR TWO SEMESTER TWO ===========\n\n");


	do {
		displayMainMenu();
        scanf_s("%d", &choice);
		system("cls");

        // For input Clearing buffer
        while ((getchar()) != '\n');

		switch (choice) {
		case 1:
			runDailySalesProgram();
			break;
		case 2:
            runEmployeeRecordsProgram();
			break;
		case 3:
            runLibraryProgram();
			break;
		case 4:
            // runAverageFactorialProgram();
			break;
		case 5:
            // runMonthlyPayrollProgram();
			break;
        case 6:
            // runArraysAndFilesProgram();
            break;
		case 7:
			// runStudendGradingSystemProgram();
			break;
        case 8:
            // runEmployeeRecordsProgram();
            break;
        case 9:
            //runMayorElectoralCollegeProgram();
            break;
        case 10:
            //runMonthlySalesProgram();
            break;
        case 11:
           // runHousePriceCalculatorProgram();
            break;
        case 12:
          //  runTheGameOfWarProgram();
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
    printf("1. Daily Sales Stats\n");
    printf("2. Employee Records\n");
    printf("3. Open Books Library\n");
    printf("4. Average & Factorial\n");
    printf("5. Monthly Payroll\n");
    printf("6. Arrays & Files\n");
	printf("7. Student Grading System\n");
    printf("8. Employee Records\n");
    printf("9. Mayor Electoral College System\n");
    printf("10. (Exam One) Monthly Sales System\n");
    printf("11. (Exam Two) House Price Calculator\n");
    printf("12. (Project) The Game of War\n");
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

		// Read input from stdin
		if (fgets(buffer, (int)bufferSize, stdin) != NULL) {
			size_t len = strlen(buffer);

			// Check if input was truncated
			if (len >= bufferSize - 1 && buffer[len - 1] != '\n') {
				printf("Input is too long. Please enter no more than %zu characters.\n", bufferSize - 1);
				while (getchar() != '\n'); // Clear remaining input
				continue;
			}

			// Remove the newline character
			if (len > 0 && buffer[len - 1] == '\n') {
				buffer[len - 1] = '\0';
				len--; // Adjust length after removing newline
			}

			// Trim leading and trailing whitespace
			char* start = buffer;
			while (isspace((unsigned char)*start)) start++;
			char* end = buffer + len - 1;
			while (end >= start && isspace((unsigned char)*end)) end--;

			// Adjust string to trimmed version
			*(end + 1) = '\0';
			memmove(buffer, start, end - start + 2); // +2 to include '\0'

			// Check if the trimmed string is not empty
			if (strlen(buffer) > 0) return;
			else printf("Input cannot be empty. Please try again.\n");
		}
		else {
			printf("Error reading input. Please try again.\n");
		}
	}
}
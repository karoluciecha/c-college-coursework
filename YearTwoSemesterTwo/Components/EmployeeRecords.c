#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 50

// Structure to store employee details
typedef struct {
    char empName[MAX_NAME_LENGTH];
    int empNumber;
    float hoursPerWeek;
    float hourlyRate;
} Employee;

// Function to display current employee records from the file
void displayEmployeeRecords() {
    FILE* file = fopen("ResourceFiles/Employee.txt", "r");

    if (!file) {
        printf("No existing employee records found.\n");
        return;
    }

    Employee employee;
    printf("\nCurrent Employee Records:\n");
    printf("---------------------------------------------");
    while (fscanf_s(file, "%[^\n] %d %f %f\n", employee.empName, (unsigned int)sizeof(employee.empName),
        &employee.empNumber, &employee.hoursPerWeek, &employee.hourlyRate) == 4) {
        employee.empName[MAX_NAME_LENGTH - 1] = '\0'; // Explicitly null-terminate the string
        printf("\nName: %s, Employee Number: %d, Hours/Week: %.2f, Hourly Rate: %.2f\n",
            employee.empName, employee.empNumber, employee.hoursPerWeek, employee.hourlyRate);
    }
    printf("---------------------------------------------\n");

    fclose(file);
}

// Function to add new employees
void addNewEmployees(int num) {
    FILE* file = fopen("Employee.txt", "a"); // Open file in append mode
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }

    Employee employee;
    for (int i = 0; i < num; i++) {
        printf("\nEnter details for Employee %d:\n", i + 1);
        
        printf("Name: ");
        while (getchar() != '\n');  // Clear input buffer
        while (scanf_s(" %[^\n]", employee.empName, (unsigned int)sizeof(employee.empName)) == 0) {
            printf("Invalid input. Please enter a valid name: ");
        }

        printf("Employee Number: ");
        while (scanf_s("%d", &employee.empNumber) != 1) {
            printf("Invalid input. Please enter a valid employee number: ");
            while (getchar() != '\n'); // Clear input buffer
        }

        printf("Hours per Week: ");
        while (scanf_s("%f", &employee.hoursPerWeek) != 1) {
            printf("Invalid input. Please enter a valid number of hours per week: ");
            while (getchar() != '\n'); // Clear input buffer
        }

        printf("Hourly Rate: ");
        while (scanf_s("%f", &employee.hourlyRate) != 1) {
            printf("Invalid input. Please enter a valid hourly rate: ");
            while (getchar() != '\n'); // Clear input buffer
        }

        // Write to file
        fprintf(file, "%s\n%d %.2f %.2f\n", employee.empName, employee.empNumber, employee.hoursPerWeek, employee.hourlyRate);
    }

    printf("\nNew employee records have been successfully added!\n");
    fclose(file);
}

void runEmployeeRecordsProgram() {

    while (1) {
        // Display existing employee records (if any)
        displayEmployeeRecords();

        // Ask the user how many new employees to add
        int numEmployees;
        printf("\nEnter the number of employees to add: ");
        while (scanf_s("%d", &numEmployees) == 0) {
            printf("Invalid input. Please enter a valid number: ");
            while (getchar() != '\n'); // Clear input buffer
        }

        if (numEmployees > 0) {
            addNewEmployees(numEmployees);
        }
        else {
            printf("No new employees added.\n");
        }

        // Ask if the user wents to run the program again
        char choice;
        printf("\nDo you want to run the program again? (y/n): ");
        while (1) {
            while (getchar() != '\n'); // Clear input buffer
            scanf_s("%c", &choice, 1);
			if (choice == 'y' || choice == 'Y') {
				break;
			}
			else if (choice == 'n' || choice == 'N') {
                printf("\n");
                system("pause");
                system("cls");
				return;
			}
			else {
				printf("Invalid choice. Please enter 'y' or 'n': ");
			}
        }
    }
}
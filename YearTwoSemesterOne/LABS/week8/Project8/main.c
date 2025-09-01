#include <stdio.h>
#include <stdlib.h>

#define FILENAME "Employee.txt"

typedef struct {
    char name[50];
    int number;
    double hoursPerWeek;
    double hourlyRate;
} Employee;

int employeeIndex = 0;

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
    while (getchar() != '\n');
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

void displayExistingRecords() {
    FILE* file = fopen(FILENAME, "r"); // read-only mode
    if (file == NULL) {
        printf("No existing records found in \"%s\".\n", FILENAME);
        return;
    }

    printf("Existing employee records:\n");
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
        employeeIndex++;
    }
    fclose(file);
}

void addNewEmployees(int count) {
    FILE* file = fopen(FILENAME, "a"); // Append mode
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        employeeIndex++;
        Employee emp;
        printf("\nEnter details for employee %d:\n", employeeIndex);
        getStringInput("Employee name: ", emp.name, 50);
        emp.number = getIntInput("Employee number: ");
        emp.hoursPerWeek = getDoubleInput("Hours per week: ");
        emp.hourlyRate = getDoubleInput("Hourly rate: ");

        // Write to file
        fprintf(file, "Name: %s, Number: %d, Hours Weekly: %.2f, Hourly Rate: %.2f\n",
            emp.name, emp.number, emp.hoursPerWeek, emp.hourlyRate);
    }
    fclose(file);
    printf("\nNew employee records have been added to \"%s\".\n", FILENAME);
}

int main() {
    printf("Checking for existing employee records...\n");
    displayExistingRecords();

    int newEmployeeCount = getIntInput("\nHow many new employees would you like to add? ");

    if (newEmployeeCount > 0) {
        addNewEmployees(newEmployeeCount);
    }
    else {
        printf("No new employees to add. Exiting.\n");
    }

    return 0;
}

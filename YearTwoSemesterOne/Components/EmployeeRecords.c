#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "ResourceFiles/Employee.txt"

typedef struct {
    char name[50];
    int number;
    double hoursPerWeek;
    double hourlyRate;
} Employee;

int employeeIndex = 0;

int getIntInput(const char* prompt);
double getDoubleInput(const char* prompt);
void getStringInput(const char* prompt, char* buffer, size_t bufferSize);

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

void runEmployeeRecordsProgram() {
    printf("Checking for existing employee records...\n");
    displayExistingRecords();

    int newEmployeeCount = getIntInput("\nHow many new employees would you like to add? ");

    if (newEmployeeCount > 0) {
        addNewEmployees(newEmployeeCount);
    }
    else {
        printf("No new employees to add. Exiting.\n");
    }
    system("pause");
    system("cls");
}

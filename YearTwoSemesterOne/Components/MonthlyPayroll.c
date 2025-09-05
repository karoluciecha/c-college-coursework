#include <stdio.h>
#include <stdlib.h>

#define COMMISSION_RATE_LOW 0.05
#define COMMISSION_RATE_HIGH 0.075
#define MILEAGE_RATE_LOW 0.40
#define MILEAGE_RATE_HIGH 0.35

typedef struct {
    int employeeNumber;
    double monthlyWage;
    double sales;
    double mileage;
    double commission;
    double mileageExpenses;
    double totalPayment;
} Employee;

int getIntInput(const char* prompt);
double getDoubleInput(const char* prompt);

double calculateCommission(double sales) {
    if (sales < 1000) {
        return sales * COMMISSION_RATE_LOW;
    }
    else {
        return sales * COMMISSION_RATE_HIGH;
    }
}

double calculateMileageExpenses(double mileage) {
    if (mileage < 400) {
        return mileage * MILEAGE_RATE_LOW;
    }
    else {
        return mileage * MILEAGE_RATE_HIGH;
    }
}

void runMonthlyPayrollProgram() {
    int numEmployees, i, maxSalesEmployeeIndex = 0;
    double totalMileageExpenses = 0;

    numEmployees = getIntInput("Enter the number of employees: ");

    // *employees is a pointer to a block of memory capable of holding multiple Employee structures.
    // beause it's a pointer, it can be later used to access elements just like arrays: employees[2].
    // malloc() returns a pointer of type void*, that needs to be casted to a specific data type: (Employee*).
    // numEmployees * sizeof(Employee) calculates memory needed to sture numEmployees woth of Employee structures.
    // calloc() is better as it guarantees that all allocated memory is set to 0.
    Employee *employees = (Employee*)calloc(numEmployees, sizeof(Employee));
    if (employees == NULL) {
        printf("Memory allocation failed./n");
        return;
    }

    for (i = 0; i < numEmployees; i++) {
        printf("\nEnter details for Employee %d:\n", i + 1);

        employees[i].employeeNumber = getIntInput("Employee Number: ");
        employees[i].monthlyWage = getDoubleInput("Monthly Wage: ");
        employees[i].sales = getDoubleInput("Amount of Sales: ");
        employees[i].mileage = getDoubleInput("Mileage: ");

        employees[i].commission = calculateCommission(employees[i].sales);
        employees[i].mileageExpenses = calculateMileageExpenses(employees[i].mileage);

        employees[i].totalPayment = employees[i].monthlyWage + employees[i].commission + employees[i].mileageExpenses;

        totalMileageExpenses += employees[i].mileageExpenses;

        if (employees[i].sales > employees[maxSalesEmployeeIndex].sales) {
            maxSalesEmployeeIndex = i;
        }

        printf("\nEmployee Number: %d", employees[i].employeeNumber);
        printf("\nMileage Expenses: %.2lf", employees[i].mileageExpenses);
        printf("\nCommission: %.2lf", employees[i].commission);
        printf("\nTotal Monthly Payment: %.2lf\n", employees[i].totalPayment);
    }

    printf("\nTotal Company Mileage Expenses Paid: %.2lf\n", totalMileageExpenses);
    printf("Employee with Maximum Sales: %d (Sales: %.2lf)\n\n", employees[maxSalesEmployeeIndex].employeeNumber, employees[maxSalesEmployeeIndex].sales);

    free(employees);
}
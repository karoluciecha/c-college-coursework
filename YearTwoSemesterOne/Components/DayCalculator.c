#include <stdio.h>

int day();
float calc();

void runDayCalculatorProgram() {
    int choice = -1;

    do {
        printf("==== DAY CALCULATOR MENU ====\n");
        printf("1. Day number program\n");
        printf("2. Calculations program\n");
        printf("0. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf_s("%d", &choice);

        // Clear buffer to avoid leftover input messing things up
        while ((getchar()) != '\n');

        switch (choice) {
            case 1:
                printf("\nResulting day number: %d.\n\n", day());
                break;
            case 2:
                printf("\nCalculation result: %.2f.\n\n", calc());
                break;
            case 0:
                printf("Exiting Day Calculator Program...\n\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n\n");
                break;
        }
    } while (choice != 0);
}


int day() {

    int numDay, numMonth, numYear, numResult = 0, isLeapYear = 0;
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    do {
        printf("\nPlease enter the day number, month number and year separated by space: ");
        scanf_s("%d %d %d", &numDay, &numMonth, &numYear);
        if ((numYear % 4 == 0 && numYear % 100 != 0) || (numYear % 400 == 0)) {
            isLeapYear = 1;
            daysInMonth[1] = 29;
        }
        else {
            daysInMonth[1] = 28;
        }
        if ((numMonth == 2 && numDay < 30 && numDay > 0 && isLeapYear == 1)
            || (numMonth == 2 && numDay < 29 && numDay > 0 && isLeapYear == 0)
            || ((numMonth == 4 || numMonth == 6 || numMonth == 9 || numMonth == 11) && numDay < 31 && numDay > 0)
            || ((numMonth == 1 || numMonth == 3 || numMonth == 5 || numMonth == 7 || numMonth == 8 || numMonth == 10 || numMonth == 12) && numDay < 32 && numDay > 0)) {
            break;
        }
        else {
            printf("Input invalid. Please try again.\n");
        }
    } while (1);
    
    for (int i = 0; i < numMonth - 1; i++) {
        numResult += daysInMonth[i];
    }
    numResult += numDay;
    return numResult;
}

float calc() {
    float numOne, numTwo, numResult = 0.0;
    char operation = 'x';

    printf("\nEnter first value: ");
    scanf_s("%f", &numOne);
    printf("Enter second value: ");
    scanf_s("%f", &numTwo);
    scanf_s("%c", &operation);

    do {
        printf("\nWhat action would you like to perform?\nA. addition\nD. division\nM. multiplication\nS. substraction\nEnter your choice (A / D / M / S): ");
        scanf_s("%c", &operation);

        switch (operation) {
        case 'a':
        case 'A':
            numResult = numOne + numTwo;
            return numResult;
        case 'd':
        case 'D':
            numResult = numOne / numTwo;
            return numResult;
        case 'm':
        case 'M':
            numResult = numOne * numTwo;
            return numResult;
        case 's':
        case 'S':
            numResult = numOne - numTwo;
            return numResult;
        default:
            printf("\nInput invalid. Please try again.\n");

        }

    } while (1);
}
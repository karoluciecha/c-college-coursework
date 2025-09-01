// Karol Uciecha - G00436758
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Declaring variables
#define NO_MONTHS 2
#define ALL_MONTHS 12

int smallestMonthThis, smallestMonthLast, highestMonthThis, highestMonthLast;
double averageHousePurchasePrices[NO_MONTHS][ALL_MONTHS], smallestPriceThis, smallestPriceLast, highestPriceThis, highestPriceLast;

// Function to get Double input
double getDoubleInput(const char* prompt) {
    double value;
    while (1) {
        printf("%s", prompt);
        if (scanf_s("%lf", &value) == 1) {
            if (value < 0) {
                printf("Entered value must be plurar. Please try again.\n");
            }
            else return value;
        }
        else {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');
        }
    }
}

// Function to display the table with average prices
void displayTable() {
    printf("\nMonth\t\tThis year\t\tLast year\n");
    for (int i = 0; i < ALL_MONTHS; i++) {
        printf("%d\t\t%.2f\t\t\t%.2f\n", i + 1, averageHousePurchasePrices[0][i], averageHousePurchasePrices[1][i]);
    }
    printf("\n");
}

// Function to find the smallest average
void findMonthSmallestAverage() {
    smallestMonthThis = 1;
    smallestMonthLast = 1;
    smallestPriceThis = averageHousePurchasePrices[0][0];
    smallestPriceLast = averageHousePurchasePrices[1][0];
    for (int i = 1; i < ALL_MONTHS; i++) {
        if (smallestPriceThis > averageHousePurchasePrices[0][i]) {
            smallestPriceThis = averageHousePurchasePrices[0][i];
            smallestMonthThis = i + 1;
        }
        if (smallestPriceLast > averageHousePurchasePrices[1][i]) {
            smallestPriceLast = averageHousePurchasePrices[1][i];
            smallestMonthLast = i + 1;
        }
    }
    printf("Month %d has the smallest average house purchases price (%.2f) this year\n", smallestMonthThis, smallestPriceThis);
    printf("Month %d has the smallest average house purchases price (%.2f) last year\n", smallestMonthLast, smallestPriceLast);
}

// Function to find the highest average
void findMonthHighestAverage() {
    highestMonthThis = 1;
    highestMonthLast = 1;
    highestPriceThis = averageHousePurchasePrices[0][0];
    highestPriceLast = averageHousePurchasePrices[1][0];
    for (int i = 1; i < ALL_MONTHS; i++) {
        if (highestPriceThis < averageHousePurchasePrices[0][i]) {
            highestPriceThis = averageHousePurchasePrices[0][i];
            highestMonthThis = i + 1;
        }
        if (highestPriceLast < averageHousePurchasePrices[1][i]) {
            highestPriceLast = averageHousePurchasePrices[1][i];
            highestMonthLast = i + 1;
        }
    }
    printf("Month %d has the highest average house purchases price (%.2f) this year\n", highestMonthThis, highestPriceThis);
    printf("Month %d has the highest average house purchases price (%.2f) last year\n", highestMonthLast, highestPriceLast);
}

// Function to output everything to the file
void outputToFile() {
    FILE* file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Cannot open file to write\n");
        return;
    }

    fprintf(file, "Month\t\tThis year\t\tLast year\n");
    for (int i = 0; i < ALL_MONTHS; i++) {
        fprintf(file, "%d\t\t%.2f\t\t\t%.2f\n", i + 1, averageHousePurchasePrices[0][i], averageHousePurchasePrices[1][i]);
    }
    fprintf(file, "\n");

    fprintf(file, "Month %d has the smallest average house purchases price (%.2f) this year\n", smallestMonthThis, smallestPriceThis);
    fprintf(file, "Month %d has the smallest average house purchases price (%.2f) last year\n\n", smallestMonthLast, smallestPriceLast);

    fprintf(file, "Month %d has the highest average house purchases price (%.2f) this year\n", highestMonthThis, highestPriceThis);
    fprintf(file, "Month %d has the highest average house purchases price (%.2f) last year\n", highestMonthLast, highestPriceLast);
    fclose(file);

    printf("\nSuccessfully outputted to file.\n");
}

int main() {
    printf("Welcome to the CSO House Price Calculation Program\n\n");

//  Entering data to the array
    for (int i = 0; i < ALL_MONTHS; i++) {
        for (int j = 0; j < NO_MONTHS; j++) {
            char prompt[100];
            if (j == 0) snprintf(prompt, sizeof(prompt), "Please enter the average house purchase for month %d of this year: ", i + 1);
            else if (j == 1) snprintf(prompt, sizeof(prompt), "Please enter the average house purchase for month %d of last year: ", i + 1);
            else snprintf(prompt, sizeof(prompt), "Please enter the average house purchase for month %d of %d. year: ", i + 1, j + 1);
            averageHousePurchasePrices[j][i] = getDoubleInput(prompt);
        }
    }

//  Function calls
    displayTable();

    findMonthSmallestAverage();

    findMonthHighestAverage();

    outputToFile();

    return 0;
}
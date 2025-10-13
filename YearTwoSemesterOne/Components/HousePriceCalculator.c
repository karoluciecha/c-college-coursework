// Karol Uciecha - G00436758
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaring variables
#define NO_MONTHS 2
#define ALL_MONTHS 12

int smallestMonthThis, smallestMonthLast, highestMonthThis, highestMonthLast;
double averageHousePurchasePrices[NO_MONTHS][ALL_MONTHS], smallestPriceThis, smallestPriceLast, highestPriceThis, highestPriceLast;

double getDoubleInput(const char* prompt);

void runHousePriceCalculatorProgram() {
    printf("Welcome to the CSO House Price Calculation Program\n\n");

    //  Entering data to the array
    for (int i = 0; i < ALL_MONTHS; i++) {
        for (int j = 0; j < NO_MONTHS; j++) {
            char prompt[100], temp;
            // Purchase price must be >= 0
            do {
                if (j == 0) snprintf(prompt, sizeof(prompt), "Please enter the average house purchase for month %d of this year: ", i + 1);
                else if (j == 1) snprintf(prompt, sizeof(prompt), "Please enter the average house purchase for month %d of last year: ", i + 1);
                else snprintf(prompt, sizeof(prompt), "Please enter the average house purchase for month %d of %d. year: ", i + 1, j + 1);
                temp = getDoubleInput(prompt);
                if (temp < 0) {
                    printf("Purchase price must be zero or positive.\n");
                }
            } while (temp < 0);
            averageHousePurchasePrices[j][i] = temp;
        }
    }

    // Display the table with average prices
    printf("\nMonth\t\tThis year\t\tLast year\n");
    for (int i = 0; i < ALL_MONTHS; i++) {
        printf("%d\t\t%.2f\t\t\t%.2f\n", i + 1, averageHousePurchasePrices[0][i], averageHousePurchasePrices[1][i]);
    }
    printf("\n");

    // Find the smallest average
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

    // Function to find the highest average
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

    // Output everything to the file
    FILE* file = fopen("ResourceFiles/HousePriceCalculationsResult.txt", "w");
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

    system("pause");
    system("cls");
}
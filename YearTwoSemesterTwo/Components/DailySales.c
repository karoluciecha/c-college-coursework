#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEPARTMENTS 3
#define MAX_NAME_LENGTH 20

// Structure to store department sales data
typedef struct {
    char name[MAX_NAME_LENGTH];
    int totalSales;
    int count;
    int maxSale;
} Department;

void runDailySalesProgram() {
    FILE* file;
    fopen_s(&file, "ResourceFiles/DailySales.txt", "r");

    if (!file) {
        printf("Error opening file!\n\n");
        return;
    }

    Department departments[MAX_DEPARTMENTS] = {
        {"Hardware", 0, 0, 0},
        {"Grocery", 0, 0, 0},
        {"Drapery", 0, 0, 0}
    };

    char departmentName[MAX_NAME_LENGTH];
    int sale, totalSales = 0;

    // Reading file data securely
    while (fscanf_s(file, "%19s %d", departmentName, (unsigned int)sizeof(departmentName), &sale) == 2) {
        departmentName[MAX_NAME_LENGTH - 1] = '\0'; // Explicitly null-terminate the string
        totalSales += sale;

        for (int i = 0; i < MAX_DEPARTMENTS; i++) {
            if (strcmp(departmentName, departments[i].name) == 0) {
                departments[i].totalSales += sale;
                departments[i].count++;
                if (sale > departments[i].maxSale) {
                    departments[i].maxSale = sale;
                }
                break;
            }
        }
    }
    fclose(file);

    // Display results
    printf("Total daily sales: %d\n\n", totalSales);

    printf("Statistics:\n");
    for (int i = 0; i < MAX_DEPARTMENTS; i++) {
        double avgSales = (departments[i].count > 0) ? (double)departments[i].totalSales / departments[i].count : 0;
        printf("%s - total sales: %d, average sales: %.2f, max sale: %d\n",
            departments[i].name, departments[i].totalSales, avgSales, departments[i].maxSale);
    }
    printf("\n");
    system("pause");
    system("cls");

    return;
}
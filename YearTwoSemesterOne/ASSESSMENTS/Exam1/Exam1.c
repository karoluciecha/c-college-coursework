// G00436758
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TIMBER,
    CONCRETE,
    BATHROOM,
    TILES
} Department;

typedef struct {
    int ProductID;
    Department DepartmentName;
    char ProductName[100];
    int OpeningInventoryQuantity;
    int QuantitySold;
    double UnitValue;
    int ReorderTreshold;
    int ClosingInventoryBalance;
    double ValueOfProductsSold;
} Product;

double TotalSalesValue = 0;
double TotalClosingStockValue = 0;

// Function to convert enum to string (for display purposes)
const char* getDepartmentName(Department dept) {
    switch (dept) {
    case TIMBER: return "Timber";
    case CONCRETE: return "Concrete";
    case BATHROOM: return "Bathroom";
    case TILES: return "Tiles";
    default: return "Unknown";
    }
}

// Method to get Int input
int getIntInput(const char* prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf_s("%d", &value) == 1) {
            if (value < 0) {
                printf("Entered value must be plurar. Please try again.\n");
            }
            else return value;
        }
        else {
            printf("Invalid input. Please enter a valid integer.\n");
            while (getchar() != '\n');
        }
    }
}

// Method to get Double input
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

// Method to check if user wants to terminate the program
int askToRunAgain() {
    int c;
    while (1) {
        printf("Please enter the Product ID or -1 to terminate : ");
        if (scanf_s("%d", &c) == 1) {
            if (c < -1) {
                printf("Product identifier must be plurar. Please try again.\n");
            }
            else if (c >= 0) {
                return c;
            }
            else return -1;
        }
    }
}

// Main Logic
void runMonthlySalesProgram(int choice, Product product) {

    product.ProductID = choice;
    fgets(product.DepartmentName, sizeof(product.DepartmentName), stdin);
    do {
        printf("Please enter the department name: ");
        fgets(product.DepartmentName, sizeof(product.DepartmentName), stdin);

        // Check if the input is just a newline character
        if (product.DepartmentName[0] == '\n') {
            printf("\nNo name entered. Please try again.");
        }
        // Implement code to check for Department Name
        else {
            break;
        }
    } while (1);

    do {
        printf("Please the product name: ");
        fgets(product.ProductName, sizeof(product.ProductName), stdin);

        // Check if the input is just a newline character
        if (product.ProductName[0] == '\n') {
            printf("\nNo name entered. Please try again.");
        }
        else {
            break;
        }
    } while (1);

    product.OpeningInventoryQuantity = getIntInput("Please enter the opening inventory quantity: ");
    product.UnitValue = getDoubleInput("Please enter the unit price: ");
    product.ReorderTreshold = getIntInput("Please enter the reorder treshold: ");
    product.QuantitySold = getIntInput("Please enter the quantity sold: ");
    product.ClosingInventoryBalance = product.OpeningInventoryQuantity - product.QuantitySold;
    product.ValueOfProductsSold = product.QuantitySold * product.UnitValue;

    if (product.ClosingInventoryBalance < product.ReorderTreshold) {
        printf("\nProduct ID: %d\nDepartment Name: %sProduct Name: %sClosing Inventory Quantity: %d\nReorder Treshold: %d\n", product.ProductID, product.DepartmentName, product.ProductName, product.ClosingInventoryBalance, product.ReorderTreshold);
    }

    TotalSalesValue += product.QuantitySold  * product.UnitValue;
    TotalClosingStockValue += product.ClosingInventoryBalance * product.UnitValue;
}

// Program Core
int main() {
    int numProducts = 1000, index = 0, closingValueMax = 0, indexClosingValueMax = 0;
    Product* products = (Product*)calloc(numProducts, sizeof(Product));
    if (products == NULL) {
        printf("Memory allocation failed./n");
        return 0;
    }

    do {
        int choice = askToRunAgain();
        if (choice != -1) {
            runMonthlySalesProgram(choice, products[index]);
            index++;
            printf("\n\n");
        }
        else break;
    } while (1);
    for (int i = 0; i < index; i++) {
        if (products[i].ClosingInventoryBalance > closingValueMax) {
            closingValueMax = products[i].ClosingInventoryBalance;
            indexClosingValueMax = i;
        }
    }
    printf("\nTotal sales value in the overall shop was: %.2f.", TotalSalesValue);
    printf("\nThe product with the largest stock is %s, with a stock of %d units.", products[indexClosingValueMax].ProductName, products[indexClosingValueMax].ClosingInventoryBalance);
    printf("\nThe total value of the closing stock is %.2f.\n", TotalClosingStockValue);

    printf("Program terminated. Thank you!\n");
    free(products);
    return 0;
}
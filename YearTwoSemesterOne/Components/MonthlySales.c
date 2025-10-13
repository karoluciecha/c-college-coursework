#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int getIntInput(const char* prompt);
double getDoubleInput(const char* prompt);

// Function to read department from user
Department getDepartmentInput() {
    int dept;
    while (1) {
        printf("Select a department\n1. Timber\n2. Concrete\n3. Bathroom\n4. Tiles\nSelect an option: ");
        if (scanf("%d", &dept) == 1 && dept >= 1 && dept <= 4) {
            return (Department)--dept;
        }
        else {
            printf("Invalid department. Try again.\n");
            while (getchar() != '\n'); // flush
        }
    }
}

// Method to check if user wants to terminate the program
int askToRunAgain() {
    int c;
    while (1) {
        printf("Please enter the Product ID or -1 to terminate: ");
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
void productInput(int choice, Product* product) {
    product->ProductID = choice;
    product->DepartmentName = getDepartmentInput();
    while (getchar() != '\n'); // flush newline from input buffer
    do {
        printf("Please the product name: ");
        fgets(product->ProductName, sizeof(product->ProductName), stdin);
        product->ProductName[strcspn(product->ProductName, "\n")] = '\0'; // strip newline

        // Check if the input is just a newline character
        if (product->ProductName[0] == '\n') {
            printf("\nNo name entered. Please try again.");
        }
        else {
            break;
        }
    } while (1);

    // Opening inventory must be >= 0
    do {
        product->OpeningInventoryQuantity = getIntInput("Please enter the opening inventory quantity: ");
        if (product->OpeningInventoryQuantity < 0) {
            printf("Value must be zero or positive.\n");
        }
    } while (product->OpeningInventoryQuantity < 0);

    // Unit price must be > 0
    do {
        product->UnitValue = getDoubleInput("Please enter the unit price: ");
        if (product->UnitValue <= 0) {
            printf("Unit price must be greater than 0.\n");
        }
    } while (product->UnitValue <= 0);

    // Reorder threshold must be >= 0
    do {
        product->ReorderTreshold = getIntInput("Please enter the reorder threshold: ");
        if (product->ReorderTreshold < 0) {
            printf("Value must be zero or positive.\n");
        }
    } while (product->ReorderTreshold < 0);

    // Quantity sold must be >= 0 and <= Opening inventory
    do {
        product->QuantitySold = getIntInput("Please enter the quantity sold: ");
        if (product->QuantitySold < 0) {
            printf("Quantity sold must be zero or positive.\n");
        }
        else if (product->QuantitySold > product->OpeningInventoryQuantity) {
            printf("Quantity sold cannot exceed opening inventory.\n");
        }
    } while (product->QuantitySold < 0 || product->QuantitySold > product->OpeningInventoryQuantity);

    product->ClosingInventoryBalance = product->OpeningInventoryQuantity - product->QuantitySold;
    product->ValueOfProductsSold = product->QuantitySold * product->UnitValue;

    if (product->ClosingInventoryBalance < product->ReorderTreshold) {
        printf("Product ID: %d\nDepartment: %s\nProduct Name: %s\nClosing Inventory Quantity: %d\nReorder Threshold: %d\n",
            product->ProductID, getDepartmentName(product->DepartmentName), product->ProductName,
            product->ClosingInventoryBalance, product->ReorderTreshold);
    }

    TotalSalesValue += product->ValueOfProductsSold;
    TotalClosingStockValue += product->ClosingInventoryBalance * product->UnitValue;
}

// Program Interface
void runMonthlySalesProgram() {
    int numProducts = 1000, index = 0, closingValueMax = 0, indexClosingValueMax = 0;
    Product* products = (Product*)calloc(numProducts, sizeof(Product));
    if (products == NULL) {
        printf("Memory allocation failed./n");
        system("pause");
        system("cls");
    }

    while (1) {
        int choice = askToRunAgain();
        if (choice != -1) {
            productInput(choice, &products[index]);
            index++;
            printf("\n\n");
        }
        else break;
    }

for (int i = 0; i < index; i++) {
        if (products[i].ClosingInventoryBalance > closingValueMax) {
            closingValueMax = products[i].ClosingInventoryBalance;
            indexClosingValueMax = i;
        }
    }

    printf("\nTotal sales value in the overall shop was: %.2f", TotalSalesValue);
    printf("\nThe product with the largest stock is %s, with a stock of %d units.", products[indexClosingValueMax].ProductName, products[indexClosingValueMax].ClosingInventoryBalance);
    printf("\nThe total value of the closing stock is %.2f.\n", TotalClosingStockValue);

    system("pause");
    free(products);
    system("cls");
}
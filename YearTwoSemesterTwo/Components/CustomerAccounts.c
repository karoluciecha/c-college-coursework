// Code author: Karol Uciecha - G00436758
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_STR_LEN 100

typedef struct customer
{
    char companyID[MAX_STR_LEN]; // Unique identifier
    char companyName[MAX_STR_LEN];
    char companyVAT[MAX_STR_LEN];
    float outstandingBalance;
    float maxCreditLimit;
    struct customer *next;
    struct customer *previous;
} Customer;

// Function prototypes
void readFloat(const char *prompt, float *value);
int mainMenu();
int isUniqueID(Customer *headRef, const char *companyID);
void collectionBackup(Customer *collectionHeadPointer);
void collectionRestore(Customer **collectionHeadPointer, Customer **collectionTailPointer);
void addCustomer(Customer **headRef, Customer **tailRef);
void listCustomersAboveLimit(Customer *headRef);
void updateOutstandingBalance(Customer *headRef);
void getTotalOutstandingBalance(Customer *headRef);

void runCustomerAccountsProgram()
{
    Customer *collectionHeadPointer = NULL; // pointer to the first item (head node)
    Customer *collectionTailPointer = NULL; // pointer to the last item (tail node)

    collectionRestore(&collectionHeadPointer, &collectionTailPointer);

    int action = mainMenu();
    while (action)
    {
        switch (action)
        {
        case 1: // Add customer
            addCustomer(&collectionHeadPointer, &collectionTailPointer);
            break;
        case 2: // Customers above limit
            listCustomersAboveLimit(collectionHeadPointer);
            break;
        case 3: // Update outstanding balance
            updateOutstandingBalance(collectionHeadPointer);
            break;
        case 4: // Total outstanding balance
            getTotalOutstandingBalance(collectionHeadPointer);
            break;
        case -1: // Exit program
            collectionBackup(collectionHeadPointer);
            printf("Exiting program...\n\n");
            Customer *temp;
            while (collectionHeadPointer)
            {
                temp = collectionHeadPointer;
                collectionHeadPointer = collectionHeadPointer->next;
                free(temp);
            }
            system("pause");
            system("cls");
            return;
        default: // Invalid option
            printf("Invalid choice. Please try again.\n\n");
            break;
        }
        system("pause");
        system("cls");
        action = mainMenu();
    }
}

// Function to read a float from user input
void readFloat(const char *prompt, float *value)
{
    while (1)
    {
        printf("%s", prompt);
        if (scanf_s("%f", value) == 1)
        {
            while (getchar() != '\n')
                ; // Clear input buffer
            return;
        }
        else
        {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n')
                ; // Clear invalid input
        }
    }
}

// Function to present menu options to the user
int mainMenu()
{
    int choice = 0;

    // Main menu input loop
    while (1)
    {
        printf("=== Customer Accounts Management System Menu ===\n");
        printf("1. Add a customer\n");
        printf("2. Get a list of customers above their credit limit\n");
        printf("3. Update a customer's outstanding balance\n");
        printf("4. Get the total outstanding balance\n");
        printf("-1. Exit program\n\n");
        readInt("Enter your choice: ", &choice);

        // Valid main menu choices (-1 && 1 - 4)
        if ((choice >= 1 && choice <= 4) || choice == -1)
        {
            return choice;
        }
        // Invalid main menu option
        printf("Invalid choice. Please try again.\n\n");
    }
}

// Checks for unique company ID in the linked list
int isUniqueID(Customer *headRef, const char *companyID)
{
    Customer *current = headRef;
    while (current)
    {
        if (strcmp(current->companyID, companyID) == 0)
        {
            return 0; // found a match - not unique
        }
        current = current->next;
    }
    return 1; // no matches - unique
}

// Function to save customer details to file
void collectionBackup(Customer *collectionHeadPointer)
{
    system("cls");
    FILE *file = fopen("ResourceFiles/customer.txt", "w"); // "w" mode: create or overwrite

    if (!file)
    {
        printf("Backup error: Could not open ResourceFiles/customer.txt for writing.\n");
        return;
    }

    Customer *current = collectionHeadPointer;

    while (current != NULL)
    {
        // Save each customer's details line by line
        fprintf(file,
                "%s\n%s\n%s\n%.2f\n%.2f\n",
                current->companyID,
                current->companyName,
                current->companyVAT,
                current->outstandingBalance,
                current->maxCreditLimit);

        current = current->next; // Move to the next customer
    }

    fclose(file);

    printf("Backup successful: ResourceFiles/customer.txt updated.\n");
}

// Function to restore customer details from file
void collectionRestore(Customer **collectionHeadPointer, Customer **collectionTailPointer)
{
    FILE *file = fopen("ResourceFiles/customer.txt", "r"); // "r" mode: read file
    if (!file)
    {
        printf("Restore error: Could not open ResourceFiles/customer.txt for reading.\n\n");
        return;
    }

    Customer *newCustomer = NULL;
    Customer *lastCustomer = NULL;
    char buffer[MAX_STR_LEN];

    // Free the existing list
    Customer *current = *collectionHeadPointer;
    while (current != NULL)
    {
        Customer *temp = current;
        current = current->next;
        free(temp);
    }

    // Reset head and tail to NULL
    *collectionHeadPointer = NULL;
    *collectionTailPointer = NULL;

    // Restore data from file
    while (!feof(file))
    {
        newCustomer = (Customer *)malloc(sizeof(Customer));
        if (!newCustomer)
        {
            printf("Restore error: Memory allocation failed.\n\n");
            fclose(file);
            return;
        }

        // Read all fields in same order as saved
        if (fgets(buffer, MAX_STR_LEN, file) == NULL)
        {
            free(newCustomer);
            printf("Nothing to initialise the linked list.\n\n");
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline and null-terminate
        strcpy_s(newCustomer->companyID, sizeof(newCustomer->companyID), buffer);

        if (fgets(buffer, MAX_STR_LEN, file) == NULL)
        {
            free(newCustomer);
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy_s(newCustomer->companyName, sizeof(newCustomer->companyName), buffer);

        if (fgets(buffer, MAX_STR_LEN, file) == NULL)
        {
            free(newCustomer);
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy_s(newCustomer->companyVAT, sizeof(newCustomer->companyVAT), buffer);

        if (fscanf_s(file, "%f\n", &newCustomer->outstandingBalance) != 1)
        {
            free(newCustomer);
            break;
        }
        if (fscanf_s(file, "%f\n", &newCustomer->maxCreditLimit) != 1)
        {
            free(newCustomer);
            break;
        }

        // Set pointers
        newCustomer->next = NULL;
        newCustomer->previous = NULL;

        // Insert into the linked list
        if (*collectionHeadPointer == NULL)
        {
            // First customer
            *collectionHeadPointer = newCustomer;
            *collectionTailPointer = newCustomer;
        }
        else
        {
            // Append to the list
            newCustomer->previous = *collectionTailPointer;
            (*collectionTailPointer)->next = newCustomer;
            *collectionTailPointer = newCustomer;
        }
    }

    fclose(file);
    printf("Restore successful: Database restored successfully from ResourceFiles/customer.txt.\n\n");
}

// Function to add a new customer to the linked list
void addCustomer(Customer **headRef, Customer **tailRef)
{
    system("cls");

    Customer *newCustomer = malloc(sizeof(*newCustomer));
    if (!newCustomer)
    {
        printf("Add error: Memory allocation failed.\n\n");
        return;
    }
    char buffer[MAX_STR_LEN];

    // 1. companyID (must be unique)
    do
    {
        readChar("Enter the company ID: ", buffer, sizeof(buffer));
        if (!isUniqueID(*headRef, buffer))
        {
            printf("That company ID already exists. Please try again.\n\n");
        }
        else
            break;
    } while (1);
    strcpy_s(newCustomer->companyID, sizeof(newCustomer->companyID), buffer);

    // 2. companyName
    readChar("Enter the company name: ", newCustomer->companyName, sizeof(newCustomer->companyName));

    // 3. companyVAT
    readChar("Enter the company VAT number: ", newCustomer->companyVAT, sizeof(newCustomer->companyVAT));

    // 4. outstandingBalance
    readFloat("Enter the outstanding balance: ", &newCustomer->outstandingBalance);

    // 5. maxCreditLimit
    readFloat("Enter the max credit limit: ", &newCustomer->maxCreditLimit);

    // Initialize links
    newCustomer->next = NULL;
    newCustomer->previous = NULL;

    // Append to tail
    if (*headRef == NULL)
    {
        *headRef = *tailRef = newCustomer;
    }
    else
    {
        newCustomer->previous = *tailRef;
        (*tailRef)->next = newCustomer;
        *tailRef = newCustomer;
    }

    printf("Customer added successfully.\n\n");
}

// Function to list customers above their credit limit
void listCustomersAboveLimit(Customer *headRef)
{
    system("cls");
    if (!headRef)
    {
        printf("No customers are registered yet.\n\n");
        return;
    }

    printf("=== List of Customers Above Their Credit Limit ===\n");
    for (Customer *cur = headRef; cur; cur = cur->next)
    {
        if (cur->outstandingBalance > cur->maxCreditLimit)
        {
            printf("Customer \"%s\" has an outstanding balance of %.2f and a credit limit of %.2f.\n", cur->companyName, cur->outstandingBalance, cur->maxCreditLimit);
        }
    }
    printf("\n");
}

// Function to update customer's outstanding balance
void updateOutstandingBalance(Customer *headRef)
{
    system("cls");
    if (!headRef)
    {
        printf("No customers are registered yet.\n\n");
        return;
    }

    char searchCompanyID[MAX_STR_LEN];
    readChar("Enter the company ID: ", searchCompanyID, sizeof(searchCompanyID));

    // Search the list
    Customer *cur = headRef;
    while (cur)
    {
        if (_stricmp(cur->companyID, searchCompanyID) == 0)
        {
            // Found
            printf("Current outstanding balance: %.2f\n", cur->outstandingBalance);
            readFloat("Enter the new outstanding balance: ", &cur->outstandingBalance);
            printf("Balance updated successfully.\n\n");
            return;
        }
        cur = cur->next;
    }

    // Not found
    printf("\nNo customer with company ID \"%s\" was found.\n", searchCompanyID);
}

// Function to get the total outstanding balance
void getTotalOutstandingBalance(Customer *headRef)
{
    system("cls");
    if (!headRef)
    {
        printf("No customers are registered yet.\n\n");
        return;
    }

    float totalOutstandingBalance = 0;

    for (Customer *cur = headRef; cur; cur = cur->next)
        totalOutstandingBalance += cur->outstandingBalance;

    printf("The total outstanding balance is: %.2f.\n\n", totalOutstandingBalance);
}
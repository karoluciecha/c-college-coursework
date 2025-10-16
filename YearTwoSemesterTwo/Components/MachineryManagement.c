#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define MAX_STR_LEN 100
#define MAX_USERS 3
#define USERNAME_LEN 7 // 6 characters + 1 for null terminator
#define PASSWORD_LEN 7 // 6 characters + 1 for null terminator

typedef enum
{
    TRACTOR,
    EXCAVATOR,
    ROLLER,
    CRANE,
    MIXER
} MachineType;

typedef enum
{
    NEVER,
    LESS_THAN_THREE,
    LESS_THAN_FIVE,
    MORE_THAN_FIVE
} BreakdownFrequency;

static const char *MachineTypeNames[] = {
    "Tractor",
    "Excavator",
    "Roller",
    "Crane",
    "Mixer"};

static const char *BreakdownFreqNames[] = {
    "Never",
    "Less than three times",
    "Less than five times",
    "More than five times"};

typedef struct machine
{
    char chassisNumber[MAX_STR_LEN]; // Unique identifier
    char make[MAX_STR_LEN];
    char model[MAX_STR_LEN];
    int manufactureYear;
    double cost;
    double currentValuation;
    double currentMileage;
    double nextServiceMileage;
    char ownerName[MAX_STR_LEN];
    char ownerEmail[MAX_STR_LEN]; // Validate @, full stop, and .com separately
    char ownerPhone[MAX_STR_LEN];
    MachineType type;
    BreakdownFrequency breakdownsThisYear;
    struct machine *next;
    struct machine *previous;
} Machine;

typedef struct login
{
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    struct login *next;
    struct login *previous;
} Login;

// Function prototypes
int greetAndLogin();
int mainMenu();
void collectionBackup(Machine *collectionHeadPointer);
void collectionRestore(Machine **collectionHeadPointer, Machine **collectionTailPointer);
int validateEmail(const char *email);
int isUniqueChassis(Machine *headRef, const char *chassisNumber);
void sortByChassisNumber(Machine **headRef, Machine **tailRef);
void addMachine(Machine **headRef, Machine **tailRef);
void readInt(const char *prompt, int *value);
void readChar(const char *prompt, char *buffer, size_t size, int allowEmpty);
void readDouble(const char *prompt, double *value);
void displayAllMachines(Machine *headRef);
void displayMachineDetails(Machine *headRef);
void saveReport(Machine *headRef);
void displayAllByValuation(Machine *headRef);
void deleteMachine(Machine **headRef, Machine **tailRef);
void updateMachine(Machine *headRef);
void displayBreakdownStats(Machine *headRef, int category);

void runMachineryManagementProgram()
{
    if (!greetAndLogin())
        return;

    Machine *collectionHeadPointer = NULL; // pointer to the first item (head node)
    Machine *collectionTailPointer = NULL; // pointer to the last item (tail node)

    collectionRestore(&collectionHeadPointer, &collectionTailPointer);

    int action = mainMenu();
    while (action != 0)
    {
        switch (action)
        {
        case 1: // Add a machine
            addMachine(&collectionHeadPointer, &collectionTailPointer);
            break;
        case 2: // Display all machines to screen
            displayAllMachines(collectionHeadPointer);
            break;
        case 3: // Display machine details
            displayMachineDetails(collectionHeadPointer);
            break;
        case 4: // Update a machine's details
            updateMachine(collectionHeadPointer);
            break;
        case 5: // Delete machine
            deleteMachine(&collectionHeadPointer, &collectionTailPointer);
            break;
        case 10: // Statistics A
            displayBreakdownStats(collectionHeadPointer, NEVER);
            break;
        case 11: // Statistics B
            displayBreakdownStats(collectionHeadPointer, LESS_THAN_THREE);
            break;
        case 12: // Statistics C
            displayBreakdownStats(collectionHeadPointer, LESS_THAN_FIVE);
            break;
        case 13: // Statistics D
            displayBreakdownStats(collectionHeadPointer, MORE_THAN_FIVE);
            break;
        case 7: // Print all machine details into a report file
            saveReport(collectionHeadPointer);
            break;
        case 8: // List all machinery in order of current valuation
            displayAllByValuation(collectionHeadPointer);
            break;
        default:
            printf("Invalid choice. Please try again.\n\n");
        }
        action = mainMenu();
    }

    collectionBackup(collectionHeadPointer);
}

// Function to read an integer from user input
void readInt(const char *prompt, int *value)
{
    while (1)
    {
        printf("%s", prompt);
        if (scanf_s("%d", value) == 1)
        {
            while (getchar() != '\n')
                ; // Clear input buffer
            return;
        }
        else
        {
            printf("Invalid input. Please enter an integer.\n");
            while (getchar() != '\n')
                ; // Clear invalid input
        }
    }
}

// Function to read a char from user input
void readChar(const char *prompt, char *buffer, size_t size, int allowEmpty)
{
    while (1)
    {
        printf("%s", prompt);
        if (gets_s(buffer, size))
        {
            if (buffer[0] != '\0' || allowEmpty)
            {
                return;
            }
            else if (!allowEmpty)
            {
                printf("Input cannot be empty. Please try again.\n");
            }
        }
        else
        {
            printf("Invalid input. Please enter a valid string.\n");
        }
    }
}

// Function to read a double from user input
void readDouble(const char *prompt, double *value)
{
    while (1)
    {
        printf("%s", prompt);
        if (scanf_s("%lf", value) == 1)
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

// Function to log the user into the system
int greetAndLogin()
{
    printf("========================================\n");
    printf("== Machinery Management System Rev. 1.11 ==\n");
    printf("========================================\n\n");
    Sleep(1000);
    printf("Please log in to continue.\n");

    // 1. Load ResourceFiles/MachineryLogin.txt
    Login *headRef = NULL;
    Login *tailRef = NULL;

    FILE *file = fopen("ResourceFiles/MachineryLogin.txt", "r");
    if (!file)
    {
        printf("Login error: Could not open ResourceFiles/MachineryLogin.txt file.\n");
        Sleep(1000);
        return 0;
    }

    int count = 0;
    int authenticated = 0;
    while (count < MAX_USERS)
    {
        char user[USERNAME_LEN] = {0}, pass[PASSWORD_LEN] = {0};
        if (fscanf_s(file, "%6s %6s", user, (unsigned)sizeof(user), pass, (unsigned)sizeof(pass)) != 2)
            break;

        // Allocate a new node and append
        Login *node = malloc(sizeof *node);
        if (!node)
        {
            fclose(file);
            printf("Login error: Memory allocation failed.\n");
            Sleep(1000);
            return 0;
        }
        strcpy_s(node->username, sizeof node->username, user);
        strcpy_s(node->password, sizeof node->password, pass);
        node->next = NULL;
        node->previous = tailRef;
        if (tailRef)
            tailRef->next = node;
        else
            headRef = node;
        tailRef = node;
        count++;
    }
    fclose(file);

    // If none were read, treat as malformed
    if (count == 0)
    {
        printf("Login error: Invalid format in login file.\n");
        Sleep(1000);
        while (headRef)
        {
            Login *next = headRef->next;
            free(headRef);
            headRef = next;
        }
        headRef = NULL;
        tailRef = NULL;
        return 0;
    }

    // 2. Prompt for credentials & authenticate
    int attempts = 3;
    char enteredUsername[USERNAME_LEN] = {0};
    char enteredPassword[PASSWORD_LEN] = {0};

    while (attempts > 0)
    {
        readChar("\nEnter username: ", enteredUsername, sizeof(enteredUsername), 0);

        printf("Enter Password: ");
        int idx = 0;
        memset(enteredPassword, 0, sizeof(enteredPassword));
        while (idx < PASSWORD_LEN - 1)
        {
            char ch = _getch();
            // Enter key
            if (ch == '\r')
                break;
            // Backspace key
            if (ch == '\b' && idx > 0)
            {
                idx--;
                printf("\b \b");
            }
            else if (ch != '\b')
            {
                enteredPassword[idx++] = ch;
                printf("*");
            }
        }
        enteredPassword[idx] = '\0';
        printf("\n");

        for (Login *cur = headRef; cur; cur = cur->next)
        {
            if (_stricmp(cur->username, enteredUsername) == 0 &&
                strcmp(cur->password, enteredPassword) == 0)
            {
                authenticated = 1;
                break;
            }
        }

        if (authenticated)
        {
            printf("\nAccess granted! Welcome, %s.\n\n", enteredUsername);
            Sleep(1000);
            break;
        }
        else
        {
            attempts--;
            printf("\nIncorrect username or password. Attempts left: %d\n", attempts);
        }
    }

    if (!authenticated)
    {
        printf("\nAccess denied. Exiting program.\n\n");
        Sleep(1000);
    }

    while (headRef)
    {
        Login *next = headRef->next;
        free(headRef);
        headRef = next;
    }
    headRef = NULL;
    tailRef = NULL;

    return authenticated;
}

// Function to present menu options to the user
int mainMenu()
{
    printf("Please wait while menu options are being loaded...\n");
    Sleep(1000);
    system("cls");

    int choice = -1;
    char subChoice;
    int c;

    // Main menu input loop
    while (1)
    {
        printf("=== Machinery Management System Menu ===\n");
        printf("1. Add a machine\n");
        printf("2. Display all machines to screen\n");
        printf("3. Display machine details\n");
        printf("4. Update machine details\n");
        printf("5. Delete machine\n");
        printf("6. Generate statistics based on machinery type\n");
        printf("7. Print all machine details into a report file\n");
        printf("8. List all machinery in order of current valuation\n");
        printf("0. Exit program\n");
        readInt("Enter your choice: ", &choice);

        // Handle submenu
        if (choice == 6)
        {
            while (1)
            {
                char subChoice[MAX_STR_LEN];
                printf("\n--- Please specify the statistics type ---\n");
                printf("A. %% of machines with no breakdowns\n");
                printf("B. %% of machines with less than 3 breakdowns\n");
                printf("C. %% of machines with less than 5 breakdowns\n");
                printf("D. %% of machines with more than 5 breakdowns\n");
                readChar("Enter your choice: ", subChoice, sizeof(subChoice), 0);

                switch (subChoice[0])
                {
                case 'A':
                case 'a':
                    return 10;
                case 'B':
                case 'b':
                    return 11;
                case 'C':
                case 'c':
                    return 12;
                case 'D':
                case 'd':
                    return 13;
                default:
                    printf("Invalid submenu choice. Please enter A, B, C, or D.\n");
                    break;
                }
            }
        }

        // Valid main menu choices (0 � 8)
        if (choice >= 0 && choice <= 8)
        {
            return choice;
        }

        // Invalid main menu option
        printf("Invalid choice. Please enter a number between 0 and 8.\n\n");
    }
}

// Function to save machine details to file
void collectionBackup(Machine *collectionHeadPointer)
{
    printf("Please wait while the backup is being created...\n");
    Sleep(1000);
    FILE *file = fopen("ResourceFiles/fleet.txt", "w"); // "w" mode: create or overwrite

    if (!file)
    {
        printf("Backup error: Could not open ResourceFiles/fleet.txt for writing.\n");
        Sleep(1000);
        return;
    }

    Machine *current = collectionHeadPointer;

    while (current != NULL)
    {
        // Save each machine's details line by line
        fprintf(file,
                "%s\n%s\n%s\n%d\n%.2f\n%.2f\n%.2f\n%.2f\n%s\n%s\n%s\n%d\n%d\n",
                current->chassisNumber,
                current->make,
                current->model,
                current->manufactureYear,
                current->cost,
                current->currentValuation,
                current->currentMileage,
                current->nextServiceMileage,
                current->ownerName,
                current->ownerEmail,
                current->ownerPhone,
                current->type,
                current->breakdownsThisYear);

        current = current->next; // Move to the next machine
    }

    fclose(file);

    printf("Backup successful: ResourceFiles/fleet.txt updated.\n");
    Sleep(1000);
}

// Function to restore machine details from file
void collectionRestore(Machine **collectionHeadPointer, Machine **collectionTailPointer)
{
    printf("Please wait while the backup is being restored...\n");
    Sleep(1000);
    FILE *file = fopen("ResourceFiles/fleet.txt", "r");
    if (!file)
    {
        printf("Restore error: Could not open ResourceFiles/fleet.txt for reading.\n\n");
        Sleep(1000);
        return;
    }

    Machine *newMachine = NULL;
    Machine *lastMachine = NULL;
    char buffer[MAX_STR_LEN];

    // Free the existing list
    Machine *current = *collectionHeadPointer;
    while (current != NULL)
    {
        Machine *temp = current;
        current = current->next;
        free(temp);
    }

    // Reset head and tail to NULL
    *collectionHeadPointer = NULL;
    *collectionTailPointer = NULL;

    // Restore data from file
    while (!feof(file))
    {
        newMachine = (Machine *)malloc(sizeof(Machine));
        if (!newMachine)
        {
            printf("Restore error: Memory allocation failed.\n\n");
            fclose(file);
            Sleep(1000);
            return;
        }

        // Read all fields in same order as saved
        if (fgets(buffer, MAX_STR_LEN, file) == NULL)
        {
            free(newMachine);
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline and null-terminate
        strcpy_s(newMachine->chassisNumber, sizeof(newMachine->chassisNumber), buffer);

        if (fgets(buffer, MAX_STR_LEN, file) == NULL)
        {
            free(newMachine);
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy_s(newMachine->make, sizeof(newMachine->make), buffer);

        if (fgets(buffer, MAX_STR_LEN, file) == NULL)
        {
            free(newMachine);
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy_s(newMachine->model, sizeof(newMachine->model), buffer);

        if (fscanf_s(file, "%d\n", &newMachine->manufactureYear) != 1)
        {
            free(newMachine);
            break;
        }
        if (fscanf_s(file, "%lf\n", &newMachine->cost) != 1)
        {
            free(newMachine);
            break;
        }
        if (fscanf_s(file, "%lf\n", &newMachine->currentValuation) != 1)
        {
            free(newMachine);
            break;
        }
        if (fscanf_s(file, "%lf\n", &newMachine->currentMileage) != 1)
        {
            free(newMachine);
            break;
        }
        if (fscanf_s(file, "%lf\n", &newMachine->nextServiceMileage) != 1)
        {
            free(newMachine);
            break;
        }

        if (fgets(buffer, MAX_STR_LEN, file) == NULL)
        {
            free(newMachine);
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy_s(newMachine->ownerName, sizeof(newMachine->ownerName), buffer);

        if (fgets(buffer, MAX_STR_LEN, file) == NULL)
        {
            free(newMachine);
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy_s(newMachine->ownerEmail, sizeof(newMachine->ownerEmail), buffer);

        if (fgets(buffer, MAX_STR_LEN, file) == NULL)
        {
            free(newMachine);
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy_s(newMachine->ownerPhone, sizeof(newMachine->ownerPhone), buffer);

        int tempType, tempBreakdowns;
        if (fscanf_s(file, "%d\n", &tempType) != 1)
        {
            free(newMachine);
            break;
        }
        if (fscanf_s(file, "%d\n", &tempBreakdowns) != 1)
        {
            free(newMachine);
            break;
        }

        newMachine->type = (MachineType)tempType;
        newMachine->breakdownsThisYear = (BreakdownFrequency)tempBreakdowns;

        // Set pointers
        newMachine->next = NULL;
        newMachine->previous = NULL;

        // Insert into the linked list
        if (*collectionHeadPointer == NULL)
        {
            // First machine
            *collectionHeadPointer = newMachine;
            *collectionTailPointer = newMachine;
        }
        else
        {
            // Append to the list
            newMachine->previous = *collectionTailPointer;
            (*collectionTailPointer)->next = newMachine;
            *collectionTailPointer = newMachine;
        }
    }

    fclose(file);
    printf("Restore successful: Fleet restored successfully from ResourceFiles/fleet.txt.\n\n");
    Sleep(1000);
}

// Function to validate email format
int validateEmail(const char *email)
{
    // 1. Find the '@'
    const char *at = strchr(email, '@');
    if (!at)
        return 0; // no '@'
    if (at == email)
        return 0; // can't start with '@'

    // 2. Only one '@'
    if (strchr(at + 1, '@'))
        return 0;

    // 3. At least one '.' before the '@'
    int hasDot = 0;
    for (const char *p = email; p < at; p++)
    {
        if (*p == '.')
        {
            hasDot = 1;
            break;
        }
    }
    if (!hasDot)
        return 0;

    // 4. Check suffix is ".com"
    size_t len = strlen(email);
    if (len < 4)
        return 0; // too short to end ".com"
    if (strcmp(email + len - 4, ".com") != 0)
        return 0;

    // All checks passed
    return 1;
}

// Checks for unique chassis number in the linked list
int isUniqueChassis(Machine *headRef, const char *chassisNumber)
{
    Machine *current = headRef;
    while (current)
    {
        if (strcmp(current->chassisNumber, chassisNumber) == 0)
        {
            return 0; // found a match - not unique
        }
        current = current->next;
    }
    return 1; // no matches - unique
}

// Sorts the linked list by chassis number using bottom-up merge sort
void sortByChassisNumber(Machine **headRef, Machine **tailRef)
{
    // Check if the list is empty or has only one element
    if (!headRef || !*headRef)
        return;

    // 1. Compute list length
    int length = 0;
    for (Machine *p = *headRef; p; p = p->next)
        ++length;
    if (length < 2)
    {
        *tailRef = *headRef;
        return;
    }

    // 2. Set up a dummy node to simplify merges at head
    Machine dummy;
    dummy.previous = NULL;
    dummy.next = *headRef;
    (*headRef)->previous = &dummy;

    Machine *newTail = NULL;

    // 3. Bottom-up merge: step = sublist size
    // step <<= 1 means step *= 2 (single left shift)
    for (int step = 1; step < length; step <<= 1)
    {
        Machine *prev = &dummy;
        Machine *curr = dummy.next;

        while (curr)
        {
            // split off left of size "step"
            Machine *left = curr;
            Machine *leftTail = left;
            for (int i = 1; i < step && leftTail->next; ++i)
                leftTail = leftTail->next;

            // split off right of size "step"
            Machine *right = leftTail->next;
            leftTail->next = NULL;
            if (right)
                right->previous = NULL;

            // find the end of the right run
            Machine *rightTail = right;
            for (int i = 1; i < step && rightTail && rightTail->next; ++i)
                rightTail = rightTail->next;

            // remember what comes after rightTail
            Machine *next = NULL;
            if (rightTail)
            {
                next = rightTail->next;
                rightTail->next = NULL;
                if (next)
                    next->previous = NULL;
            }

            // merge "left" and "right" by chassisNumber
            Machine *l = left;
            Machine *r = right;
            while (l && r)
            {
                if (_stricmp(l->chassisNumber, r->chassisNumber) <= 0)
                {
                    prev->next = l;
                    l->previous = prev;
                    l = l->next;
                }
                else
                {
                    prev->next = r;
                    r->previous = prev;
                    r = r->next;
                }
                prev = prev->next;
            }
            // attach remainder of whichever list is non-empty
            Machine *rem = l ? l : r;
            while (rem)
            {
                prev->next = rem;
                rem->previous = prev;
                prev = rem;
                rem = rem->next;
            }

            // advance to the next pair
            curr = next;
        }

        // finish this pass
        prev->next = NULL;           // terminate the list
        dummy.next->previous = NULL; // detach dummy
        newTail = prev;              // recoed real tail
    }

    // 4. Disconnect the dummy node (Update headRef / tailRef)
    *headRef = dummy.next;
    (*headRef)->previous = NULL;
    *tailRef = newTail;
}

// Function to add a new machine to the linked list
void addMachine(Machine **headRef, Machine **tailRef)
{
    printf("\nPlease wait while the add function is being initialized...\n");
    Sleep(1000);
    system("cls");

    Machine *newMachine = malloc(sizeof(*newMachine));
    if (!newMachine)
    {
        printf("Add error: Memory allocation failed.\n");
        return;
    }
    char buffer[MAX_STR_LEN];

    // 1. chassisNumber (must be unique)
    do
    {
        readChar("Enter chassis number: ", buffer, sizeof(buffer), 0);
        if (!isUniqueChassis(*headRef, buffer))
        {
            printf("That chassis number already exists. Please try again.\n\n");
        }
        else
            break;
    } while (1);
    strcpy_s(newMachine->chassisNumber, sizeof(newMachine->chassisNumber), buffer);

    // 2. make
    readChar("Enter make: ", newMachine->make, sizeof(newMachine->make), 0);

    // 3. model
    readChar("Enter model: ", newMachine->model, sizeof(newMachine->model), 0);

    // 4. manufactureYear
    readInt("Enter year of manufacture: ", &newMachine->manufactureYear);

    // 5. cost
    readDouble("Enter cost: ", &newMachine->cost);

    // 6. currentValuation
    readDouble("Enter current valuation: ", &newMachine->currentValuation);

    // 7. currentMileage
    readDouble("Enter current mileage: ", &newMachine->currentMileage);

    // 8. nextServiceMileage
    readDouble("Enter next service mileage: ", &newMachine->nextServiceMileage);

    // 9. ownerName
    readChar("Enter owner name: ", newMachine->ownerName, sizeof(newMachine->ownerName), 0);

    // 10. ownerEmail (validate format)
    do
    {
        readChar("Enter owner email: ", buffer, sizeof(buffer), 0);
        if (!validateEmail(buffer))
        {
            printf("Invalid email. Must contain one '@', at least one '.', and end with \".com\". Please try again.\n");
        }
        else
            break;
    } while (1);
    strcpy_s(newMachine->ownerEmail, sizeof(newMachine->ownerEmail), buffer);

    // 11. ownerPhone
    readChar("Enter owner phone: ", newMachine->ownerPhone, sizeof(newMachine->ownerPhone), 0);

    // 12. type
    int t;
    printf("Select machine type:\n");
    for (int i = 0; i < sizeof(MachineTypeNames) / sizeof(MachineTypeNames[0]); i++)
    {
        printf("%d. %s\n", i + 1, MachineTypeNames[i]);
    }
    do
    {
        readInt("Enter type: ", &t);
        t--;
        if (t < 0 || t >= sizeof(MachineTypeNames) / sizeof(MachineTypeNames[0]))
        {
            printf("Invalid selection. Please enter a number between 1 and %zu.\n", sizeof(MachineTypeNames) / sizeof(MachineTypeNames[0]));
        }
    } while (t < 0 || t >= sizeof(MachineTypeNames) / sizeof(MachineTypeNames[0]));
    newMachine->type = (MachineType)t;

    // 13. breakdownsThisYear
    int b;
    printf("Select breakdown frequency:\n");
    for (int i = 0; i < sizeof(BreakdownFreqNames) / sizeof(BreakdownFreqNames[0]); i++)
    {
        printf("%d. %s\n", i + 1, BreakdownFreqNames[i]);
    }
    do
    {
        readInt("Enter frequency: ", &b);
        b--;
        if (b < 0 || b >= sizeof(BreakdownFreqNames) / sizeof(BreakdownFreqNames[0]))
        {
            printf("Invalid selection. Please enter a number between 1 and %zu.\n", sizeof(BreakdownFreqNames) / sizeof(BreakdownFreqNames[0]));
        }
    } while (b < 0 || b >= sizeof(BreakdownFreqNames) / sizeof(BreakdownFreqNames[0]));
    newMachine->breakdownsThisYear = (BreakdownFrequency)b;

    // Initialize links
    newMachine->next = NULL;
    newMachine->previous = NULL;

    // Append to tail
    if (*headRef == NULL)
    {
        *headRef = *tailRef = newMachine;
    }
    else
    {
        newMachine->previous = *tailRef;
        (*tailRef)->next = newMachine;
        *tailRef = newMachine;
    }

    printf("Please wait while machine data is being saved...\n");
    Sleep(1000);
    printf("Machine added successfully.\n");
    Sleep(1000);
    printf("Please wait while the machine list is being sorted...\n");
    Sleep(1000);
    sortByChassisNumber(headRef, tailRef);
    printf("List sorted successfully.\n");
    Sleep(1000);
}

// Function to display all machines sorted by chassis number
void displayAllMachines(Machine *headRef)
{
    printf("\nPlease wait while the machine list is being loaded...\n");
    Sleep(1000);
    system("cls");
    if (!headRef)
    {
        printf("No machines are registered yet.\n");
        system("pause");
        return;
    }

    printf("=== All Machinery Details (by Chassis Number) ===\n\n");
    int idx = 1;
    for (Machine *cur = headRef; cur; cur = cur->next, ++idx)
    {
        printf("Machine #%d:\n", idx);
        printf("\tChassis Number      : %s\n", cur->chassisNumber);
        printf("\tMake                : %s\n", cur->make);
        printf("\tModel               : %s\n", cur->model);
        printf("\tYear of Manufacture : %d\n", cur->manufactureYear);
        printf("\tCost                : %.2f\n", cur->cost);
        printf("\tCurrent Valuation   : %.2f\n", cur->currentValuation);
        printf("\tCurrent Mileage     : %.2f\n", cur->currentMileage);
        printf("\tNext Service Mileage: %.2f\n", cur->nextServiceMileage);
        printf("\tOwner Name          : %s\n", cur->ownerName);
        printf("\tOwner Email         : %s\n", cur->ownerEmail);
        printf("\tOwner Phone         : %s\n", cur->ownerPhone);
        printf("\tMachine Type        : %s\n", MachineTypeNames[cur->type]);
        printf("\tBreakdowns This Year: %s\n\n", BreakdownFreqNames[cur->breakdownsThisYear]);
    }
    system("pause");
}

// Function to display details of a specific machine
void displayMachineDetails(Machine *headRef)
{
    printf("\nPlease wait while the function initializes...\n");
    Sleep(1000);
    system("cls");
    if (!headRef)
    {
        printf("No machines are registered yet.\n");
        system("pause");
        return;
    }

    char searchChassis[MAX_STR_LEN];
    readChar("Enter chassis number to look up: ", searchChassis, sizeof(searchChassis), 0);

    printf("\nPlease wait while the search function executes...\n");
    Sleep(1000);

    // Search the list (case-insensitive)
    Machine *cur = headRef;
    while (cur)
    {
        if (_stricmp(cur->chassisNumber, searchChassis) == 0)
        {
            // Found � print details
            printf("\n=== Machine Details for \"%s\" ===\n", cur->chassisNumber);
            printf("\tChassis Number      : %s\n", cur->chassisNumber);
            printf("\tMake                : %s\n", cur->make);
            printf("\tModel               : %s\n", cur->model);
            printf("\tYear of Manufacture : %d\n", cur->manufactureYear);
            printf("\tCost                : %.2f\n", cur->cost);
            printf("\tCurrent Valuation   : %.2f\n", cur->currentValuation);
            printf("\tCurrent Mileage     : %.2f\n", cur->currentMileage);
            printf("\tNext Service Mileage: %.2f\n", cur->nextServiceMileage);
            printf("\tOwner Name          : %s\n", cur->ownerName);
            printf("\tOwner Email         : %s\n", cur->ownerEmail);
            printf("\tOwner Phone         : %s\n", cur->ownerPhone);
            printf("\tMachine Type        : %s\n", MachineTypeNames[cur->type]);
            printf("\tBreakdowns This Year: %s\n\n", BreakdownFreqNames[cur->breakdownsThisYear]);
            system("pause");
            return;
        }
        cur = cur->next;
    }

    // Not found
    printf("\nNo machine with chassis number \"%s\" was found.\n", searchChassis);
    system("pause");
}

// Function to save a report of all machines to a file
void saveReport(Machine *headRef)
{
    printf("\nPlease wait while the function initializes...\n");
    Sleep(1000);
    system("cls");
    if (!headRef)
    {
        printf("No machines registered yet.\n");
        system("pause");
        return;
    }

    char baseName[MAX_STR_LEN];
    char fileName[MAX_STR_LEN + 5]; // enough for ".txt" + '\0'

    // 1. Ask user for report file name
    readChar("Enter report file name (without extension): ", baseName, sizeof(baseName), 0);

    // 2. Build the filename
    snprintf(fileName, sizeof(fileName), "ResourceFiles/%s.txt", baseName);

    printf("Please wait while report \"%s\" is being created...\n", fileName);
    Sleep(1000);

    // 3. Open for writing (overwrite if exists)
    FILE *file = fopen(fileName, "w");
    if (!file)
    {
        printf("Report error: Could not open \"%s\" for writing.\n", fileName);
        Sleep(1000);
        return;
    }

    // 4. Write header
    fprintf(file, "=== Machinery Report ===\n");

    // 5. Iterate and print each machine
    int idx = 1;
    for (Machine *cur = headRef; cur; cur = cur->next, ++idx)
    {
        fprintf(file, "\n--- Machine #%d ---\n", idx);
        fprintf(file, "Chassis Number      : %s\n", cur->chassisNumber);
        fprintf(file, "Make                : %s\n", cur->make);
        fprintf(file, "Model               : %s\n", cur->model);
        fprintf(file, "Year of Manufacture : %d\n", cur->manufactureYear);
        fprintf(file, "Cost                : %.2f\n", cur->cost);
        fprintf(file, "Current Valuation   : %.2f\n", cur->currentValuation);
        fprintf(file, "Current Mileage     : %.2f\n", cur->currentMileage);
        fprintf(file, "Next Service Mileage: %.2f\n", cur->nextServiceMileage);
        fprintf(file, "Owner Name          : %s\n", cur->ownerName);
        fprintf(file, "Owner Email         : %s\n", cur->ownerEmail);
        fprintf(file, "Owner Phone         : %s\n", cur->ownerPhone);
        fprintf(file, "Machine Type        : %s\n", MachineTypeNames[cur->type]);
        fprintf(file, "Breakdowns This Year: %s\n", BreakdownFreqNames[cur->breakdownsThisYear]);
    }

    // 6. Compute and write performance statistics
    int total = 0;
    int counts[4] = {0};
    for (Machine *cur = headRef; cur; cur = cur->next)
    {
        total++;
        counts[cur->breakdownsThisYear]++;
    }

    fprintf(file, "\n\n=== Performance Statistics ===\n");
    fprintf(file, "Total Machines: %d\n\n", total);
    for (int i = 0; i < 4; ++i)
    {
        double pct = total ? (counts[i] * 100.0) / total : 0.0;
        fprintf(file, "%s:\n", BreakdownFreqNames[i]);
        fprintf(file, "\tCount   : %d\n", counts[i]);
        fprintf(file, "\tPercent : %.2f%%\n\n", pct);
    }

    fclose(file);

    printf("Report saved successfully to '%s'.\n", fileName);
    Sleep(1000);
}

// Function to display all machines sorted by current valuation
void displayAllByValuation(Machine *headRef)
{
    printf("\nPlease wait while the function initializes...\n");
    Sleep(1000);
    system("cls");
    if (!headRef)
    {
        printf("No machines are registered yet.\n");
        system("pause");
        return;
    }

    // 1. Count machines
    int count = 0;
    for (Machine *cur = headRef; cur; cur = cur->next)
        ++count;

    // 2. Build an array of pointers to each Machine
    Machine **arr = malloc(count * sizeof(Machine *));
    if (!arr)
    {
        printf("Display error: Memory allocation failed.\n");
        system("pause");
        return;
    }
    int idx = 0;
    for (Machine *cur = headRef; cur; cur = cur->next)
        arr[idx++] = cur;

    // 3. Sort the array in-place by currentValuation descending (selection sort)
    for (int i = 0; i < count - 1; ++i)
    {
        int max_idx = i;
        for (int j = i + 1; j < count; ++j)
        {
            if (arr[j]->currentValuation > arr[max_idx]->currentValuation)
                max_idx = j;
        }
        if (max_idx != i)
        {
            Machine *tmp = arr[i];
            arr[i] = arr[max_idx];
            arr[max_idx] = tmp;
        }
    }

    // 4. Print in sorted order
    printf("=== All Machinery Details (by Current Valuation) ===\n\n");
    for (int i = 0; i < count; ++i)
    {
        Machine *m = arr[i];
        printf("Machine #%d:\n", i + 1);
        printf("\tChassis Number      : %s\n", m->chassisNumber);
        printf("\tMake                : %s\n", m->make);
        printf("\tModel               : %s\n", m->model);
        printf("\tYear of Manufacture : %d\n", m->manufactureYear);
        printf("\tCost                : %.2f\n", m->cost);
        printf("\tCurrent Valuation   : %.2f\n", m->currentValuation);
        printf("\tCurrent Mileage     : %.2f\n", m->currentMileage);
        printf("\tNext Service Mileage: %.2f\n", m->nextServiceMileage);
        printf("\tOwner Name          : %s\n", m->ownerName);
        printf("\tOwner Email         : %s\n", m->ownerEmail);
        printf("\tOwner Phone         : %s\n", m->ownerPhone);
        printf("\tMachine Type        : %s\n", MachineTypeNames[m->type]);
        printf("\tBreakdowns This Year: %s\n\n", BreakdownFreqNames[m->breakdownsThisYear]);
    }

    // 5. Clean up and pause
    free(arr);
    system("pause");
}

// Function to delete a machine from the linked list
void deleteMachine(Machine **headRef, Machine **tailRef)
{
    printf("\nPlease wait while the delete function initializes...\n");
    Sleep(1000);
    system("cls");
    if (!*headRef)
    {
        printf("No machines are registered yet.\n");
        system("pause");
        return;
    }

    // 1. Ask for the chassis number to delete
    char target[MAX_STR_LEN];
    readChar("Enter chassis number to delete: ", target, sizeof(target), 0);
    printf("\nPlease wait while the system searches for the machine \"%s\"\n", target);
    Sleep(1000);

    // 2. Find the node
    Machine *cur = *headRef;
    while (cur)
    {
        if (_stricmp(cur->chassisNumber, target) == 0)
        {
            // 3. Confirm deletion
            char resp[4];
            readChar("Are you sure you want to delete this machine? (Y/N): ", resp, sizeof(resp), 0);
            if (!(resp[0] == 'Y' || resp[0] == 'y'))
            {
                printf("Deletion cancelled.\n");
                system("pause");
                return;
            }
            printf("\nPlease wait while the delete function executes\n");
            Sleep(1000);

            // 4. Unlink from list
            if (cur->previous)
            {
                cur->previous->next = cur->next;
            }
            else
            {
                // was head
                *headRef = cur->next;
            }
            if (cur->next)
            {
                cur->next->previous = cur->previous;
            }
            else
            {
                // was tail
                *tailRef = cur->previous;
            }

            // 4. Free and report
            free(cur);
            printf("Machine \"%s\" deleted successfully.\n", target);
            return;
        }
        cur = cur->next;
    }

    // Not found
    printf("No machine with chassis number \"%s\" was found.\n", target);
    system("pause");
}

// Function to update a machine's details
void updateMachine(Machine *headRef)
{
    printf("\nPlease wait while the delete function initializes...\n");
    Sleep(1000);
    system("cls");
    if (!headRef)
    {
        printf("No machines registered yet.\n");
        system("pause");
        return;
    }

    // 1. Ask for the chassis number to update
    char target[MAX_STR_LEN];
    readChar("Enter chassis number to update: ", target, sizeof(target), 0);
    printf("\nPlease wait while the system searches for the machine \"%s\"\n", target);
    Sleep(1000);

    // 2. Find the machine (case-insensitive)
    Machine *cur = headRef;
    while (cur && _stricmp(cur->chassisNumber, target) != 0)
    {
        cur = cur->next;
    }
    if (!cur)
    {
        printf("No machine with chassis number \"%s\" was found.\n", target);
        system("pause");
        return;
    }

    // 3. Update details
    printf("\nFound machine \"%s\". Press Enter to skip any field.\n\n", cur->chassisNumber);

    char buf[MAX_STR_LEN];
    char *endptr;

    // 1. Make
    printf("Current Make: %s\n", cur->make);
    readChar("New Make: ", buf, sizeof buf, 1);
    if (buf[0])
    {
        strcpy_s(cur->make, sizeof cur->make, buf);
    }

    // 2. Model
    printf("\nCurrent Model: %s\n", cur->model);
    readChar("New Model: ", buf, sizeof buf, 1);
    if (buf[0])
    {
        strcpy_s(cur->model, sizeof cur->model, buf);
    }

    // 3. Year of Manufacture
    printf("\nCurrent Year of Manufacture: %d\n", cur->manufactureYear);
    readChar("New Year of Manufacture: ", buf, sizeof buf, 1);
    if (buf[0])
    {
        long v = strtol(buf, &endptr, 10);
        if (endptr != buf)
        {
            cur->manufactureYear = (int)v;
        }
    }

    // 4. Cost
    printf("\nCurrent Cost: %.2f\n", cur->cost);
    readChar("New Cost: ", buf, sizeof buf, 1);
    if (buf[0])
    {
        double d = strtod(buf, &endptr);
        if (endptr != buf)
        {
            cur->cost = d;
        }
    }

    // 5. Current Valuation
    printf("\nCurrent Valuation: %.2f\n", cur->currentValuation);
    readChar("New Current Valuation: ", buf, sizeof buf, 1);
    if (buf[0])
    {
        double d = strtod(buf, &endptr);
        if (endptr != buf)
        {
            cur->currentValuation = d;
        }
    }

    // 6. Current Mileage
    printf("\nCurrent Mileage: %.2f\n", cur->currentMileage);
    readChar("New Current Mileage: ", buf, sizeof buf, 1);
    if (buf[0])
    {
        double d = strtod(buf, &endptr);
        if (endptr != buf)
        {
            cur->currentMileage = d;
        }
    }

    // 7. Next Service Mileage
    printf("\nNext Service Mileage: %.2f\n", cur->nextServiceMileage);
    readChar("New Next Service Mileage: ", buf, sizeof buf, 1);
    if (buf[0])
    {
        double d = strtod(buf, &endptr);
        if (endptr != buf)
        {
            cur->nextServiceMileage = d;
        }
    }

    // 8. Owner Name
    printf("\nCurrent Owner Name: %s\n", cur->ownerName);
    readChar("New Owner Name: ", buf, sizeof buf, 1);
    if (buf[0])
    {
        strcpy_s(cur->ownerName, sizeof cur->ownerName, buf);
    }

    // 9. Owner Email
    printf("\nCurrent Owner Email: %s\n", cur->ownerEmail);
    while (1)
    {
        readChar("New Owner Email: ", buf, sizeof buf, 1);
        if (!buf[0])
            break;
        if (validateEmail(buf))
        {
            strcpy_s(cur->ownerEmail, sizeof cur->ownerEmail, buf);
            break;
        }
        else
        {
            printf("Invalid email. Must contain one '@', at least one '.', and end with \".com\". Please try again.\n");
        }
    }

    // 10. Owner Phone
    printf("\nCurrent Owner Phone: %s\n", cur->ownerPhone);
    readChar("New Owner Phone: ", buf, sizeof buf, 1);
    if (buf[0])
    {
        strcpy_s(cur->ownerPhone, sizeof cur->ownerPhone, buf);
    }

    // 11. Machine Type
    printf("\nCurrent Machine Type: %s\nAvailable Types:\n", MachineTypeNames[cur->type]);
    for (int i = 0; i < sizeof(MachineTypeNames) / sizeof(MachineTypeNames[0]); i++)
    {
        printf("%d. %s\n", i + 1, MachineTypeNames[i]);
    }
    while (1)
    {
        readChar("New Type (1 - 5): ", buf, sizeof buf, 1);
        if (buf[0] == '\0')
        {
            // skip on Enter
            break;
        }
        long v = strtol(buf, &endptr, 10);
        if (endptr != buf && *endptr == '\0' && v >= 1 && v <= 5)
        {
            cur->type = (MachineType)(v - 1);
            break;
        }
        printf("Invalid selection. Please enter a number between 1 and %zu or press Enter to skip.\n", sizeof(MachineTypeNames) / sizeof(MachineTypeNames[0]));
    }

    // 12. Breakdown Frequency
    printf("\nCurrent Breakdowns This Year: %s\nAvailable Options:\n", BreakdownFreqNames[cur->breakdownsThisYear]);
    for (int i = 0; i < sizeof(BreakdownFreqNames) / sizeof(BreakdownFreqNames[0]); i++)
    {
        printf("%d. %s\n", i + 1, BreakdownFreqNames[i]);
    }
    while (1)
    {
        readChar("New Frequency (1 - 4): ", buf, sizeof buf, 1);
        if (buf[0] == '\0')
        {
            // skip on Enter
            break;
        }
        long v = strtol(buf, &endptr, 10);
        if (endptr != buf && *endptr == '\0' && v >= 1 && v <= 4)
        {
            cur->breakdownsThisYear = (BreakdownFrequency)(v - 1);
            break;
        }
        printf("Invalid selection. Please enter a number between 1 and %zu or press Enter to skip.\n", sizeof(BreakdownFreqNames) / sizeof(BreakdownFreqNames[0]));
    }

    printf("\Details of machine \"%s\" updated successfully.\n", cur->chassisNumber);
    Sleep(1000);
}

// Function to display breakdown statistics
void displayBreakdownStats(Machine *headRef, int category)
{
    printf("\nPlease wait while the statistics function initializes...\n");
    Sleep(1000);
    system("cls");
    if (!headRef)
    {
        printf("No machines are registered yet.\n");
        system("pause");
        return;
    }

    int total = 0;
    int matches = 0;
    for (Machine *cur = headRef; cur; cur = cur->next)
    {
        total++;
        if (cur->breakdownsThisYear == (BreakdownFrequency)category)
            matches++;
    }

    double percent = (matches * 100.0) / total;
    printf("=== Breakdown Statistics ===\n");
    printf("Category: %s\n", BreakdownFreqNames[category]);
    printf("Matched:  %d out of %d machines\n", matches, total);
    printf("Percent:  %.2f%%\n\n", percent);
    system("pause");
}
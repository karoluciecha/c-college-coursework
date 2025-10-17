#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOGIN_FILE "ResourceFiles/loginn.txt"
#define DATABASE_FILE "ResourceFiles/libraryy.txt"

// Structure for a book
typedef struct book
{
    int isbn;
    char title[31];  // 30 characters + 1 for null terminator
    char author[26]; // 25 characters + 1 for null terminator
    double price;
    struct book *next;
} Book;

// Function prototypes
int login();
void displayMenu(int isAdmin, Book **headPtr);
void libraryBackup(Book *headPtr);
void libraryRestore(Book **headPtr);
void addBookStart(Book **headPtr);
void addBookPosition(Book **headPtr);
void addBookLast(Book **headPtr);
void deleteBookStart(Book **headPtr);
void deleteBookPosition(Book **headPtr);
void deleteBookLast(Book **headPtr);
void deleteBookIsbn(Book **headPtr);
void searchBookIsbn(Book *headPtr);
void displayBookAll(Book *headPtr);
void editBookAll(Book **headPtr);
void editBookIsbn(Book **headPtr);
void editBookTitle(Book **headPtr);
void editBookAuthor(Book **headPtr);
void editBookPrice(Book **headPtr);

void runLinkedLibraryProgram()
{
    Book *libraryPointer = NULL; // pointer to the first book (head node)
    int isAdmin = login();
    int choice = 0;

    if (isAdmin)
    {
        // Admin: Load or create a new database;
        do
        {
            readInt("Do you want to:\n1. Load a previously saved database\n2. Create a new database\nEnter choice: ", &choice);
            system("cls");
        } while (choice != 1 && choice != 2);
    }
    else
    {
        // Guest: Load the database
        choice = 1;
    }

    if (choice == 1)
    {
        printf("Loading the library...\n");
        libraryRestore(&libraryPointer);
    }
    else if (choice == 2)
    {
        printf("Creating a new library...\n");
    }

    displayMenu(isAdmin, &libraryPointer);

    // Freeing memory
    Book *temp;
    while (libraryPointer != NULL)
    {
        temp = libraryPointer;
        libraryPointer = libraryPointer->next;
        free(temp);
    }

    printf("Program terminated. Goodbye!\n\n");
    system("pause");
    system("cls");
}

// Function to log in as Admin or Guest
int login()
{
    char password[20], storedPassword[20];
    FILE *file = fopen(LOGIN_FILE, "r");

    if (file == NULL)
    {
        printf("Error: Cannot open login file.\n");
        return 0;
    }
    fscanf_s(file, "%19s", storedPassword, (unsigned)sizeof(storedPassword));
    storedPassword[19] = '\0'; // Ensure null termination
    fclose(file);

    int choice = 0;
    do
    {
        readInt("Login as:\n1. Admin\n2. Guest\nEnter choice: ", &choice);
        system("cls");
    } while (choice != 1 && choice != 2);

    if (choice == 1)
    {
        printf("Enter Admin Password: ");
        scanf_s("%19s", password, (unsigned)sizeof(password));
        password[19] = '\0'; // Ensure null termination
        while (getchar() != '\n')
            ; // Clear input buffer
        if (strcmp(password, storedPassword) == 0)
        {
            printf("Login Successful! Welcome, Admin.\n");
            return 1; // Admin access granted
        }
        else
        {
            printf("Incorrect Password! Changing login to Guest.\n");
        }
    }

    printf("Logged in as Guest.\n");
    return 0; // Guest access
}

// Function to display menu options
void displayMenu(int isAdmin, Book **headPtr)
{
    int option = 0;
    do
    {
        if (!isAdmin)
            readInt("Library Management System Menu:\n1. Search for a book by ISBN\n2. Display all books\n-1. to exit\n----------------------------------\nPlease enter your option: ", &option);
        else
            readInt("Library Management System Menu:\n1. Search for a book by ISBN\n2. Display all books\n3. Add a new book\n4. Edit a book's details\n5. Delete a book\n6. Save the database\n-1. to exit\n----------------------------------\nPlease enter your option: ", &option);

        if (option == 1)
            searchBookIsbn(*headPtr); // Function to search for a book by ISBN
        else if (option == 2)
            displayBookAll(*headPtr); // Function to display all books
        else if (option == 3 && isAdmin)
        {
            do
            {
                system("cls");
                option = 0;
                printf("1. to add a book at the start\n");
                printf("2. to add a book at the position\n");
                printf("3. to add a book at the end\n");
                printf("-1. to go back\n");
                printf("----------------------------------\n");
                readInt("Please enter your option: ", &option);

                if (option == 1)
                    addBookStart(headPtr);
                else if (option == 2)
                    addBookPosition(headPtr);
                else if (option == 3)
                    addBookLast(headPtr);
                else if (option == -1)
                    printf("Back to Main Menu...\n");
                else
                    printf("Invalid option\n");

                if (option != -1)
                {
                    system("pause");
                }
            } while (option != -1);
            option = 0;
        }
        else if (option == 4 && isAdmin)
        {
            do
            {
                system("cls");
                option = 0;
                printf("1. to edit all book information\n");
                printf("2. to edit the book ISBN\n");
                printf("3. to edit the book title\n");
                printf("4. to edit the book author\n");
                printf("5. to edit the book price\n");
                printf("-1. to go back\n");
                printf("----------------------------------\n");
                readInt("Please enter your option: ", &option);

                if (option == 1)
                    editBookAll(headPtr);
                else if (option == 2)
                    editBookIsbn(headPtr);
                else if (option == 3)
                    editBookTitle(headPtr);
                else if (option == 4)
                    editBookAuthor(headPtr);
                else if (option == 5)
                    editBookPrice(headPtr);

                else if (option == -1)
                    printf("Back to Main Menu...\n");
                else
                    printf("Invalid option\n");

                if (option != -1)
                {
                    system("pause");
                }
            } while (option != -1);
            option = 0;
        }
        else if (option == 5)
        {
            do
            {
                system("cls");
                option = 0;
                printf("1. to delete a node at the start\n");
                printf("2. to delete a node at the position\n");
                printf("3. to delete a node at the end\n");
                printf("4. to delete a node with specific data\n");
                printf("-1. to exit\n");
                printf("----------------------------------\n");
                readInt("Please enter your option: ", &option);

                if (option == 1)
                    deleteBookStart(headPtr);
                else if (option == 2)
                    deleteBookPosition(headPtr);
                else if (option == 3)
                    deleteBookLast(headPtr);
                else if (option == 4)
                    deleteBookIsbn(headPtr);
                else if (option == -1)
                    break;
                else
                    printf("Invalid option\n");

                if (getchar() != '\n')
                {
                    while (getchar() != '\n')
                        ; // Clears the buffer
                }
                system("pause");
            } while (option != -1);
            option = 0;
        }
        else if (option == 6)
            libraryBackup(*headPtr); // Function to save the library to file
        else if (option == -1)
            printf("Exiting the program...\n");
        else
            printf("Invalid option\n");

        if (option != -1)
        {
            system("pause");
            system("cls");
        }
    } while (option != -1);
}

// Function to save books to file (Admin only)
void libraryBackup(Book *headPtr)
{
    FILE *fptr;
    errno_t err = fopen_s(&fptr, DATABASE_FILE, "w");
    if (err != 0 || fptr == NULL)
    {
        printf("Library could not be backed up.\n");
        return;
    }

    while (headPtr != NULL)
    {
        // Ensure each field is written on a separate line
        fprintf(fptr, "%d\n", headPtr->isbn);
        fprintf(fptr, "%s\n", headPtr->title);
        fprintf(fptr, "%s\n", headPtr->author);
        fprintf(fptr, "%.2f\n", headPtr->price); // Consistent decimal precision
        headPtr = headPtr->next;
    }

    fclose(fptr);
    printf("Library backed up successfully.\n");
}

// Function to restore books from file (Admin only)
void libraryRestore(Book **headPtr)
{
    FILE *fptr;
    Book *temp = *headPtr;
    int isbn;
    char title[31], author[26];
    double price;

    fopen_s(&fptr, DATABASE_FILE, "r");
    if (fptr == NULL)
    {
        printf("Library could not be opened.\n");
        return;
    }

    // Free the current list
    while (temp != NULL)
    {
        Book *next = temp->next;
        free(temp);
        temp = next;
    }
    *headPtr = NULL;

    // Restore books from file
    while (fscanf_s(fptr, "%d\n", &isbn) == 1)
    {
        if (fgets(title, sizeof(title), fptr) == NULL)
            break;
        if (fgets(author, sizeof(author), fptr) == NULL)
            break;
        if (fscanf_s(fptr, "%lf\n", &price) != 1)
            break;

        // Remove newline characters
        title[strcspn(title, "\n")] = '\0';
        author[strcspn(author, "\n")] = '\0';

        // Create new node
        Book *newNode = (Book *)malloc(sizeof(Book));
        if (newNode == NULL)
        {
            printf("Memory allocation failed.\n");
            fclose(fptr);
            return;
        }

        newNode->isbn = isbn;
        strncpy_s(newNode->title, sizeof(newNode->title), title, _TRUNCATE);
        strncpy_s(newNode->author, sizeof(newNode->author), author, _TRUNCATE);
        newNode->price = price;
        newNode->next = NULL;

        // Append to end of list
        if (*headPtr == NULL)
        {
            *headPtr = newNode;
        }
        else
        {
            Book *last = *headPtr;
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = newNode;
        }
    }

    fclose(fptr);
    printf("Library restored successfully.\n");
}

// Function to add a book at the start of the list
void addBookStart(Book **headPtr)
{
    Book *newNode = (Book *)malloc(sizeof(Book)); // allocate memory for the new book
    if (newNode == NULL)
    {
        printf("\nMemory allocation failed!\n");
        return;
    }

    readInt("\nPlease enter the book's ISBN: ", &newNode->isbn);
    readChar("Please enter the book's title: ", newNode->title, sizeof(newNode->title), 0);
    readChar("Please enter the book's author: ", newNode->author, sizeof(newNode->author), 0);
    readDouble("Please enter the book's price: ", &newNode->price);
    newNode->next = *headPtr; // newNode->next is set to point to the current headPtr (i.e., the old head)
    *headPtr = newNode;       // headPtr is updated to the new node
}

// Function to add a book at a specific position in the list
void addBookPosition(Book **headPtr)
{
    int position;
    readInt("\nEnter the position to insert the book: ", &position);
    position--; // Convert to 0-based index

    if (position < 0)
    {
        printf("Invalid position!\n");
        return;
    }

    // Special case: insert at the beginning
    if (position == 0)
    {
        addBookStart(headPtr);
        return;
    }

    // Traverse to validate the position first
    Book *current = *headPtr;
    int i = 0;
    while (current != NULL && i < position - 1)
    {
        current = current->next;
        i++;
    }

    if (current == NULL)
    {
        printf("Position is out of bounds. Book not added.\n");
        return;
    }

    // Now that the position is valid, create and fill the new book node
    Book *newNode = (Book *)malloc(sizeof(Book));
    if (newNode == NULL)
    {
        printf("\nMemory allocation failed!\n");
        return;
    }

    readInt("\nPlease enter the book's ISBN: ", &newNode->isbn);
    readChar("Please enter the book's title: ", newNode->title, sizeof(newNode->title), 0);
    readChar("Please enter the book's author: ", newNode->author, sizeof(newNode->author), 0);
    readDouble("Please enter the book's price: ", &newNode->price);
    newNode->next = current->next;
    current->next = newNode;
}

// Function to add a book at the end of the list
void addBookLast(Book **headPtr)
{
    // If the library is empty, use addBookStart directly
    if (*headPtr == NULL)
    {
        addBookStart(headPtr);
        return;
    }
    Book *temp = *headPtr; // Start from the head
    while (temp->next != NULL)
    {
        temp = temp->next; // Traverse the libary until the last node
    }
    Book *newNode = (Book *)malloc(sizeof(Book)); // allocate memory for the new book
    if (newNode == NULL)
    {
        printf("\nMemory allocation failed!\n");
        return;
    }

    readInt("\nPlease enter the book's ISBN: ", &newNode->isbn);
    readChar("Please enter the book's title: ", newNode->title, sizeof(newNode->title), 0);
    readChar("Please enter the book's author: ", newNode->author, sizeof(newNode->author), 0);
    readDouble("Please enter the book's price: ", &newNode->price);
    newNode->next = NULL; // The new book will be the last node
    temp->next = newNode; // Link the new book to the last node
}

// Function to delete a book at the start of the list
void deleteBookStart(Book **headPtr)
{
    if (*headPtr == NULL)
    {
        printf("\nThe list is empty. Nothing to delete.\n");
        return;
    }

    Book *temp = *headPtr;
    *headPtr = temp->next; // Move head to the next node
    free(temp);            // Free the old head node
    printf("First book deleted successfully.\n");
}

// Function to delete a book at a specific position in the list
void deleteBookPosition(Book **headPtr)
{
    int position;

    if (*headPtr == NULL)
    {
        printf("The list is empty. Nothing to delete.\n");
        return;
    }

    readInt("\nEnter the position to delete: ", &position);
    position--; // Convert to 0-based index

    if (position < 0)
    {
        printf("Invalid position!\n");
        return;
    }

    if (position == 0)
    {
        deleteBookStart(headPtr);
        return;
    }

    Book *current = *headPtr;
    int i = 0;

    // Traverse to the node before the one to delete
    while (current != NULL && i < position - 1)
    {
        current = current->next;
        i++;
    }

    if (current == NULL || current->next == NULL)
    {
        printf("Position out of bounds. Nothing deleted.\n");
        return;
    }

    Book *temp = current->next;
    current->next = temp->next;
    free(temp);
    printf("Book at position %d deleted successfully.\n", position + 1);
}

// Function to delete a book at the end of the list
void deleteBookLast(Book **headPtr)
{
    if (*headPtr == NULL)
    {
        printf("The list is empty. Nothing to delete.\n");
        return;
    }

    if ((*headPtr)->next == NULL)
    {
        // Only one node in the list
        free(*headPtr);
        *headPtr = NULL;
        printf("Last book deleted successfully.\n");
        return;
    }

    Book *current = *headPtr;
    while (current->next->next != NULL)
    {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
    printf("Last book deleted successfully.\n");
}

// Function to delete a book by ISBN
void deleteBookIsbn(Book **headPtr)
{
    if (*headPtr == NULL)
    {
        printf("The list is empty. Nothing to delete.\n");
        return;
    }

    int targetIsbn;
    readInt("\nEnter the ISBN of the book to delete: ", &targetIsbn);

    Book *current = *headPtr;
    Book *prev = NULL;

    // Check if the head node matches the ISBN
    if (current->isbn == targetIsbn)
    {
        *headPtr = current->next; // Move head to next node
        free(current);            // Free the node
        printf("Book with ISBN %d deleted successfully.\n", targetIsbn);
        return;
    }

    // Traverse the list to find the book with the matching ISBN
    while (current != NULL && current->isbn != targetIsbn)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Book with ISBN %d not found. Nothing deleted.\n", targetIsbn);
        return;
    }

    // Found the book, unlink and delete
    prev->next = current->next;
    free(current);
    printf("Book with ISBN %d deleted successfully.\n", targetIsbn);
}

// Function to search for a book by ISBN
void searchBookIsbn(Book *headPtr)
{
    if (headPtr == NULL)
    {
        printf("The list is empty. No books to search.\n");
        return;
    }

    int targetIsbn;
    readInt("\nEnter the ISBN of the book to search for: ", &targetIsbn);

    Book *current = headPtr;
    while (current != NULL)
    {
        if (current->isbn == targetIsbn)
        {
            // Book found � print details
            printf("\nBook found:\n");
            printf("ISBN: %d\n", current->isbn);
            printf("Title: %s\n", current->title);
            printf("Author: %s\n", current->author);
            printf("Price: %.2f\n", current->price);
            return;
        }
        current = current->next;
    }

    printf("Book with ISBN %d not found.\n", targetIsbn);
}

// Function to display all books
void displayBookAll(Book *headPtr)
{
    if (headPtr == NULL)
    {
        printf("The list is empty. No books to display.\n");
        return;
    }

    Book *current = headPtr;
    int index = 1;

    printf("\nAll books in the list:\n");

    while (current != NULL)
    {
        printf("\nBook %d:\n", index);
        printf("ISBN: %d\n", current->isbn);
        printf("Title: %s\n", current->title);
        printf("Author: %s\n", current->author);
        printf("Price: %.2f\n", current->price);
        current = current->next;
        index++;
    }
}

// Function to edit all details of a book by ISBN
void editBookAll(Book **headPtr)
{
    if (*headPtr == NULL)
    {
        printf("The list is empty. No books to edit.\n");
        return;
    }

    int targetIsbn;
    readInt("\nEnter the ISBN of the book to edit: ", &targetIsbn);
    Book *current = *headPtr;

    while (current != NULL)
    {
        if (current->isbn == targetIsbn)
        {
            printf("Editing book with ISBN %d...\n", targetIsbn);
            readInt("Enter new ISBN: ", &current->isbn);
            readChar("Enter new title: ", current->title, sizeof(current->title), 0);
            readChar("Enter new author: ", current->author, sizeof(current->author), 0);
            readDouble("Enter new price: ", &current->price);
            printf("Book updated successfully.\n");
            return;
        }
        current = current->next;
    }

    printf("Book with ISBN %d not found.\n", targetIsbn);
}

// Function to edit the ISBN of a book
void editBookIsbn(Book **headPtr)
{
    if (*headPtr == NULL)
    {
        printf("The list is empty. No books to edit.\n");
        return;
    }

    int targetIsbn;
    readInt("\nEnter the current ISBN of the book: ", &targetIsbn);
    Book *current = *headPtr;

    while (current != NULL)
    {
        if (current->isbn == targetIsbn)
        {
            readInt("Enter new ISBN: ", &current->isbn);
            printf("ISBN updated successfully.\n");
            return;
        }
        current = current->next;
    }

    printf("Book with ISBN %d not found.\n", targetIsbn);
}

// Function to edit the title of a book
void editBookTitle(Book **headPtr)
{
    if (*headPtr == NULL)
    {
        printf("The list is empty. No books to edit.\n");
        return;
    }

    int targetIsbn;
    readInt("\nEnter the ISBN of the book to edit the title: ", &targetIsbn);
    Book *current = *headPtr;

    while (current != NULL)
    {
        if (current->isbn == targetIsbn)
        {
            readChar("Enter new title: ", current->title, sizeof(current->title), 0);
            printf("Title updated successfully.\n");
            return;
        }
        current = current->next;
    }

    printf("Book with ISBN %d not found.\n", targetIsbn);
}

// Function to edit the author of a book
void editBookAuthor(Book **headPtr)
{
    if (*headPtr == NULL)
    {
        printf("The list is empty. No books to edit.\n");
        return;
    }

    int targetIsbn;
    readInt("\nEnter the ISBN of the book to edit the author: ", &targetIsbn);
    Book *current = *headPtr;

    while (current != NULL)
    {
        if (current->isbn == targetIsbn)
        {
            readChar("Enter new author: ", current->author, sizeof(current->author), 0);
            printf("Author updated successfully.\n");
            return;
        }
        current = current->next;
    }

    printf("Book with ISBN %d not found.\n", targetIsbn);
}

// Function to edit the price of a book
void editBookPrice(Book **headPtr)
{
    if (*headPtr == NULL)
    {
        printf("The list is empty. No books to edit.\n");
        return;
    }

    int targetIsbn;
    readInt("\nEnter the ISBN of the book to edit the price: ", &targetIsbn);
    Book *current = *headPtr;

    while (current != NULL)
    {
        if (current->isbn == targetIsbn)
        {
            readDouble("Enter new price: ", &current->price);
            printf("Price updated successfully.\n");
            return;
        }
        current = current->next;
    }

    printf("Book with ISBN %d not found.\n", targetIsbn);
}
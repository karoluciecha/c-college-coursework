#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>

#define MAX_TITLE_LENGTH 30
#define MAX_AUTHOR_LENGTH 25
#define MAX_PASSWORD_LENGTH 50
#define PASSWORD_NAME "ResourceFiles/login.txt"
#define LIBRARY_NAME "ResourceFiles/library.txt"

// Define the structure for a library book
typedef struct {
	unsigned long long number;
	char title[MAX_TITLE_LENGTH];
	char author[MAX_AUTHOR_LENGTH];
	double price;
} Book;

int getRangeInclusiveIntInput(const char* prompt, int min, int max);
unsigned long long getISBN(const char* prompt, unsigned long long min, unsigned long long max, int option);
double getRangeInclusiveDoubleInput(const char* prompt, double min, double max);
void initializeBooks(Book* books, int count);
void addBook(Book* books, int count);
void displayBook(Book* books, int count);
void editBook(Book* books, int count);
void displayBookISBN(Book* books, int i);
void saveBooksToFile(Book* books, int count);
int loadBooksFromFile(Book** books, int* numBooks);
int authenticateAdmin();


void runLibraryProgram() {
	printf("Welcome to the Library System!\n");
	Book* books = NULL;
	int choice, numBooks = 0, loginMode = getRangeInclusiveIntInput("\n1. Admin Login\n2. Guest Access\nChoose an option: ", 1, 2);

	if (loginMode == 1) {
		if (!authenticateAdmin()) {
			printf("Incorrect password. Switching to guest mode.\n");
			loginMode = 2; // Switch to guest mode
			loadBooksFromFile(&books, &numBooks);
		}
		else {
			printf("Login successful. Access granted.\n");
			if (getRangeInclusiveIntInput("\n1. Create new Database (overwrites the old one)\n2. Load existing Database\nChoose an option: ", 1, 2) == 1) {
				numBooks = getRangeInclusiveIntInput("\nEnter the number of books in the library database: ", 1, INT_MAX);

				// Allocate memory for the books
				books = (Book*)malloc(numBooks * sizeof(Book));
				if (books == NULL) {
					printf("Memory allocation failed.\n\n");
					system("pause");
					system("cls");
					return;
				}

				// Initialize the books
				initializeBooks(books, numBooks);
			}
			else {
				if (books != NULL) free(books);
				if (!loadBooksFromFile(&books, &numBooks)) {
					printf("No database loaded or file missing.\n\n");
					system("pause");
					system("cls");
					return;
				}
			}
		}
	}
	else {
		if (!loadBooksFromFile(&books, &numBooks)) {
			printf("No database loaded or file missing.\n\n");
			system("pause");
			system("cls");
			return;
		}
	}

	do {
		choice = getRangeInclusiveIntInput("\nMain menu:\n1. Display book details\n2. Add a new book to the library\n3. Edit book price\n-1. Exit now\nChoose an option: ", -1, 3);

		switch (choice) {
		case 1:
			system("cls");
			displayBook(books, numBooks);
			break;
		case 2:
			system("cls");
			addBook(books, numBooks);
			break;
		case 3:
			system("cls");
			editBook(books, numBooks);
			break;
		case -1:
			printf("Saving the library database...\n");
			saveBooksToFile(books, numBooks);
			printf("Exiting the program...\n");
			break;
		}
	} while (choice != -1);

	// Free allocated memory
	free(books);
	printf("\n");
    system("pause");
    system("cls");
	return;
}


int getRangeInclusiveIntInput(const char* prompt, int min, int max) {
	int value;
	while (1) {
		printf("%s", prompt);
		if (scanf_s("%d", &value) == 1) {
			if ((min == 0 && max == 0) || (value >= min && value <= max)) {
				while (getchar() != '\n');
				break;
			}
			else {
				printf("Please enter an integer in the range of %d - %d\n", min, max);
			}
		}
		else {
			printf("Invalid input. Please enter a valid integer.\n");
		}
		while (getchar() != '\n');
	}
	return value;
}

unsigned long long getISBN(const char* prompt, unsigned long long min, unsigned long long max, int option) {
	unsigned long long value;
	while (1) {
		printf("%s", prompt);
		if (scanf_s("%llu", &value) == 1) {
			if ((value >= min && value <= max) || option && value == 0) {
				while (getchar() != '\n');
				break;
			}
			else {
				printf("Please enter an ISBN in the range of %llu - %llu\n", min, max);
			}
		}
		else {
			printf("Invalid input. Please enter a valid ISBN.\n");
		}
		while (getchar() != '\n');
	}
	return value;
}

double getRangeInclusiveDoubleInput(const char* prompt, double min, double max) {
	double value;
	while (1) {
		printf("%s", prompt);
		if (scanf_s("%lf", &value) == 1) {
			if ((min == 0 && max == 0) || (value >= min && value <= max)) {
				break;
			}
			else {
				printf("Please enter a double in the range of %.2f - %.2f\n", min, max);
			}
		}
		else {
			printf("Invalid input. Please enter a valid double.\n");
		}
		while (getchar() != '\n');
	}
	return value;
}

// Function to initialize the book array
void initializeBooks(Book* books, int count) {
	for (int i = 0; i < count; i++) {
		books[i].number = 0;  // Initialize book number to 0
		strcpy_s(books[i].title, MAX_TITLE_LENGTH, "");
		strcpy_s(books[i].author, MAX_AUTHOR_LENGTH, "");
		books[i].price = 0.0;
	}
}

int authenticateAdmin() {
	char storedPassword[MAX_PASSWORD_LENGTH];
	FILE* file;

	if (fopen_s(&file, PASSWORD_NAME, "r") != 0) {
		printf("Error: Unable to open login.txt\n");
		return 0;
	}

	if (fgets(storedPassword, MAX_PASSWORD_LENGTH, file) == NULL) {
		printf("Error: Unable to read password.\n");
		fclose(file);
		return 0;
	}
	fclose(file);

	// Remove newline character if present
	size_t len = strlen(storedPassword);
	if (len > 0 && storedPassword[len - 1] == '\n') {
		storedPassword[len - 1] = '\0';
	}

	char enteredPassword[MAX_PASSWORD_LENGTH];
	getStringInput("Enter admin password: ", enteredPassword, MAX_PASSWORD_LENGTH);

	return strcmp(storedPassword, enteredPassword) == 0;
}

// Function to display book details
void displayBook(Book* books, int count) {
	unsigned long long ISBN = getISBN("Enter the ISBN of the book: ", 9780000000000, 9799999999999, 1);
	//  Display all books if ISBN is 0
	if (ISBN == 0) {
		for (int i = 0; i < count; i++) {
			displayBookISBN(books, i);
		}
	}
	// Display the book with the given ISBN
	else {
		for (int i = 0; i < count; i++) {
			if (books[i].number == ISBN) {
				displayBookISBN(books, i);
				return;
			}
		}
		printf("Book with ISBN %llu not found.\n", ISBN);
	}
}

// Function to add a new book to the library
void addBook(Book* books, int count) {
	for (int i = 0; i < count; i++) {
		if (books[i].number == 0) { // Find the next available slot
			books[i].number = getISBN("Enter Book ISBN: ", 9780000000000, 9799999999999, 0);
			getStringInput("Enter book title: ", books[i].title, MAX_TITLE_LENGTH);
			getStringInput("Enter book author: ", books[i].author, MAX_AUTHOR_LENGTH);
			books[i].price = getRangeInclusiveDoubleInput("Enter Price: ", 0.0, DBL_MAX);
			printf("Book added successfully!\n");
			return;
		}
	}
	printf("No space left to add a new book.\n");
}

void editBook(Book* books, int count) {
	unsigned long long ISBN = getISBN("Enter the ISBN of the book: ", 9780000000000, 9799999999999, 1);
	for (int i = 0; i < count; i++) {
		if (books[i].number == ISBN) {
			displayBookISBN(books, i);
			double newPrice = getRangeInclusiveDoubleInput("Enter the new price: ", 0.0, DBL_MAX);
			books[i].price = newPrice;
			printf("Price updated successfully!\n");
			return;
		}
	}
	printf("Book with ISBN %llu not found.\n", ISBN);
}

void displayBookISBN(Book* books, int i) {
	printf("\nBook details:\n");
	printf("ISBN: %llu\n", books[i].number);
	printf("Title: %s\n", books[i].title);
	printf("Author: %s\n", books[i].author);
	printf("Price: %.2f\n", books[i].price);
	printf("------------------------------\n");
	return;
}
void saveBooksToFile(Book* books, int count) {
	FILE* file = fopen(LIBRARY_NAME, "w");
	if (!file) {
		printf("Error saving books to file.\n");
		return;
	}
	fprintf(file, "%d\n", count); // Save the number of books at the beginning
	for (int i = 0; i < count; i++) {
		if (books[i].number != 0) {
			fprintf(file, "%llu|%s|%s|%.2f\n", books[i].number, books[i].title, books[i].author, books[i].price);
		}
	}
	fclose(file);
}

int loadBooksFromFile(Book** books, int* numBooks) {
	FILE* file;
	if (fopen_s(&file, LIBRARY_NAME, "r") != 0 || !file) {
		*numBooks = 0;
		return 0;
	}

	// Read the number of books
	if (fscanf_s(file, "%d\n", numBooks) != 1) {
		fclose(file);
		*numBooks = 0;
		return 0;
	}

	// Allocate memory for books
	*books = (Book*)malloc((*numBooks) * sizeof(Book));
	if (!*books) {
		fclose(file);
		*numBooks = 0;
		return 0;
	}

	// Read book details
	for (int i = 0; i < *numBooks; i++) {
		fscanf_s(file, "%llu|%29[^|]|%24[^|]|%lf\n",
			&((*books)[i].number),
			(*books)[i].title, (unsigned int)sizeof((*books)[i].title),
			(*books)[i].author, (unsigned int)sizeof((*books)[i].author),
			&((*books)[i].price));
	}

	fclose(file);
	return *numBooks;
}
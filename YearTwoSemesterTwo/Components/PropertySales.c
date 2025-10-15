// Program Written by Karol Uciecha: G00436758
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_NAME "ResourceFiles/Sales.txt"

// Define the structure for a property sale details
typedef struct
{
	int regNo;
	char eircode[8]; // 7 characters + 1 for null terminator
	char county[26]; // 25 characters + 1 for null terminator
	int propertyType;
	int year;
	int price;
	int status;
} Sale;

// Function prototypes
void initializeSales(Sale *sales, int size);
void addSale(Sale *sales, int size);
void editSale(Sale *sales, int size);
void searchSale(Sale *sales, int size);
void calcAverageSales(Sale *sales, int size);
void display_menu();
void read_int(const char *prompt, int *value);
void read_char(const char *prompt, char *buffer, int size);
void saveSalesToFile(Sale *sales, int count);

void runPropertySalesProgram()
{
	int choice, salesNo;

	printf("Welcome to the Property Sales System!\n");

	// Dynamically allocate memory for sales array
	read_int("Please enter the size of sales database: ", &salesNo);
	Sale *sales = (Sale *)malloc(salesNo * sizeof(Sale));
	if (sales == NULL)
	{
		printf("Memory allocation failed. Exiting...\n\n");
		system("pause");
		system("cls");
		return;
	}
	initializeSales(sales, salesNo);

	do
	{
		display_menu();
		read_int("Enter your choice: ", &choice);

		switch (choice)
		{
		case 1:
			addSale(sales, salesNo);
			break;
		case 2:
			editSale(sales, salesNo);
			break;
		case 3:
			searchSale(sales, salesNo);
			break;
		case 4:
			calcAverageSales(sales, salesNo);
			break;
		case -1:
			printf("Exiting the program...\n\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
		}

	} while (choice != -1);

	// Saving data and exiting program
	saveSalesToFile(sales, salesNo);
	free(sales);
	system("pause");
	system("cls");
	return;
}

// Function to display menu options
void display_menu()
{
	printf("\nMain Menu:\n");
	printf("1. Add new property sale\n");
	printf("2. Edit existing sale details\n");
	printf("3. Search for sale details\n");
	printf("4. Calculate average sales price\n");
	printf("-1. Exit\n");
}

// Function to initialize the sales array
void initializeSales(Sale *sales, int size)
{
	for (int i = 0; i < size; i++)
	{
		(sales + i)->regNo = 0; // Indicating empty slot
	}
}

// Function to add a sale
void addSale(Sale *sales, int size)
{
	int choice = 0, duplicate = 1;

	for (int i = 0; i < size; i++)
	{
		if ((sales + i)->regNo == 0)
		{ // Find first empty slot
			do
			{
				duplicate = 0;
				read_int("Please enter the sales registration number: ", &(sales + i)->regNo);
				for (int j = 0; j < i; j++)
				{
					if ((sales + j)->regNo == (sales + i)->regNo)
					{
						printf("The sales number already exists.\n");
						duplicate = 1;
						continue;
					}
				}
			} while (duplicate);
			read_char("Enter property eircode: ", (sales + i)->eircode, sizeof((sales + i)->eircode));
			read_char("Enter property county: ", (sales + i)->county, sizeof((sales + i)->county));
			do
			{
				read_int("Enter property type:\n1. Bungalow\n2. Two Story House\n3. Apartment\n4. Commercial Building\nChoice (1 - 4): ", &choice);

				switch (choice)
				{
				case 1:
				case 2:
				case 3:
				case 4:
					(sales + i)->propertyType = choice;
					break;
				default:
					printf("Invalid choice. Please try again.\n");
				}
			} while (choice < 1 || choice > 4);

			read_int("Enter year of the sale: ", &(sales + i)->year);
			read_int("Enter property price: ", &(sales + i)->price);
			do
			{
				read_int("Enter sale status:\n1. Open\n2. Sale agreed\n3. Sold\nChoice (1 - 3): ", &choice);

				switch (choice)
				{
				case 1:
				case 2:
				case 3:
					(sales + i)->status = choice;
					break;
				default:
					printf("Invalid choice. Please try again.\n");
				}
			} while (choice < 1 || choice > 3);

			printf("Sale added successfully!\n");
			return;
		}
	}
	printf("Database is full! Cannot add more sales.\n");
}

void editSale(Sale *sales, int size)
{
	int salesRegNo = 0, newPrice = 0, newStatus = 0;

	read_int("Please enter the sales registration number: ", &salesRegNo);
	for (int i = 0; i < size; i++)
	{
		if ((sales + i)->regNo == salesRegNo)
		{
			if ((sales + i)->status == 3)
			{
				printf("Cannot edit this sale. Sale is already closed.\n");
				return;
			}
			else
			{
				printf("Current property sale price: %d\n", (sales + i)->price);
				read_int("Please enter a new sale price (0 to cancel): ", &newPrice);
				if (newPrice != 0)
					(sales + i)->price = newPrice;
				printf("Current property sale status: %d\n", (sales + i)->status);
				read_int("Please enter a new sale status:\n1. Open\n2. Sale agreed\n3. Sold\n0. to cancel\nChoice: ", &newStatus);
				if (newStatus != 0)
					(sales + i)->status = newStatus;
				return;
			}
		}
	}
	printf("Sale with registration number of %d cannot be found in the database.\n", salesRegNo);
}

void searchSale(Sale *sales, int size)
{
	int salesRegNo = 0;

	read_int("Please enter the sales registration number: ", &salesRegNo);
	for (int i = 0; i < size; i++)
	{
		if ((sales + i)->regNo == salesRegNo)
		{
			printf("Property Registration Number: %d\n", sales[i].regNo);
			printf("Property Eircode: %s\n", sales[i].eircode);
			printf("Property County: %s\n", sales[i].county);
			printf("Property Type: ");
			if (sales[i].propertyType == 1)
				printf("Bungalow\n");
			else if (sales[i].propertyType == 2)
				printf("Two Story House\n");
			else if (sales[i].propertyType == 3)
				printf("Apartment\n");
			else if (sales[i].propertyType == 4)
				printf("Commercial Building\n");
			printf("Year of the sale: %d\n", sales[i].year);
			printf("Property sale price: %d\n", sales[i].price);
			printf("Sale status: ");
			if (sales[i].status == 1)
				printf("Open\n\n");
			else if (sales[i].status == 2)
				printf("Sale Agreed\n\n");
			else if (sales[i].status == 3)
				printf("Sold\n\n");
			return;
		}
	}
	printf("Sale with registration number of %d cannot be found in the database.\n", salesRegNo);
}

// Funciton to display average sales price for a specific property type
void calcAverageSales(Sale *sales, int size)
{
	int choice = 0, totalPrice = 0, count = 0;

	do
	{
		read_int("Enter property type:\n1. Bungalow\n2. Two Story House\n3. Apartment\n4. Commercial Building\nChoice (1 - 4): ", &choice);

		switch (choice)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			break;
		default:
			printf("Invalid choice. Please try again.\n");
		}
	} while (choice < 1 || choice > 4);

	for (int i = 0; i < size; i++)
	{
		if ((sales + i)->regNo != 0 && (sales + i)->propertyType == choice)
		{
			totalPrice += (sales + i)->price;
			count++;
		}
	}

	if (count > 0)
	{
		printf("The average sales value for property type ");
		if (choice == 1)
			printf("Bungalow ");
		else if (choice == 2)
			printf("Two Story House ");
		else if (choice == 3)
			printf("Apartment ");
		else if (choice == 4)
			printf("Commercial Building ");
		printf("is: %d\n\n", totalPrice / count);
	}
	else
	{
		printf("No records found for that property type.\n\n");
	}
}

// Function to save sales to file
void saveSalesToFile(Sale *sales, int count)
{
	FILE *file = fopen(DATABASE_NAME, "w");
	if (!file)
	{
		printf("Error saving sales to file.\n");
		return;
	}
	fprintf(file, "%d\n", count); // Save the number of sales at the beginning
	for (int i = 0; i < count; i++)
	{
		if (sales[i].regNo != 0)
		{
			fprintf(file, "Property Registration Number: %d\n", sales[i].regNo);
			fprintf(file, "Property Eircode: %s\n", sales[i].eircode);
			fprintf(file, "Property County: %s\n", sales[i].county);
			fprintf(file, "Property Type: ");
			if (sales[i].propertyType == 1)
				fprintf(file, "Bungalow\n");
			else if (sales[i].propertyType == 2)
				fprintf(file, "Two Story House\n");
			else if (sales[i].propertyType == 3)
				fprintf(file, "Apartment\n");
			else if (sales[i].propertyType == 4)
				fprintf(file, "Commercial Building\n");
			fprintf(file, "Year of the sale: %d\n", sales[i].year);
			fprintf(file, "Property sale price: %d\n", sales[i].price);
			fprintf(file, "Sale status: ");
			if (sales[i].status == 1)
				fprintf(file, "Open\n\n");
			else if (sales[i].status == 2)
				fprintf(file, "Sale Agreed\n\n");
			else if (sales[i].status == 3)
				fprintf(file, "Sold\n\n");
		}
	}
	printf("Sales saved successfully.\n");
	fclose(file);
}

// Function to safely read an integer
void read_int(const char *prompt, int *value)
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

// Function to safely read a string
void read_char(const char *prompt, char *buffer, int size)
{
	printf("%s", prompt);
	if (scanf_s("%s", buffer, (unsigned)size) == 1)
	{
		return;
	}
	else
	{
		printf("Invalid input. Please enter a valid string.\n");
	}
}
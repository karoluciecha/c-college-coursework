#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	int data; // data part of the node
	struct node* NEXT; // pointer to the next node
}nodeT;

void addNodeStart(nodeT** headPtr);
void addNodePosition(nodeT** headPtr);
void addNodeLast(nodeT** headPtr);
void displayNodes(nodeT* headPtr);
void deleteNodeStart(nodeT** headPtr);
void deleteNodePosition(nodeT** headPtr);
void deleteNodeLast(nodeT** headPtr);
void deleteNodeData(nodeT** headPtr);
int calculateLength(nodeT* headPtr);
int search(nodeT* headPtr);
void backup(nodeT* headPtr);
void restore(nodeT** headPtr);

void runSingleLinkedListProgram()
{
	nodeT* headPtr = NULL; // pointer to the first node (head node)
	int option; // user option

	do
	{
		printf("Main Menu:\n");
		printf("1. to add a node\n");
		printf("2. to delete a node\n");
		printf("3. to display all the nodes\n");
		printf("4. to display the length\n");
		printf("5. to search for specific integer\n");
		printf("6. to backup the list\n");
		printf("7. to restore the list\n");
		printf("-1. to exit\n");
		printf("----------------------------------\n");
		printf("Please enter your option: ");
		scanf_s("%d", &option);

		if (option == 1) {
			do {
				system("cls");
				option = 0;
				printf("1. to add a node at the start\n");
				printf("2. to add a node at the position\n");
				printf("3. to add a node at the end\n");
				printf("-1. to exit\n");
				printf("----------------------------------\n");
				printf("Please enter your option: ");
				scanf_s("%d", &option);

				if (option == 1) addNodeStart(&headPtr);
				else if (option == 2) addNodePosition(&headPtr);
				else if (option == 3) addNodeLast(&headPtr);
				else if (option == -1) break;
				else printf("Invalid option\n");

				while (getchar() != '\n');  // Clears the buffer
				system("pause");
			} while (option != -1 || option != 1 || option != 2 || option != 3);
			option = 0;
		}
		else if (option == 2) {
			do {
				system("cls");
				option = 0;
				printf("1. to delete a node at the start\n");
				printf("2. to delete a node at the position\n");
				printf("3. to delete a node at the end\n");
				printf("4. to delete a node with specific data\n");
				printf("-1. to exit\n");
				printf("----------------------------------\n");
				printf("Please enter your option: ");
				scanf_s("%d", &option);

				if (option == 1) deleteNodeStart(&headPtr);
				else if (option == 2) deleteNodePosition(&headPtr);
				else if (option == 3) deleteNodeLast(headPtr);
				else if (option == 4) deleteNodeData(&headPtr);
				else if (option == -1) break;
				else printf("Invalid option\n");

				while (getchar() != '\n');  // Clears the buffer
				system("pause");
			} while (option != -1 || option != 1 || option != 2 || option != 3);
			option = 0;
		}
		else if (option == 3) displayNodes(headPtr); // No & because the function expects a pointer (nodeT*)
		else if (option == 4) printf("Current length of the list is: %d.\n", calculateLength(headPtr));
		else if (option == 5) search(headPtr);
		else if (option == 6) backup(headPtr);
		else if (option == 7) restore(&headPtr);
		else if (option == -1) printf("Exiting the program...\n\n");
		else printf("Invalid option\n");


		while (getchar() != '\n');  // Clears the buffer
		system("pause");
		system("cls");
	} while (option != -1);
}

void addNodeStart(nodeT** headPtr) {
	nodeT* newNode = (nodeT*)malloc(sizeof(nodeT)); // allocate memory for the new node
	if (newNode == NULL) {
		printf("\nMemory allocation failed!\n");
		return;
	}

	printf("\nPlease enter the data: ");
	scanf_s("%d", &newNode->data); // User input saved to int data

	// Using -> notation (common way for struct pointers)
	// newNode->data = 10;

	// Using (*newNode).data (valid but less common)
	// (*newNode).data = 20;

	newNode->NEXT = *headPtr; // newNode->NEXT is set to point to the current headPtr (i.e., the old head)
	*headPtr = newNode; // headPtr is updated to the new node
	// headPtr is a pointer to a pointer (nodeT**), so the update should be *headPtr, not headPtr itself.
	// Otherwise, headPtr inside the function will change, but the original head pointer in main() won't be updated.

	// Before insertion:
	// headPtr -> [10] -> [20] -> NULL
	// After inserting 5:
	// headPtr -> [5] -> [10] -> [20] -> NULL
}

void addNodePosition(nodeT** headPtr) {
	int position, i = 0;
	nodeT* current = *headPtr;
	nodeT* previous = NULL;
	do {
		printf("Please enter the position to insert: ");
		if ((scanf_s("%d", &position) == 1) && (position > 0 && position <= calculateLength(current) + 1)) break;
		printf("Invalid input. Allowed input is: 1 - %d\n", calculateLength(current) + 1);
		while (getchar() != '\n');  // Clears the buffer
	} while (1);

	// If entered position is 1, use addNodeStart directly
	if (position == 1) {
		addNodeStart(headPtr);
		return;
	}

	// If entered position is the last, use addNodeLast directly
	else if (position == calculateLength(current) + 1) {
		addNodeLast(headPtr);
		return;
	}

	while (current != NULL) {
		i++;
		if (i == position) {
			nodeT* newNode = (nodeT*)malloc(sizeof(nodeT)); // allocate memory for the new node
			if (newNode == NULL) {
				printf("\nMemory allocation failed!\n");
				return;
			}
			printf("\nPlease enter the data: ");
			scanf_s("%d", &newNode->data); // User input saved to int data
			newNode->NEXT = current; // newNode->NEXT is set to point to the current node
			previous->NEXT = newNode; // Bypass the current
		}
		else {
			previous = current;
			current = current->NEXT;
		}
	}
}

void addNodeLast(nodeT** headPtr) {
	// If the list is empty, use addNodeFirst directly
	if (*headPtr == NULL) {
		addNodeStart(headPtr);
		return;
	}

	nodeT* temp = *headPtr; // Start from the head
	while (temp->NEXT != NULL) {
		temp = temp->NEXT; // Traverse to the last node so that temp
	}

	// Now temp is pointing to the last node
	addNodeStart(&(temp->NEXT)); // Pass address of temp->NEXT to insert at the end
}

void displayNodes(nodeT* headPtr) {
	int i = 1;
	// If the list is empty, use addNodeFirst directly
	if (headPtr == NULL) {
		printf("\nThe list is empty!\n");
		return;
	}

	nodeT* temp = headPtr;
	printf("\nDisplaying all the nodes:\n");
	while (temp != NULL) {
		printf("The value of the node number %d is %d\n", i++, temp->data);
		temp = temp->NEXT;
	}
}

void deleteNodeStart(nodeT** headPtr) {
    if (*headPtr == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    nodeT* temp = *headPtr;
    *headPtr = (*headPtr)->NEXT;
    free(temp);
    printf("First node deleted successfully.\n");
}

void deleteNodePosition(nodeT** headPtr) {
	nodeT* current = *headPtr;
	nodeT* previous = NULL;
	int input, i = 0;

	if (calculateLength(current) < 2) {
		printf("Cannot delete. List too short.\n");
		return;
	}

	do {
		printf("Please enter the position to delete: ");
		if ((scanf_s("%d", &input) == 1) && (input > 0 && input <= calculateLength(current))) break;
		printf("Invalid input. Allowed input is: 1 - %d\n", calculateLength(current));
		while (getchar() != '\n');  // Clears the buffer
	} while (1);

	if (input == 1) {
		deleteNodeStart(headPtr);
		return;
	}

	if (input == calculateLength(current) + 1) {
		//deleteNodeLast(headPtr);
		return;
	}

	while (current != NULL) {
		i++;
		if (i == input) {
			do {
				while (getchar() != '\n');  // Clears the buffer
				char confirm;
				printf("Position: %d | Value: %d.\nDo you want to delete this node? (Y / N): ", i, current->data);
				if (scanf_s("%c", &confirm, (int)sizeof(confirm)) != 1) printf("Invalid input\n");
				if (confirm == 'n' || confirm == 'N') return;
				if (confirm == 'y' || confirm == 'Y') break;
			} while (1);

			// Perform deletion
			if (i == 1) *headPtr = current->NEXT; // Updating head pointer when deleting first node
			else previous->NEXT = current->NEXT; // Bypass the node to be deleted. Head pointer doesn't have to be updated
			free(current);
			printf("Selected node deleted successfully.\n");
			return;
		}
		else {
			previous = current;
			current = current->NEXT;
		}
	}
}

void deleteNodeLast(nodeT** headPtr) {
    nodeT* current = *headPtr;
    nodeT* previous = NULL;
    if (current == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    if (current->NEXT == NULL) {
        // Only one node in the list
        free(current);
        *headPtr = NULL;
        printf("Last node deleted successfully.\n");
        return;
    }
    while (current->NEXT != NULL) {
        previous = current;
        current = current->NEXT;
    }
    previous->NEXT = NULL;
    free(current);
    printf("Last node deleted successfully.\n");
}

void deleteNodeData(nodeT** headPtr) {
	int input, i = 0;
	nodeT* current = *headPtr;
	nodeT* previous = NULL;

	if (calculateLength(current) < 2) {
		printf("Cannot delete. List too short.\n");
		return;
	}
	do {
		printf("Please enter an integer value to delete: ");
		if (scanf_s("%d", &input) == 1) break;
		printf("Invalid input\n");
		while (getchar() != '\n');  // Clears the buffer
	} while (1);
	while (current != NULL) {
		i++;
		if (current->data == input) {
			do {
				while (getchar() != '\n');  // Clears the buffer
				char confirm;
				printf("Position: %d | Value: %d.\nDo you want to delete this node? (Y / N): ", i, current->data);
				if (scanf_s("%c", &confirm, (int)sizeof(confirm)) != 1) printf("Invalid input\n");
				if (confirm == 'n' || confirm == 'N') return;
				if (confirm == 'y' || confirm == 'Y') break;
			} while (1);

			// Perform deletion
			if (i == 1) *headPtr = current->NEXT; // Updating head pointer when deleting first node
			else previous->NEXT = current->NEXT; // Bypass the node to be deleted. Head pointer doesn't have to be updated
			free(current);
			printf("Selected node deleted successfully.\n");
			return;
		}
		else {
			previous = current;
			current = current->NEXT;
		}
	}
	printf("Value %d has not been found on the list.\n", input);
	return;
}

int calculateLength(nodeT* headPtr) {
	int i = 0;
	while (headPtr != NULL) {
		i++;
		headPtr = headPtr->NEXT; // Traverse to the last node so that temp
	}
	return i;
}

int search(nodeT* headPtr) {
	int input, i = 0;
	do {
		printf("Please enter an integer value to search nodes: ");
		if (scanf_s("%d", &input) == 1) break;
		printf("Invalid input\n");
		while (getchar() != '\n');  // Clears the buffer
	} while (1);
	while (headPtr != NULL) {
		i++;
		if (headPtr->data == input) {
			printf("Value %d has been found on position %d at address %p.\n", headPtr->data, i, (void*)headPtr);
			// headPtr - memory address of the current node in the list (Correct)
			// (void*)headPtr - converts headPtr to void*, ensuring safe and standard-compliant behavior
			// &headPtr - address of the pointer variable itself (Incorrect)
			// *headPtr - dereferences headPtr, giving the node structure (not an address)
			return 1;
		}
		else headPtr = headPtr->NEXT;
	}
	printf("Value %d has not been found on the list.\n", input);
	return 0;
}

void backup(nodeT* headPtr) {
	FILE* fptr;
	fopen_s(&fptr, "ResourceFiles/backup.txt", "w");
	if (fptr == NULL) {
		printf("Backup could not be created.\n");
		return;
	}
	while (headPtr != NULL) {
		fprintf(fptr, "%d\n", headPtr->data);
		headPtr = headPtr->NEXT;
	}
	fclose(fptr);
	printf("Backup successful.\n");
}

void restore(nodeT** headPtr) {
	nodeT* temp = *headPtr;
	FILE* fptr;
	int data;

	// Load the backup file
	fopen_s(&fptr, "ResourceFiles/backup.txt", "r");
	if (fptr == NULL) {
		printf("Backup could not be opened.\n");
		return;
	}
	
	// Free the current list
	while (temp != NULL) {
		nodeT* next = temp->NEXT;
		free(temp);
		temp = next;
	}
	*headPtr = NULL; // Reset the head pointer
	
	// Restore the list from the backup
    while (fscanf_s(fptr, "%d", &data) == 1) {
		nodeT* newNode = (nodeT*)malloc(sizeof(nodeT));
		if (newNode == NULL) {
			printf("Memory allocation failed.\n");
			return;
		}
		newNode->data = data;
		newNode->NEXT = *headPtr;
		*headPtr = newNode;
	}
	fclose(fptr);
	printf("Restore successful.\n");
}
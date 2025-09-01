#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getRangeInclusiveIntInputs(const char* prompt, int min, int max) {
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


char* getStringInputs(const char* prompt) {
    char tempBuffer[1024]; // Temporary buffer for input
    char* result = NULL;

    while (1) {
        printf("%s", prompt);

        if (fgets(tempBuffer, sizeof(tempBuffer), stdin) != NULL) {
            // Remove the newline character if it's in the buffer
            size_t len = strlen(tempBuffer);
            if (len > 0 && tempBuffer[len - 1] == '\n') {
                tempBuffer[len - 1] = '\0';
                len--;
            }

            // Check if the string is not empty
            if (len > 0) {
                // Allocate memory for the result and copy the input using strcpy_s
                result = malloc(len + 1);
                if (result == NULL) {
                    printf("Memory allocation failed. Exiting.\n");
                    exit(1);
                }
                // Use strcpy_s for safer copying
                if (strcpy_s(result, len + 1, tempBuffer) != 0) {
                    printf("String copy failed. Exiting.\n");
                    free(result);
                    exit(1);
                }
                return result;
            }
            else {
                printf("Input cannot be empty. Please try again.\n");
            }
        }
        else {
            printf("Invalid input. Please enter a valid string.\n");
        }
    }
}

int main() {
    int value = getRangeInclusiveIntInputs("Enter a number (0 and 0 allows any range): ", 0, 0);
    printf("You entered: %d\n", value);

    value = getRangeInclusiveIntInputs("Enter a number between 5 and 10: ", 5, 10);
    printf("You entered: %d\n", value);

    char* name = getStringInputs("Enter your name: ");
    printf("Hello, %s!\n", name);

    char* color = getStringInputs("Enter your favorite color: ");
    printf("Your favorite color is %s.\n", color);

    value = getRangeInclusiveIntInputs("Enter a number between 5 and 10: ", 5, 10);
    printf("You entered: %d\n", value);

    // Free the allocated memory
    free(name);
    free(color);

    return 0;
}
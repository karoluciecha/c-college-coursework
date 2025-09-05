// C program to show input and output
#include <stdio.h>

void runVariablesIOProgram()
{

    // Declare the variables
    int num;
    char ch;
    float f;
    char string[50];
    char sentence[50];

    // --- Integer ---

    // Input the integer
    printf("Enter your age: ");
    scanf_s("%d", &num);

    // Output the integer
    printf("\nEntered age is: %d", num);

    // --- Float ---

    //For input Clearing buffer
    while ((getchar()) != '\n');

    // Input the float
    printf("\n\nEnter a number you like: ");
    scanf_s("%f", &f);

    // Output the float
    printf("\nEntered number is: %f", f);

    // --- Character ---

    //For input Clearing buffer
    while ((getchar()) != '\n');

    // Input the Character
    printf("\n\nEnter the first character of your surname: ");
    scanf_s("%c", &ch, 1);

    // Output the Character
    printf("\nEntered character is: %c", ch);

    // --- String ---
    // To read a word

    // For input Clearing buffer
    while ((getchar()) != '\n');

    // Input the Word
    printf("\n\nEnter your name: ");
    scanf_s("%s", string, (unsigned)sizeof(string));

    // Output the Word
    printf("\nEntered name is: %s", string);

    // Clear the input buffer
    while ((getchar()) != '\n');

    // --- String ---
    // To read a Sentence

    // Input the Sentence
    printf("\n\nEnter your saying: ");
    scanf_s("%[^\n]", sentence, (unsigned)sizeof(sentence));

    // Output the String
    printf("\nEntered saying is: %s", sentence);

    // --- All ---

    printf("\n\nHello, %s %c! Your age is %d, and you like number %f:)\nYour favourite saying is: %s\n\n", string, ch, num, f, sentence);

    return;
}

#include <stdio.h>

void tiles();
void results();

void runLightCalculationsProgram() {
    int choice = -1;

    do {
        printf("==== LIGHT CALCULATIONS MENU ====\n");
        printf("1. Tiles calculator program\n");
        printf("2. Student's result calculator program\n");
        printf("0. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf_s("%d", &choice);

        // Clear buffer
        while ((getchar()) != '\n');

        switch (choice) {
            case 1:
                tiles();
                break;
            case 2:
                results();
                break;
            case 0:
                printf("Exiting Light Calculations Program...\n\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n\n");
                break;
        }
        printf("\n");  // Add spacing after each run
    } while (choice != 0);
}

void tiles() {
    float wallSpace, tileWidth, gap, tiledSpace;
    int numOfTiles;

    printf("Please enter the wall width and the tile width: ");
    scanf_s("%f %f", &wallSpace, &tileWidth);

    numOfTiles = wallSpace / tileWidth;

    if (numOfTiles % 2 == 0) {
        numOfTiles = numOfTiles - 1;
    }

    tiledSpace = numOfTiles * tileWidth;
    gap = (wallSpace - tiledSpace) / 2;

    printf("The number of tiles is %d and the gap is %f\n", numOfTiles, gap);
}

void results() {
    float assignmentMark, labExamMark, writtenExamMark, overallMark;

    printf("Enter the assignment mark (percentage): ");
    scanf_s("%f", &assignmentMark);

    printf("Enter the lab exam mark (percentage): ");
    scanf_s("%f", &labExamMark);

    printf("Enter the written exam mark (percentage): ");
    scanf_s("%f", &writtenExamMark);

    overallMark = (assignmentMark * 0.3) + (labExamMark * 0.1) + (writtenExamMark * 0.6);

    printf("The overall mark is %.2f%%\n", overallMark);
}
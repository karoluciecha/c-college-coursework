#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define MAX_NO_PLAYERS 4
#define MAX_NO_ROUNDS 13

int currentRound = -1, numberOfPlayers = 0, gameStatus = 0, playerPointsLeaderboard[4][2] = { {0, 0}, {1, 0}, {2, 0}, {3, 0} }, pointsAtStake, highestScoreLeaderboardPoints[10];
// playerPointsLeaderboard = player number, points / [0] - first place / [3] - fourth place
char playerNames[MAX_NO_PLAYERS][50];
char highestScoreLeaderboardNames[10][50];


// Current action options:
// Game status options: -1 - error occured, 0 - game start, 1 - loading autosave, 2 - loading save, 8 - save game, 10 - new game
// 11 - no autosave found, 15 - show statistics, 20 - game loaded, 30 - play next round, 50 - round finished, 60 - show highest leaderboard,
// 80 - exit with save, 90 - exit w/o save, 100 - game finished.

// Explanation {{Card Number, Suit (1 - clubs, 2 - diamonds, 3 - hearts, 4 - spades), Ownership (0 - free, 1 - p1, 2 - p2, 3 - p3, 4 - p4), Card Status (0 - free, 1 - in hand, 10 - at war, 100 - used)}
int cards[4][13][4] = {
    {{2, 1, 0, 0}, {3, 1, 0, 0}, {4, 1, 0, 0}, {5, 1, 0, 0}, {6, 1, 0, 0}, {7, 1, 0, 0}, {8, 1, 0, 0}, {9, 1, 0, 0}, {10, 1, 0, 0}, {11, 1, 0, 0}, {12, 1, 0, 0}, {13, 1, 0, 0}, {14, 1, 0, 0}},
    {{2, 2, 0, 0}, {3, 2, 0, 0}, {4, 2, 0, 0}, {5, 2, 0, 0}, {6, 2, 0, 0}, {7, 2, 0, 0}, {8, 2, 0, 0}, {9, 2, 0, 0}, {10, 2, 0, 0}, {11, 2, 0, 0}, {12, 2, 0, 0}, {13, 2, 0, 0}, {14, 2, 0, 0}},
    {{2, 3, 0, 0}, {3, 3, 0, 0}, {4, 3, 0, 0}, {5, 3, 0, 0}, {6, 3, 0, 0}, {7, 3, 0, 0}, {8, 3, 0, 0}, {9, 3, 0, 0}, {10, 3, 0, 0}, {11, 3, 0, 0}, {12, 3, 0, 0}, {13, 3, 0, 0}, {14, 3, 0, 0}},
    {{2, 4, 0, 0}, {3, 4, 0, 0}, {4, 4, 0, 0}, {5, 4, 0, 0}, {6, 4, 0, 0}, {7, 4, 0, 0}, {8, 4, 0, 0}, {9, 4, 0, 0}, {10, 4, 0, 0}, {11, 4, 0, 0}, {12, 4, 0, 0}, {13, 4, 0, 0}, {14, 4, 0, 0}}};
// Printing example:
// printf("First card of Clubs: %s\n", cardNames[0][0]); // 2 of Clubs
// printf("Last card of Spades: %s\n", cardNames[3][12]); // Ace of Spades

char cardNames[4][13][20] = {
    { // 1st row: Clubs
        "2 of Clubs", "3 of Clubs", "4 of Clubs", "5 of Clubs", "6 of Clubs",
        "7 of Clubs", "8 of Clubs", "9 of Clubs", "10 of Clubs",
        "Jack of Clubs", "Queen of Clubs", "King of Clubs", "Ace of Clubs"
    },
    { // 2nd row: Diamonds
        "2 of Diamonds", "3 of Diamonds", "4 of Diamonds", "5 of Diamonds", "6 of Diamonds",
        "7 of Diamonds", "8 of Diamonds", "9 of Diamonds", "10 of Diamonds",
        "Jack of Diamonds", "Queen of Diamonds", "King of Diamonds", "Ace of Diamonds"
    },
    { // 3rd row: Hearts
        "2 of Hearts", "3 of Hearts", "4 of Hearts", "5 of Hearts", "6 of Hearts",
        "7 of Hearts", "8 of Hearts", "9 of Hearts", "10 of Hearts",
        "Jack of Hearts", "Queen of Hearts", "King of Hearts", "Ace of Hearts"
    },
    { // 4th row: Spades
        "2 of Spades", "3 of Spades", "4 of Spades", "5 of Spades", "6 of Spades",
        "7 of Spades", "8 of Spades", "9 of Spades", "10 of Spades",
        "Jack of Spades", "Queen of Spades", "King of Spades", "Ace of Spades"
    }
};

// Function declarations
int getRangeInclusiveIntInput(const char* prompt, int min, int max);
void getUserInput(const char* prompt, char* buffer, size_t bufferSize);
void greet();
void printName();
int askYesNo(const char* prompt);
void showStats();
int gameMenu();
void readInAutoSave(int gameStage);
void writeOutAutoSave();
void readInSave();
void dealCards();
void newGame();
void playRound();
void writeOutSave();
void sortLeaderboard(int arr[MAX_NO_PLAYERS][2]);
void gameSummary();
void readInHighestScoreLeaderboard();
void showHighestScoreLeaderboard();
void writeOutHighestScoreLeaderboard();

void runTheGameOfWarProgram() {

    greet();
    readInAutoSave(0);
    readInHighestScoreLeaderboard();

    while (gameStatus != 80 && gameStatus != 90) {
        gameStatus = gameMenu();

        if (gameStatus == 1) readInAutoSave(1);

        if (gameStatus == 2) readInSave();

        if (gameStatus == 8) writeOutSave();

        if (gameStatus == 10) newGame();

        if (gameStatus == 100) gameSummary();

        if (gameStatus == 30) playRound();

        if (gameStatus == 15) showStats();

        if (gameStatus == 60) showHighestScoreLeaderboard();

        if (gameStatus == -1) {
            printf("Something went wrong");
            Sleep(100);
            printf(".");
            Sleep(100);
            printf(".");
            Sleep(100);
            printf(".\n");
            Sleep(100);
            printf("Resetting");
            Sleep(100);
            printf(".");
            Sleep(100);
            printf(".");
            Sleep(100);
            printf(".\n");
            readInAutoSave(0);
        }

        writeOutAutoSave();

        if (gameStatus != 80 && gameStatus != 90 && gameStatus != 100) system("PAUSE");
    }
    
    if (gameStatus == 80) writeOutSave();

    writeOutAutoSave();

    system("pause");
    system("cls");
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

void getUserInput(const char* prompt, char* buffer, size_t bufferSize) {
    while (1) {
        printf("%s", prompt);

        // Read input from stdin
        if (fgets(buffer, bufferSize, stdin) != NULL) {
            size_t len = strlen(buffer);

            // Check if input was truncated
            if (len >= bufferSize - 1 && buffer[len - 1] != '\n') {
                printf("Input is too long. Please enter no more than %zu characters.\n", bufferSize - 1);
                while (getchar() != '\n'); // Clear remaining input
                continue;
            }

            // Remove the newline character
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
                len--; // Adjust length after removing newline
            }

            // Trim leading and trailing whitespace
            char* start = buffer;
            while (isspace((unsigned char)*start)) start++;
            char* end = buffer + len - 1;
            while (end >= start && isspace((unsigned char)*end)) end--;

            // Adjust string to trimmed version
            *(end + 1) = '\0';
            memmove(buffer, start, end - start + 2); // +2 to include '\0'

            // Check if the trimmed string is not empty
            if (strlen(buffer) > 0) return;
            else printf("Input cannot be empty. Please try again.\n");
        }
        else {
            printf("Error reading input. Please try again.\n");
        }
    }
}

void greet() {
    // Copyright by: https://patorjk.com/software/taag/#p=display&f=Cards&t=WELCOME%20TO%20THE%0AGAME%20OF%20WAR
    printf(".------..------..------..------..------..------..------.     .------..------.     .------..------..------.\n");
    Sleep(200);
    printf("|W.--. ||E.--. ||L.--. ||C.--. ||O.--. ||M.--. ||E.--. |     |T.--. ||O.--. |     |T.--. ||H.--. ||E.--. |\n");
    Sleep(200);
    printf("| :/\\: || (\\/) || :/\\: || :/\\: || :/\\: || (\\/) || (\\/) |     | :/\\: || :/\\: |     | :/\\: || :/\\: || (\\/) |\n");
    Sleep(200);
    printf("| :\\/: || :\\/: || (__) || :\\/: || :\\/: || :\\/: || :\\/: |     | (__) || :\\/: |     | (__) || (__) || :\\/: |\n");
    Sleep(200);
    printf("| '--'W|| '--'E|| '--'L|| '--'C|| '--'O|| '--'M|| '--'E|     | '--'T|| '--'O|     | '--'T|| '--'H|| '--'E|\n");
    Sleep(200);
    printf("`------'`------'`------'`------'`------'`------'`------'     `------'`------'     `------'`------'`------'\n");
    Sleep(500);
    printf("\t\t.------..------..------..------.     .------..------.     .------..------..------.\n");
    Sleep(200);
    printf("\t\t|G.--. ||A.--. ||M.--. ||E.--. |     |O.--. ||F.--. |     |W.--. ||A.--. ||R.--. |\n");
    Sleep(200);
    printf("\t\t| :/\\: || (\\/) || (\\/) || (\\/) |     | :/\\: || :(): |     | :/\\: || (\\/) || :(): |\n");
    Sleep(200);
    printf("\t\t| :\\/: || :\\/: || :\\/: || :\\/: |     | :\\/: || ()() |     | :\\/: || :\\/: || ()() |\n");
    Sleep(200);
    printf("\t\t| '--'G|| '--'A|| '--'M|| '--'E|     | '--'O|| '--'F|     | '--'W|| '--'A|| '--'R|\n");
    Sleep(200);
    printf("\t\t`------'`------'`------'`------'     `------'`------'     `------'`------'`------'\n\n\n");
    Sleep(2000);
}

void printName() {
    system("cls");
    // Copyright by: https://patorjk.com/software/taag/#p=display&f=Cards&t=GAME%20OF%20WAR
    printf(".------..------..------..------.     .------..------.     .------..------..------.\n");
    printf("|G.--. ||A.--. ||M.--. ||E.--. |     |O.--. ||F.--. |     |W.--. ||A.--. ||R.--. |\n");
    printf("| :/\\: || (\\/) || (\\/) || (\\/) |     | :/\\: || :(): |     | :/\\: || (\\/) || :(): |\n");
    printf("| :\\/: || :\\/: || :\\/: || :\\/: |     | :\\/: || ()() |     | :\\/: || :\\/: || ()() |\n");
    printf("| '--'G|| '--'A|| '--'M|| '--'E|     | '--'O|| '--'F|     | '--'W|| '--'A|| '--'R|\n");
    printf("`------'`------'`------'`------'     `------'`------'     `------'`------'`------'\n\n\n");
}

int askYesNo(const char* prompt) {
    char buffer[10]; // Buffer to store user input
    while (1) {
        printf("%s (Y / N): ", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Remove the newline character if it's in the buffer
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';

            // Check if the input is a single character and valid
            if (strlen(buffer) == 1) {
                char choice = tolower(buffer[0]); // Convert to lowercase
                if (choice == 'y') return 1; // True for 'Y'
                if (choice == 'n') return 0; // False for 'N'
            }

            // Invalid input, prompt again
            printf("Invalid input. Please enter 'Y' or 'N'.\n");
            while (getchar() != '\n'); // Clear input buffer
        }
        else {
            // Handle unexpected EOF or input error
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }
}

void showStats() {
    system("cls");
    printName();
    printf("Showing statistics:\n\n");
    printf("Current round: %d\n", currentRound);
    if (gameStatus != 100) printf("Points rolled over to the next round: %d\n", pointsAtStake);
    printf("\nLeaderboard:\n");
    printf("Current leader is %s with %d points\n", playerNames[playerPointsLeaderboard[0][0]], playerPointsLeaderboard[0][1]);
    printf("2nd place: %s with %d points\n", playerNames[playerPointsLeaderboard[1][0]], playerPointsLeaderboard[1][1]);
    if (numberOfPlayers >= MAX_NO_PLAYERS - 1) printf("3rd place: %s with %d points\n", playerNames[playerPointsLeaderboard[2][0]], playerPointsLeaderboard[2][1]);
    if (numberOfPlayers == MAX_NO_PLAYERS) printf("4th place: %s with %d points\n", playerNames[playerPointsLeaderboard[3][0]], playerPointsLeaderboard[3][1]);
    printf("----------------------------------------\n");
    gameStatus = 50;
}

int gameMenu() {
    int i = 1, choice = -1;

    printName();

    switch (gameStatus) {
    case 0:
        printf("%d. Resume autosaved game\n", i++);
        printf("%d. Load a game from save\n", i++);
        printf("%d. Start a new game\n", i++);
        printf("%d. Show highest score leaderboard\n", i++);
        printf("0. Exit now\n");
        choice = getRangeInclusiveIntInput("Choose an option: ", 0, i - 1);
        switch (choice) {
        case 0:
            choice = 90;
            break;
        case 1:
            choice = 1;
            break;
        case 2:
            choice = 2;
            break;
        case 3:
            choice = 10;
            break;
        case 4:
            choice = 60;
            break;
        }
        break;
    case 11:
        printf("%d. Load a game from save\n", i++);
        printf("%d. Start a new game\n", i++);
        printf("%d. Show highest score leaderboard\n", i++);
        printf("0. Exit now\n");
        choice = getRangeInclusiveIntInput("Choose an option: ", 0, i - 1);
        switch (choice) {
        case 0:
            choice = 90;
            break;
        case 1:
            choice = 2;
            break;
        case 2:
            choice = 10;
            break;
        case 3:
            choice = 60;
            break;
        }
        break;
    case 20:
        printf("%d. Next round\n", i++);
        printf("%d. Show statistics\n", i++);
        printf("%d. Start a new game\n", i++);
        printf("%d. Save current progress\n", i++);
        printf("0. Exit now\n");
        choice = getRangeInclusiveIntInput("Choose an option: ", 0, i - 1);
        switch (choice) {
        case 0:
            if (currentRound >= 1 && currentRound <= MAX_NO_ROUNDS) {
                choice = askYesNo("Would you like to save current game progress?");
                if (choice == 1) choice = 80;
                else choice = 90;
            }
            else choice = 90;
            break;
        case 1:
            choice = 30;
            break;
        case 2:
            choice = 15;
            break;
        case 3:
            choice = askYesNo("Are you sure? Your current progress will be lost.");
            if (choice == 1) choice = 10;
            else choice = 20;
            break;
        case 4:
            choice = 8;
            break;
        }
        break;
    case 50:
        printf("%d. Next round\n", i++);
        printf("%d. Start a new game\n", i++);
        printf("%d. Save current progress\n", i++);
        printf("0. Exit now\n");
        choice = getRangeInclusiveIntInput("Choose an option: ", 0, i - 1);
        switch (choice) {
        case 0:
            if (currentRound >= 1 && currentRound <= MAX_NO_ROUNDS) {
                choice = askYesNo("Would you like to save current game progress?");
                if (choice == 1) choice = 80;
                else choice = 90;
            }
            else choice = 90;
            break;
        case 1:
            choice = 30;
            break;
        case 2:
            choice = askYesNo("Are you sure? Your current progress will be lost.");
            if (choice == 1) choice = 10;
            else choice = 50;
            break;
        case 3:
            choice = 8;
            break;
        }
        break;
    default:
        choice = 0;
        break;
    case 100:
        printf("%d. End game & show summary\n", i++);
        printf("%d. Start a new game\n", i++);
        printf("0. Exit now\n");
        choice = getRangeInclusiveIntInput("Choose an option: ", 0, i - 1);
        switch (choice) {
        case 0:
            choice = 90;
            break;
        case 1:
            choice = 100;
            break;
        case 2:
            choice = 10;
            break;
        }
        break;
    }
    system("cls");
    return choice;
}

void readInAutoSave(int gameStage) {

    FILE* file;
    const char* filePath = "ResourceFiles/TheGameOfWarAutosave.txt";

    if (fopen_s(&file, filePath, "r") != 0) {
        gameStatus = 11;
        return;
    }

    if (!gameStage) {
        gameStatus = 0;
        fclose(file);
        return;
    }

    printName();
    printf("Loading game data");

    // Read general game data with validation
    if (fscanf_s(file, "%d", &pointsAtStake) != 1 || pointsAtStake < 0) {
        printf("\nError: Invalid pointsAtStake value in file.\n");
        fclose(file);
        gameStatus = -1;
        return;
    }

    if (fscanf_s(file, "%d", &currentRound) != 1 || currentRound < 1 || currentRound > 13) {
        printf("\nError: Invalid currentRound value in file.\n");
        fclose(file);
        gameStatus = -1;
        return;
    }

    if (fscanf_s(file, "%d", &numberOfPlayers) != 1 || numberOfPlayers < 2 || numberOfPlayers > 4) {
        printf("\nError: Invalid numberOfPlayers value in file.\n");
        fclose(file);
        gameStatus = -1;
        return;
    }

    if (fscanf_s(file, "%d", &gameStatus) != 1 ||
        (gameStatus != -1 && gameStatus != 0 && gameStatus != 1 &&
            gameStatus != 2 && gameStatus != 8 && gameStatus != 10 &&
            gameStatus != 11 && gameStatus != 15 && gameStatus != 20 &&
            gameStatus != 30 && gameStatus != 50 && gameStatus != 80 &&
            gameStatus != 90 && gameStatus != 100)) {
        printf("\nError: Invalid gameStatus value in file.\n");
        fclose(file);
        gameStatus = -1;
        return;
    }

    Sleep(250);
    printf(".");

    // Read player names with validation
    for (int i = 0; i < numberOfPlayers; i++) {
        if (fscanf_s(file, "%s", playerNames[i], (unsigned int)sizeof(playerNames[i])) != 1 ||
            strlen(playerNames[i]) == 0 || strlen(playerNames[i]) > 50) {
            printf("\nError: Invalid player name for player %d.\n", i + 1);
            fclose(file);
            gameStatus = -1;
            return;
        }
    }

    Sleep(250);
    printf(".");

    // Read card data with validation
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 0; rank < 13; rank++) {
            if (fscanf_s(file, "%d %d",
                &cards[suit][rank][2],  // Ownership
                &cards[suit][rank][3]) != 2 ||
                cards[suit][rank][2] < 0 || cards[suit][rank][2] > 4 ||
                (cards[suit][rank][3] != 0 && cards[suit][rank][3] != 1 &&
                    cards[suit][rank][3] != 10 && cards[suit][rank][3] != 100)) {
                printf("\nError: Invalid card data for suit %d, rank %d.\n", suit, rank);
                fclose(file);
                gameStatus = -1;
                return;
            }
        }
    }

    Sleep(250);
    printf(".");

    // Read player points leaderboard with validation
    for (int player = 0; player < numberOfPlayers; player++) {
        if (fscanf_s(file, "%d %d",
            &playerPointsLeaderboard[player][0],  // Player number
            &playerPointsLeaderboard[player][1]) != 2 ||                  // Ensure two values are read
            playerPointsLeaderboard[player][0] < 0 ||                    // Player number must be non-negative
            playerPointsLeaderboard[player][0] >= numberOfPlayers ||      // Player number must be within valid range
            playerPointsLeaderboard[player][1] < 0) {                    // Points must be non-negative
            printf("\nError: Invalid leaderboard data for player %d.\n", player + 1);
            fclose(file);
            gameStatus = -1;
            return;
        }
    }

    // Reset unused slots
    for (int player = numberOfPlayers; player < 4; player++) {
        playerPointsLeaderboard[player][0] = 0;
        playerPointsLeaderboard[player][1] = 0;
    }

    fclose(file);

    Sleep(250);
    printf(" done!\n");

    gameStatus = 20;
}

void writeOutAutoSave() {
    if (gameStatus == 100 || currentRound < 1 || currentRound >= MAX_NO_ROUNDS) return;

    const char* filePath = "ResourceFiles/TheGameOfWarAutosave.txt";
    FILE* file = fopen(filePath, "w");

    if (file == NULL) {
        gameStatus = -1;
        return;
    }

    // Save general game data
    fprintf(file, "%d\n", pointsAtStake);
    fprintf(file, "%d\n", currentRound);
    fprintf(file, "%d\n", numberOfPlayers);
    fprintf(file, "%d\n", gameStatus);

    // Save player names
    for (int i = 0; i < numberOfPlayers; i++) {
        fprintf(file, "%s\n", playerNames[i]);
    }

    // Save card data (raw values only)
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 0; rank < 13; rank++) {
            fprintf(file, "%d %d ",
                cards[suit][rank][2],  // Ownership
                cards[suit][rank][3]   // Card Status
            );
        }
        fprintf(file, "\n");  // New line after each suit
    }

    for (int player = 0; player < numberOfPlayers; player++) {
        fprintf(file, "%d %d",
            playerPointsLeaderboard[player][0],  // Player
            playerPointsLeaderboard[player][1]   // Points
        );
        fprintf(file, "\n");  // New line after each player
    }

    fclose(file);

    // gameStatus = 0;
}

void readInSave() {
    char filePath[260]; // Buffer for file path (Windows MAX_PATH is 260)
    char userInput[200];

    printName();
    getUserInput("Please enter the path to the save file: ", userInput, 200);
    userInput[strcspn(userInput, "\n")] = '\0';
    snprintf(filePath, sizeof(filePath), "ResourceFiles/%s", userInput);

    system("cls");
    printName();

    FILE* file;
    if (fopen_s(&file, filePath, "r") != 0) {
        printf("\nError: Could not open file at '%s'\n", filePath);
        gameStatus = -1;
        return;
    }

    printf("Loading game data");

    // Read general game data with validation
    if (fscanf_s(file, "%d", &pointsAtStake) != 1 || pointsAtStake < 0) {
        printf("\nError: Invalid pointsAtStake value in file.\n");
        fclose(file);
        gameStatus = -1;
        return;
    }

    if (fscanf_s(file, "%d", &currentRound) != 1 || currentRound < 1 || currentRound > 13) {
        printf("\nError: Invalid currentRound value in file.\n");
        fclose(file);
        gameStatus = -1;
        return;
    }

    if (fscanf_s(file, "%d", &numberOfPlayers) != 1 || numberOfPlayers < 2 || numberOfPlayers > 4) {
        printf("\nError: Invalid numberOfPlayers value in file.\n");
        fclose(file);
        gameStatus = -1;
        return;
    }

    if (fscanf_s(file, "%d", &gameStatus) != 1 ||
        (gameStatus != -1 && gameStatus != 0 && gameStatus != 1 &&
            gameStatus != 2 && gameStatus != 8 && gameStatus != 10 &&
            gameStatus != 11 && gameStatus != 15 && gameStatus != 20 &&
            gameStatus != 30 && gameStatus != 50 && gameStatus != 80 &&
            gameStatus != 90 && gameStatus != 100)) {
        printf("\nError: Invalid gameStatus value in file.\n");
        fclose(file);
        gameStatus = -1;
        return;
    }

    Sleep(250);
    printf(".");

    // Read player names with validation
    for (int i = 0; i < numberOfPlayers; i++) {
        if (fscanf_s(file, "%s", playerNames[i], (unsigned int)sizeof(playerNames[i])) != 1 ||
            strlen(playerNames[i]) == 0 || strlen(playerNames[i]) > 50) {
            printf("\nError: Invalid player name for player %d.\n", i + 1);
            fclose(file);
            gameStatus = -1;
            return;
        }
    }

    Sleep(250);
    printf(".");

    // Read card data with validation
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 0; rank < 13; rank++) {
            if (fscanf_s(file, "%d %d",
                &cards[suit][rank][2],  // Ownership
                &cards[suit][rank][3]) != 2 ||
                cards[suit][rank][2] < 0 || cards[suit][rank][2] > 4 ||
                (cards[suit][rank][3] != 0 && cards[suit][rank][3] != 1 &&
                    cards[suit][rank][3] != 10 && cards[suit][rank][3] != 100)) {
                printf("\nError: Invalid card data for suit %d, rank %d.\n", suit, rank);
                fclose(file);
                gameStatus = -1;
                return;
            }
        }
    }

    Sleep(250);
    printf(".");

    // Read player points leaderboard with validation
    for (int player = 0; player < numberOfPlayers; player++) {
        if (fscanf_s(file, "%d %d",
            &playerPointsLeaderboard[player][0],                            // Player number
            &playerPointsLeaderboard[player][1]) != 2 ||                  // Ensure two values are read
            playerPointsLeaderboard[player][0] < 0 ||                    // Player number must be non-negative
            playerPointsLeaderboard[player][0] >= numberOfPlayers ||      // Player number must be within valid range
            playerPointsLeaderboard[player][1] < 0) {                    // Points must be non-negative
            printf("\nError: Invalid leaderboard data for player %d.\n", player + 1);
            fclose(file);
            gameStatus = -1;
            return;
        }
    }

    // Reset unused slots
    for (int player = numberOfPlayers; player < 4; player++) {
        playerPointsLeaderboard[player][0] = 0;
        playerPointsLeaderboard[player][1] = 0;
    }

    fclose(file);

    Sleep(250);
    printf(" done!\n");

    gameStatus = 20;
}

void dealCards() {
    // Seed the random number generator
    srand(time(NULL));

    int suit, rank;

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j <= numberOfPlayers; j++) {
            while (1) {
                // Generate random indices for suit (0-3) and rank (0-12)
                suit = rand() % 4;
                rank = rand() % 13;

                // Check if the card is free (ownership is 0)
                if (cards[suit][rank][2] == 0) {
                    // Change ownership to player 1 & card status to in hand
                    cards[suit][rank][2] = j;
                    cards[suit][rank][3] = 1;

                    // printf("\nSelected Card: Number=%d, Suit=%d, For: %s", cards[suit][rank][0], cards[suit][rank][1], playerNames[j]);
                    break;
                }
            }
        }
    }
}

void newGame() {
    printName();
    writeOutAutoSave();

    // Resetting variables to their default values
    numberOfPlayers = 0;
    pointsAtStake = 0;

    // Reset playerPointsLeaderboard
    for (int i = 0; i < 4; i++) {
        playerPointsLeaderboard[i][0] = i; // Player number
        playerPointsLeaderboard[i][1] = 0; // Points
    }

    // Reset playerNames
    for (int i = 0; i < MAX_NO_PLAYERS; i++) {
        playerNames[i][0] = '\0'; // Clear each player name
    }

    // Reset cards
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 0; rank < 13; rank++) {
            cards[suit][rank][2] = 0;  // Ownership
            cards[suit][rank][3] = 0;  // Card Status
        }
    }

    numberOfPlayers = getRangeInclusiveIntInput("Please enter the number of players (2 - 4): ", 2, MAX_NO_PLAYERS);
    printf("\n");
    for (int i = 0; i < numberOfPlayers; i++) {
        char prompt[100];
        snprintf(prompt, sizeof(prompt), "Please enter the name of the %d. player: ", i + 1);
        getUserInput(prompt, playerNames[i], 50);

    }

    printf("\nPlease wait while the cards are dealt");

    Sleep(250);
    printf(".");
    Sleep(250);
    printf(".");
    Sleep(250);

    dealCards();

    printf(".");
    Sleep(250);

    currentRound = 0;

    printf(" done!\n\n");
    Sleep(500);
    printf("The game is starting");
    Sleep(250);
    printf(".");
    Sleep(250);
    printf(".");
    Sleep(250);
    printf(".");
    Sleep(250);
    printf(" done!\n");
    Sleep(500);
    gameStatus = 30;
}

void playRound() {

    currentRound++;
    // suit | rank | value
    int battleCards[MAX_NO_PLAYERS][3], cardFrequency[13] = { 0 };

    for (int i = 0; i < numberOfPlayers; i++) {
        int selectedCard[13][2], cardNumber = 0;
        char prompt[100];

        system("cls");
        printName();

        printf("Playing %d. round\n\n", currentRound);

        printf("Please give the device to %s\n", playerNames[i]);
        system("pause");

        system("cls");
        printName();

        printf("Playing %d. round (%s)\n\n", currentRound, playerNames[i]);
        printf("Available cards:\n\n");

        for (int suit = 0; suit < 4; suit++) {       // Iterate through suits
            for (int rank = 0; rank < 13; rank++) {  // Iterate through ranks
                if (cards[suit][rank][2] == (i + 1) && cards[suit][rank][3] == 1) { // Ownership = 1, Status = 1
                    printf("%d.\t%s\n", ++cardNumber, cardNames[suit][rank]); // Print card name
                    selectedCard[(cardNumber - 1)][0] = suit;
                    selectedCard[(cardNumber - 1)][1] = rank;
                }
            }
        }

        snprintf(prompt, sizeof(prompt), "\nPlease enter the card number that you want to fight with (1 - %d): ", cardNumber);
        cardNumber = (getRangeInclusiveIntInput(prompt, 1, cardNumber)) - 1;
        printf("Selected card: %s\n", cardNames[selectedCard[cardNumber][0]][selectedCard[cardNumber][1]]);
        battleCards[i][0] = selectedCard[cardNumber][0];
        battleCards[i][1] = selectedCard[cardNumber][1];
        cardFrequency[selectedCard[cardNumber][1]]++;
        //printf("%d, %d\n", selectedCard[cardNumber][1], cardFrequency[selectedCard[cardNumber][1]]);
        battleCards[i][2] = cards[selectedCard[cardNumber][0]][selectedCard[cardNumber][1]][0];
        //printf("%d, %d, %d\n", battleCards[i][0], battleCards[i][1], battleCards[i][2]);
        cards[selectedCard[cardNumber][0]][selectedCard[cardNumber][1]][3] = 10;
        system("pause");
    }

    system("cls");
    printName();

    printf("! ! ! BATTLE ! ! !\n\n");

    Sleep(250);

    for (int i = 0; i < numberOfPlayers; i++) {
        printf("%s's card: %s\n", playerNames[i], cardNames[battleCards[i][0]][battleCards[i][1]]);
        pointsAtStake += cards[battleCards[i][0]][battleCards[i][1]][0];
    }

    Sleep(250);

    for (int i = ((sizeof(cardFrequency) / sizeof(cardFrequency[0])) - 1); i >= 0; i--) {
        if (cardFrequency[i] == 1) {
            //printf("Winning card is %d\n", i);
            for (int j = 0; j < numberOfPlayers; j++) {
                if (battleCards[j][1] == i) {
                    printf("\nThe winner of round %d. is %s with %s card!\n", currentRound, playerNames[j], cardNames[battleCards[j][0]][battleCards[j][1]]);
                    for (int h = 0; h < numberOfPlayers; h++) {
                        if (playerPointsLeaderboard[h][0] == j) {
                            playerPointsLeaderboard[h][1] += pointsAtStake;
                            printf("%s recieves %d points!\n", playerNames[j], pointsAtStake);
                            pointsAtStake = 0;
                            for (int k = 0; k < numberOfPlayers; k++) cards[battleCards[k][0]][battleCards[k][1]][3] = 100;
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
        else if (i == 0 && cardFrequency[i] != 1) {
            if (currentRound < MAX_NO_ROUNDS) printf("All tie. No win this round. %d points will be rolled over to the next round.\n", pointsAtStake);
            if (currentRound == MAX_NO_ROUNDS) printf("All tie. %d points are lost in the battlefield.\n", pointsAtStake);
        }
    }
    printf("\n");
    
    sortLeaderboard(playerPointsLeaderboard);
    system("pause");

    if (currentRound == MAX_NO_ROUNDS) {
        gameStatus = 100;
    }
    else gameStatus = 15;
}

void sortLeaderboard(int arr[MAX_NO_PLAYERS][2]) {
    int temp[2]; // Temporary array to swap rows

    // Bubble Sort based on the second column
    for (int i = 0; i < MAX_NO_PLAYERS - 1; i++) {
        for (int j = 0; j < MAX_NO_PLAYERS - i - 1; j++) {
            if (arr[j][1] < arr[j + 1][1]) { // Compare points (descending order)
                // Swap rows using a temporary array
                for (int k = 0; k < 2; k++) {
                    temp[k] = arr[j][k];
                    arr[j][k] = arr[j + 1][k];
                    arr[j + 1][k] = temp[k];
                }
            }
        }
    }
}

void writeOutSave() {
    char filePath[260]; // Buffer for file path (Windows MAX_PATH is 260)
    char userInput[200];

    printName();
    getUserInput("Please enter the path to the save file: ", userInput, 200);
    userInput[strcspn(userInput, "\n")] = '\0';
    snprintf(filePath, sizeof(filePath), "ResourceFiles/%s", userInput);

    system("cls");
    printName();

    FILE* file;
    if (fopen_s(&file, filePath, "w") != 0) {
        printf("\nError: Could not create file at '%s'\n", filePath);
        gameStatus = -1;
        return;
    }

    printf("Saving game data");

    // Save general game data
    fprintf(file, "%d\n", pointsAtStake);
    fprintf(file, "%d\n", currentRound);
    fprintf(file, "%d\n", numberOfPlayers);
    fprintf(file, "%d\n", gameStatus);

    Sleep(250);
    printf(".");

    // Save player names
    for (int i = 0; i < numberOfPlayers; i++) {
        fprintf(file, "%s\n", playerNames[i]);
    }

    Sleep(250);
    printf(".");

    // Save card data (raw values only)
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 0; rank < 13; rank++) {
            fprintf(file, "%d %d ",
                cards[suit][rank][2],  // Ownership
                cards[suit][rank][3]   // Card Status
            );
        }
        fprintf(file, "\n");  // New line after each suit
    }

    Sleep(250);
    printf(".");

    for (int player = 0; player < 4; player++) {
        fprintf(file, "%d %d",
            playerPointsLeaderboard[player][0],  // Player
            playerPointsLeaderboard[player][1]   // Points
        );
        fprintf(file, "\n");  // New line after each player
    }

    fclose(file);
    gameStatus = 0;

    Sleep(250);
    printf(" done!\n");
}

void gameSummary() {
    system("cls");
    printName();

    printf("The winner is %s with %d points! ", playerNames[playerPointsLeaderboard[0][0]], playerPointsLeaderboard[0][1]);
    Sleep(500);
    printf("Congratulations!\n\n");
    Sleep(500);
    printf("2nd place: %s with %d points\n", playerNames[playerPointsLeaderboard[1][0]], playerPointsLeaderboard[1][1]);
    Sleep(500);
    if (numberOfPlayers >= MAX_NO_PLAYERS - 1) {
        printf("3rd place: %s with %d points\n", playerNames[playerPointsLeaderboard[2][0]], playerPointsLeaderboard[2][1]);
        Sleep(500);
    }
    if (numberOfPlayers == MAX_NO_PLAYERS) {
        printf("4th place: %s with %d points\n", playerNames[playerPointsLeaderboard[3][0]], playerPointsLeaderboard[3][1]);
        Sleep(500);
    }
    
    if (playerPointsLeaderboard[0][1] > highestScoreLeaderboardPoints[9]) {
        highestScoreLeaderboardPoints[9] = playerPointsLeaderboard[0][1];
        strcpy_s(highestScoreLeaderboardNames[9], sizeof(highestScoreLeaderboardNames[9]), playerNames[playerPointsLeaderboard[0][0]]);
        printf("\nThe highest score leaderboard has been updated and now features your score, %s. Congratulations!\n", playerNames[playerPointsLeaderboard[0][0]]);
        Sleep(500);
        gameStatus = 60;
    }

    printf("\nThank you for playing!\n");

    // Resetting variables to their default values
    currentRound = -1;
    numberOfPlayers = 0;
    pointsAtStake = 0;

    // Reset playerPointsLeaderboard
    for (int i = 0; i < 4; i++) {
        playerPointsLeaderboard[i][0] = i; // Player number
        playerPointsLeaderboard[i][1] = 0; // Points
    }

    // Reset playerNames
    for (int i = 0; i < MAX_NO_PLAYERS; i++) {
        playerNames[i][0] = '\0'; // Clear each player name
    }

    // Reset cards
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 0; rank < 13; rank++) {
            cards[suit][rank][2] = 0;  // Ownership
            cards[suit][rank][3] = 0;  // Card Status
        }
    }

    remove("ResourceFiles/TheGameOfWarAutosave.txt");
    if (gameStatus == 60) system("pause");
    if (gameStatus != 60) gameStatus = 11;
}

void readInHighestScoreLeaderboard() {
    FILE* file;
    const char* filePath = "ResourceFiles/highLeaderboard.txt";

    if (fopen_s(&file, filePath, "r") != 0) {
        gameStatus = 11;
        return;
    }

    // Read data from the file
    int i = 0;
    while (i < 10 && fscanf_s(file, "%49s %d", highestScoreLeaderboardNames[i], (unsigned)_countof(highestScoreLeaderboardNames[i]), &highestScoreLeaderboardPoints[i]) == 2) {
        i++; // Move to the next index
    }

    // Close file
    fclose(file);
}

void showHighestScoreLeaderboard() {
    // Sort the leaderboard based on points (Descending Order)
    for (int i = 0; i < 10 - 1; i++) {
        for (int j = 0; j < 10 - i - 1; j++) {
            if (highestScoreLeaderboardPoints[j] < highestScoreLeaderboardPoints[j + 1]) {
                // Swap points
                int tempPoints = highestScoreLeaderboardPoints[j];
                highestScoreLeaderboardPoints[j] = highestScoreLeaderboardPoints[j + 1];
                highestScoreLeaderboardPoints[j + 1] = tempPoints;

                // Swap names
                char tempName[50];
                strcpy_s(tempName, sizeof(tempName), highestScoreLeaderboardNames[j]);
                strcpy_s(highestScoreLeaderboardNames[j], sizeof(highestScoreLeaderboardNames[j]), highestScoreLeaderboardNames[j + 1]);
                strcpy_s(highestScoreLeaderboardNames[j + 1], sizeof(highestScoreLeaderboardNames[j + 1]), tempName);
            }
        }
    }

    // Display the sorted leaderboard
    printName();
    printf("Highest Score Leaderboard:\n");
    printf("--------------------------\n\n");
    for (int i = 0; i < 10; i++) {
        if (highestScoreLeaderboardPoints[i] > 0) { // Only show entries with scores
            printf("%d. %s - %d points\n", i + 1, highestScoreLeaderboardNames[i], highestScoreLeaderboardPoints[i]);
        }
    }
    printf("\n\n");
    writeOutHighestScoreLeaderboard();
    readInAutoSave(0);
}

void writeOutHighestScoreLeaderboard() {
    FILE* file;
    const char* filePath = "ResourceFiles/highLeaderboard.txt";

    if (fopen_s(&file, filePath, "w") != 0) {
        gameStatus = 11;
        return;
    }

    // Write data to the file
    for (int i = 0; i < 10; i++) {
        if (highestScoreLeaderboardPoints[i] > 0) { // Save only entries with scores
            fprintf(file, "%s %d\n", highestScoreLeaderboardNames[i], highestScoreLeaderboardPoints[i]);
        }
    }

    // Close file
    fclose(file);
}
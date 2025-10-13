#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_STUDENTS 10
#define MAX_CHAR_NAME 50
#define NO_SUBJECTS 7

double getDoubleInput(const char* prompt);
void getStringInput(const char* prompt, char* buffer, size_t bufferSize);


// the compare function for double values
int compare(const void* a, const void* b) {
    if (*(double*)b > *(double*)a) return 1;
    else if (*(double*)b < *(double*)a) return -1;
    else return 0;
}

// Method to calculate best six subjects average
double calculateAverageSixSubjects(double* subjects, int students, int grades) {
    double gradesArray[NO_STUDENTS];
    for (int i = 0; i < grades; i++) {
        gradesArray[i] = subjects[i * students];
    }
    int n = sizeof(gradesArray) / sizeof(gradesArray[0]);
    double avg = 0;
    // qsort(array pointer, number of elements, size of one element, compare function);
    qsort(gradesArray, n, sizeof(double), compare);
    for (int i = 0; i < 6 && i < n; i++) avg += gradesArray[i];
    return avg / 6;
}

// Method to calculate total points for best six subjects
int calculatePointsSixSubjects(double* subjects, int students, int grades) {
    double gradesArray[NO_STUDENTS];
    int points = 0;
    for (int i = 0; i < grades; i++) {
        gradesArray[i] = subjects[i * students];
    }
    int n = sizeof(gradesArray) / sizeof(gradesArray[0]);
    // qsort(array pointer, number of elements, size of one element, compare function);
    qsort(gradesArray, n, sizeof(double), compare);
    for (int i = 0; i < 6; i++) {
        if (gradesArray[i] >= 90) points += 100;
        else if (gradesArray[i] >= 80) points += 88;
        else if (gradesArray[i] >= 70) points += 77;
        else if (gradesArray[i] >= 60) points += 66;
        else if (gradesArray[i] >= 50) points += 56;
        else if (gradesArray[i] >= 40) points += 46;
        else if (gradesArray[i] >= 30) points += 37;
        else continue;
    }
    return points;
}

// Method to calculate the best result for each subject
double calculateBest(double *subjects, int grades) {
    double best = 0;
    for (int i = 0; i < grades; i++) if (best < subjects[i]) best = subjects[i];
    return best;
}

int runStudendGradingSystemProgram() {
    char studentName[NO_STUDENTS][MAX_CHAR_NAME];
    double studentResult[NO_SUBJECTS][NO_STUDENTS];
    char subjectName[NO_SUBJECTS][MAX_CHAR_NAME] = { "Mathemetics", "Irish", "English", "French", "Science", "Business", "History" };
    double bestResultSubject[NO_SUBJECTS];
    int indexBestStudent = 0;

    for (int i = 0; i < NO_STUDENTS; i++) {
        char prompt[100];
        snprintf(prompt, sizeof(prompt), "Please enter the name of the %d. student: ", i + 1);
        getStringInput(prompt, studentName[i], MAX_CHAR_NAME);
    }

    for (int i = 0; i < NO_STUDENTS; i++) {
        for (int j = 0; j < NO_SUBJECTS; j++) {
            double score;
            char prompt[100];
            do {
                snprintf(prompt, sizeof(prompt), "Please enter %s's %s score: ", studentName[i], subjectName[j]);
                score = getDoubleInput(prompt);
                if (score < 0 || score > 100) {
                    printf("Invalid score. Please enter a value between 0 and 100 inclusive.\n");
                }
            } while (score < 0 || score > 100);
            studentResult[j][i] = score;
        }
    }

    // Print the header row with student names
    printf("\n\n");
    printf("%-12s", "Subjects");  // Column header for subjects
    for (int i = 0; i < NO_STUDENTS; i++) {
        printf("%-10s", studentName[i]);
    }
    printf("\n");

    // Print each subject row with scores for each student
    for (int i = 0; i < NO_SUBJECTS; i++) {
        printf("%-12s", subjectName[i]);  // Print the subject name
        for (int j = 0; j < NO_STUDENTS; j++) {
            printf("%-10.2f", studentResult[i][j]);  // Print the score for each student in that subject
        }
        printf("\n");
    }

    // Print individual student with the highest average mark (6 best subjects)
    for (int i = 1; i < NO_STUDENTS; i++) {
        if (calculateAverageSixSubjects(&studentResult[0][indexBestStudent], NO_STUDENTS, NO_SUBJECTS) < calculateAverageSixSubjects(&studentResult[0][i], NO_STUDENTS, NO_SUBJECTS)) indexBestStudent = i;
    }
    printf("\n\nThe student with the highest average mark (6 best subjects) is: %s, average: %.2f.\n\n", studentName[indexBestStudent], calculateAverageSixSubjects(&studentResult[0][indexBestStudent], NO_STUDENTS, NO_SUBJECTS));

    // Print the maximum result achieved in each subject for each student
    for (int i = 0; i < NO_SUBJECTS; i++) {
        bestResultSubject[i] = calculateBest(&studentResult[i][0], NO_STUDENTS);
        printf("\nThe maximum result achieved in %s is: %.2f.", subjectName[i], bestResultSubject[i]);
    }

    // Print total points achieved (6 best subject) for each student
    printf("\n");
    for (int i = 0; i < NO_STUDENTS; i++) {
        printf("\n%s achieved a total of: %d points.", studentName[i], calculatePointsSixSubjects(&studentResult[0][i], NO_STUDENTS, NO_SUBJECTS));
    }
    printf("\n");
    system("pause");
    system("cls");
}
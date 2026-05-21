#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 50
#define NUM_SUBJECTS 5
#define MAX_SUBJECT_NAME 30
typedef struct {
    char subjectName[MAX_SUBJECT_NAME];
    float marks;
} Subject;

typedef struct {
    char studentName[50];
    Subject performance[NUM_SUBJECTS];
    float average;
    char letterGrade;
} Student;
char calculateLetterGrade(float average) {
    if (average >= 90.0) return 'A';
    if (average >= 80.0) return 'B';
    if (average >= 70.0) return 'C';
    if (average >= 60.0) return 'D';
    return 'F';
}

void addStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("\n[!] Error: Tracker storage is full.\n");
        return;
    }

    Student s;
    printf("\nEnter student name: ");
    getchar(); // Clear the input buffer from previous menu selections
    fgets(s.studentName, sizeof(s.studentName), stdin);
    s.studentName[strcspn(s.studentName, "\n")] = 0; 

    float sum = 0.0;
    printf("\nEnter details for %d subjects:\n", NUM_SUBJECTS);
    
    for (int i = 0; i < NUM_SUBJECTS; i++) {
    
        printf("\n  Subject %d Name: ", i + 1);
        fgets(s.performance[i].subjectName, MAX_SUBJECT_NAME, stdin);
        s.performance[i].subjectName[strcspn(s.performance[i].subjectName, "\n")] = 0; 

    
        do {
            printf("  Enter marks for %s (0-100): ", s.performance[i].subjectName);
            scanf("%f", &s.performance[i].marks);
            getchar(); 
            
            if (s.performance[i].marks < 0 || s.performance[i].marks > 100) {
                printf("  [!] Invalid marks. Must be between 0 and 100.\n");
            }
        } while (s.performance[i].marks < 0 || s.performance[i].marks > 100);
        
        sum += s.performance[i].marks;
    }

    s.average = sum / NUM_SUBJECTS;
    s.letterGrade = calculateLetterGrade(s.average);

    students[*count] = s;
    (*count)++;
    printf("\n--> Record for %s added successfully!\n", s.studentName);
}


void generateReportCards(Student students[], int count) {
    if (count == 0) {
        printf("\n[!] No student records found. Add records first.\n");
        return;
    }

    printf("\n=============================================");
    printf("\n               REPORT CARDS            ");
    printf("\n=============================================");

    for (int i = 0; i < count; i++) {
        printf("\n\nStudent Name : %s", students[i].studentName);
        printf("\n---------------------------------------------");
        printf("\n%-25s | Marks Secured", "Subject");
        printf("\n---------------------------------------------");
        
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            printf("\n%-25s : %.2f", students[i].performance[j].subjectName, students[i].performance[j].marks);
        }
        
        printf("\n---------------------------------------------");
        printf("\nAverage Marks : %.2f", students[i].average);
        printf("\nFinal Grade   : %c", students[i].letterGrade);
        printf("\n=============================================");
    }
    printf("\n");
}

int main() {
    Student tracker[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    while (1) {
        printf("\n--- STUDENT GRADE TRACKER ---");
        printf("\n1. Add Student Record");
        printf("\n2. Generate Report Cards");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(tracker, &studentCount);
                break;
            case 2:
                generateReportCards(tracker, studentCount);
                break;
            case 3:
                printf("\nExiting program. Goodbye!\n");
                return 0;
            default:
                printf("\n[!] Invalid choice. Please select options 1-3.\n");
        }
    }
    return 0;
}
#include <stdio.h>
#include <string.h>
#define MAX_TASKS 100
#define MAX_LENGTH 100
struct Task {
    char name[MAX_LENGTH];
    int completed;
};
struct Task tasks[MAX_TASKS];
int count = 0;
void addTask() {
    if(count >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }
    printf("Enter task: ");
    getchar(); 
    fgets(tasks[count].name, MAX_LENGTH, stdin);
    tasks[count].name[strcspn(tasks[count].name, "\n")] = 0;
    tasks[count].completed = 0;
    count++;
    printf("Task added successfully!\n");
}
void viewTasks() {
    if(count == 0) {
        printf("No tasks available.\n");
        return;
    }
    printf("\n----- TO-DO LIST -----\n");
    for(int i = 0; i < count; i++) {
        printf("%d. %s [%s]\n",
               i + 1,
               tasks[i].name,
               tasks[i].completed ? "Completed" : "Pending");
    }
}
void editTask() {
    int num;
    viewTasks();
    printf("Enter task number to edit: ");
    scanf("%d", &num);
    if(num < 1 || num > count) {
        printf("Invalid task number.\n");
        return;
    }
    printf("Enter new task: ");
    getchar();
    fgets(tasks[num - 1].name, MAX_LENGTH, stdin);
    tasks[num - 1].name[strcspn(tasks[num - 1].name, "\n")] = 0;
    printf("Task updated successfully!\n");
}
void markComplete() {
    int num;
    viewTasks();
    printf("Enter task number to mark complete: ");
    scanf("%d", &num);
    if(num < 1 || num > count) {
        printf("Invalid task number.\n");
        return;
    }
    tasks[num - 1].completed = 1;
    printf("Task marked as completed!\n");
}
int main() {
    int choice;
    do {
        printf("\n===== TO-DO LIST MENU =====\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Edit Task\n");
        printf("4. Mark Task Complete\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                editTask();
                break;
            case 4:
                markComplete();
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while(choice != 5);
    return 0;
}
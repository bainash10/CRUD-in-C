#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Student {
    char name[50];
    int age;
};

void createRecord() {
    FILE *file;
    struct Student student;

    file = fopen("students.txt", "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter name: ");
    scanf("%s", student.name);
    printf("Enter age: ");
    scanf("%d", &student.age);

    fprintf(file, "%s %d\n", student.name, student.age);

    fclose(file);
}

void displayRecords() {
    FILE *file;
    char name[50];
    int age;

    file = fopen("students.txt", "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nList of Students:\n");
    while (fscanf(file, "%s %d", name, &age) != EOF) {
        printf("Name: %s, Age: %d\n", name, age);
    }

    fclose(file);
}

void updateRecord() {
    FILE *file, *temp;
    char name[50];
    int age, newAge;
    struct Student student;
    int found = 0;

    file = fopen("students.txt", "r");
    temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter name to update: ");
    scanf("%s", name);
    printf("Enter new age: ");
    scanf("%d", &newAge);

    while (fscanf(file, "%s %d", student.name, &student.age) != EOF) {
        if (strcmp(student.name, name) == 0) {
            fprintf(temp, "%s %d\n", student.name, newAge);
            found = 1;
        } else {
            fprintf(temp, "%s %d\n", student.name, student.age);
        }
    }

    fclose(file);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (!found) {
        printf("Record not found!\n");
    } else {
        printf("Record updated successfully.\n");
    }
}

void deleteRecord() {
    FILE *file, *temp;
    char name[50];
    struct Student student;
    int found = 0;

    file = fopen("students.txt", "r");
    temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter name to delete: ");
    scanf("%s", name);

    while (fscanf(file, "%s %d", student.name, &student.age) != EOF) {
        if (strcmp(student.name, name) == 0) {
            found = 1;
        } else {
            fprintf(temp, "%s %d\n", student.name, student.age);
        }
    }

    fclose(file);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (!found) {
        printf("Record not found!\n");
    } else {
        printf("Record deleted successfully.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\nCRUD Operations on Students Records\n");
        printf("1. Create Record\n");
        printf("2. Display Records\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createRecord();
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                updateRecord();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}


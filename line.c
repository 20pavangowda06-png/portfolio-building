#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 256

char doc[MAX_LINES][MAX_LENGTH];
int line_count = 0;

void greet(const char *name) {
    printf("Hello, %s! Welcome to your GitHub portfolio.\n", name);
}

void display_document() {
    printf("\n--- DOCUMENT CONTENT ---\n");
    if (line_count == 0) {
        printf("(Empty Document)\n");
    } else {
        for (int i = 0; i < line_count; i++) {
            printf("%d: %s\n", i + 1, doc[i]);
        }
    }
    printf("------------------------\n\n");
}

void insert_line(int line_num, const char *text) {
    if (line_count >= MAX_LINES) {
        printf("Error: Document is full!\n");
        return;
    }
    if (line_num < 1 || line_num > line_count + 1) {
        printf("Error: Invalid line number!\n");
        return;
    }

    int idx = line_num - 1;
    for (int i = line_count; i > idx; i--) {
        strcpy(doc[i], doc[i - 1]);
    }
    strcpy(doc[idx], text);
    line_count++;
    printf("Line inserted successfully.\n");
}

void delete_line(int line_num) {
    if (line_count == 0) {
        printf("Error: Document is empty!\n");
        return;
    }
    if (line_num < 1 || line_num > line_count) {
        printf("Error: Invalid line number!\n");
        return;
    }

    int idx = line_num - 1;
    for (int i = idx; i < line_count - 1; i++) {
        strcpy(doc[i], doc[i + 1]);
    }
    line_count--;
    printf("Line deleted successfully.\n");
}

void show_stats() {
    int total_words = 0;
    for (int i = 0; i < line_count; i++) {
        char temp[MAX_LENGTH];
        strcpy(temp, doc[i]);
        char *token = strtok(temp, " \t\n");
        while (token != NULL) {
            total_words++;
            token = strtok(NULL, " \t\n");
        }
    }
    printf("\n--- DOCUMENT STATISTICS ---\n");
    printf("Total Lines: %d\n", line_count);
    printf("Total Words: %d\n", total_words);
    printf("---------------------------\n\n");
}

int main() {
    int choice, line_num;
    char buffer[MAX_LENGTH];

    greet("Ada");

    while (1) {
        printf("=== LINE EDITOR MENU ===\n");
        printf("1. Display Document\n");
        printf("2. Insert Line\n");
        printf("3. Delete Line\n");
        printf("4. Show Statistics (Line/Word Count)\n");
        printf("5. Exit\n");
        printf("Enter choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input! Try again.\n\n");
            continue;
        }
        getchar();

        switch (choice) {
            case 1:
                display_document();
                break;
            case 2:
                printf("Enter line number to insert at (1 to %d): ", line_count + 1);
                scanf("%d", &line_num);
                getchar();
                printf("Enter line text: ");
                fgets(buffer, MAX_LENGTH, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                insert_line(line_num, buffer);
                break;
            case 3:
                printf("Enter line number to delete (1 to %d): ", line_count);
                scanf("%d", &line_num);
                getchar();
                delete_line(line_num);
                break;
            case 4:
                show_stats();
                break;
            case 5:
                printf("Exiting editor. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Choose between 1 and 5.\n\n");
        }
    }
    return 0;
}
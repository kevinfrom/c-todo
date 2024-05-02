#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "cJSON.h"

struct Todo {
    int completed;
    char title[256];
};

int main() {
    printf("Todo manager\n");

    struct Todo *todos = (struct Todo *)malloc(0);
    int counter = 0;
    char option;
    int indexToComplete;
    char newTodoTitle[256];

    cJSON *json;

    while(1) {
        printf("Menu:\n");
        printf("A - Add a todo\n");
        printf("C - Complete a todo\n");
        printf("P - Print all todos\n");
        printf("S - Save all todos in a JSON file\n");
        printf("Q - Quit\n");
        printf("Select an option: ");
        scanf(" %c", &option);

        switch(option) {
            case 'a':
            case 'A':
                printf("Enter a new title for your todo: ");
                scanf(" %s", newTodoTitle);

                strcpy(todos[counter].title, newTodoTitle);
                todos[counter].completed = 0;
                counter++;
            break;
            case 'c':
            case 'C':
                printf("Enter a number of a todo to complete: ");
                scanf(" %d", &indexToComplete);

                todos[indexToComplete + -1].completed = 1;
                printf("Completed todo: %d\n", indexToComplete);
            break;
            case 'p':
            case 'P':
                if (counter <= 0) {
                    printf("No todos yet.\n");
                } else {
                    for (int i = 0; i < counter; i++) {
                        printf("Todo: %s. Completed: %d\n", todos[i].title, todos[i].completed);
                    }
                }
            break;
            case 's':
            case 'S':
                json = cJSON_CreateArray();

                for (int i = 0; i < counter; i++) {
                    cJSON *todoObj = cJSON_CreateObject();
                    cJSON_AddStringToObject(todoObj, "title", todos[i].title);
                    cJSON_AddNumberToObject(todoObj, "completed", todos[i].completed);
                    cJSON_AddItemToArray(json, todoObj);
                }

                char *json_string = cJSON_Print(json);

                FILE *file = fopen("todos.json", "w");
                if (file == NULL)
                {
                    printf("Could not open todos.json\n");
                    return 1;
                }

                fwrite(json_string, 1, strlen(json_string), file);
                fclose(file);

                cJSON_Delete(json);
                free(json_string);
            break;
            case 'q':
            case 'Q':
                free(todos);
                printf("Bye!\n");

                return 0;
            default:
                printf("Unknown option!\n");
        }
    }

    return 0;
}

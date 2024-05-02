#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <cjson/cJSON.h>

struct Todo {
    int completed;
    char title[256];
};

int main() {
    cJSON *json = cJSON_CreateObject();

    if (json == NULL)
    {
        free(json);
        printf("Failed to initialize JSON object\n");
        return 1;
    }

    cJSON_Delete(json);
    return 0;
}

int old_main() {
    printf("Todo manager\n");

    struct Todo *todos = (struct Todo *)malloc(0);
    int counter = 0;
    char option;
    int indexToComplete;

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
                strcpy(todos[counter].title, "Test");
                todos[counter].completed = 0;
                counter++;
            break;
            case 'c':
            case 'C':
                printf("Enter a number of a todo to complete: ");
                scanf(" %d", &indexToComplete);

                int amountOfTodos = sizeof(*todos) / sizeof(todos[0]);

                if (indexToComplete > amountOfTodos) {
                    printf("Entered number %d does not exist.\n", indexToComplete);
                } else {
                    todos[indexToComplete + -1].completed = 1;
                    printf("Completed todo: %d\n", indexToComplete);
                }
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
                //cJSON *root = cJSON_CreateObject();
                //cJSON_AddStringToObject(root, "name", "John");

                //char *json_string = cJSON_Print(root);

                //cJSON_Delete(root);
                //free(json_string);
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

// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/tokenizer.h"
#include "src/history.h"

#define MAX_INPUT_SIZE 1024

int main() {
    char input[MAX_INPUT_SIZE];
    List *history = init_history();

    printf("Welcome to the Tokenizer with History!\n");
    printf("Enter commands. Type 'exit' to quit.\n");

    while (1) {
        printf("$ "); // Prompt indicator
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("\nExiting.\n");
            break;
        }

        // Remove trailing newline character
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        // Check for 'exit' command
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Check for 'history' command to display history
        if (strcmp(input, "history") == 0) {
            print_history(history);
            continue;
        }

        // Check for history recall command (e.g., !2)
        if (input[0] == '!' && strlen(input) > 1) {
            int id = atoi(&input[1]);
            if (id > 0) {
                char *historical_input = get_history(history, id);
                if (historical_input != NULL) {
                    printf("%s\n", historical_input); // Echo the historical command
                    // Tokenize and print tokens
                    char **tokens = tokenize(historical_input);
                    print_tokens(tokens);
                    free_tokens(tokens);
                    continue;
                } else {
                    printf("No history entry found for ID %d.\n", id);
                    continue;
                }
            }
        }

        // Add the input to history
        add_history(history, input);

        // Tokenize and print tokens
        char **tokens = tokenize(input);
        print_tokens(tokens);
        free_tokens(tokens);
    }

    // Cleanup
    free_history(history);
    return 0;
}
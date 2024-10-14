// src/tokenizer.c
#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

/* Return true (non-zero) if c is a whitespace character ('\t' or ' '). */
int space_char(char c) {
    return (c == ' ' || c == '\t') ? 1 : 0;
}

/* Return true (non-zero) if c is a non-whitespace character. */
int non_space_char(char c) {
    return (!space_char(c) && c != '\0') ? 1 : 0;
}

/* Returns a pointer to the first non-space character in the first token. */
char *token_start(char *str) {
    if (str == NULL) return NULL;
    while (space_char(*str)) {
        str++;
    }
    return non_space_char(*str) ? str : NULL;
}

/* Returns a pointer to the character after the end of the token. */
char *token_terminator(char *token) {
    if (token == NULL) return NULL;
    while (non_space_char(*token)) {
        token++;
    }
    return token;
}

/* Counts the number of tokens in the string. */
int count_tokens(char *str) {
    int count = 0;
    char *current = token_start(str);
    while (current != NULL) {
        count++;
        current = token_start(token_terminator(current));
    }
    return count;
}

/* Returns a freshly allocated string containing len characters from inStr. */
char *copy_str(char *inStr, short len) {
    if (inStr == NULL || len <= 0) return NULL;
    char *copy = (char *)malloc((len + 1) * sizeof(char));
    if (copy == NULL) {
        perror("Failed to allocate memory for copy_str");
        exit(EXIT_FAILURE);
    }
    for (short i = 0; i < len; i++) {
        copy[i] = inStr[i];
    }
    copy[len] = '\0';
    return copy;
}

/* Tokenizes the input string and returns an array of tokens. */
char **tokenize(char* str) {
    if (str == NULL) return NULL;

    int num_tokens = count_tokens(str);
    char **tokens = (char **)malloc((num_tokens + 1) * sizeof(char *));
    if (tokens == NULL) {
        perror("Failed to allocate memory for tokens");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    char *current = token_start(str);
    while (current != NULL) {
        char *end = token_terminator(current);
        short len = end - current;
        tokens[index++] = copy_str(current, len);
        current = token_start(end);
    }
    tokens[index] = NULL; // Null-terminate the array
    return tokens;
}

/* Prints all tokens. */
void print_tokens(char **tokens) {
    if (tokens == NULL) return;
    for (int i = 0; tokens[i] != NULL; i++) {
        printf("Token[%d]: %s\n", i, tokens[i]);
    }
}

/* Frees all tokens and the array containing them. */
void free_tokens(char **tokens) {
    if (tokens == NULL) return;
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
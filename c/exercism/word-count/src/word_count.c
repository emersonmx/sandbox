#include "word_count.h"

#include <ctype.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_word(const char *input, const char *delimiters);
int str_replace(const char *search, const char *replace, const char *subject,
                char *str);

int word_count(const char *input_text, word_count_word_t *words)
{
    memset(words, 0, sizeof(word_count_word_t) * MAX_WORDS);

    char input[MAX_WORD_LENGTH + 1];
    memset(input, 0, MAX_WORD_LENGTH + 1);
    strncpy(input, input_text, strlen(input_text));
    char delimiters[] = " ,\n";
    char *token = strtok(input, delimiters);
    int j = 0;
    int word_index = 0;
    bool word_exists = false;

    while (token) {
        word_exists = false;
        word_index = 0;
        for (int i = 0; i < MAX_WORDS; ++i) {
            if (strncmp(token, words[i].text, strlen(token)) == 0) {
                word_exists = true;
                word_index = i;
                break;
            }
        }

        if (word_exists) {
            ++words[word_index].count;
        } else {
            strncpy(words[j].text, token, MAX_WORD_LENGTH);
            ++words[j].count;
            ++j;
        }

        token = strtok(NULL, delimiters);
    }

    return j;
}

int str_replace(const char *search, const char *replace, const char *subject,
                char *str)
{
    printf("%s %s %s %s\n", search, replace, subject, str);
    // buscar por search em subject
    // se encontra substitui por replace
    // coloca o resulta em str
    return 0;
}

int find_word(const char *input, const char *delimiters)
{
    printf("%s %s\n", input, delimiters);
    return -1;
}

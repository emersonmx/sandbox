#include "acronym.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

char *abbreviate(const char *phrase)
{
    if (!phrase || strlen(phrase) == 0) {
        return NULL;
    }

    char c;
    int words = 1;
    for (int i = 0; phrase[i] != '\0'; ++i) {
        c = phrase[i];
        words += (c == ' ' || c == '-') ? 1 : 0;
    }

    bool after_delim = true;
    int abbr_index = 0;
    char* abbr = calloc(words + 1, sizeof(char));

    for (int i = 0; phrase[i] != '\0'; ++i) {
        c = toupper(phrase[i]);
        if (c == ' ' || c == '-') {
            after_delim = true;
            continue;
        }

        if (!after_delim) {
            continue;
        }
        
        abbr[abbr_index++] = c;
        after_delim = false;
    }

    return abbr;
}

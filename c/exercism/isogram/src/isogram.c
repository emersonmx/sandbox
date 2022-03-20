#include "isogram.h"
#include <string.h>
#include <ctype.h>

bool is_isogram(const char phrase[])
{
    if (!phrase) {
        return false;
    }

    int size = strlen(phrase);
    for (int i = 0; i < size; ++i) {
        int count = 0;
        char current = tolower(phrase[i]);
        if (current == '-' || current == ' ') {
            continue;
        }

        for (int j = 0; j < size; ++j) {
            count += current == tolower(phrase[j]) ? 1 : 0;
        }

        if (count > 1) {
            return false;
        }
    }

    return true;
}

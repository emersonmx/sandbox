// Experiment to find out what happens when `printf`'s argument string contains
// `\c`, where `'c` is some character not listed above.

#include <stdio.h>

int main()
{
    printf("hello, world\a"); // bell
    printf("hello, world\b"); // backspace
    printf("\033[31;1;4mhello, world\033[0m"); // with colors! :D
    return 0;
}

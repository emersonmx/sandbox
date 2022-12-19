#include <stdio.h>

main()
{
    printf("hello, world\a"); // bell
    printf("hello, world\b"); // backspace
    printf("\033[31;1;4mhello, world\033[0m"); // with colors! :D
}

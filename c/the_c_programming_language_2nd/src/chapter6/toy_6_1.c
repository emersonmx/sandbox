#include <stdio.h>

struct {
    unsigned char is_keyword : 1;
    unsigned char is_extern : 1;
    unsigned char is_static : 1;
} flags;

int main()
{
    flags.is_keyword = 1;
    flags.is_static = 1;
    printf("%d %d %d\n", flags.is_keyword, flags.is_extern, flags.is_static);
    printf("%lu\n", sizeof flags);

    return 0;
}

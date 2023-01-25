#include <stdio.h>

struct {
    unsigned int is_keyword : 1;
    unsigned int is_extern : 1;
    unsigned int is_static : 1;
} flags;

int main()
{
    flags.is_keyword = 1;
    flags.is_static = 1;
    printf("%d %d %d\n", flags.is_keyword, flags.is_extern, flags.is_static);
    printf("%ld\n", sizeof flags);

    return 0;
}

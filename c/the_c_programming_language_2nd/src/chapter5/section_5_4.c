#include <stdio.h>
#include <string.h>

#define ALLOCSIZE 10000 // size of available space

static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf; // next free position

char *alloc(int n);
void afree(char *p);

int main()
{
    char t[] = "Hello World";
    int ts = strlen(t);
    char *p = alloc(ts + 1);

    for (int i = 0; i < ts + 1; ++i)
        p[i] = t[i];

    printf("%s\n", p);

    afree(p);

    return 0;
}

char *alloc(int n) // return pointer to n characters
{
    if (allocbuf + ALLOCSIZE - allocp >= n) { // it fits
        allocp += n;
        return allocp - n; // old p
    } else { // not enough room
        return 0;
    }
}

void afree(char *p) // free storage pointed to by p
{
    if (allocbuf <= p && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

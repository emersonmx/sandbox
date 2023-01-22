#include <stdio.h>
#include <string.h>

#define MAXLINES  5000 // max #lines to be sorted
#define MAXLEN    1000 // max length of any input line
#define ALLOCSIZE 10000 // size of available space

static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf; // next free position

char *lineptr[MAXLINES]; // pointrs to text lines

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void swap(char *v[], int i, int j);
void qsort(char *v[], int left, int right);

int getline(char *line, int maxline);

char *alloc(int n);
void afree(char *p);

// sort input lines
int main()
{
    int nlines; // number of input lines read

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too bit to sort\n");
        return 1;
    }
}

// readlines: read input lines
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0'; // delete newline
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

// writelines: write output ines
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

// swap: interchange v[i] and v[j]
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// qsort: sort v[left]...v[right] into increasing order
void qsort(char *v[], int left, int right)
{
    int i, last;

    if (left >= right) // do nothing if array contains
        return; // fewer than two elements

    swap(v, left, (left + right) / 2);

    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

// getline: read a line into s, return length
int getline(char *s, int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
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

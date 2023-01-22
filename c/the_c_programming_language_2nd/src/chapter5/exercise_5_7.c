// Rewrite `readlines` to store lines in an array supplied by `main`, rather
// than calling `alloc` to maintain storage. How much faster is the program?

#include <stdio.h>
#include <string.h>

#define MAXLINES  5000 // max #lines to be sorted
#define MAXLEN    1000 // max length of any input line
#define ALLOCSIZE 10000 // size of available space
#define MAXSTOR   5000

char *lineptr[MAXLINES]; // pointrs to text lines
char linestor[MAXLINES];

int readlines(char *lineptr[], char *linestor, int maxlines);
void writelines(char *lineptr[], int nlines);

void swap(char *v[], int i, int j);
void qsort(char *v[], int left, int right);

int getline(char *line, int maxline);

// sort input lines
int main()
{
    int nlines; // number of input lines read

    if ((nlines = readlines(lineptr, linestor, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too bit to sort\n");
        return 1;
    }
}

// readlines: read input lines
int readlines(char *lineptr[], char *linestor, int maxlines)
{
    int len, nlines;
    char line[MAXLEN];
    char *p = linestor;
    char *linestop = linestor + MAXSTOR;

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || p + len > linestop) {
            return -1;
        } else {
            line[len - 1] = '\0'; // delete newline
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
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

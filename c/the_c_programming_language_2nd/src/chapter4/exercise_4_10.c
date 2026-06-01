// An alternate organization uses `getline` to read an entire input line; this
// makes `getch` and `ungetch` unnecessary. Revise the calculator to use this
// approach.

#include <ctype.h> // for atof()
#include <stdio.h>
#include <stdlib.h> // for atof()

#define MAXOP   100 // max size of operand or operator
#define NUMBER  '0' // signal that a number was found
#define MAXVAL  100 // maximum depth of val stack
#define BUFSIZE 100
#define MAXLINE 100

int sp = 0; // next free stack position
double val[MAXVAL]; // value stack
int li = 0;
char line[MAXLINE]; // input line

int getop(char s[]);
void push(double f);
double pop(void);
int getline(char line[], int limit);

// reverse Polish calculator
int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

// push: push f onto value stack
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

// pop: pop and return top value from stack
double pop(void)
{
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

// getop: get next operator or numeric operand
int getop(char s[])
{
    int i, c;

    if (line[li] == '\0') {
        if (getline(line, MAXLINE) == 0)
            return EOF;
        else
            li = 0;
    }

    while ((s[0] = c = line[li++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; // not a number

    i = 0;
    if (isdigit(c)) // collect integer part
        while (isdigit(s[++i] = c = line[li++]))
            ;
    if (c == '.') // collect fraction part
        while (isdigit(s[++i] = c = line[li++]))
            ;
    s[i] = '\0';

    li--;
    return NUMBER;
}

int getline(char s[], int lim)
{
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}

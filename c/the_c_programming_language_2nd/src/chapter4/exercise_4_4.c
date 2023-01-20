// Add commands to print the top element of the stack without popping, to
// duplicate it, and to swap the top two elements. Add a command to clear the
// stack.

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXVAL  100
#define BUFSIZE 100
#define MAXOP   100
#define NUMBER  '0'

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;

int getop(char s[]);
int getch(void);
void ungetch(int c);
void push(double n);
double pop(void);

int main()
{
    int type;
    double t1, t2;
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
            t1 = pop();
            push(pop() - t1);
            break;
        case '/':
            t1 = pop();
            if (t1 != 0.0)
                push(pop() / t1);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            t1 = pop();
            if (t1 != 0.0)
                push(fmod(pop(), t1));
            else
                printf("error: zero divisor\n");
            break;
        case 'p':
            t1 = val[sp - 1];
            printf("\tTop: %.8g\n", t1);
            break;
        case 'd':
            t1 = val[sp - 1];
            push(t1);
            break;
        case 's':
            t1 = pop();
            t2 = pop();
            push(t1);
            push(t2);
            break;
        case 'c':
            sp = 0;
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

int getop(char s[])
{
    int c, i;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c;

    i = 0;
    if (c == '-' || isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);

    if (i == 1 && s[0] == '-')
        return '-';
    return NUMBER;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void push(double n)
{
    if (sp < MAXVAL)
        val[sp++] = n;
    else
        printf("error: stack full, can't push %g\n", n);
}

double pop(void)
{
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

// Add access to library functions like `sin`, `exp` and `pow`. See `<math.h>`
// in Appendix B, Section 4.

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXVAL   100
#define BUFSIZE  100
#define MAXOP    100
#define NUMBER   '0'
#define FUNCTION '1'

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;

int getop(char s[]);
int getch(void);
void ungetch(int c);
void push(double n);
double pop(void);
void clear(void);
void show_top(void);
void duplicate(void);
void swap(void);
void exec_function(char s[]);

int main()
{
    int type;
    double t1;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case FUNCTION:
            exec_function(s);
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
        case '?':
            show_top();
            break;
        case '#':
            duplicate();
            break;
        case '~':
            swap();
            break;
        case '!':
            clear();
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
    if (isalpha(c)) {
        i = 0;
        while (isalpha(s[i++] = c))
            c = getch();
        s[i - 1] = '\0';
        if (c != EOF)
            ungetch(c);
        return FUNCTION;
    }
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

void clear(void)
{
    sp = 0;
}

void show_top(void)
{
    if (sp > 0) {
        printf("\tTop: %.8g\n", val[sp - 1]);
    } else {
        printf("error: stack empty\n");
    }
}

void duplicate(void)
{
    double aux = pop();
    push(aux);
    push(aux);
}

void swap(void)
{
    double a = pop();
    double b = pop();
    push(a);
    push(b);
}

void exec_function(char s[])
{
    if (strcmp(s, "sin") == 0) {
        push(sin(pop()));
    } else if (strcmp(s, "exp") == 0) {
        push(exp(pop()));
    } else if (strcmp(s, "pow") == 0) {
        double aux = pop();
        push(pow(pop(), aux));
    } else
        printf("%s is not a supported function.\n", s);
}

#define N 10
#include <stdio.h>
#include <ctype.h>

int main(void) {
    int data[N];
    int top;
    top = -1;
    int a, b, c, line;
    line = 1;

    while ((c  = getchar()) != EOF) {
        if (isdigit(c)) {
            int current = c - '0';
            c = getchar();
            while (isdigit(c)) {
                current = current * 10 + (c - '0');
                c = getchar();
            }
            if (top < 9) {
                top++;
                data[top] = current;
            }
            else {
                c = current + '0';
                goto error;
            }
        }
        if (c == ' ') {
            continue;
        }
        else if ((c == '+' || c == '-' || c == '*' || c == '/') && top > 0) {
            a = data[top--];
            b = data[top--];
            switch(c) {
                case '+':
                    data[++top] = a + b;
                    break;
                case '-':
                    data[++top] = b - a;
                    break;
                case '*':
                    data[++top] = b * a;
                    break;
                case '/':
                    if (a != 0) {
                        data[++top] = b / a;
                    }
                    else {
                        goto error;
                    }
            }
        }
        else if (c == '\n') {
            if (top == 0) {
                printf("line %d: %d\n", line, data[top]);
            }
            else {
                printf("line %d: error at %s\n", line, "\\n");
            }
            top = -1;
            line++;
        } 
        else {
            error:
            printf("line %d: error at %c\n", line, c);
            top = -1;
            while ((c = getchar()) != '\n') {

            }
            line++;
        }
    }
    return 0;
}

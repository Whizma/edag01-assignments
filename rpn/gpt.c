#include <stdio.h>
#include <ctype.h>

#define N 10

int data[N]; // Stack as an array
int top = -1; // Top of the stack

int main(void) {
    int a, b, c, line;
    line = 1;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            continue;
        } else if (isdigit(c)) {
            int current = c - '0';
            c = getchar();
            while (isdigit(c)) {
                current = current * 10 + (c - '0');
                c = getchar();
            }
            if (top < N - 1) {
                data[++top] = current;
            } else {
                c = current + '0';
                goto error;
            }
        }
        if (c == ' ') {
            continue;
        } else if ((c == '+' || c == '-' || c == '*' || c == '/') && top > 0) {
            if (top <= 0) {
                goto error;
            }
            a = data[top--];;
            b = data[top--];;
            int res;
            switch (c) {
                case '+':
                    res = a + b;
                    data[++top] = res;
                    break;
                case '-':
                    res = b - a;
                    data[++top] = res;
                    break;
                case '*':
                    res = a * b;
                    data[++top] = res;
                    break;
                case '/':
                    if (a != 0) {
                        res = b / a;
                        data[++top] = res;
                    } else {
                        goto error;
                        continue;
                    }
            }
        } else if (c == '\n') {
            if (top == 0) {
                printf("line %d: %d\n", line, data[top]);
                line++;
            } else {
                printf("line %d: error at %s\n", line, "\\n");
                line++;
            }
            top = -1; // Reset top to -1 for a new line
        } else {
            error:
            printf("line %d: error at %c\n", line, c);
            line++;
            top = -1; // Reset top to -1 for a new line
            while ((c = getchar()) != '\n') {
                // Consume remaining characters until newline
            }
        }
    }
    return 0;
}

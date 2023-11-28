#define N 10
#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Stack data structure
typedef struct Stack Stack;
struct Stack {
    int data[N];
    int top;
};

int main(void) {
    Stack stack;
    stack.top = -1;

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
            if (stack.top < 9) {
                stack.top++;
                stack.data[stack.top] = current;
            }
            else {
                c = current + '0';
                goto error;
            }
        }
        if (c == ' ') {
            continue;
        }
        else if ((c == '+' || c == '-' || c == '*' || c == '/') && stack.top > 0) {
            a = stack.data[stack.top--];
            b = stack.data[stack.top--];
            switch(c) {
                case '+':
                    stack.data[++stack.top] = a + b;
                    break;
                case '-':
                    stack.data[++stack.top] = b - a;
                    break;
                case '*':
                    stack.data[++stack.top] = b * a;
                    break;
                case '/':
                    if (a != 0) {
                        stack.data[++stack.top] = b / a;
                    }
                    else {
                        goto error;
                        continue;
                    }
            }
        }
        else if (c == '\n') {
            if (stack.top == 0) {
                printf("line %d: %d\n", line, stack.data[stack.top]);
                line++;
                while (stack.top != -1) {
                    stack.top--;
                }
            }
            else {
                printf("line %d: error at %s\n", line, "\\n");
                line++;
                while (stack.top != -1) {
                    stack.top--;
                }
            }
        } 
        else {
            error:
            printf("line %d: error at %c\n", line, c);
            line++;
            while (stack.top != -1) {
                stack.top--;
            }
            while ((c = getchar()) != '\n') {

            }
        }
    }
    return 0;
}

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

// Function prototypes
void initStack(Stack* stack);
void push(Stack* stack, int value);

int main(void) {
    Stack stack;
    stack.top = -1;

    int a, b, c, line;
    line = 1;

    while ((c  = getchar()) != EOF) {
        if (c == ' ') {
            continue;
        }
        else if (isdigit(c)) {
            int current = c - '0';
            c = getchar();
            while (isdigit(c)) {
                current = current * 10 + (c - '0');
                c = getchar();
            }
            if (stack.top < 9) {
                push(&stack, current);
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
            if (stack.top <= 0) {
                goto error;
            }
            a = stack.data[stack.top];
            stack.top--;
            b = stack.data[stack.top];
            stack.top--;
            int res;
            switch(c) {
                case '+':
                    res = a + b;
                    push(&stack, res);
                    break;
                case '-':
                    res = b - a;
                    push(&stack, res);
                    break;
                case '*':
                    res = a * b;
                    push(&stack, res);
                    break;
                case '/':
                    if (a != 0) {
                        res = b / a;
                        push(&stack, res);
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

// Push value onto stack
void push(Stack* stack, int value) {
    stack->top++;
    stack->data[stack->top] = value;
}

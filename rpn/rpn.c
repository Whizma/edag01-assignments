#define N		(10)
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
int pop(Stack* stack);
int peek(Stack* stack);

int main(void) {
    Stack stack;
    initStack(&stack);

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
            printf("%d stack size \n",stack.top);
            if (stack.top < 9) {
                push(&stack, current);
            }
            else {
                printf("borde vara här vi fuckar stacken\n");
                printf("current: %d\n", current);
                goto error;
            }
        }
        if (c == ' ') {
            continue;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' && stack.top > 0) {
            a = pop(&stack);
            b = pop(&stack);
            int res;
            switch(c) {
                case '+':
                    res = a + b;
                    break;
                case '-':
                    res = b - a;
                    break;
                case '*':
                    res = a * b;
                    break;
                case '/':
                    if (a != 0) {
                        res = b / a;
                    }
                    else {
                        goto error;
                        continue;
                    }
                    break;
        }
            push(&stack, res);
        }
        else if (c == '\n') {
            if (stack.top == 0) {
                printf("line %d : %d\n", line, pop(&stack));
                line++;
                while (stack.top != -1) {
                    pop(&stack);
                }
            }
            else {
                printf("line %d : error at %s \n", line, "\\n");
                line++;
                while (stack.top != -1) {
                    pop(&stack);
                }
            }
        } 
        else {
            error:
            printf("line %d : error at %c \n", line, c);
            line++;
            while (stack.top != -1) {
                pop(&stack);
            }
        }
    }
    return 0;
}

// Initialize stack
void initStack(Stack* stack) {
    stack->top = -1;
}

// Push value onto stack
void push(Stack* stack, int value) {
    if (stack->top == N - 1) {
        printf("%s\n", "Stack is full. i push ");
        return;
    }
    stack->top++;
    stack->data[stack->top] = value;
}

// Pop value from stack
int pop(Stack* stack) {
    if (stack->top == -1) {
        printf("%s\n", "Stack is empty. i pop ");
        return -1;
    }
    int value = stack->data[stack->top];
    stack->top--;
    return value;
}

int peek(Stack *stack) {
    if (stack->top == -1) {
        printf("%s\n", "Stack is empty. i peek ");
        return -1;
    }
    return stack->data[stack->top];
}

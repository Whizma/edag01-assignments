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
void push(Stack* stack, char operator);
int pop(Stack* stack);
int peek(Stack* stack);

int main(void) {
    Stack stack;
    initStack(&stack);

    int a;
    int b;
    int c;
    int line;
    int ch;
    line = 0;

    while ((c  = getchar()) != EOF) {
        if (c == ' ') {
            continue;
        }
        if (isdigit(c)) {
            int current = c;
            while ((ch = getchar()) != ' ') {
                current = current * 10 + (ch - '0');
            }
            push(&stack, current - '0');
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
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
                        printf("%s\n", "Division med noll ");
                        continue;
                    }
                    break;
            }
            printf("%s %d\n", "peek innan vi pushar resultat till stacken", peek(&stack));
            printf("%s %d\n", "res innan vi pushar resultat till stacken", res);
            push(&stack, res);
            printf("%s %d\n", "peek efter vi pushat resultatet till stacken", peek(&stack));
        }
        else if (c == '\n') {
            if (stack.top == -1) {
                printf("%s\n", "Stack is empty. ");
            }
            printf("line %d %s %d\n", line, ":", pop(&stack));
            line++;
        } else {
            printf("%s\n", "något skumt hände");
        }
    }
    return 0;
}

// Initialize stack
void initStack(Stack* stack) {
    stack->top = -1;
}

// Push value onto stack
void push(Stack* stack, char operator) {
    if (stack->top == N - 1) {
        printf("%s\n", "Stack is full. i push ");
        return;
    }
    stack->top++;
    stack->data[stack->top] = operator;
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

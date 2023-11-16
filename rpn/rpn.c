#define N		(10)
#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Stack data structure
typedef struct Stack Stack;
struct Stack {
    char data[N];
    int top;
};

// Function prototypes
void initStack(Stack* stack);
void push(Stack* stack, char operator);
char pop(Stack* stack);

int main(void) {
    Stack stack;
    initStack(&stack);
    int a;
    int b;
    int c;
    int index;
    index = 0;
    while ((c  = getchar()) != EOF) {
        if (c == ' ') {
            continue;
        }
        if (isdigit(c)) {
            push(&stack, c - '0');
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            switch(c) {
                case '+':
                    a = pop(&stack);
                    b = pop(&stack);
                    push(&stack, a + b);
                    break;
                case '-':
                    a = pop(&stack);
                    b = pop(&stack);
                    push(&stack, b - a);
                    break;
                case '*':
                    a = pop(&stack);
                    b = pop(&stack);
                    push(&stack, a * b);
                    break;
                case '/':
                    a = pop(&stack);
                    b = pop(&stack);
                    if (a != 0) {
                        push(&stack, b / a);
                    }
                    else {
                        printf("%s", "Division med noll");
                    }
                    break;
            }
        }
        else if (c == '\n') {
            if (stack.top == -1) {
                printf("%s\n", "Stack is empty.");
            }
        } else {
            printf("%c", c);
            printf("%s\n", "något skumt hände");
        } 
        printf("line: %d %d\n", index, (int) stack.top);
        index++;
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
        printf("Stack is full");
        return;
    }
    stack->top++;
    stack->data[stack->top] = operator;
}

// Pop value from stack
char pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack is empty");
        return -1;
    }
    int value = stack->data[stack->top];
    stack->top--;
    return value;
}

char peek(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack is empty.");
        return -1;
    }
    return stack->data[stack->top];
}

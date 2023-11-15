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
void calculateExpression(Stack* stack, char operator);

int main(void) {
    Stack stack;
    initStack(&stack);
    int c;
    while ((c  = getchar()) != EOF) {
        if (isdigit(c)) {
            push(&stack, c);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
        }
        else if (c == '\n') {
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


// Perform calculation based on operator
void calculateExpression(Stack* stack, char operator) {
    
}

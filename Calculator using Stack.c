#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>

#define STACK_SIZE 20

double stack[STACK_SIZE];
int top = -1;

void push(double x) {
    if (top < STACK_SIZE - 1) {
        stack[++top] = x;
    } else {
        printf("Stack overflow!\n");
    }
}

double pop() {
    if (top >= 0) {
        return stack[top--];
    } else {
        printf("Stack underflow!\n");
        return 0.0;
    }
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int priority(char x) {
    if (x == '(')
        return 0;
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    return -1; // Invalid operator
}

void infixToPostfix(char* infixExp, char* postfixExp) {
    char *e, x;
    char postfix[STACK_SIZE];
    int index = 0;
    e = infixExp;

    while (*e != '\0') {
        if (isdigit(*e) || *e == '.') {
            while (isdigit(*e) || *e == '.') {
                postfixExp[index++] = *e;
                e++;
            }
            postfixExp[index++] = ' ';
        } else if (*e == '(') {
            push(*e);
            e++;
        } else if (*e == ')') {
            while ((x = pop()) != '(') {
                postfixExp[index++] = x;
                postfixExp[index++] = ' ';
            }
            e++;
        } else {
            while (top != -1 && priority(stack[top]) >= priority(*e)) {
                postfixExp[index++] = pop();
                postfixExp[index++] = ' ';
            }
            push(*e);
            e++;
        }
    }

    while (top != -1) {
        postfixExp[index++] = pop();
        postfixExp[index++] = ' ';
    }
    postfixExp[index] = '\0';
}

double evaluatePostfix(char* postfixExp) {
    char *e;
    double operand1, operand2;
    e = postfixExp;

    while (*e != '\0') {
        if (isdigit(*e) || *e == '.') {
            char* endptr;
            double num = strtod(e, &endptr); // strtod() is string to double conversion function 
            push(num);
            e = endptr;// after conversion updates the pointer e to point to the next character after the parsed numeric operand
        } else if (isOperator(*e)) {
            operand2 = pop();
            operand1 = pop();
            switch (*e) {
                case '+':
                    push(operand1 + operand2);
                    break;
                case '-':
                    push(operand1 - operand2);
                    break;
                case '*':
                    push(operand1 * operand2);
                    break;
                case '/':
                    if (operand2 != 0) {
                        push(operand1 / operand2);
                    } else {
                        printf("Division by zero!\n");
                        return 0.0;
                    }
                    break;
                default:
                    printf("Invalid operator!\n");
                    return 0.0;
            }
            e++;
        } else if (*e == ' ') {
            e++;
        } else {
            printf("Invalid character: %c\n", *e);
            return 0.0;
        }
    }
    return pop();
}

int main() {
    char infixExp[20];
    char postfixExp[20];
    double result;

    printf("Enter an infix expression: ");
    scanf("%s", infixExp);

    infixToPostfix(infixExp, postfixExp);
    printf("Postfix expression: %s\n", postfixExp);

    result = evaluatePostfix(postfixExp);
    printf("Result: %.2f\n", result);

	getch(); 
    return 0;
}


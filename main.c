/**
 * CS200
 * Project 3: Bitwise Ops
 * Jason Travis
 * January 18, 2013 
 *
 * Implements a Single-Digit RPN Calculator that demonstrates
 * bitwise operations on integers that are evaluated in decimal, hex, and
 * binary format. 
 */

#include <stdio.h>
#include "stack.h"

void evaluate(Stack*, int);

void binary(int);

void main()
{
    Stack S;

    init(&S);

    printf("\nProject 3: Bitwise Ops\nSingle-Digit RPN Calculator\n\n");

	int c;
	// RPN calculator loop
	while((c = getchar()) != EOF) {
		switch(c) {
			case '+':
			case '-':
			case '*':
			case '/':
			case '=':
				evaluate(&S, c);
				break;			
			case '\n':
				PrintStack(&S);
				break;
			default:
				if(c < '0' || c > '9') {
					printf("%c is invalid\n", c);
				} else {
					// Shift char to get int value
					push(&S, c-'0');
				}
		}
	}
}

/*
 * evaluate pops the last two integers off the Stack,
 * applies the operator, and pushes the result to the Stack.
 *
 * Finally, it prints the result of the following operations
 * in decimal, hex, and binary format: &, |, ^, ~, >>, <<
 */
void evaluate(Stack *S, int operator) {
	// not enough digits
	if(S->top < 2) return;

	int b = pop(S);
	int a = pop(S);

	switch(operator) {
			case '+':
				push(S, a + b);
				break;
			case '-':
				push(S, a - b);
				break;
			case '*':
				push(S, a * b);
				break;
			case '/':
				if(b == 0) {
					printf("Error: divide by zero\n");
					push(S, a);
					push(S, b);
					return;
				}
				push(S, a / b);
				break;
			case '=':
				// '=', unlike the other operators, evaluates the last two integers
				// without modifying the Stack
				push(S, a);
				push(S, b);
				break;
	}

	printf("Bitwise Ops:\n");
	printf("%d & %d = %d %#x ", a, b, a & b, a & b);
	binary(a & b);
	printf("%d | %d = %d %#x ", a, b, a | b, a | b);
	binary(a | b);
	printf("%d ^ %d = %d %#x ", a, b, a ^ b, a ^ b);
	binary(a ^ b);
	printf("~%d = %d %#x ", a, ~a, ~a);
	binary(~a);
	printf("%d >> %d = %d %#x ", a, b, a >> b, a >> b);
	binary(a >> b);
	printf("%d << %d = %d %#x ", a, b, a << b, a << b);
	binary(a << b);
}

/*
 * binary prints an integer in binary format
 */
void binary(int n) {
	int i;
	for(i = 31; i >= 0; i--) {
		printf("%d", (n >> i) & 1);
	}
	printf("\n");
}

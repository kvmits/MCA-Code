// Write a C program to convert an infix expression into a postfix expression using a stack.
// Dated 15/10/2026

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 512

int precedence(char op) {
	switch (op) {
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '^':
			return 3;
		default:
			return 0;
	}
}

int isOperator(char symbol) {
	return symbol == '+' || symbol == '-' || symbol == '*' ||
	       symbol == '/' || symbol == '^';
}

int convertToPostfix(const char *infix, char *postfix) {
	char operators[MAX_SIZE];
	int top = -1;
	int outputIndex = 0;

	for (int index = 0; infix[index] != '\0'; index++) {
		char symbol = infix[index];
		if (isspace((unsigned char)symbol)) {
			continue;
		}
		if (isalnum((unsigned char)symbol)) {
			postfix[outputIndex++] = symbol;
		} else if (symbol == '(') {
			operators[++top] = symbol;
		} else if (symbol == ')') {
			while (top >= 0 && operators[top] != '(') {
				postfix[outputIndex++] = operators[top--];
			}
			if (top < 0) {
				return 0;
			}
			top--;
		} else if (isOperator(symbol)) {
			while (top >= 0 && isOperator(operators[top]) &&
			       (precedence(operators[top]) > precedence(symbol) ||
			        (precedence(operators[top]) == precedence(symbol) && symbol != '^'))) {
				postfix[outputIndex++] = operators[top--];
			}
			operators[++top] = symbol;
		} else {
			return 0;
		}
	}

	while (top >= 0) {
		if (operators[top] == '(') {
			return 0;
		}
		postfix[outputIndex++] = operators[top--];
	}
	postfix[outputIndex] = '\0';
	return outputIndex > 0;
}

int main(void) {
	char infix[MAX_SIZE];
	char postfix[MAX_SIZE];

	printf("Enter infix expression: ");
	if (fgets(infix, sizeof(infix), stdin) == NULL) {
		return 1;
	}
	infix[strcspn(infix, "\n")] = '\0';

	if (!convertToPostfix(infix, postfix)) {
		printf("Invalid expression.\n");
		return 1;
	}
	printf("Postfix expression: %s\n", postfix);
	return 0;
}

/*Algorithm
precedence(op):
    Start
	switch op
		case '+', '-': return 1
		case '*', '/': return 2
		case '^': return 3
		default: return 0
    Stop

isOperator(symbol):
	Start
	If symbol is '+', '-', '*', '/', or '^'
		Return true
	Return false
	Stop

convertToPostfix(infix, postfix):
    Start
	Declare operators[MAX_SIZE], top = -1, outputIndex = 0
	for each symbol in infix
		If symbol is whitespace
			Continue
		If symbol is an operand
			postfix[outputIndex++] = symbol
		Else if symbol == '('
			Push symbol onto operators
		Else if symbol == ')'
			While top >= 0 and operators[top] != '('
				postfix[outputIndex++] = operators[top]
				Decrement top
			If top < 0
				Return failure
			Decrement top to discard '('
		Else if isOperator(symbol)
			While top >= 0 and operators[top] is an operator and
				  (precedence(operators[top]) > precedence(symbol) or
				  (precedence is equal and symbol != '^'))
				postfix[outputIndex++] = operators[top]
				Decrement top
			Push symbol onto operators
		Else
			Return failure
	While top >= 0
		If operators[top] == '('
			Return failure
		postfix[outputIndex++] = operators[top]
		Decrement top
	Add '\0' to postfix
	If outputIndex > 0, return success
	Return failure
    Stop

main():
    Start
	Declare infix[MAX_SIZE], postfix[MAX_SIZE]
	Display "Enter infix expression: "
    Read infix expression
	If input fails
		Return failure
	Remove newline from infix
	If convertToPostfix(infix, postfix) fails
		Display "Invalid expression."
		Return failure
	Display postfix expression
    Stop
*/

/*Output:
Enter infix expression: A+B*(C-D)
Postfix expression: ABCD-*+
*/
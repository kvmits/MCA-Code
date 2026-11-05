// Write a C program to evaluate a postfix expression using a stack.
// Assume single-digit operands and the operators +, -, *, and /.

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 512

int evaluatePostfix(const char *expression, int *result) {
	int values[MAX_SIZE];
	int top = -1;

	for (int index = 0; expression[index] != '\0'; index++) {
		char symbol = expression[index];
		if (isspace((unsigned char)symbol)) {
			continue;
		}
		if (symbol >= '0' && symbol <= '9') {
			if (top >= MAX_SIZE - 1) {
				return 0;
			}
			values[++top] = symbol - '0';
		} else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') {
			if (top < 1) {
				return 0;
			}
			int right = values[top--];
			int left = values[top--];
			if (symbol == '/' && right == 0) {
				return 0;
			}
			switch (symbol) {
				case '+':
					values[++top] = left + right;
					break;
				case '-':
					values[++top] = left - right;
					break;
				case '*':
					values[++top] = left * right;
					break;
				case '/':
					values[++top] = left / right;
					break;
			}
		} else {
			return 0;
		}
	}

	if (top != 0) {
		return 0;
	}
	*result = values[top];
	return 1;
}

int main(void) {
	char postfix[MAX_SIZE];
	int result;

	printf("Enter postfix expression: ");
	if (fgets(postfix, sizeof(postfix), stdin) == NULL) {
		return 1;
	}
	postfix[strcspn(postfix, "\n")] = '\0';

	if (!evaluatePostfix(postfix, &result)) {
		printf("Invalid postfix expression.\n");
		return 1;
	}
	printf("Result: %d\n", result);
	return 0;
}

/*Algorithm
evaluatePostfix(expression, result):
    Start
    Declare values[MAX_SIZE], top = -1
    For each symbol in expression
        If symbol is whitespace
            Continue
        If symbol is a digit
            If stack is full
                Return failure
            Convert symbol to integer value
            Push value onto stack
        Else if symbol is an operator
            If top < 1
                Return failure
            right = values[top]
            Decrement top
            left = values[top]
            Decrement top
            If symbol == '/' and right == 0
                Return failure
            switch symbol
                case '+':
                    Push left + right
                case '-':
                    Push left - right
                case '*':
                    Push left * right
                case '/':
                    Push left / right using integer division
        Else
            Return failure
    If top != 0, return failure
    result = values[top]
    Return success
    Stop

main():
    Start
    Declare postfix[MAX_SIZE], result
    Display "Enter postfix expression: "
    Read postfix expression
    If input fails
        Return failure
    Remove newline from postfix expression
    If evaluatePostfix(postfix, result) fails
        Display "Invalid postfix expression."
        Return failure
    Display result
    Stop
*/

/*Output:
Enter postfix expression: 23*54*+9-
Result: 17
*/

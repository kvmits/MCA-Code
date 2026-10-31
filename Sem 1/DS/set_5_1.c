//Program to impelement stack operations using array
#include <stdio.h>

int main() {
    int stack[5], top = -1, ch, val;
    do {
        printf("\nMenu: 1. Push 2. Pop 3. Display 4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                if (top == 5 - 1) {
                    printf("Stack Overflow %d\n", val);
                } else {
                    printf("Enter value to push: ");
                    scanf("%d", &val);
                    stack[++top] = val;
                    printf("%d pushed to stack.\n", val);
                }
                break;
            case 2:
                if (top == -1) {
                    printf("Empty stack.\n");
                } else {
                    val = stack[top--];
                    printf("%d popped from stack.\n", val);
                }
                break;
            case 3:
                if (top == -1) {
                    printf("Stack is empty.\n");
                } else {
                    printf("Stack elements:\n");
                    for (int i = top; i >= 0; i--) {
                        printf("%d\n", stack[i]);
                    }
                }
                break;
            case 4:
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (ch != 4);
    return 0;
}

/*Algorithm
main():
    Start
    Declare stack[5], top = -1, ch, val
    do
        Display Menu
        Read ch
        switch ch
            case 1:
                if top == 4
                    Display "Stack Overflow"
                else
                    Read val
                    stack[++top] = val
                    Display value pushed
            case 2:
                if top == -1
                    Display "Empty stack"
                else
                    value = stack[top--]
                    Display value popped
            case 3:
                if top == -1
                    Display "Stack is empty"
                else
                    Display stack elements from top to bottom
            case 4:
                break
            default:
                Display "Invalid choice"
    while ch != 4
    Stop
*/
/*Output:
Menu: 1. Push 2. Pop 3. Display 4. Exit
Enter your choice: 1
Enter value to push: 10
10 pushed to stack.
Menu: 1. Push 2. Pop 3. Display 4. Exit
Enter your choice: 1
Enter value to push: 20
20 pushed to stack.
Menu: 1. Push 2. Pop 3. Display 4. Exit
Enter your choice: 3
Stack elements:
20
10
Menu: 1. Push 2. Pop 3. Display 4. Exit
Enter your choice: 2
20 popped from stack.
Menu: 1. Push 2. Pop 3. Display 4. Exit
Enter your choice: 3
Stack elements:
10
Menu: 1. Push 2. Pop 3. Display 4. Exit
Enter your choice: 4
*/
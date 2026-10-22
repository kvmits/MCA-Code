//To implement a menu driven program to perform following stack operations using linked list
// i. push
// ii. pop
// iii. Traversal

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

int push(struct node **top, int val)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (!new_node)
    {
        printf("Memory allocation failed!\n");
        return -1;
    }
    new_node->data = val;
    new_node->next = *top;
    *top = new_node;
    printf("%d pushed to stack\n", val);
    return 0;
}

int pop(struct node **top)
{
    if (*top == NULL)
    {
        printf("Stack underflow! Cannot pop from an empty stack.\n");
        return -1;
    }
    struct node *temp = *top;
    int popped_value = temp->data;
    *top = (*top)->next;
    free(temp);
    printf("%d popped from stack\n", popped_value);
    return popped_value;
}

int traversal(struct node *top)
{
    if (top == NULL)
    {
        printf("Stack is empty!\n");
        return -1;
    }
    printf("Stack elements: ");
    struct node *current = top;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    return 0;
}


int main()
{
    struct node *top = NULL;
    int ch, val;

    while (1)
    {
        printf("\nStack Operations:\n1. Push\n2. Pop\n3. Traversal\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &val);
                push(&top, val);
                break;
            case 2:
                pop(&top);
                break;
            case 3:
                traversal(top);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;  
}

/*Algorithm
push(top, val):
    Start
    Allocate memory for new_node
    If new_node == NULL
        Display "Memory allocation failed"
        Return
    new_node->data = val
    new_node->next = *top
    *top = new_node
    Display "value pushed to stack"
    Stop

pop(top):
    Start
    If *top == NULL
        Display "Stack underflow"
        Return
    temp = *top
    *top = (*top)->next
    Free temp
    Display "value popped from stack"
    Stop

traversal(top):
    Start
    If top == NULL
        Display "Stack is empty"
        Return
    current = top
    While current != NULL
        Display current->data
        current = current->next
    Stop

main():
    Start
    Set top = NULL
    While true
        Display menu
        Read ch
        If ch == 1
            Read val
            Call push(&top, val)
        Else if ch == 2
            Call pop(&top)
        Else if ch == 3
            Call traversal(top)
        Else if ch == 4
            Exit
        Else
            Display "Invalid choice"
    Stop
*/

/*Output:
Stack Operations:
1. Push
2. Pop
3. Traversal
4. Exit
Enter your choice: 1
Enter value to push: 10
10 pushed to stack

Enter your choice: 1
Enter value to push: 20
20 pushed to stack

Enter your choice: 3
Stack elements: 20 10

Enter your choice: 2
20 popped from stack

Enter your choice: 3
Stack elements: 10

Enter your choice: 4
*/
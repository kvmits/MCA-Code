//To implement a menu driven program to perform following queue operations using linked list
//1. enqueue
//2. dequeue
// 3. Traversal

#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
};

int enqueue(struct node **front, struct node **rear, int val)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (!new_node)
    {
        printf("Memory allocation failed!\n");
        return -1;
    }
    new_node->data = val;
    new_node->next = NULL;

    if (*rear == NULL)
    {
        *front = *rear = new_node;
    }
    else
    {
        (*rear)->next = new_node;
        *rear = new_node;
    }
    printf("%d enqueued to queue\n", val);
    return 0;
}

int dequeue(struct node **front, struct node **rear)
{
    if (*front == NULL)
    {
        printf("Queue underflow! Cannot dequeue from an empty queue.\n");
        return -1;
    }
    struct node *temp = *front;
    int dequeued_value = temp->data;
    *front = (*front)->next;

    if (*front == NULL)
    {
        *rear = NULL;
    }

    free(temp);
    printf("%d dequeued from queue\n", dequeued_value);
    return dequeued_value;
}

int traversal(struct node *front)
{
    if (front == NULL)
    {
        printf("Queue is empty!\n");
        return -1;
    }
    printf("Queue elements: ");
    struct node *current = front;
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
    struct node *front = NULL;
    struct node *rear = NULL;
    int ch, val;

    while (1) 
    {
        printf("\nQueue Operations: 1. Enqueue  2. Dequeue  3. Traversal  4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter value to enqueue: ");
            scanf("%d", &val);
            enqueue(&front, &rear, val);
            break;
        case 2:
            dequeue(&front, &rear);
            break;
        case 3:
            traversal(front);
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

}

/*Algorithm
enqueue(front, rear, val):
    Start
    Allocate memory for new_node
    If new_node == NULL
        Display "Memory allocation failed"
        Return
    new_node->data = val
    new_node->next = NULL
    If *rear == NULL
        *front = *rear = new_node
    Else
        (*rear)->next = new_node
        *rear = new_node
    Display "value enqueued to queue"
    Stop

dequeue(front, rear):
    Start
    If *front == NULL
        Display "Queue underflow"
        Return
    temp = *front
    *front = (*front)->next
    If *front == NULL
        *rear = NULL
    Free temp
    Display "value dequeued from queue"
    Stop

traversal(front):
    Start
    If front == NULL
        Display "Queue is empty"
        Return
    current = front
    While current != NULL
        Display current->data
        current = current->next
    Stop

main():
    Start
    Set front = NULL and rear = NULL
    While true
        Display menu
        Read ch
        If ch == 1
            Read val
            Call enqueue(&front, &rear, val)
        Else if ch == 2
            Call dequeue(&front, &rear)
        Else if ch == 3
            Call traversal(front)
        Else if ch == 4
            Exit
        Else
            Display "Invalid choice"
    Stop
*/

/*Output:
Queue Operations: 1. Enqueue  2. Dequeue  3. Traversal  4. Exit
Enter your choice: 1
Enter value to enqueue: 10
10 enqueued to queue

Enter your choice: 1
Enter value to enqueue: 20
20 enqueued to queue

Enter your choice: 3
Queue elements: 10 20

Enter your choice: 2
10 dequeued from queue

Enter your choice: 3
Queue elements: 20

Enter your choice: 4
*/

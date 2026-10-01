//Program to implement queue operations using arrays 

#include <stdio.h>

int main() {
    int queue[5], front = -1, rear = -1, ch, val;
    do {
        printf("\nMenu: 1. Enqueue 2. Dequeue 3. Display 4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                if (rear == 5 - 1) {
                    printf("Queue Overflow %d\n", val);
                } else {
                    printf("Enter value to enqueue: ");
                    scanf("%d", &val);
                    if (front == -1) front = 0;
                    queue[++rear] = val;
                    printf("%d enqueued to queue.\n", val);
                }
                break;
            case 2:
                if (front == -1 || front > rear) {
                    printf("Queue Underflow.\n");
                } else {
                    val = queue[front++];
                    printf("%d dequeued from queue.\n", val);
                }
                break;
            case 3:
                if (front == -1 || front > rear) {
                    printf("Queue is empty.\n");
                } else {
                    printf("Queue elements:\n");
                    for (int i = front; i <= rear; i++) {
                        printf("%d\n", queue[i]);
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
    Declare queue[5], front = -1, rear = -1, ch, val
    do
        Display Menu
        Read ch
        switch ch
            case 1:
                if rear == 4
                    Display "Queue Overflow"
                else
                    Read val
                    if front == -1 then front = 0
                    queue[++rear] = val
                    Display value enqueued
            case 2:
                if front == -1 or front > rear
                    Display "Queue Underflow"
                else
                    value = queue[front++]
                    Display value dequeued
            case 3:
                if front == -1 or front > rear
                    Display "Queue is empty"
                else
                    Display queue elements from front to rear
            case 4:
                break
            default:
                Display "Invalid choice"
    while ch != 4
    Stop
*/
/*Output:
Menu: 1. Enqueue 2. Dequeue 3. Display 4. Exit
Enter your choice: 1
Enter value to enqueue: 10
10 enqueued to queue.
Menu: 1. Enqueue 2. Dequeue 3. Display 4. Exit
Enter your choice: 1
Enter value to enqueue: 20
20 enqueued to queue.
Menu: 1. Enqueue 2. Dequeue 3. Display 4. Exit
Enter your choice: 3
Queue elements:
10
20
Menu: 1. Enqueue 2. Dequeue 3. Display 4. Exit
Enter your choice: 2
10 dequeued from queue.
Menu: 1. Enqueue 2. Dequeue 3. Display 4. Exit
Enter your choice: 4
*/
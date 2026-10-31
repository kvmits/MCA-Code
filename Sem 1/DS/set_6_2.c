//Program to implement circular queue using array. 

#include <stdio.h>

int main() {
    int queue[5], front = -1, rear = -1, ch, val;
    do {
        printf("\nMenu: 1. Enqueue 2. Dequeue 3. Display 4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                if ((rear + 1) % 5 == front) {
                    printf("Circular Queue Overflow %d\n", val);
                } else {
                    printf("Enter value to enqueue: ");
                    scanf("%d", &val);
                    if (front == -1) front = 0;
                    rear = (rear + 1) % 5;
                    queue[rear] = val;
                    printf("%d enqueued to circular queue.\n", val);
                }
                break;
            case 2:
                if (front == -1) {
                    printf("Circular Queue Underflow.\n");
                } else {
                    val = queue[front];
                    if (front == rear) {
                        front = rear = -1;
                    } else {
                        front = (front + 1) % 5;
                    }
                    printf("%d dequeued from circular queue.\n", val);
                }
                break;
            case 3:
                if (front == -1) {
                    printf("Circular Queue is empty.\n");
                } else {
                    printf("Circular Queue elements:\n");
                    int i = front;
                    while (1) {
                        printf("%d\n", queue[i]);
                        if (i == rear) break;
                        i = (i + 1) % 5;
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
                if (rear + 1) % 5 == front
                    Display "Circular Queue Overflow"
                else
                    Read val
                    if front == -1 then front = 0
                    rear = (rear + 1) % 5
                    queue[rear] = val
                    Display value enqueued
            case 2:
                if front == -1
                    Display "Circular Queue Underflow"
                else
                    val = queue[front]
                    if front == rear then front = rear = -1
                    else front = (front + 1) % 5
                    Display value dequeued
            case 3:
                if front == -1
                    Display "Circular Queue is empty"
                else
                    i = front
                    while true
                        Display queue[i]
                        if i == rear then break
                        i = (i + 1) % 5
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
10 enqueued to circular queue.

Menu: 1. Enqueue 2. Dequeue 3. Display 4. Exit
Enter your choice: 1
Enter value to enqueue: 20
20 enqueued to circular queue.

Menu: 1. Enqueue 2. Dequeue 3. Display 4. Exit
Enter your choice: 3
Circular Queue elements:
10
20

Menu: 1. Enqueue 2. Dequeue 3. Display 4. Exit
Enter your choice: 2
10 dequeued from circular queue.

Menu: 1. Enqueue 2. Dequeue 3. Display 4. Exit
Enter your choice: 3
Circular Queue elements:
20

Menu: 1. Enqueue 2. Dequeue 3. Display 4. Exit
Enter your choice: 4
*/
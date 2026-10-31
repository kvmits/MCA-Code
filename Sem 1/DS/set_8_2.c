 /* To implement the following operations on a singly linked list
   i. Creation,
  ii. Deletion from beginning
 iii. Deletion from the end
  iv. Deletion from particular location
   v. Traversal.
*/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *createNode(int value) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void createList(struct node **head) {
    int nodeCount, value, i;
    struct node *newNode, *tail = NULL;

    printf("How many nodes you want to enter? ");
    scanf("%d", &nodeCount);

    *head = NULL;
    for (i = 0; i < nodeCount; i++) {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &value);

        newNode = createNode(value);
        if (*head == NULL) {
            *head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    printf("Linked list created successfully.\n");
}

void deleteFromBeginning(struct node **head) {
    if (*head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    struct node *temp = *head;
    *head = (*head)->next;
    free(temp);
    printf("Deleted node from beginning.\n");
}

void deleteFromEnd(struct node **head) {
    if (*head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        printf("Deleted the only node.\n");
        return;
    }

    struct node *temp = *head;
    struct node *prev = NULL;

    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = NULL;
    free(temp);
    printf("Deleted node from end.\n");
}

void deleteFromPosition(struct node **head, int position) {
    if (*head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    struct node *temp = *head;
    struct node *prev = NULL;
    int currentPos = 1;

    while (temp != NULL && currentPos < position) {
        prev = temp;
        temp = temp->next;
        currentPos++;
    }

    if (temp == NULL) {
        printf("Position not found.\n");
        return;
    }

    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Deleted node at position %d.\n", position);
}

void traverse(struct node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Linked list: ");
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void displayMenu() {
    printf("\nSingly Linked List Operations\n");
    printf("1. Create linked list\n");
    printf("2. Delete from beginning\n");
    printf("3. Delete from end\n");
    printf("4. Delete from a particular position\n");
    printf("5. Traverse\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct node *head = NULL;
    int choice, position;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createList(&head);
                break;

            case 2:
                deleteFromBeginning(&head);
                break;

            case 3:
                deleteFromEnd(&head);
                break;

            case 4:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deleteFromPosition(&head, position);
                break;

            case 5:
                traverse(head);
                break;

            case 6:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

/*Algorithm
createList(head):
    Start
    Declare variables n, i, value, newNode, temp
    Read n
    *head = NULL
    for i = 0; i < n; i++
        Read value
        newNode = createNode(value)
        If *head == NULL
            *head = newNode
        Else
            temp = *head
            while temp->next != NULL
                temp = temp->next
            temp->next = newNode
    display "List created successfully."
    Stop

insertAtEnd(head, value):
    Start
    newNode = createNode(value)
    If *head == NULL
        *head = newNode
        return
    temp = *head
    while temp->next != NULL
        temp = temp->next
    temp->next = newNode
    Stop

insertAtFront(head, value):
    Start
    newNode = createNode(value)
    newNode->next = *head
    *head = newNode
    display "Inserted value at the front."
    Stop

insertAfterNode(head, key, value):
    Start
    temp = head
    while temp != NULL and temp->data != key
        temp = temp->next
    If temp == NULL
        display "Node with key not found."
        return
    newNode = createNode(value)
    newNode->next = temp->next
    temp->next = newNode
    display "Inserted value after key."
    Stop

insertAtEnd(head, value):
    Start
    newNode = createNode(value)
    If *head == NULL
        *head = newNode
        return
    temp = *head
    while temp->next != NULL
        temp = temp->next
    temp->next = newNode
    Stop

searchNode(head, key):
    Start
    temp = head
    position = 1
    while temp != NULL
        If temp->data == key
            display "Element found at position."
            return 1
        temp = temp->next
        position++
    display "Element not found."
    return 0

traverseList(head):
    Start
    temp = head
    If temp == NULL
        display "List is empty."
    else
        display "Linked List: "
        while temp != NULL
            display temp->data
            temp = temp->next
    Stop

main():
    Start
    print (Menu)
    switch (choice)
        case 1: read n and values
            createList(&head); break;
        case 2: read value
            insertAtFront(&head, value); break;
        case 3: read key and value
            insertAfterNode(head, key, value); break;
        case 4: read value
            insertAtEnd(&head, value); break;
        case 5: read key
            searchNode(head, key); break;
        case 6: traverseList(head); break;
        case 7: Exit;
        default: print(Invalid);
    }

*/

/*Output:
Singly Linked List Operations
1. Create linked list
2. Delete from beginning
3. Delete from end
4. Delete from a particular position
5. Traverse
6. Exit
Enter your choice: 1
How many nodes you want to enter? 5
Enter value for node 1: 1
Enter value for node 2: 2
Enter value for node 3: 3
Enter value for node 4: 4
Enter value for node 5: 5
Linked list created successfully.

Singly Linked List Operations
1. Create linked list
2. Delete from beginning
3. Delete from end
4. Delete from a particular position
5. Traverse
6. Exit
Enter your choice: 2
Deleted node from beginning.

Singly Linked List Operations
1. Create linked list
2. Delete from beginning
3. Delete from end
4. Delete from a particular position
5. Traverse
6. Exit
Enter your choice: 3
Deleted node from end.

Singly Linked List Operations
1. Create linked list
2. Delete from beginning
3. Delete from end
4. Delete from a particular position
5. Traverse
6. Exit
Enter your choice: 4
Enter position to delete: 2
Deleted node at position 2.

Singly Linked List Operations
1. Create linked list
2. Delete from beginning
3. Delete from end
4. Delete from a particular position
5. Traverse
6. Exit
Enter your choice: 5
Linked list: 2 -> 4 -> NULL

Singly Linked List Operations
1. Create linked list
2. Delete from beginning
3. Delete from end
4. Delete from a particular position
5. Traverse
6. Exit
Enter your choice: 6
Exiting program.
*/
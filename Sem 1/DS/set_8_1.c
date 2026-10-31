// To implement the following operations on a singly linked list
// i. Creation,
// ii. Insert a new node at front
// iii. Insert an element after a particular node
// iv. Insert a new node at end
// v. Searching
// vi. Traversal.

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void createList(struct Node** head) {
    int n, i, value;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    *head = NULL;

    for (i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &value);

        struct Node* newNode = createNode(value);
        if (*head == NULL) {
            *head = newNode;
        } else {
            struct Node* temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    printf("List created successfully.\n");
}

void insertAtFront(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
    printf("Inserted %d at the front.\n", data);
}

void insertAfterNode(struct Node* head, int key, int data) {
    struct Node* temp = head;

    while (temp != NULL && temp->data != key) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Node with key %d not found.\n", key);
        return;
    }

    struct Node* newNode = createNode(data);
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Inserted %d after %d.\n", data, key);
}

void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        printf("Inserted %d at the end.\n", data);
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    printf("Inserted %d at the end.\n", data);
}

int searchNode(struct Node* head, int key) {
    int position = 1;
    struct Node* temp = head;

    while (temp != NULL) {
        if (temp->data == key) {
            printf("Element %d found at position %d.\n", key, position);
            return 1;
        }
        temp = temp->next;
        position++;
    }

    printf("Element %d not found.\n", key);
    return 0;
}

void traverseList(struct Node* head) {
    struct Node* temp = head;

    if (temp == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    int choice, data, key;
    struct Node* head = NULL;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create List\n");
        printf("2. Insert at Front\n");
        printf("3. Insert After a Node\n");
        printf("4. Insert at End\n");
        printf("5. Search\n");
        printf("6. Traverse\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createList(&head);
                break;
            case 2:
                printf("Enter data to insert at front: ");
                scanf("%d", &data);
                insertAtFront(&head, data);
                break;
            case 3:
                printf("Enter the node value after which to insert: ");
                scanf("%d", &key);
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertAfterNode(head, key, data);
                break;
            case 4:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;
            case 5:
                printf("Enter element to search: ");
                scanf("%d", &key);
                searchNode(head, key);
                break;
            case 6:
                traverseList(head);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

/*Algorithm

createList():
Start
for i < n {
    printf("Enter data for node %d: ", i + 1);
    scanf("%d", &value);
    struct Node* newNode = createNode(value);
    if (*head == NULL)
        *head = newNode;
    else { 
        struct Node* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}
Stop

insertAtFront():
    Start
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
    Stop

insertAfterNode():
    Start
    struct Node* temp = head;
    struct Node* newNode = createNode(data);
    while (temp != NULL && temp->data != key) {
        temp = temp->next;
    }
    if (temp == NULL) {
       print(Not Found)
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    Stop

insertAtEnd():
    Start
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    Stop

searchNode():
    Start
    struct Node* temp = head;
    int position = 1;
    while (temp != NULL) {
        if (temp->data == key) {
            printf("Element %d found at position %d.\n", key, position);
            return 1;
        }
        temp = temp->next;
        position++;
    }
    print(Not Found)
    return 0;
    Stop

traverseList():
    Start
    struct Node* temp = head;
    if (temp == NULL) {
        print(Empty)
        return;
    }
    print(Linked List: )
    while (temp != NULL) {
        print(%d -> , temp->data);
        temp = temp->next;
    }
    print(NULL\n);
    Stop

int main():
    Start
    while (1) {
        print(Menu)
        read choice
        switch (choice) {
            case 1: createList(&head); break;
            case 2: read data 
                insertAtFront(&head, data); break;
            case 3: read key and data
                insertAfterNode(head, key, data); break;
            case 4: read data
                insertAtEnd(&head, data); break;
            case 5: read key
                searchNode(head, key); break;
            case 6: traverseList(head); break;
            case 7: exit(0);
            default: print(Invalid);
    }
    Stop


*/
/* Output:

Menu:
1. Create List
2. Insert at Front
3. Insert After a Node
4. Insert at End
5. Search
6. Traverse
7. Exit
Enter your choice: 1
Enter number of nodes: 3
Enter data for node 1: 1
Enter data for node 2: 2
Enter data for node 3: 3
List created successfully.

Menu:
1. Create List
2. Insert at Front
3. Insert After a Node
4. Insert at End
5. Search
6. Traverse
7. Exit
Enter your choice: 6
Linked List: 1 -> 2 -> 3 -> NULL

Menu:
1. Create List
2. Insert at Front
3. Insert After a Node
4. Insert at End
5. Search
6. Traverse
7. Exit
Enter your choice: 2
Enter data to insert at front: 10
Inserted 10 at the front.

Menu:
1. Create List
2. Insert at Front
3. Insert After a Node
4. Insert at End
5. Search
6. Traverse
7. Exit
Enter your choice: 3
Enter the node value after which to insert: 2
Enter data to insert: 4
Inserted 4 after 2.

Menu:
1. Create List
2. Insert at Front
3. Insert After a Node
4. Insert at End
5. Search
6. Traverse
7. Exit
Enter your choice: 4
Enter data to insert at end: 100
Inserted 100 at the end.

Menu:
1. Create List
2. Insert at Front
3. Insert After a Node
4. Insert at End
5. Search
6. Traverse
7. Exit
Enter your choice: 5
Enter element to search: 1
Element 1 found at position 2.

Menu:
1. Create List
2. Insert at Front
3. Insert After a Node
4. Insert at End
5. Search
6. Traverse
7. Exit
Enter your choice: 6
Linked List: 10 -> 1 -> 2 -> 4 -> 3 -> 100 -> NULL

Menu:
1. Create List
2. Insert at Front
3. Insert After a Node
4. Insert at End
5. Search
6. Traverse
7. Exit
Enter your choice: 7

*/
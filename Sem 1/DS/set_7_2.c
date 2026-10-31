// Write a C program to create a singly linked list containing 5 nodes. Read an integer value for each node, link the nodes dynamically, and display all the elements of the linked list.

#include <stdio.h>
#include <stdlib.h>

int main() {
    struct Node {
        int data;
        struct Node* next;
    };
    struct Node* head = NULL;
    struct Node* temp = NULL;
    struct Node* newNode = NULL;
    for (int i = 0; i < 5; i++) {
        newNode = (struct Node*)malloc(sizeof(struct Node));
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &newNode->data);
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            temp = head;
        } else {
            temp->next = newNode;
            temp = temp->next;
        }
    }
    printf("Elements in the linked list:\n");
    temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
    temp = head;
    while (temp != NULL) {
        struct Node* nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    return 0;
}

/*Algorithm
main():
    Start
    Define Struct Node with data and next pointer
    (head, temp, newNode) = NULL
    for i = 0 to 4
        Allocate memory for newNode
        Read newNode->data
        Set newNode->next to NULL
        if (head == NULL)
            head = newNode;
            temp = head;
        else
            temp->next = newNode;
            temp = temp->next;
    Print "Elements in the linked list:"
    temp = head
    while temp != NULL
        Print temp->data   
        temp = temp->next
    temp = head
    while temp != NULL
        nextNode = temp->next;
        Free temp
        temp = nextNode
    Stop
*/
/*Output:
Enter value for node 1: 10
Enter value for node 2: 20
Enter value for node 3: 30
Enter value for node 4: 40
Enter value for node 5: 50
Elements in the linked list:
10 -> 20 -> 30 -> 40 -> 50 -> NULL
*/
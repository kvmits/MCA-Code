//To implement the following operations on a Doubly linked list.
//i. Creation
//ii. Insert a node at first position
//iii. Insert a node at last
//iv. Delete a node from the first position
//v. Delete a node from last
// vi. Traversal

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

int create(struct node **head, int val)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (!new_node)
    {
        printf("Memory allocation failed!\n");
        return -1;
    }
    new_node->data = val;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        struct node *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
    }
    printf("%d added to the list\n", val);
    return 0;
}

int insert_first(struct node **head, int val)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (!new_node)
    {
        printf("Memory allocation failed!\n");
        return -1;
    }
    new_node->data = val;
    new_node->next = *head;
    new_node->prev = NULL;

    if (*head != NULL)
    {
        (*head)->prev = new_node;
    }
    *head = new_node;
    printf("%d inserted at the first position\n", val);
    return 0;
}

int insert_last(struct node **head, int val)
{
    return create(head, val);
}

int delete_first(struct node **head)
{
    if (*head == NULL)
    {
        printf("List is empty! Cannot delete from the first position.\n");
        return -1;
    }
    struct node *temp = *head;
    int deleted_value = temp->data;
    *head = (*head)->next;

    if (*head != NULL)
    {
        (*head)->prev = NULL;
    }

    free(temp);
    printf("%d deleted from the first position\n", deleted_value);
    return deleted_value;
}

int delete_last(struct node **head)
{
    if (*head == NULL)
    {
        printf("List is empty! Cannot delete from the last position.\n");
        return -1;
    }
    struct node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    int deleted_value = temp->data;

    if (temp->prev != NULL)
    {
        temp->prev->next = NULL;
    }
    else
    {
        *head = NULL; // List becomes empty
    }

    free(temp);
    printf("%d deleted from the last position\n", deleted_value);
    return deleted_value;
}

int traversal(struct node *head)
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return -1;
    }
    printf("List elements: ");
    struct node *current = head;
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
    struct node *head = NULL;
    int ch, val;
    while (1)
    {
        printf("\n1. Create | 2. Insert at First | 3. Insert at Last | 4. Delete from First | 5. Delete from Last | 6. Traversal | 7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("Enter value to create: ");
            scanf("%d", &val);
            create(&head, val);
            break;
        case 2:
            printf("Enter value to insert at first position: ");
            scanf("%d", &val);
            insert_first(&head, val);
            break;
        case 3:
            printf("Enter value to insert at last position: ");
            scanf("%d", &val);
            insert_last(&head, val);
            break;
        case 4:
            delete_first(&head);
            break;
        case 5:
            delete_last(&head);
            break;
        case 6:
            traversal(head);
            break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

}

/*Algorithm
create(head, val):
    Start
    Allocate memory for new_node
    If new_node == NULL
        Display "Memory allocation failed"
        Return
    Set data, next, and prev of new_node
    If *head == NULL
        *head = new_node
    Else
        temp = *head
        While temp->next != NULL
            temp = temp->next
        temp->next = new_node
        new_node->prev = temp
    Display "value added to the list"
    Stop

insert_first(head, val):
    Start
    Allocate memory for new_node
    Set new_node->data = val
    Set new_node->next = *head and new_node->prev = NULL
    If *head != NULL
        (*head)->prev = new_node
    *head = new_node
    Display "value inserted at the first position"
    Stop

insert_last(head, val):
    Start
    Call create(head, val)
    Stop

delete_first(head):
    Start
    If *head == NULL
        Display "List is empty"
        Return
    temp = *head
    *head = (*head)->next
    If *head != NULL
        (*head)->prev = NULL
    Free temp
    Display "value deleted from the first position"
    Stop

delete_last(head):
    Start
    If *head == NULL
        Display "List is empty"
        Return
    temp = *head
    While temp->next != NULL
        temp = temp->next
    If temp->prev != NULL
        temp->prev->next = NULL
    Else
        *head = NULL
    Free temp
    Display "value deleted from the last position"
    Stop

traversal(head):
    Start
    If head == NULL
        Display "List is empty"
        Return
    current = head
    While current != NULL
        Display current->data
        current = current->next
    Stop

main():
    Start
    Set head = NULL
    While true
        Display menu
        Read ch
        If ch == 1
            Read val
            Call create(&head, val)
        Else if ch == 2
            Read val
            Call insert_first(&head, val)
        Else if ch == 3
            Read val
            Call insert_last(&head, val)
        Else if ch == 4
            Call delete_first(&head)
        Else if ch == 5
            Call delete_last(&head)
        Else if ch == 6
            Call traversal(head)
        Else if ch == 7
            Exit
        Else
            Display "Invalid choice"
    Stop
*/

/*Output:
1. Create | 2. Insert at First | 3. Insert at Last | 4. Delete from First | 5. Delete from Last | 6. Traversal | 7. Exit
Enter your choice: 1
Enter value to create: 10
10 added to the list

Enter your choice: 3
Enter value to insert at last position: 20
20 added to the list

Enter your choice: 2
Enter value to insert at first position: 5
5 inserted at the first position

Enter your choice: 6
List elements: 5 10 20

Enter your choice: 4
5 deleted from the first position

Enter your choice: 5
20 deleted from the last position

Enter your choice: 6
List elements: 10

Enter your choice: 7
*/
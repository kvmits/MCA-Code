//To implement the following operations on a Doubly linked list.
//i. Creation
//ii. Count the number of nodes
//iii. Searching
// iv. Traversal


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

int search(struct node *head, int val)
{
    struct node *current = head;
    while (current != NULL)
    {
        if (current->data == val)
        {
            printf("%d found in the list\n", val);
            return 1;
        }
        current = current->next;
    }
    printf("%d not found in the list\n", val);
    return 0;
}

int count_nodes(struct node *head)
{
    int count = 0;
    struct node *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
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
        printf("\n1. Create\n2. Count Nodes\n3. Search\n4. Traversal\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter value to add: ");
            scanf("%d", &val);
            create(&head, val);
            break;
        case 2:
            printf("Number of nodes: %d\n", count_nodes(head));
            break;
        case 3:
            printf("Enter value to search: ");
            scanf("%d", &val);
            search(head, val);
            break;
        case 4:
            traversal(head);
            break;
        case 5:
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

count_nodes(head):
    Start
    count = 0
    current = head
    While current != NULL
        count++
        current = current->next
    Return count
    Stop

search(head, val):
    Start
    current = head
    While current != NULL
        If current->data == val
            Display "value found in the list"
            Return
        current = current->next
    Display "value not found in the list"
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
            Display count_nodes(head)
        Else if ch == 3
            Read val
            Call search(head, val)
        Else if ch == 4
            Call traversal(head)
        Else if ch == 5
            Exit
        Else
            Display "Invalid choice"
    Stop
*/

/*Output:
1. Create
2. Count Nodes
3. Search
4. Traversal
5. Exit
Enter your choice: 1
Enter value to add: 10
10 added to the list

Enter your choice: 1
Enter value to add: 20
20 added to the list

Enter your choice: 2
Number of nodes: 2

Enter your choice: 3
Enter value to search: 20
20 found in the list

Enter your choice: 4
List elements: 10 20

Enter your choice: 5
*/

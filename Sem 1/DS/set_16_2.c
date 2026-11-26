// Set 16.2 - Basic operations on a Fibonacci Min-Heap.

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000
#define MAX_DEGREE 64

struct node {
    int key;
    int degree;
    int mark;
    struct node *parent;
    struct node *child;
    struct node *left;
    struct node *right;
};

typedef struct node Node;

Node *minimum = NULL;
int node_count = 0;

Node *create_node(int key)
{
    Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->key = key;
    new_node->degree = 0;
    new_node->mark = 0;
    new_node->parent = NULL;
    new_node->child = NULL;
    new_node->left = new_node;
    new_node->right = new_node;
    return new_node;
}

void add_to_list(Node **head, Node *item)
{
    if (*head == NULL) {
        *head = item;
        item->left = item;
        item->right = item;
        return;
    }
    Node *tail = (*head)->left;
    item->left = tail;
    item->right = *head;
    tail->right = item;
    (*head)->left = item;
}

void remove_from_list(Node *item)
{
    item->left->right = item->right;
    item->right->left = item->left;
    item->left = item;
    item->right = item;
}

void insert_root(Node *item)
{
    item->parent = NULL;
    item->mark = 0;
    add_to_list(&minimum, item);
    if (minimum == NULL || item->key < minimum->key) {
        minimum = item;
    }
}

void insert_key(int key)
{
    Node *new_node = create_node(key);
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    insert_root(new_node);
    node_count++;
    printf("%d inserted.\n", key);
}

void link_child(Node *child, Node *parent)
{
    child->parent = parent;
    child->mark = 0;
    add_to_list(&parent->child, child);
    parent->degree++;
}

void consolidate(void)
{
    Node *roots[MAX_NODES];
    Node *degree_table[MAX_DEGREE] = {NULL};
    int root_count = 0;

    if (minimum == NULL) {
        return;
    }
    Node *current = minimum;
    do {
        roots[root_count++] = current;
        current = current->right;
    } while (current != minimum && root_count < MAX_NODES);

    minimum = NULL;
    for (int index = 0; index < root_count; index++) {
        Node *tree = roots[index];
        tree->left = tree;
        tree->right = tree;
        int degree = tree->degree;
        while (degree_table[degree] != NULL) {
            Node *other = degree_table[degree];
            if (other->key < tree->key) {
                Node *temporary = tree;
                tree = other;
                other = temporary;
            }
            degree_table[degree] = NULL;
            link_child(other, tree);
            degree++;
        }
        degree_table[degree] = tree;
    }
    for (int degree = 0; degree < MAX_DEGREE; degree++) {
        if (degree_table[degree] != NULL) {
            insert_root(degree_table[degree]);
        }
    }
}

int extract_minimum(int *minimum_key)
{
    Node *removed = minimum;
    if (removed == NULL) {
        return 0;
    }
    *minimum_key = removed->key;

    while (removed->child != NULL) {
        Node *child = removed->child;
        if (child->right == child) {
            removed->child = NULL;
        } else {
            removed->child = child->right;
        }
        remove_from_list(child);
        removed->degree--;
        insert_root(child);
    }

    if (removed->right == removed) {
        minimum = NULL;
    } else {
        Node *next = removed->right;
        remove_from_list(removed);
        minimum = next;
    }
    free(removed);
    node_count--;
    consolidate();
    return 1;
}

void display_list(const Node *start, int depth)
{
    if (start == NULL) {
        return;
    }
    const Node *current = start;
    do {
        for (int index = 0; index < depth; index++) {
            printf("  ");
        }
        printf("%d\n", current->key);
        display_list(current->child, depth + 1);
        current = current->right;
    } while (current != start);
}

void free_list(Node *start)
{
    if (start == NULL) {
        return;
    }
    Node *current = start;
    do {
        Node *next = current->right;
        free_list(current->child);
        free(current);
        current = next;
    } while (current != start);
}

int main(void)
{
    int choice, key;
    while (1) {
        printf("\n1. Insert\n2. Find minimum\n3. Extract minimum\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            break;
        }
        switch (choice) {
            case 1:
                if (node_count == MAX_NODES) {
                    printf("Heap capacity reached.\n");
                    break;
                }
                printf("Enter value: ");
                if (scanf("%d", &key) != 1) {
                    free_list(minimum);
                    return 1;
                }
                insert_key(key);
                break;
            case 2:
                if (minimum == NULL) {
                    printf("Heap is empty.\n");
                } else {
                    printf("Minimum value: %d\n", minimum->key);
                }
                break;
            case 3:
                if (extract_minimum(&key)) {
                    printf("Extracted minimum: %d\n", key);
                } else {
                    printf("Heap is empty.\n");
                }
                break;
            case 4:
                if (minimum == NULL) {
                    printf("Heap is empty.\n");
                } else {
                    printf("Fibonacci Heap:\n");
                    display_list(minimum, 0);
                }
                break;
            case 5:
                free_list(minimum);
                minimum = NULL;
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    free_list(minimum);
    return 0;
}

/*Algorithm
INSERT(heap, key)
    node <- NEW_NODE(key)
    ADD_TO_CIRCULAR_LIST(heap.root_list, node)
    node.parent <- NULL
    IF heap.minimum = NULL OR node.key < heap.minimum.key THEN
        heap.minimum <- node

FIND_MINIMUM(heap)
    RETURN heap.minimum

EXTRACT_MINIMUM(heap)
    root <- heap.minimum
    IF root = NULL THEN RETURN EMPTY
    minimum_key <- root.key
    WHILE root.child != NULL
        child <- root.child
        REMOVE_FROM_CIRCULAR_LIST(root.child, child)
        root.degree <- root.degree - 1
        child.parent <- NULL
        ADD_TO_CIRCULAR_LIST(heap.root_list, child)
    IF root.right = root THEN
        heap.minimum <- NULL
    ELSE
        next_root <- root.right
        REMOVE_FROM_CIRCULAR_LIST(heap.root_list, root)
        heap.minimum <- next_root
    FREE(root)
    CONSOLIDATE(heap)
    RETURN minimum_key

CONSOLIDATE(heap)
    degree_table[0..MAX_DEGREE-1] <- NULL
    roots <- COPY_OF(heap.root_list)
    heap.root_list <- EMPTY
    heap.minimum <- NULL
    FOR each root IN roots
        degree <- root.degree
        WHILE degree_table[degree] != NULL
            other <- degree_table[degree]
            IF other.key < root.key THEN SWAP(root, other)
            degree_table[degree] <- NULL
            ADD_TO_CIRCULAR_LIST(root.child, other)
            other.parent <- root
            other.mark <- false
            root.degree <- root.degree + 1
            degree <- degree + 1
        degree_table[degree] <- root
    FOR degree <- 0 TO MAX_DEGREE - 1
        IF degree_table[degree] != NULL THEN
            ADD_TO_CIRCULAR_LIST(heap.root_list, degree_table[degree])
            IF heap.minimum = NULL OR degree_table[degree].key < heap.minimum.key THEN
                heap.minimum <- degree_table[degree]
*/

/*Output:
1. Insert
2. Find minimum
3. Extract minimum
4. Display
5. Exit
Enter your choice: 1
Enter value: 10
10 inserted.
Enter your choice: 1
Enter value: 3
3 inserted.
Enter your choice: 1
Enter value: 7
7 inserted.
Enter your choice: 2
Minimum value: 3
Enter your choice: 3
Extracted minimum: 3
Enter your choice: 4
Fibonacci Heap:
7
  10
*/

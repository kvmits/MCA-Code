// Set 16.1 - Basic operations on a Binomial Min-Heap.

#include <stdio.h>
#include <stdlib.h>

#define MAX_DEGREE 32

struct node {
    int key;
    int degree;
    struct node *parent;
    struct node *child;
    struct node *sibling;
};

typedef struct node Node;
typedef Node *BinomialHeap[MAX_DEGREE];

Node *create_node(int key)
{
    Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->key = key;
    new_node->degree = 0;
    new_node->parent = NULL;
    new_node->child = NULL;
    new_node->sibling = NULL;
    return new_node;
}

Node *link_trees(Node *first, Node *second)
{
    if (second->key < first->key) {
        Node *temporary = first;
        first = second;
        second = temporary;
    }
    second->parent = first;
    second->sibling = first->child;
    first->child = second;
    first->degree++;
    return first;
}

void insert_tree(BinomialHeap heap, Node *tree)
{
    int degree = tree->degree;
    while (heap[degree] != NULL) {
        tree = link_trees(heap[degree], tree);
        heap[degree] = NULL;
        degree++;
    }
    heap[degree] = tree;
}

int minimum_index(BinomialHeap heap)
{
    int minimum = -1;
    for (int degree = 0; degree < MAX_DEGREE; degree++) {
        if (heap[degree] != NULL &&
            (minimum == -1 || heap[degree]->key < heap[minimum]->key)) {
            minimum = degree;
        }
    }
    return minimum;
}

int extract_minimum(BinomialHeap heap, int *minimum_key)
{
    int degree = minimum_index(heap);
    if (degree == -1) {
        return 0;
    }

    Node *minimum_root = heap[degree];
    heap[degree] = NULL;
    *minimum_key = minimum_root->key;
    Node *child = minimum_root->child;
    while (child != NULL) {
        Node *next = child->sibling;
        child->parent = NULL;
        child->sibling = NULL;
        insert_tree(heap, child);
        child = next;
    }
    free(minimum_root);
    return 1;
}

void display_tree(const Node *root, int depth)
{
    for (int index = 0; index < depth; index++) {
        printf("  ");
    }
    printf("%d\n", root->key);
    for (const Node *child = root->child; child != NULL; child = child->sibling) {
        display_tree(child, depth + 1);
    }
}

void display_heap(BinomialHeap heap)
{
    int empty = 1;
    for (int degree = 0; degree < MAX_DEGREE; degree++) {
        if (heap[degree] != NULL) {
            empty = 0;
            printf("B%d tree:\n", degree);
            display_tree(heap[degree], 0);
        }
    }
    if (empty) {
        printf("Heap is empty.\n");
    }
}

void free_tree(Node *root)
{
    while (root != NULL) {
        Node *next = root->sibling;
        free_tree(root->child);
        free(root);
        root = next;
    }
}

int main(void)
{
    BinomialHeap heap = {NULL};
    int choice, key;

    while (1) {
        printf("\n1. Insert\n2. Find minimum\n3. Extract minimum\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            break;
        }
        switch (choice) {
            case 1: {
                printf("Enter value: ");
                if (scanf("%d", &key) != 1) {
                    free_tree(heap[0]);
                    return 1;
                }
                Node *new_node = create_node(key);
                if (new_node == NULL) {
                    printf("Memory allocation failed.\n");
                } else {
                    insert_tree(heap, new_node);
                    printf("%d inserted.\n", key);
                }
                break;
            }
            case 2: {
                int degree = minimum_index(heap);
                if (degree == -1) {
                    printf("Heap is empty.\n");
                } else {
                    printf("Minimum value: %d\n", heap[degree]->key);
                }
                break;
            }
            case 3:
                if (extract_minimum(heap, &key)) {
                    printf("Extracted minimum: %d\n", key);
                } else {
                    printf("Heap is empty.\n");
                }
                break;
            case 4:
                display_heap(heap);
                break;
            case 5:
                for (int degree = 0; degree < MAX_DEGREE; degree++) {
                    free_tree(heap[degree]);
                }
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    for (int degree = 0; degree < MAX_DEGREE; degree++) {
        free_tree(heap[degree]);
    }
    return 0;
}

/*Algorithm
LINK_TREES(first, second)
    IF second.key < first.key THEN SWAP(first, second)
    second.parent <- first
    second.sibling <- first.child
    first.child <- second
    first.degree <- first.degree + 1
    RETURN first

INSERT(heap, key)
    tree <- NEW_NODE(key)
    degree <- tree.degree
    WHILE heap[degree] != NULL
        tree <- LINK_TREES(heap[degree], tree)
        heap[degree] <- NULL
        degree <- degree + 1
    heap[degree] <- tree

FIND_MINIMUM(heap)
    RETURN root with the smallest key

EXTRACT_MINIMUM(heap)
    root <- FIND_MINIMUM(heap)
    REMOVE root from heap
    FOR each child of root
        detach child from root
        INSERT_TREE(heap, child)
    FREE root
    RETURN root.key
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
B1 tree:
7
  10
*/

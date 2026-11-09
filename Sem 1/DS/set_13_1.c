// Menu-driven Red-Black Tree with insertion, rotations, and in-order traversal.
// Set 13.1 - Data Structures Lab

#include <stdio.h>
#include <stdlib.h>

enum color { RED, BLACK };

struct node {
	int data;
	enum color color;
	struct node *left;
	struct node *right;
	struct node *parent;
};

static struct node nil_node = {0, BLACK, &nil_node, &nil_node, &nil_node};
#define NIL (&nil_node)

struct node *root = NIL;

struct node *create_node(int value) {
	struct node *new_node = malloc(sizeof(*new_node));
	if (new_node == NULL) {
		printf("Memory allocation failed!\n");
		return NULL;
	}
	new_node->data = value;
	new_node->color = RED;
	new_node->left = NIL;
	new_node->right = NIL;
	new_node->parent = NIL;
	return new_node;
}

struct node *find_node(int value) {
	struct node *current = root;
	while (current != NIL && current->data != value) {
		current = value < current->data ? current->left : current->right;
	}
	return current;
}

void left_rotate(struct node *pivot) {
	struct node *child = pivot->right;
	pivot->right = child->left;
	if (child->left != NIL) {
		child->left->parent = pivot;
	}
	child->parent = pivot->parent;
	if (pivot->parent == NIL) {
		root = child;
	} else if (pivot == pivot->parent->left) {
		pivot->parent->left = child;
	} else {
		pivot->parent->right = child;
	}
	child->left = pivot;
	pivot->parent = child;
}

void right_rotate(struct node *pivot) {
	struct node *child = pivot->left;
	pivot->left = child->right;
	if (child->right != NIL) {
		child->right->parent = pivot;
	}
	child->parent = pivot->parent;
	if (pivot->parent == NIL) {
		root = child;
	} else if (pivot == pivot->parent->right) {
		pivot->parent->right = child;
	} else {
		pivot->parent->left = child;
	}
	child->right = pivot;
	pivot->parent = child;
}

int insert(int value) {
	struct node *parent = NIL;
	struct node *current = root;
	while (current != NIL) {
		parent = current;
		if (value == current->data) {
			printf("Duplicate values are not allowed.\n");
			return 0;
		}
		current = value < current->data ? current->left : current->right;
	}

	struct node *new_node = create_node(value);
	if (new_node == NULL) {
		return 0;
	}
	new_node->parent = parent;
	if (parent == NIL) {
		root = new_node;
	} else if (value < parent->data) {
		parent->left = new_node;
	} else {
		parent->right = new_node;
	}

	while (new_node != root && new_node->parent->color == RED) {
		if (new_node->parent == new_node->parent->parent->left) {
			struct node *uncle = new_node->parent->parent->right;
			if (uncle->color == RED) {
				new_node->parent->color = BLACK;
				uncle->color = BLACK;
				new_node->parent->parent->color = RED;
				new_node = new_node->parent->parent;
			} else {
				if (new_node == new_node->parent->right) {
					new_node = new_node->parent;
					left_rotate(new_node);
				}
				new_node->parent->color = BLACK;
				new_node->parent->parent->color = RED;
				right_rotate(new_node->parent->parent);
			}
		} else {
			struct node *uncle = new_node->parent->parent->left;
			if (uncle->color == RED) {
				new_node->parent->color = BLACK;
				uncle->color = BLACK;
				new_node->parent->parent->color = RED;
				new_node = new_node->parent->parent;
			} else {
				if (new_node == new_node->parent->left) {
					new_node = new_node->parent;
					right_rotate(new_node);
				}
				new_node->parent->color = BLACK;
				new_node->parent->parent->color = RED;
				left_rotate(new_node->parent->parent);
			}
		}
	}
	root->color = BLACK;
	return 1;
}

void inorder(struct node *current) {
	if (current != NIL) {
		inorder(current->left);
		printf("%d(%c) ", current->data, current->color == RED ? 'R' : 'B');
		inorder(current->right);
	}
}

void free_tree(struct node *current) {
	if (current != NIL) {
		free_tree(current->left);
		free_tree(current->right);
		free(current);
	}
}

int main(void) {
	int choice, value, count;
	while (1) {
		printf("\n1. Create Red-Black Tree\n2. Insert a new node\n3. Left rotate\n");
		printf("4. Right rotate\n5. In-order traversal\n6. Exit\nEnter your choice: ");
		if (scanf("%d", &choice) != 1) {
			break;
		}
		switch (choice) {
			case 1:
				printf("Enter number of nodes: ");
				if (scanf("%d", &count) != 1 || count < 0) {
					printf("Invalid number of nodes.\n");
					break;
				}
				free_tree(root);
				root = NIL;
				for (int index = 0; index < count; index++) {
					printf("Enter value: ");
					if (scanf("%d", &value) != 1 || !insert(value)) {
						printf("Could not add the value.\n");
						break;
					}
				}
				break;
			case 2:
				printf("Enter value to insert: ");
				if (scanf("%d", &value) == 1 && insert(value)) {
					printf("%d inserted into the Red-Black Tree.\n", value);
				}
				break;
			case 3:
			case 4:
				printf("Enter pivot value: ");
				if (scanf("%d", &value) == 1) {
					struct node *pivot = find_node(value);
					if (pivot == NIL) {
						printf("%d not found in the tree.\n", value);
					} else if (choice == 3 && pivot->right == NIL) {
						printf("Left rotation is not possible at %d.\n", value);
					} else if (choice == 4 && pivot->left == NIL) {
						printf("Right rotation is not possible at %d.\n", value);
					} else {
						if (choice == 3) {
							left_rotate(pivot);
						} else {
							right_rotate(pivot);
						}
						printf("Rotation completed at %d.\n", value);
					}
				}
				break;
			case 5:
				printf("In-order traversal (value/color): ");
				inorder(root);
				printf("\n");
				break;
			case 6:
				free_tree(root);
				root = NIL;
				return 0;
			default:
				printf("Invalid choice! Please try again.\n");
		}
	}
	free_tree(root);
	root = NIL;
	return 0;
}

/*Algorithm
left_rotate(pivot):
	Start
	child = pivot->right;
	pivot->right = child->left;
	if (child->left != NIL)
		child->left->parent = pivot;
	child->parent = pivot->parent;
	if (pivot->parent == NIL)
		root = child;
	else if (pivot == pivot->parent->left)
		pivot->parent->left = child;
	else
		pivot->parent->right = child;
	child->left = pivot;
	pivot->parent = child;
	Stop

right_rotate(pivot):
	Start
	child = pivot->left;
	pivot->left = child->right;
	if (child->right != NIL)
		child->right->parent = pivot;
	child->parent = pivot->parent;
	if (pivot->parent == NIL)
		root = child;
	else if (pivot == pivot->parent->right)
		pivot->parent->right = child;
	else
		pivot->parent->left = child;
	child->right = pivot;
	pivot->parent = child;
	Stop

insert(value):
	Start
	parent = NIL;
	current = root;
	while (current != NIL) {
		parent = current;
		if (value == current->data) {
			printf("Duplicate values are not allowed.\n");
			return 0;
		}
		current = (value < current->data) ? current->left : current->right;
	}
	new_node = create_node(value);
	if (new_node == NULL)
		return 0;
	new_node->parent = parent;
	if (parent == NIL)
		root = new_node;
	else if (value < parent->data)
		parent->left = new_node;
	else
		parent->right = new_node;
	while (new_node != root && new_node->parent->color == RED) {
		if (new_node->parent == new_node->parent->parent->left) {
			uncle = new_node->parent->parent->right;
			if (uncle->color == RED) {
				new_node->parent->color = BLACK;
				uncle->color = BLACK;
				new_node->parent->parent->color = RED;
				new_node = new_node->parent->parent;
			} else {
				if (new_node == new_node->parent->right) {
					new_node = new_node->parent;
					left_rotate(new_node);
				}
				new_node->parent->color = BLACK;
				new_node->parent->parent->color = RED;
				right_rotate(new_node->parent->parent);
			}
		} else {
			uncle = new_node->parent->parent->left;
			if (uncle->color == RED) {
				new_node->parent->color = BLACK;
				uncle->color = BLACK;
				new_node->parent->parent->color = RED;
				new_node = new_node->parent->parent;
			} else {
				if (new_node == new_node->parent->left) {
					new_node = new_node->parent;
					right_rotate(new_node);
				}
				new_node->parent->color = BLACK;
				new_node->parent->parent->color = RED;
				left_rotate(new_node->parent->parent);
			}
		}
	}
	root->color = BLACK;
	Stop

inorder(root):
	Start
	if (root != NIL) {
		inorder(root->left);
		printf("%d(%c) ", root->data, root->color == RED ? 'R' : 'B');
		inorder(root->right);
	}
	Stop

main(void):
	Start
	root = NIL;
	while (1) {
		printf("1. Create Red-Black Tree ... 6. Exit");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				scanf("%d", &count);
				if (count < 0)
					printf("Invalid number of nodes.\n");
				else {
					free_tree(root);
					root = NIL;
					for (index = 0; index < count; index++) {
						scanf("%d", &value);
						insert(value);
					}
				}
				break;
			case 2:
				scanf("%d", &value);
				insert(value);
				break;
			case 3:
			case 4:
				scanf("%d", &value);
				pivot = find_node(value);
				if (pivot == NIL)
					printf("%d not found in the tree.\n", value);
				else if (choice == 3 && pivot->right == NIL)
					printf("Left rotation is not possible.\n");
				else if (choice == 4 && pivot->left == NIL)
					printf("Right rotation is not possible.\n");
				else if (choice == 3)
					left_rotate(pivot);
				else
					right_rotate(pivot);
				break;
			case 5:
				inorder(root);
				break;
			case 6:
				free_tree(root);
				root = NIL;
				return 0;
			default:
				printf("Invalid choice! Please try again.\n");
		}
	}
	Stop
*/

/*Output:
Enter number of nodes: 5
Enter value: 10
Enter value: 20
Enter value: 30
Enter value: 15
Enter value: 25
In-order traversal (value/color): 10(B) 15(R) 20(B) 25(R) 30(B)
*/
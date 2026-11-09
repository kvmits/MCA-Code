// Menu-driven Binary Search Tree: creation, deletion, searching, and traversal.
// Set 12.2 - Data Structures Lab

#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *left;
	struct node *right;
};

struct node *create_node(int value) {
	struct node *new_node = malloc(sizeof(*new_node));
	if (new_node == NULL) {
		printf("Memory allocation failed!\n");
		return NULL;
	}
	new_node->data = value;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

int insert(struct node **root, int value) {
	if (*root == NULL) {
		*root = create_node(value);
		return *root != NULL;
	}
	if (value == (*root)->data) {
		printf("Duplicate values are not allowed.\n");
		return 0;
	}
	if (value < (*root)->data) {
		return insert(&(*root)->left, value);
	}
	return insert(&(*root)->right, value);
}

struct node *search(struct node *root, int value) {
	while (root != NULL && root->data != value) {
		root = value < root->data ? root->left : root->right;
	}
	return root;
}

struct node *delete_node(struct node *root, int value) {
	if (root == NULL) {
		return NULL;
	}
	if (value < root->data) {
		root->left = delete_node(root->left, value);
	} else if (value > root->data) {
		root->right = delete_node(root->right, value);
	} else if (root->left == NULL || root->right == NULL) {
		struct node *child = root->left != NULL ? root->left : root->right;
		free(root);
		return child;
	} else {
		struct node *successor = root->right;
		while (successor->left != NULL) {
			successor = successor->left;
		}
		root->data = successor->data;
		root->right = delete_node(root->right, successor->data);
	}
	return root;
}

void inorder(struct node *root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

void free_tree(struct node *root) {
	if (root != NULL) {
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}

int main(void) {
	struct node *root = NULL;
	int choice, value, count;

	while (1) {
		printf("\n1. Create BST\n2. Delete a node\n3. Search\n4. In-order traversal\n5. Exit\n");
		printf("Enter your choice: ");
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
				root = NULL;
				for (int index = 0; index < count; index++) {
					printf("Enter value: ");
					if (scanf("%d", &value) != 1 || !insert(&root, value)) {
						printf("Could not add the value.\n");
						break;
					}
				}
				break;
			case 2:
				printf("Enter value to delete: ");
				if (scanf("%d", &value) == 1) {
					if (search(root, value) == NULL) {
						printf("%d not found in the BST.\n", value);
					} else {
						root = delete_node(root, value);
						printf("%d deleted from the BST.\n", value);
					}
				}
				break;
			case 3:
				printf("Enter value to search: ");
				if (scanf("%d", &value) == 1) {
					printf(search(root, value) != NULL ? "%d found in the BST.\n" : "%d not found in the BST.\n", value);
				}
				break;
			case 4:
				printf("In-order traversal: ");
				inorder(root);
				printf("\n");
				break;
			case 5:
				free_tree(root);
				return 0;
			default:
				printf("Invalid choice! Please try again.\n");
		}
	}
	free_tree(root);
	return 0;
}

/*Algorithm
create_node(value):
	Start
	new_node = malloc(sizeof(struct node));
	if (new_node == NULL) {
		printf("Memory allocation failed!\n");
		return NULL;
	}
	new_node->data = value;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
	Stop

insert(root, value):
	Start
	if (*root == NULL) {
		*root = create_node(value);
		return (*root != NULL);
	}
	if (value == (*root)->data) {
		printf("Duplicate values are not allowed.\n");
		return 0;
	}
	if (value < (*root)->data)
		return insert(&(*root)->left, value);
	return insert(&(*root)->right, value);
	Stop

search(root, value):
	Start
	current = root;
	while (current != NULL && current->data != value) {
		if (value < current->data)
			current = current->left;
		else
			current = current->right;
	}
	return current;
	Stop

delete_node(root, value):
	Start
	if (root == NULL)
		return NULL;
	if (value < root->data)
		root->left = delete_node(root->left, value);
	else if (value > root->data)
		root->right = delete_node(root->right, value);
	else if (root->left == NULL || root->right == NULL) {
		child = (root->left != NULL) ? root->left : root->right;
		free(root);
		return child;
	} else {
		successor = root->right;
		while (successor->left != NULL)
			successor = successor->left;
		root->data = successor->data;
		root->right = delete_node(root->right, successor->data);
	}
	return root;
	Stop

free_tree(root):
	Start
	if (root == NULL)
		return;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
	Stop

inorder(root):
	Start
	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
	Stop

main(void):
	Start
	root = NULL;
	while (1) {
		printf("1. Create BST ... 5. Exit");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				scanf("%d", &count);
				if (count < 0)
					printf("Invalid number of nodes.\n");
				else {
					free_tree(root);
					root = NULL;
					for (index = 0; index < count; index++) {
						scanf("%d", &value);
						if (!insert(&root, value))
							break;
					}
				}
				break;
			case 2:
				scanf("%d", &value);
				if (search(root, value) == NULL)
					printf("%d not found in the BST.\n", value);
				else
					root = delete_node(root, value);
				break;
			case 3:
				scanf("%d", &value);
				if (search(root, value) != NULL)
					printf("%d found in the BST.\n", value);
				else
					printf("%d not found in the BST.\n", value);
				break;
			case 4:
				inorder(root);
				break;
			case 5:
				free_tree(root);
				return 0;
			default:
				printf("Invalid choice! Please try again.\n");
		}
	}
	Stop
*/

/*Output:
1. Create BST
Enter number of nodes: 5
Enter value: 40
Enter value: 20
Enter value: 60
Enter value: 10
Enter value: 30
In-order traversal: 10 20 30 40 60
Enter value to search: 30
30 found in the BST.
Enter value to delete: 40
40 deleted from the BST.
In-order traversal: 10 20 30 60
*/
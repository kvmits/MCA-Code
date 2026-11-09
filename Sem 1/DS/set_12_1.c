// Menu-driven Binary Search Tree: creation, insertion, and traversals.
// Set 12.1 - Data Structures Lab

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

void free_tree(struct node *root) {
	if (root == NULL) {
		return;
	}
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}

void inorder(struct node *root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

void preorder(struct node *root) {
	if (root != NULL) {
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(struct node *root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}

int main(void) {
	struct node *root = NULL;
	int choice, value, count;

	while (1) {
		printf("\n1. Create BST\n2. Insert a new node\n3. In-order traversal\n");
		printf("4. Pre-order traversal\n5. Post-order traversal\n6. Exit\n");
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
				printf("Enter value to insert: ");
				if (scanf("%d", &value) == 1 && insert(&root, value)) {
					printf("%d inserted into the BST.\n", value);
				}
				break;
			case 3:
				printf("In-order traversal: ");
				inorder(root);
				printf("\n");
				break;
			case 4:
				printf("Pre-order traversal: ");
				preorder(root);
				printf("\n");
				break;
			case 5:
				printf("Post-order traversal: ");
				postorder(root);
				printf("\n");
				break;
			case 6:
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

preorder(root):
	Start
	if (root != NULL) {
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
	Stop

postorder(root):
	Start
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
	Stop

main(void):
	Start
	root = NULL;
	while (1) {
		printf("1. Create BST ... 6. Exit");
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
				insert(&root, value);
				break;
			case 3:
				inorder(root);
				break;
			case 4:
				preorder(root);
				break;
			case 5:
				postorder(root);
				break;
			case 6:
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
Pre-order traversal: 40 20 10 30 60
Post-order traversal: 10 30 20 60 40
*/
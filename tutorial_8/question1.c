#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <pthread.h>
#include <semaphore.h>
#include <time.h>

typedef	struct proc	{
	char *parent[256];
	char *name[256];
	int priority;
	int memory;
	int val;
} proc_t;

typedef struct node {
	proc_t *data;
	struct node *left;
	struct node *right;
} node_t;

node_t* init();
void insert(node_t *head, int data);
void print_tree(node_t *head);
void printDFS(node_t *head);

void proc_insert(proc_t *head, proc_t *target);


node_t *proc_tree;


node_t* init() {
	node_t *new_node = (node_t*)malloc(sizeof(node_t));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->data = NULL;

	return new_node;
}

void insert(node_t *tree, int val) {
	if (tree->data == NULL) {
		tree->data = (proc_t*)malloc(sizeof(proc_t));
		tree->data->val = val;
	} else if (val < tree->data->val) {
		if (tree->left != NULL) {
			insert(tree->left, val);
		} else {
			tree->left = malloc(sizeof(node_t));
			tree->left->data = (proc_t*)malloc(sizeof(proc_t));
			tree->left->data->val = val;
		}
	} else if (val >= tree->data->val) {
		if (tree->right != NULL) {
			insert(tree->right, val);
		} else {
			tree->right = malloc(sizeof(node_t));
			tree->right->data = (proc_t*)malloc(sizeof(proc_t));
			tree->right->data->val = val;
		}
	}
}

void print_tree(node_t * current) {
	if (current != NULL)
		printf("\n%d ", current->data->val);
	if (current->left != NULL)
		printf("L%d ", current->left->data->val);
	if (current->right != NULL)
		printf("R%d", current->right->data->val);
	if (current->left != NULL)
		print_tree(current->left);
	if (current->right != NULL)
		print_tree(current->right);

}

void printDFS(node_t * current) {
	if (current->left != NULL)
		printDFS(current->left);
	if (current != NULL)
		printf("%d ", current->data->val);
	if (current->right != NULL)
		printDFS(current->right);
}

int main() {
	proc_tree = init();

	insert(proc_tree, 1);
	insert(proc_tree, 2);
	insert(proc_tree, 8);
	insert(proc_tree, 5);
	insert(proc_tree, 0);
	insert(proc_tree, 3);


	printf("printing tree..\n");
	print_tree(proc_tree);
	printf("\n");

	printf("printing DFS\n");
	printDFS(proc_tree);
	printf("\n");

}

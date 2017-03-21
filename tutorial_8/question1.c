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
} proc_t;

typedef struct node {
	proc_t *data;
	struct node *left;
	struct node *right;
} node_t;

node_t* init();
void insert(node_t *head, proc_t *data);
void print_tree(node_t *head);
void printDFS(node_t *head);
void read_file();

node_t *proc_tree;

node_t* init() {
	node_t *new_node = (node_t*)malloc(sizeof(node_t));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->data = NULL;

	return new_node;
}

void insert(node_t *tree, proc_t *target) {
	if (tree->data == NULL) {
		tree->data = (proc_t*)malloc(sizeof(proc_t));
		tree->data = target;
	} else if (target->priority < tree->data->priority) {
		if (tree->left != NULL) {
			insert(tree->left, target);
		} else {
			tree->left = malloc(sizeof(node_t));
			tree->left->data = (proc_t*)malloc(sizeof(proc_t));
			tree->left->data = target;
		}
	} else if (target->priority >= tree->data->priority) {
		if (tree->right != NULL) {
			insert(tree->right, target);
		} else {
			tree->right = malloc(sizeof(node_t));
			tree->right->data = (proc_t*)malloc(sizeof(proc_t));
			tree->right->data = target;
		}
	}
}

void print_tree(node_t * current) {
	if (current != NULL)
		printf("\nParent: %d, ", current->data->priority);
	if (current->left != NULL)
		printf("L child: %d, ", current->left->data->priority);
	if (current->right != NULL)
		printf("R child: %d,", current->right->data->priority);
	if (current->left != NULL)
		print_tree(current->left);
	if (current->right != NULL)
		print_tree(current->right);

}

void printDFS(node_t * current) {
	if (current->left != NULL)
		printDFS(current->left);
	if (current != NULL)
		printf("%d ", current->data->priority);
	if (current->right != NULL)
		printDFS(current->right);
}

void read_file() {
	FILE *process_file;
	char line[256];

	process_file = fopen("processes_tree.txt", "r");
	if (process_file != NULL) {
		char *pt;
		while ( fgets (line, 256, process_file) != NULL) {
			proc_t *temp = malloc(sizeof(proc_t));

			pt = strtok (line, ",");
			strcpy(temp->parent, pt);

			pt = strtok (NULL, ",");
			strcpy(temp->name, pt);

			pt = strtok (NULL, ",");
			temp->priority = atoi(pt);

			pt = strtok (NULL, ",");
			temp->memory = atoi(pt);

			insert(proc_tree, temp);
		}

	} else {
		printf("error opening processes_tree.txt for reading\n");
		exit(1);
	}
}

int main() {
	proc_tree = init();

	// proc_t *temp = (proc_t*)malloc(sizeof(proc_t));
	// proc_t *temp1 = (proc_t*)malloc(sizeof(proc_t));
	// proc_t *temp2 = (proc_t*)malloc(sizeof(proc_t));


	read_file();
	// temp->val = 1;
	// insert(proc_tree, temp);
	// temp1->val = 6;
	// insert(proc_tree, temp1);
	// temp2->val = 9;
	// insert(proc_tree, temp2);


	printf("---\nprinting tree..\n---\n");
	print_tree(proc_tree);
	printf("\n");

	printf("---\nprinting DFS\n---\n");
	printDFS(proc_tree);
	printf("\n");

}

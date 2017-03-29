#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <pthread.h>
#include <semaphore.h>
#include <time.h>

/// Process structure.
/// Contains cool process data.
typedef	struct proc	{
	char parent[256];
	char name[256];
	int priority;
	int memory;
} proc_t;

/// Tree node.
/// It's a binary tree, you know.
typedef struct node {
	proc_t *data;
	struct node *left;
	struct node *right;
} node_t;

/// Returns the root node of a new binary tree.
node_t* init();

/// Stores process 'data' in a new node under head,
/// In a sorted fashion.
void insert(node_t *head, proc_t *data);

/// Prints head and children under it.
void print_tree(node_t *head);

/// Outputs the results of a depth first search to stdout.
void printDFS(node_t *head);

/// It's gonna make a tree out of processes_tree.txt
void read_file(node_t* head);

/// Find something
node_t* dfsFind(node_t* head, const char* name);

node_t* init() {
	// the tree is empty
	node_t *new_node = (node_t*)malloc(sizeof(node_t));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->data = NULL;

	// be free
	return new_node;
}

void insert(node_t *tree, proc_t *target) {
	// figure out where target goes
	if (strcmp(target->parent, "NULL") == 0) {
	 tree->data = (proc_t*)malloc(sizeof(proc_t));
	 tree->data = target;
 } else if (strcmp(tree->data->name, target->parent) == 0) {
		// one of these has to be it, right?
		if(tree->right == NULL) {
			tree->right = malloc(sizeof(node_t));
			tree->right->data = (proc_t*)malloc(sizeof(proc_t));
			tree->right->data = target;
		} else if (tree->left == NULL) {
			tree->left = malloc(sizeof(node_t));
			tree->left->data = (proc_t*)malloc(sizeof(proc_t));
			tree->left->data = target;
		} else {
			assert(false);
		}

	} else {
		node_t* node = dfsFind(tree, target->parent);
		if(node == NULL) {
			printf("unable to place '%s'->'%s' under '%s'\n", target->parent
				, target->name, tree->data->name);
			assert(false);
		} else {
			insert(node, target);
		}
	}
}

void print_tree(node_t * current) {
	// Print stuff
	printf("%s priority %d size %d (parent '%s'", current->data->name
		, current->data->priority, current->data->memory, current->data->parent);
	if (current->left != NULL)
		printf(", L child: '%s'", current->left->data->name);
	if (current->right != NULL)
		printf(", R child: '%s'", current->right->data->name);
	printf(")\n");

	// now print children stuff
	if (current->left != NULL)
		print_tree(current->left);
	if (current->right != NULL)
		print_tree(current->right);

}

void printDFS(node_t * current) {
	if (current->left != NULL)
		printDFS(current->left);
	if (current != NULL)
		printf("%s ", current->data->name);
	if (current->right != NULL)
		printDFS(current->right);
}

void read_file(node_t* head) {
	FILE *process_file;
	char line[256];

	process_file = fopen("processes_tree.txt", "r");
	if (process_file != NULL) {
		char *pt;
		while ( fgets (line, 256, process_file) != NULL) {
			proc_t *temp = malloc(sizeof(proc_t));

			pt = strtok (line, ", ");
			strcpy(temp->parent, pt);

			pt = strtok (NULL, ", ");
			strcpy(temp->name, pt);

			pt = strtok (NULL, ",");
			temp->priority = atoi(pt);

			pt = strtok (NULL, ",");
			temp->memory = atoi(pt);

			insert(head, temp);
		}

	} else {
		printf("error opening processes_tree.txt for reading\n");
		exit(1);
	}
}

node_t* dfsFind(node_t* head, const char* name) {
	if(head == NULL) {
		return NULL;
	} else if(strcmp(head->data->name, name) == 0) {
		return head;
	} else {
		node_t* right = dfsFind(head->right, name);
		node_t* left = dfsFind(head->left, name);
		if(right != NULL)
			return right;
		if(left != NULL)
			return left;
		else
			return NULL;
	}
}

int main() {
	node_t*	proc_tree = init();

	read_file(proc_tree);

	printf("---\nprinting tree..\n---\n");
	print_tree(proc_tree);
	printf("\n");

	printf("---\nprinting DFS\n---\n");
	printDFS(proc_tree);
	printf("\n");

}

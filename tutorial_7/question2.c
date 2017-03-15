#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

typedef struct proc {
	char name[256];
	int priority;
	int pid;
	int runtime;
} proc_t;

typedef struct queue {
	proc_t *process;
	struct queue *next;
} queue_t;

queue_t *Queue = NULL;

void push(proc_t *process);
void print_list();
void init_queue();
proc_t pop();
proc_t *delete_name(char *name);
proc_t *delete_pid(int pid);
void read_in_proc_file();

void push(proc_t *process) {
	queue_t *current = Queue;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = malloc(sizeof(queue_t));
	current->next->process = process;
	current->next->next = NULL;
}

proc_t pop() {
	proc_t *ret_node = NULL;
	queue_t *next_node = Queue->next;

	if (Queue->process != NULL) {
		ret_node = Queue->process;
		Queue = next_node;
	}
	return *ret_node;
}

proc_t* delete_process(queue_t** get_rid_of_this_one, queue_t* previous_one) {
	// remove from queue structure
	if(previous_one != NULL)
		previous_one->next = (*get_rid_of_this_one)->next;

  // save the process before you delete the node for sure
	proc_t* process = (*get_rid_of_this_one)->process;
	free(*get_rid_of_this_one);
	return process;
}

//YES WORK
proc_t *delete_pid(int pid) {
	if(Queue == NULL)
		return NULL;

	queue_t *previous_node = NULL;
	queue_t *current_node = Queue;
	while(current_node->next != NULL) {
		if(current_node->process->pid == pid) {
			return delete_process(&current_node, previous_node);
		}

		// iterate
		previous_node = current_node;
		current_node = current_node->next;
	}

	// not found
	return NULL;
}

//YES WORK.
proc_t *delete_name(char *name) {
	if(Queue == NULL)
		return NULL;

	queue_t *previous_node = NULL;
	queue_t *current_node = Queue;
	while(current_node->next != NULL) {
		if(strcmp(name, current_node->process->name) == 0) {
			return delete_process(&current_node, previous_node);
		}

		// iterate
		previous_node = current_node;
		current_node = current_node->next;
	}

	// not found
	return NULL;
}

void print_process(proc_t* current) {
	printf("%s, %d, %d, %d\n", current->name, current->priority, current->pid, current->runtime);
}

void print_list() {
	queue_t *current = Queue;

	while (current != NULL) {
		print_process(current->process);
		current = current->next;
	}
}

void init_queue(proc_t *head_proc) {
	Queue->process = malloc(sizeof(proc_t));
	Queue->process = head_proc;
	Queue->next = NULL;
}

void read_in_proc_file() {
	proc_t *node;
	FILE *process_file;
	char line[256];

	process_file = fopen("processes.txt", "r");
	if (process_file != NULL) {
		char *pt;
		while ( fgets (line, 256, process_file) != NULL) {
			// printf("%s", line);
			node = malloc(sizeof(proc_t));
			pt = strtok (line, ",");
			strcpy(node->name, pt);

			pt = strtok (NULL, ",");
			int a = atoi(pt);
			node->priority = a;

			pt = strtok (NULL, ",");
			int b = atoi(pt);
			node->pid = b;

			pt = strtok (NULL, ",");
			int c = atoi(pt);
			node->runtime = c;

			if (Queue->process == NULL) {
				init_queue(node);
			} else {
				push(node);
			}
		}
	} else {
		printf("error opening sum.txt for reading\n");
		exit(1);
	}
}

int main(void) {
	// read in the queue
	Queue = malloc(sizeof(queue_t));
	read_in_proc_file();
	print_list();

	// delete & print emacs
	proc_t *emacs = delete_name("emacs");
	proc_t *the_pid_one = delete_pid(12235);
	printf("\nafter delete\n");
	print_list();

	// print stuff
	printf("we found these procs:\n");
	print_process(emacs);
	print_process(the_pid_one);

	// ok that's it
	return 0;
}

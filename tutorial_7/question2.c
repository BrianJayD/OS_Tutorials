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
proc_t delete_pid(int pid);
void read_in_proc_file();

void push(proc_t *process) {
	queue_t *current = Queue;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = malloc(sizeof(queue_t));
	current->next->process = process;
	current->next->next = NULL;
	// printf("pushed %s %d\n", current->process->name, current->process->pid);
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

//NO WORK
proc_t delete_pid(int pid) {
	proc_t *ret_node = NULL;
	return *ret_node;
}

//NO WORK
proc_t *delete_name(char *name) {
	proc_t *ret_node = NULL;
	// queue_t *temp = NULL;
	// queue_t *current_node = Queue;

	// while (current_node != NULL) {
	// 	if (strcmp(name, current_node->process->name) != 0) {
	// 		temp = current_node->next;
	// 		current_node->next = temp->next;
	// 	} else {
	// 		printf("test\n");
	// 		temp = current_node->next;
	// 		ret_node = current_node->process;
	// 		current_node->next->next = temp->next;
	// 		free(temp);
	// 		printf("\n>>found %s\n", ret_node->name);
	// 		break;
	// 	}
	// }
	// // Queue = next_node;
	return ret_node;
}

void print_list() {
	queue_t *current = Queue;

	while (current != NULL) {
		printf("%s, %d, %d, %d\n", current->process->name, current->process->priority, current->process->pid, current->process->runtime);
		current = current->next;
	}
}

void init_queue(proc_t *head_proc) {
	Queue->process = malloc(sizeof(proc_t));
	Queue->process = head_proc;
	Queue->next = NULL;
}

void read_in_proc_file() {
	proc_t *node = malloc(sizeof(proc_t));
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
	Queue = malloc(sizeof(queue_t));
	proc_t *x = NULL;

	read_in_proc_file();


	print_list();
	x = delete_name("emacs");
	printf("\nafter delete\n");
	print_list();

}

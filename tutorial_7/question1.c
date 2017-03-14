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

int main(void) {
	Queue = malloc(sizeof(queue_t));
	// Queue = malloc(sizeof(queue_t));
	proc_t *node = malloc(sizeof(proc_t));

	FILE *process_file;
	char line[256];
	size_t len = 0;
	ssize_t read;

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

			if (Queue->process == NULL)
			{
				init_queue(node);
			} else {
				push(node);
			}
		}


	} else {
		printf("error opening sum.txt for reading\n");
		exit(1);
	}

	print_list();
}

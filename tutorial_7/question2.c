#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "queue.h"

void init_queue_for_first_thing_cause_yeah(queue_t* Queue, proc_t *head_proc) {
	Queue->process = malloc(sizeof(proc_t));
	Queue->process = head_proc;
	Queue->next = NULL;
}

void read_in_proc_file(queue_t* Queue) {
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
				init_queue_for_first_thing_cause_yeah(Queue, node);
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
	queue_t** Queue = init_queue();
	read_in_proc_file(*Queue);
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

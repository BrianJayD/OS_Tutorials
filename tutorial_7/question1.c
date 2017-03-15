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

int main(void) {
	queue_t** head = init_queue();
	proc_t *node = malloc(sizeof(proc_t));

	FILE *process_file;
	char line[256];
	size_t len = 0;
	ssize_t read;

	process_file = fopen("processes.txt", "r");
	if (process_file != NULL) {
		char *pt;
		while ( fgets (line, 256, process_file) != NULL) {
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

			if ((*head)->process == NULL)
			{
				(*head)->process = malloc(sizeof(proc_t));
				(*head)->process = node;
				(*head)->next = NULL;
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

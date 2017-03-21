#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define MEMORY 1024

void read_file();

int main() {
	queue_t** head = init_queue();

	read_file();
}

void read_file() {
	FILE *process_file;
	char line[256];

	process_file = fopen("processes_q2.txt", "r");
	if (process_file != NULL) {
		char *pt;
		while ( fgets (line, 256, process_file) != NULL) {
			proc_t *temp = malloc(sizeof(proc_t));

			pt = strtok (line, ",");
			strcpy(temp->name, pt);

			pt = strtok (NULL, ",");
			temp->priority = atoi(pt);

			temp->pid = 0;

			temp->address = 0;

			pt = strtok (NULL, ",");
			temp->memory = atoi(pt);

			pt = strtok (NULL, ",");
			temp->runtime = atoi(pt);

			temp->suspended = false;

			// push();
			print_process(temp);
			free(temp);
		}

	} else {
		printf("error opening processes_q2.txt for reading\n");
		exit(1);
	}
}


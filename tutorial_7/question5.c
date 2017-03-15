#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <assert.h>
#include "queue.h"

void read_in_proc_file(queue_t* head, FILE* file) {
	char line[256];
	while ( fgets (line, 256, file) != NULL) {
		// printf("%s", line);
		proc_t* node = malloc(sizeof(proc_t));
		char* token = strtok (line, ",");
		strcpy(node->name, token);

		token = strtok (NULL, ",");
		int a = atoi(token);
		node->priority = a;

		token = strtok (NULL, ",");
		int c = atoi(token);
		node->runtime = c;

		node->pid = 0;

		if (head->process == NULL) {
			head->process = malloc(sizeof(proc_t));
			head->process = node;
			head->next = NULL;
		} else {
			push(node);
		}
	}
}

queue_t* get_node_of_priority(queue_t* head, bool want_zero_priority) {
	return head;
/*
		// iterate over all nodes
		while(head != NULL) {
			if(head->process->priority == 0)
			//if(false && false)
				return head;
			head = head->next;
		}
		return NULL;
		*/
}

// returns NULL if we done
queue_t* get_next_process_node(queue_t* head) {
	return get_node_of_priority(head, true);
}

int main(void){
	// load file
	static const char* FILE_NAME_PATH = "processes_q5.txt";
	FILE* in = fopen(FILE_NAME_PATH, "r");
	if(!in) {
		fprintf(stderr, "No open '%s' I close now\n", FILE_NAME_PATH);
		return EXIT_FAILURE;
	}

	// get stuff from file
	queue_t** head = init_queue();
	read_in_proc_file(*head, in);
	fclose(in);

	// iterate over procs
	queue_t* current_node;
	while((current_node = get_next_process_node(*head)) != NULL) {
		print_process(current_node->process);
		//print_process(current_node->next->process);
		proc_t* process = delete_name(current_node->process->name);
		//printf("deleted: '%s' head: '%s'", process->name, (*head)->process->name);
		//printf("-> '%s'\n", (*head)->next == NULL ? "null" : (*head)->next->process->name);
		assert(process != NULL);
	}

	// done
	if(*head != NULL) {
		fprintf(stderr, "Failed to execute all procs in head. DARN\n");
		return EXIT_FAILURE;
	}
	return 0;
}

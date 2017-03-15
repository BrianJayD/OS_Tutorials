#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
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

queue_t* get_node_of_priority_zero(queue_t* head) {
	// iterate over all nodes
	while(head != NULL) {
		if(head->process->priority == 0)
			return head;
		head = head->next;
	}
	return NULL;
}

// returns NULL if we done
queue_t* get_next_process_node(queue_t* head) {
	queue_t* node = get_node_of_priority_zero(head);
	return node ? node : head;
}

void launch_process(proc_t* process) {
	pid_t pid = fork();
	if(pid == 0) { // child
		execl("process", "process", NULL);
	} else if (pid > 0) { // parent
		process->pid = pid;
		sleep(process->runtime);
		kill(process->pid, SIGINT);
		waitpid(process->pid, NULL, 0);
		print_process(process);
	} else {
		fprintf(stderr, "Oh well uh this one failed to launch OOPS: ");
		print_process(process);
		exit(EXIT_FAILURE);
	}
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
		proc_t* process = delete_name(current_node->process->name);
		launch_process(process);
	}

	// done
	if(*head != NULL) {
		fprintf(stderr, "Failed to execute all procs in head. DARN\n");
		return EXIT_FAILURE;
	}
	return 0;
}

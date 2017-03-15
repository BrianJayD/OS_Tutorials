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

queue_t *Queue = NULL;

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
	if(previous_one != NULL) {// update that shit
    //printf("Previous one is for real %s\n", previous_one->process->name);
		previous_one->next = (*get_rid_of_this_one)->next;
  } else {// this is head and queue so fix it
    //printf("reassign queue to queue->next: %s\n", (*get_rid_of_this_one)->process == NULL ? "<nothing>" : (*get_rid_of_this_one)->process->name);
    assert(*get_rid_of_this_one == Queue);
    Queue = Queue->next;
  }

  // save the process before you delete the node for sure
	proc_t* process = (*get_rid_of_this_one)->process;
	free(*get_rid_of_this_one);


  // done
	return process;
}

//YES WORK
proc_t *delete_pid(int pid) {
	if(Queue == NULL)
		return NULL;

	queue_t *previous_node = NULL;
	queue_t *current_node = Queue;
	while(current_node != NULL) {
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
	while(current_node != NULL) {
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
  if(Queue == NULL) {
    printf("<no processes in queue>\n");
    return;
  }
	queue_t *current = Queue;

	while (current != NULL) {
    if(current->process != NULL)
		  print_process(current->process);
    else
      printf("%s\n", NULL);
		current = current->next;
	}
}

queue_t** init_queue(void) {
	Queue = malloc(sizeof(queue_t));
	return &Queue;
}

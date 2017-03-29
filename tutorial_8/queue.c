#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "queue.h"

void push(queue_t **target, proc_t *process) {
	queue_t *current = *target;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = malloc(sizeof(queue_t));
	current->next->process = process;
	current->next->next = NULL;
}

proc_t pop(queue_t** head) {
  // pop the front node, while retrieving process address.
	proc_t *found_proc = NULL;
	if (head != NULL) {
		found_proc = (*head)->process;
		*head = (*head)->next;
	}

  // make copy for return; then free memory used by process.
  proc_t process = *found_proc;
  free(found_proc);
	return process;
}

proc_t* delete_process(queue_t** head, queue_t** get_rid_of_this_one, queue_t* previous_one) {
	// remove from queue structure
	if(previous_one != NULL) {// update that shit
    //printf("Previous one is for real %s\n", previous_one->process->name);
		previous_one->next = (*get_rid_of_this_one)->next;
  } else {// this is head and queue so fix it
    //printf("reassign queue to queue->next: %s\n", (*get_rid_of_this_one)->process == NULL ? "<nothing>" : (*get_rid_of_this_one)->process->name);
    assert(*get_rid_of_this_one == *head);
    *head = (*head)->next;
  }

  // save the process before you delete the node for sure
	proc_t* process = (*get_rid_of_this_one)->process;
	free(*get_rid_of_this_one);


  // done
	return process;
}

//YES WORK
proc_t *delete_pid(queue_t** head, int pid) {
	if(*head == NULL)
		return NULL;

	queue_t *previous_node = NULL;
	queue_t *current_node = *head;
	while(current_node != NULL) {
		if(current_node->process->pid == pid) {
			return delete_process(head, &current_node, previous_node);
		}

		// iterate
		previous_node = current_node;
		current_node = current_node->next;
	}

	// not found
	return NULL;
}

//YES WORK.
proc_t *delete_name(queue_t** head, char *name) {
	if(*head == NULL)
		return NULL;

	queue_t *previous_node = NULL;
	queue_t *current_node = *head;
	while(current_node != NULL) {
		if(strcmp(name, current_node->process->name) == 0) {
			return delete_process(head, &current_node, previous_node);
		}

		// iterate
		previous_node = current_node;
		current_node = current_node->next;
	}

	// not found
	return NULL;
}

void print_process(proc_t* current) {
	printf("%s, %d, %d, %d, %d, %d, %d\n", current->name, current->priority, current->pid, current->address, current->memory, current->runtime, current->suspended);
}

void print_list(queue_t* head) {
  if(head== NULL) {
    printf("<no processes in queue>\n");
    return;
  }
	queue_t *current = head;

	while (current != NULL) {
    if(current->process != NULL)
		  print_process(current->process);
    else
      printf("%s\n", NULL);
		current = current->next;
	}
}

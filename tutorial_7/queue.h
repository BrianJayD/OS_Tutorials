#ifndef QUEUE_H
#define QUEUE_H

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

proc_t* delete_process(queue_t** get_rid_of_this_one, queue_t* previous_one);
void push(proc_t *process);
void print_list();
proc_t pop();
proc_t *delete_name(char *name);
proc_t *delete_pid(int pid);
queue_t** init_queue(void);
void print_process(proc_t* current);

#endif //QUEUE_H

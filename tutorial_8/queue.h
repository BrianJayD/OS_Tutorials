#ifndef QUEUE_H
#define QUEUE_H

/// Process data
typedef struct proc {
	char name[256];
	int priority;
	int pid;
	int address;
	int memory;
	int runtime;
	bool suspended;
} proc_t;

/// Queue linked-list node.
typedef struct queue {
	proc_t *process;
	struct queue *next;

/// gets rid of process, where 'previous_one' is the node behind the one to be
} queue_t;

/// removed. Returns the excised process.
proc_t* delete_process(queue_t** get_rid_of_this_one, queue_t* previous_one);

/// Adds process to end of the process queue.
void push(queue_t **target, proc_t *process);

/// Prints the process queue.
void print_list();

/// Removes a process from the front of the process queue.
proc_t pop();

/// Removes a process from process queue based on name.
proc_t *delete_name(char *name);

/// Remove a process from process queue based on pid.
proc_t *delete_pid(int pid);

/// initializes the process queue.
queue_t** init_queue(void);

/// prints out the data for 'current'
void print_process(proc_t* current);

#endif //QUEUE_H

#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

void spawn_n_procs(int n);
void write_ipc_file();
void read_ipc_file();

void spawn_n_procs(int n) {
	pid_t pid;
	for (int i = 0; i < n; ++i) {
		pid = fork();
		if (pid) {
			//launch something
			sleep(1); // waits for 1 second
			read_ipc_file(i + 1);
			continue;
		} else if (pid == 0) {
			//back to parent thread
			break;
		} else {
			printf("fork error\n");
			exit(1);
		}
	}
}

void read_ipc_file(int i) {
	FILE *child;
	char read_in[256];
	if (i == 1){
		child = fopen("child1.txt", "r");
	} else if (i == 2) {
		child = fopen("child2.txt", "r");
	} else {
		printf("error\n");
		exit(1);
	}

	if (child == NULL){
		printf("error read_ipc_file %d\n", i);
		exit(0);
	} else {
		while (fscanf(child, "%s", read_in) != EOF)
			printf("%s\n", read_in);
	}
	fclose(child);
}

void write_ipc_file() {
	FILE *child1, *child2;
	child1 = fopen("child1.txt", "w");
	child2 = fopen("child2.txt", "w");

	if (child1 == NULL || child2 == NULL)
	{
		printf("error write_ipc_file\n");
		exit(0);
	} else {
		fprintf(child1, "child1\n");
		fprintf(child2, "child2\n");
		printf("files written successfully...starting child processes\n");

	}
	fclose(child1);
	fclose(child2);
}

int main(void){
	write_ipc_file();
	spawn_n_procs(2);
	return 0;
}

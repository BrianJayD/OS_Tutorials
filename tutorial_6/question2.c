#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

void spawn_n_procs(int n);

void spawn_n_procs(int n) {
	pid_t pid, c_pid;
	int status;
	for (int i = 0; i < n; ++i) {
		pid = fork();
		if (pid == 0) {
			//launch something
			sleep(1); // waits for 1 second
			printf("child process - after 1 second sleep\n");
			continue;
		} else if (pid == -1) {
			printf("fork error\n");
			exit(1);
		} else {
			//back to parent thread
			if (waitpid(pid, &status, 0) == -1)
			{
				exit(EXIT_FAILURE);
			}
			if ( WIFEXITED(status) ) {
				printf("child exit status %d\n", WEXITSTATUS(status));
				printf("parent process\n");
			}
			break;
		}
	}
}

int main(void) {
	spawn_n_procs(1);
}

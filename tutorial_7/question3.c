#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){

	int status;
	pid_t pid;

	pid = fork();

	// Execute process
	if (pid == 0)
	{
			execl("process", "process", NULL);
			fprintf(stderr, "Ok well we tried (please make the 'process' executable)\n");
			return -1;
	}

	// Control process
	else if (pid > 0)
	{
		// give it 5 seconds before you interrupt.
		sleep(5);
		kill(pid, SIGINT);
	}

	// No fork can't eat food ;C
	else if (pid < 0)
	{
		printf("error!");
	}
}

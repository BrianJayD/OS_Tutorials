#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
	int status;
	pid_t pid;

	pid = fork();

	// Execute process
	if (pid == 0)
	{
			execl("process", "process", "10", NULL);
			fprintf(stderr, "Ok well we tried (please make the 'process' executable)\n");
			return -1;
	}

	// Control process
	else if (pid > 0)
	{
		// let it go for 5 seconds then TAKE OVER
		sleep(5);
		kill(pid, SIGTSTP);
		sleep(10);
		kill(pid, SIGCONT);
		waitpid(pid, NULL, 0);
	}

	// No fork can't eat food ;C
	else if (pid < 0)
	{
		printf("error!");
	}
}

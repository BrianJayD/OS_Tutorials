#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int main(void) {
	pid_t pid = fork();

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

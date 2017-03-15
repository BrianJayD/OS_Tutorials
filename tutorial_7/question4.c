#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>



#define BLUE "\x1B[34m"
#define WHITE "\e[0m"
#define RED "\e[31m"

int main(void){
	
	int status;
	pid_t pid;

	pid = fork();


	if (pid == 0) 
	{
		printf("Putting process to sleep\n");
		for (int i = 1; i <= 5; i++)
		{

			printf(WHITE "process %i has been asleep for ", pid);
			printf(BLUE "%i seconds\n", i);
			sleep(1);
		
		}
		
		printf(WHITE "Woke up: Now sleeping for 10 seconds\n");
		sleep(1);
		for (int i = 1; i <= 10; i++)
		{
			printf(WHITE "process %i has been asleep for ", pid);
			printf(RED "%i seconds\n", i);
			sleep(1);
		
		}
		signal(SIGTSTP, pid);
		printf(WHITE"child process continued\n");
		
	}

	else if (pid > 0)
	{

		waitpid(pid, &status, 0);
		signal(SIGCONT, pid);
		printf(WHITE"Parent Process\n");
	}

	else if (pid < 0)
	{
		printf("error!");
	}
}

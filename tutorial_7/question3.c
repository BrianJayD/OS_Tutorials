#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 5
#define RED   "\x1B[31m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

void SIGINT_handler(int);
static void SignalHandler(int);
static int signal_SIGINT = FALSE;

int main(void) {
  pid_t pid = fork();
	int status;
	int i;
	signal(SIGINT, SignalHandler);

	for (i = 0; i < N; i++) {
		if (pid == 0) {
			printf("pid=" BLU "%d" RESET " alive for " BLU "%d" RESET " seconds.\n", getpid(), i);
			sleep(5);
			if (signal_SIGINT) {
				printf(RED "%7d; tick %d" RESET "\n", (int) pid, i);
				exit(1);
			}
		} else {
			waitpid(pid, &status, 0);
			printf("We are parent\n");
			kill(pid, SIGKILL);
		}
	}

}

void SIGINT_handler(int sig) {
     printf(RED "From SIGINT: just got a %d (SIGINT ^C) signal\n" RESET, sig);
}

static void SignalHandler(int sig) {
	signal_SIGINT = TRUE;
}

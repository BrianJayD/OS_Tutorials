#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUMBERS 5
void spawn_n_procs(int n);
void factorial(int n);
int factorial_n(int n);

sem_t semaphore;
pthread_t threads[NUMBERS];
pthread_mutex_t mutex_lock;
int total_sum = 0;


void factorial(int n) {
	sem_wait(&semaphore);
	pthread_mutex_lock(&mutex_lock);
	
	int temp = 0;
	temp = factorial_n(n);
	printf("Entered %d, Fact Value: %d, Prev Sum: %d\n", n, temp, total_sum);
	total_sum += temp;

	pthread_mutex_unlock(&mutex_lock);
	sem_post(&semaphore);
}

int factorial_n(int n)
{
	if (n == 0)
		return 1;
	else if (n < 0)
		return 0;
	else
		return (n * factorial_n(n - 1));
}

void spawn_n_procs(int n) {
	pid_t pid, c_pid;
	int status, rc, read_in, read_sum;
	FILE *in_numbers_txt, *sum_txt;
	in_numbers_txt = fopen("numbers.txt", "r");
	if (in_numbers_txt == NULL) {
		printf("error opening numbers.txt for reading\n");
		exit(0);
	}
	for (int i = 0; i < n; ++i) {
		pid = fork();
		if (pid == 0) {
			//launch something (child)
			for (int j = 0; j < NUMBERS; j++) {
				if (fscanf(in_numbers_txt, "%d", &read_in) != EOF) {
					rc = pthread_create(&threads[j], NULL, (void *(*)(void*))factorial, (void*)(size_t)read_in);
					if (rc) {
						printf("ERROR; return code from pthread_create() is %d\n", rc);
						exit(-1);
					}
				}
			}
			fclose(in_numbers_txt);
			for (int k = 0; k < NUMBERS; k++) {
				(void) pthread_join(threads[k], NULL);
			}

			sum_txt = fopen("sum.txt", "w");
			if (sum_txt != NULL) {
				fprintf(sum_txt, "%d\n", total_sum);
			} else {
				printf("error opening sum.txt for writing\n");
				exit(1);
			}
			fclose(sum_txt);
			continue;
		} else if (pid == -1) {
			printf("fork error\n");
			exit(1);
		} else {
			//back to parent thread
			//waits until all children have died
			if (waitpid(pid, &status, 0) == -1) {
				exit(EXIT_FAILURE);
			}
			// do something after all children are dead
			if ( WIFEXITED(status) ) {
				printf("child exit status %d\n", WEXITSTATUS(status));
				// printf("parent process\n");
				sum_txt = fopen("sum.txt", "r");

				while (fscanf(sum_txt, "%d", &read_sum) != EOF)
					printf("TOTAL SUM: %d\n", read_sum);
			}
			//return to main
			break;
		}
	}
}

int main(void)
{
	FILE *numbers_txt;
	int num_array[NUMBERS];
	pid_t pid;

	sem_init(&semaphore, 0, 1);
	pthread_mutex_init(&mutex_lock, NULL);

	numbers_txt = fopen("numbers.txt", "w");

	if (numbers_txt != NULL) {
		for (int i = 0; i < NUMBERS; ++i) {
			printf("Enter a number: ");
			scanf("%d", &num_array[i]);
			fprintf(numbers_txt, "%d\n", num_array[i]);
		}
	} else {
		printf("error opening numbers.txt\n");
		exit(0);
	}
	fclose(numbers_txt);
	spawn_n_procs(1);
}

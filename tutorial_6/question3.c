#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

typedef struct num_index
{
	int value;
	int index; //0-4
} num_index;

void factorial(struct num_index* input);
long factorial_n(int n);

int moving_sum[5] = {0, 0, 0, 0, 0};
pthread_t threads[5];
sem_t semaphore;

void factorial(struct num_index *x) {
	int fact_temp = 0, prev_value = 0;

	if (x->index == 0)
	{
		fact_temp = factorial_n(x->value);
	} else {
		sem_wait(&semaphore);
		prev_value = moving_sum[x->index - 1];
		fact_temp = factorial_n(x->value) + prev_value;
		sem_post(&semaphore);
	}
	moving_sum[x->index] = fact_temp;
}

long factorial_n(int n)
{
	if (n == 0)
		return 1;
	else if (n < 0)
		return 0;
	else
		return (n * factorial_n(n - 1));
}

int main(void)
{
	sem_init(&semaphore, 0, 5);
	struct num_index *x[5];
	int rc, temp;
	for (int i = 0; i < 5; i++)
	{
		// sem_wait(&semaphore);

		x[i] = malloc(sizeof(struct num_index));

		printf("Enter a number: ");
		scanf("%d", &x[i]->value);
		x[i]->index = i;
		// &x[i]->value = temp;
	}

	for (int j = 0; j < 5; j++)
	{
		rc = pthread_create(&threads[j], NULL, (void *(*)(void*))factorial, x[j]);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
		// sem_post(&semaphore);
	}

	(void) pthread_join(threads[0], NULL);
	(void) pthread_join(threads[1], NULL);
	(void) pthread_join(threads[2], NULL);
	(void) pthread_join(threads[3], NULL);
	(void) pthread_join(threads[4], NULL);

	printf("\n--OUTPUT--\n[ ");
	for (int k = 0; k < 5; k++)
	{
		printf("%d ", moving_sum[k]);
	}
	printf("]\n");

	pthread_exit(NULL);
}

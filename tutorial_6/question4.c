#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <limits.h>

#define NUMBERS 10
#define BUFFER_SIZE 5

void *producer(int array[]);
void *consumer();
void add_buffer(int x);
int con_buffer();
void sleep_rand();

int buffer[5] = {0};
sem_t full_sem, empty_sem;
pthread_mutex_t mutex_lock;
int index;


void sleep_rand() {
   struct timespec tv;
  
   int msec = (int)(((double)random() / INT_MAX) * 1000);
  
   tv.tv_sec = 0;
   tv.tv_nsec = 1000000 * msec;
  
   if(nanosleep(&tv, NULL) == -1) {
      perror("sleep error");
   }
}


void *producer(int array[]) {
	int i = -1;
	while (i++ < NUMBERS - 1) {
		// sleep(rand() % 2 + 1);
		sleep_rand();
		sem_wait(&full_sem);
		pthread_mutex_lock(&mutex_lock);
		//critical section
		add_buffer(array[i]);
		//end critical section
		pthread_mutex_unlock(&mutex_lock);
		sem_post(&empty_sem);
	}
	return NULL;
}

void *consumer() {
	int i = 0;
	while (i++ < NUMBERS) {
		// sleep(rand() % 2 + 1);
		sleep_rand();

		sem_wait(&empty_sem);
		pthread_mutex_lock(&mutex_lock);
		//critical section
		printf("consumed <%d>\n", con_buffer());
		//end critical section
		pthread_mutex_unlock(&mutex_lock);
		sem_post(&full_sem);
	}
	return NULL;
}

void add_buffer(int x) {
	if (index < BUFFER_SIZE) {
		buffer[index++] = x;
		printf("produced <%d>\n", buffer[index - 1]);
	} else {
		printf("error overflow\n");
	}
}

int con_buffer() {
	int temp;
	if (index > 0) {
		temp = buffer[--index];
		buffer[index] = 0;
		return temp;
	} else {
		printf("buffer underflow\n");
	}
	return 0;
}

int main(void)
{
	index = 0;
	pthread_mutex_init(&mutex_lock, NULL);
	srand(time(NULL));   // should only be called once

	sem_init(&full_sem, 0, 5);
	sem_init(&empty_sem, 0, 0);

	pthread_t producer_thrd, consumer_thrd;
	int num_array[NUMBERS];

	for (int i = 0; i < NUMBERS; ++i)
	{
		printf("Enter a number: ");
		scanf("%d", &num_array[i]);
	}

	pthread_create(&producer_thrd, NULL, (void *(*)(void*))producer, &num_array);
	pthread_create(&consumer_thrd, NULL, (void *(*)(void*))consumer, NULL);

	(void) pthread_join(producer_thrd, NULL);
	(void) pthread_join(consumer_thrd, NULL);

	for (int i = 0; i < BUFFER_SIZE; ++i)
	{
		printf("%d\n", buffer[i]);
	}

	pthread_exit(NULL);

}

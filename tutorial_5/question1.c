#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <wait.h>

void *hello_world(void *x);
void goodbye(void *x);

void *hello_world(void *x) {
	int randomTime = rand() % 2 + 1;
	sleep(randomTime);
	printf("Hello World!\n");
	pthread_exit(NULL);
}

void goodbye(void *x) {
	int randomTime = rand() % 2 + 1;
	sleep(randomTime);
	printf("Goodbye\n");
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t thread1, thread2;
	long t;
	int rc, rc2;
	rc = pthread_create(&thread1, NULL, hello_world, (void *)t);
	rc2 = pthread_create(&thread2, NULL, goodbye, (void*)t);
	if (rc || rc2) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}

	pthread_exit(NULL);
}

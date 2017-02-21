#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <wait.h>

void bellcurve(float* grade);

void bellcurve(float* grade) {
	float sum = 0;
	sum = (*grade * 1.50);
	printf("grade: %f \n", sum);
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t students[5];
	float* grades[5];
	long t;
	int rc;

	for (int i = 0; i < 5; i++)
	{
		printf("Enter Your Student Grade: ");
		scanf("%f", &grades[i]);
	}

	for (int j = 0; j < 5; ++j)
	{
		rc = pthread_create(&students[j], NULL, bellcurve, &grades[j]);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	pthread_exit(NULL);
}

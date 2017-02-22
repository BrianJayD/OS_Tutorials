#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <wait.h>

float total_grade = 0;
pthread_mutex_t thread_lock;

void class_total(float* grade);

void class_total(float* grade) {
  pthread_mutex_lock(&thread_lock);
  pthread_t thread_id = pthread_self();
	total_grade += *grade;
	printf("grade: %f \n", total_grade);
  pthread_mutex_unlock(&thread_lock);
  pthread_exit(NULL);
}

int main(void)
{
	pthread_t students[10];
	float *grades[10];
	long t;
	int rc;

	for (int i = 0; i < 10; i++)
	{
		printf("Enter Your Student Grade: ");
		scanf("%f", &grades[i]);
	}

	for (int j = 0; j < 10; ++j)
	{
		rc = pthread_create(&students[j], NULL, class_total, &grades[j]);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	pthread_exit(NULL);
}

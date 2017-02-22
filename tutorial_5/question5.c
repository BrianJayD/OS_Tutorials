#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <wait.h>

#define BUFFER_LEN 256

float total_grade = 0;
float total_bellcurve = 0;
pthread_mutex_t thread_lock;
pthread_barrier_t barrier;
pthread_barrierattr_t attr;
float *input[10]; //max 10 lines


void save_bellcurve(float *grade);
void read_grades();

void read_grades() {
	FILE *infile;
	int w = 0;

	//open file in read mode
	infile = fopen("grades.txt", "r");

	//check for errors opening file
	if (infile == 0) {
		fprintf(stderr, "Error while opening");
		exit(1);
	} else

	//allocate memory for first array location
	input[0] = malloc(BUFFER_LEN);

	//continue reading lines unitl end of file
	while (!feof(infile)) {
		//dynamically allocate memory for each new array position
		input[w] = malloc(BUFFER_LEN);
		fscanf(infile, "%f\n", input[w]);
		w++; //next array element
	}

	fclose(infile);
	pthread_barrier_wait(&barrier);
	pthread_exit(NULL);
}

void save_bellcurve(float *grade) {
	pthread_mutex_lock(&thread_lock);
	pthread_t thread_id = pthread_self();
	
	total_grade += *grade;
	total_bellcurve += (*grade * 1.50);
	
	printf("total grade: %f total bellcurve %f\n", total_grade, total_bellcurve);

	FILE *outfile = fopen("bellcurve.txt", "ab");
	if (outfile == NULL) {
		printf("ERROR\n");
		exit(-1);
	}
	
	fprintf(outfile, "%f\n", (*grade * 1.50));
	
	fclose(outfile);
	pthread_mutex_unlock(&thread_lock);
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t students[10];
	pthread_t readFile;
	float *grades[10];
	int rc;

	int ret;
	(void) pthread_barrier_init(&barrier, &attr, 1);

	(void) pthread_create(&readFile, NULL, read_grades, NULL);

	pthread_barrier_destroy(&barrier);

	for (int j = 0; j < 10; ++j)
	{
		(void) pthread_create(&students[j], NULL, save_bellcurve, &input[j]);
	}

	for (int y = 0; y < 10; ++y)
	{
		pthread_join(students[y], NULL);
	}

	for (int r = 0; r < 10; ++r)
	{
		printf("%f\n", *input[r]);
	}

	pthread_exit(NULL);
}

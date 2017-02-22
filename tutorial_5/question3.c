#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <wait.h>
#include <string.h>

#define VAL 128

struct student_t {
	char *name;
	char *student_id;
	char *grade; // percentage expressed like 50 --> 50%
} typedef student_t;

char* askName();
void askID(student_t *x);
void askGrade(student_t *x);
void bellcurve(student_t *x);

char* askName() {
	static const size_t buffer_size = 256;
	// scan in the name.
	char* buffer = calloc(buffer_size, sizeof(char));
	printf("\nenter name: ");
	if (fgets(buffer, buffer_size, stdin) == NULL) {
		fprintf(stderr, "Error reading name.\n");
		free(buffer);
		return NULL;
	} else {
		char* newline = strchr(buffer, '\n');
		if (newline != NULL)
			*newline = '\0';
		return buffer;
	}
}

void askGrade(student_t *x) {
	static const size_t buffer_size = 32;
	char* buffer = calloc(buffer_size, sizeof(char));
	printf("enter grade: ");
	fgets(buffer, buffer_size, stdin);
	x->grade = buffer;
}

void askID(student_t *x) {
	static const size_t buffer_size = 64;
	printf("enter student id: ");
	char* buffer = calloc(buffer_size, sizeof(char));
	fgets(buffer, buffer_size, stdin);
	x->student_id = buffer;
}

void bellcurve(student_t *x) {
	float sum = 0;
	sum = (atoi(x->grade) * 1.50);
	printf("\nstudent id: %sstudent name: %s\ngrade: %f\n", x->student_id, x->name, sum/*x->grade*/);
	free(x->name);
	free(x->student_id);
	free(x->grade);
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t threads[5];
	student_t students[5];
	long t;
	int rc, i = 0;

	for (; i < 5; i++)
	{
		students[i].name = askName();
		askID(&students[i]);
		askGrade(&students[i]);
	}

	printf(">> starting threads...\n");

	for (int j = 0; j < i; ++j)
	{
		rc = pthread_create(&threads[j], NULL, bellcurve, &students[j]);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	pthread_exit(NULL);
}

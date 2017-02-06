// Create a program that does the following
// - Create a struct called ​ student ​ containing their ​ student id, age​ , and the
// year​ they started at UOIT.
// - Create a function called ​ save_student​ which does the following
// - Takes as its argument the ​ student​ struct and returns ​ voidOpens a file called ​ students.txt​ in ​ append​ mode
// Saves the student id, age, and year from the ​ students​ struct to the
// file on one line delimited by commas (e.g. ​ 100123456,19,2014​ ).
// In the console prompt the user for their ​ student id​ , ​ age​ , and the ​ year​ they
// start at UOIT.
// Store the values entered by the user in the ​ student​ struct.
// Call the function ​ save_student​ with the student struct to save the data to
// the ​ students.txt​ file.

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	int age;
	int year_started;
	char *first_name;
} student;

void save_student(student);

void save_student(student x) {
	// printf("%s %i %i\n", x.first_name, x.age, x.year_started);
	FILE *outfile = fopen("question3.txt", "ab");
	if (outfile == NULL){
		printf("EROOR\n");
		exit(-1);
	}
	fprintf(outfile, "%s,%d,%d\n", x.first_name, x.age, x.year_started);
	fclose(outfile);
}

int main(void)
{
	student input;
	char input_name[256];
	printf("Enter Your Name: ");
	scanf("%s", input_name);

	int input_age = 0;
	printf("Enter Your Age: ");
	scanf("%i", &input_age);

	int input_year = 0;
	printf("Enter Your Starting Year: ");
	scanf("%i", &input_year);

	input.first_name = input_name;
	input.age = input_age;
	input.year_started = input_year;

	save_student(input);
}

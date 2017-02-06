// Create a program that does the following
// - Creates three pointers, a character pointer ​ professor​ , and two integer
// pointers ​ student_ids​ , ​ grades
// - Using dynamic memory, use ​ calloc​ to allocate 256 characters for the
// professor ​ pointer
// - Prompts the professor for their ​ name​ , and the ​ number of students​ to
// mark.
// - Stores the professor’s name using the ​ professor​ pointer​ ​ and in an integer
// the number of students to mark.
// - Using dynamic memory, use ​ malloc​ to allocate memory for ​ student_ids
// and ​ grades​ to hold the number of students​ ​ the professor needs to mark.
// - The program does not need to do anything else, ensure that you ​ free​ your
// memory before terminating.
// - You will need to review the ​ malloc​ , ​ calloc​ , ​ ​ and ​ sizeof​ documentation.

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* askName();
int prompt_for_number_of_students();
void askGrades();


// retrieve number of students from standard input
int prompt_for_number_of_students(const char* professor) {
	static const size_t buffer_size = 16;
	char buffer[buffer_size] = {0};
	int count;
	printf("OK %s, How many students are there? ", professor);
	if (fgets(buffer, buffer_size, stdin) == NULL
	        || sscanf(buffer, "%d", &count) != 1) {
		fprintf(stderr, "[Error] '%s' is invalid\n", buffer);
		return 0;
	}
	return count;
}

char* askName() {
	static const size_t buffer_size = 256;
	// scan in the name.
	char* buffer = calloc(buffer_size, sizeof(char));
	printf("Give me your name: ");
	if (fgets(buffer, buffer_size, stdin) == NULL) { // Fucked up the name reading
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

int main(void)
{
	char *professor = askName();
	int student_num = prompt_for_number_of_students(professor);
	int *student_ids;
	int* grades = malloc(student_num);
	student_ids = malloc(student_num * sizeof(grades));
	printf(">%s %i\n", professor, student_num);
	free(professor);
	free(grades);	
	free (student_ids);
}

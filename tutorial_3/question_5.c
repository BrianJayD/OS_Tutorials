/*Building upon the previous questions you will create a marking system for
professors at UOIT.
- Structs can be used the same as any other data type in C, instead of
having two arrays for the grades and student ids create a struct called
grade​ that contains two integers: ​ student_id​ and ​ mark​ .
Create a function ​ grade_students​ which takes the following arguments: a
pointer​ to the ​ grade​ struct called ​ grades​ , ​ ​ and an integer ​ num_students.
The function returns ​ void ​ and does the following:
- Opens the file ​ grades.txt​ in ​ write​ mode
- Using the ​ num_students​ parameter iterates through all of the
grade structs pointed to by the ​ grades​ parameter (remember
arrays are pointers, you can treat pointers like arrays).
- For each​ grade structure ​ adds​ the ​ mark ​ member of the struct to a
variable called ​ sum​ that holds the sum of all student’s grades.-
- For each​ grade structure​ write​ to the file ​ grades.txt​ the ​ student id
and the ​ mark​ on a single line.
After adding every student's​ mark​ to the ​ sum​ variable, calculate
the ​ average​ (mean)​ ​ and ​ standard deviation​, you will need to use
<math.h>​ don’t forget when you compile to add -lm
Write​ to the file ​ grades.txt the average​ and​ standard deviation
that you calculated*/

// Includes
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/// Grade type
struct grade_t {
  int student_id;
  int mark; // percentage expressed like 50 --> 50%
} typedef grade_t;

/// Here are some nice function declarations.
/// Prints to stderr & returns NULL upon IO failure, where relevant.
void grade_students(grade_t* grades, int num_students);
char* prompt_for_name(void);
int prompt_for_number_of_students(const char* professor);
grade_t* prompt_for_grades(int num_students);

/// This is the driver
int main() {
  char* professor = prompt_for_name();
  int number_of_students = prompt_for_number_of_students(professor);
  grade_t* grades = prompt_for_grades(number_of_students);
  grade_students(grades, number_of_students);
  free(grades);
  free(professor);
  return 0;
}

// -------- The rest of the implementation is down here ------------------------

/// Writes data to file 'grades.txt'
/// Each grade, along with the average & standard deviation.
///   grades : array of student grades
///   num_students : size of grades array
void grade_students(grade_t* grades, int num_students) {
  static const char* GRADES_TXT = "grades.txt";
  assert(num_students > 1);
  assert(grades != NULL);

  // Opens grades.txt in write mode
  FILE* fin = fopen(GRADES_TXT, "w");
  if(fin == NULL) {
    fprintf(stderr, "[Error]Could not open '%s'!\n", GRADES_TXT);
    return;
  }

  // For each grade, add to sum & write to file.
  double sum = 0;
  double sum_squares = 0;
  for(int i = 0; i < num_students; i++) {
    grade_t grade = grades[i];
    sum += grade.mark;
    sum_squares += grade.mark * grade.mark;
    fprintf(fin, "%d %d\n", grade.student_id, grade.mark);
  }

  // Calculate stats
  double mean = sum/num_students;
  double sxx = sum_squares - sum*sum/num_students; // I worked this out on paper
  double variance = sxx/num_students; //              and tested it, too (*v* )b
  double stddev = sqrt(variance);
  fprintf(fin, "mean: %.1f%%\nstandard deviation: %.6f\n", mean, stddev);

  // close grades.txt
  if(fclose(fin) != 0) {
    fprintf(stderr, "[Error]Could not close '%s'!\n", GRADES_TXT);
  }
}

/// retrieve professor's name from standard input.
char* prompt_for_name(void) {
  static const size_t buffer_size = 256;

  // scan in the name.
  char* buffer = calloc(buffer_size, sizeof(char));
  printf("Give me your name: ");
  if(fgets(buffer, buffer_size, stdin) == NULL) { // Fucked up the name reading
    fprintf(stderr, "Error reading name.\n");
    free(buffer);
    return NULL;
  } else {
    char* newline = strchr(buffer, '\n');
    if(newline != NULL)
      *newline = '\0';
    return buffer;
  }
}

/// retrieve number of students from standard input
int prompt_for_number_of_students(const char* professor) {
  static const size_t buffer_size = 16;
  char buffer[buffer_size] = {0};
  int count;
  printf("OK %s, How many students are there? ", professor);
  if(fgets(buffer, buffer_size, stdin) == NULL
    || sscanf(buffer, "%d", &count) != 1) {
    fprintf(stderr, "[Error] '%s' is invalid\n", buffer);
    return 0;
  }
  return count;
}

bool prompt_for_grade(grade_t* grade_dest) {
  static const size_t buffer_size = 16;
  char buffer[buffer_size] = {0};
  grade_t grade;
  printf("Please enter student id & mark: ");
  if(fgets(buffer, buffer_size, stdin) == NULL
    || sscanf(buffer, "%d %d", &grade.student_id, &grade.mark) != 2) {
    fprintf(stderr, "[Error] '%s' is invalid\n", buffer);
    return false;
  }
  *grade_dest = grade;
  return true;
}

// prompts for grades.
grade_t* prompt_for_grades(int num_students) {
  assert(num_students > 1);
  grade_t* grades = malloc(num_students*sizeof(grades));
  for(int i = 0; i < num_students; i++) {
    grade_t grade;
    printf("[%d/%d] ", i+1, num_students); // print out current progress
    if(!prompt_for_grade(&grade)) { // try again
      i--;
      continue;
    }
    grades[i] = grade;
  }
  return grades;
}

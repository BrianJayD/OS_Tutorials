# the compiler: gcc for C program, define as g++ for C++
CC =clang

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  #  -Wextra  
CFLAGS  = -Wall -Wextra -std=c99

  # the build target executable:
.PHONY : default
default : all

all : question1 question2 question3 question4 question5
.PHONY : all

question1 : question1.o
	$(CC) -o question_1 question1.o 

question2 : question2.o
	$(CC) -o question_2 question2.o 

question3 : question3.o
	$(CC) -o question_3 question3.o 

question4 : question4.o
	$(CC) -o question_4 question4.o 

question5 : question5.o
	$(CC) -lm -o question_5 question5.o

.PHONY : clean
clean :
	-rm *.o $(objects) question_*

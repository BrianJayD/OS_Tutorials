.SUFFIXES: .c
.PHONY : default all clean

# the compiler: gcc for C program, define as g++ for C++
CC = clang
OBJECTS := $(subst .c,.o,$(SOURCES))
BIN = question_1 question_2 question_3 question_4 question_5
# LIBS := -lm 
LDFLAGS := -lm



  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  #  -Wextra 
CFLAGS  = -Wall -Wextra -std=gnu99

# shiet -std=c99 changed to -std=gnu99 <----

#   # the build target executable:
default : all

all : question_1 question_2 question_3 question_4 question_5

% : %.o
	$(CC) $(CFLAGS) $< $(LIBS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $< 


clean :
	rm -f $(OBJECTS) $(BIN) *.o *~


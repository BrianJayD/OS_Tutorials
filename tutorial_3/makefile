CC := clang
CFLAGS := -Wall -Wextra -std=c99
CPPFLAGS:= 
LFLAGS = 
LIBS := -lm
SOURCES := question1.c question2.c question3.c question4.c question5.c
OBJECTS := $(subst .c,.o,$(SOURCES))
BIN = question1 question2 question3 question4 question5
.PHONY: clean all default

default : all

all : $(BIN)

question1 : question1.o
	$(CC) -o question1 question1.o 

question2 : question2.o
	$(CC) -o question2 question2.o 

question3 : question3.o
	$(CC) -o question3 question3.o 

question4 : question4.o
	$(CC) -o question4 question4.o 

question5 : question5.o
	$(CC) -lm -o question5 question5.o


clean:
	rm -f $(OBJECTS) $(BIN) *~

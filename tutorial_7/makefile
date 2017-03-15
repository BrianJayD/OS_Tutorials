CC := clang
CFLAGS := -std=c99
CPPFLAGS:= 
LFLAGS = 
LIBS := 
# SOURCES := question1.c question2.c question3.c question4.c question5.c
OBJECTS := $(subst .c,.o,$(SOURCES))
BIN = question1 question2 question3 question4 question5 process
.PHONY: clean all default

default : all

all : $(BIN)

process : sigtrap.c
	clang -std=gnu99 sigtrap.c -o process

question1 : question1.o
	$(CC) $(CFLAGS) -o question1 question1.o 

question2 : question2.o
	$(CC) $(CFLAGS) -o question2 question2.o 

question3 : question3.o
	$(CC) $(CFLAGS) -o question3 question3.o 

question4 : question4.o
	$(CC) $(CFLAGS) -o question4 question4.o 

question5 : question5.o
	$(CC) $(CFLAGS) -o question5 question5.o


# % : %.o
# 	$(CC) $(CFLAGS) $< $(LIBS) -o $@ 

# %.o : %.c
# 	$(CC) $(CFLAGS) -c $< 


clean:
	rm -f $(OBJECTS) $(BIN) *~

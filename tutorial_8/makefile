CC := clang
CFLAGS := -std=gnu99 -Wall
SOURCES := question2.c question1.c queue.c
DEPS = queue.o
OBJECTS := $(subst .c,.o,$(SOURCES)) queue.o
BIN := question2 question1 process 

.PHONY: clean all

all : $(BIN)

process : sigtrap.c
	clang -std=gnu99 $< -o $@

% : %.o $(DEPS)
	$(CC) $(DEPS) $(CFLAGS) $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $<

$(BIN) : $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(BIN) *~

CC := clang
CFLAGS := -Wall -Wextra -std=gnu99
SOURCES := question5.c question4.c question3.c question2.c question1.c queue.c
DEPS = queue.o
OBJECTS := $(subst .c,.o,$(SOURCES))
BIN := question5 question4 question3 question2 question1 process
.PHONY: clean all

all : $(BIN)

process : sigtrap.c
	clang -std=gnu99 $< -o $@

% : %.o
	$(CC) $(DEPS) $(CFLAGS) $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $<

$(BIN) : $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(BIN) *~

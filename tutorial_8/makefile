CC := clang
CFLAGS := -std=gnu99 -Wall
SOURCES := question2.c question1.c
DEPS =
# OBJECTS := $(subst .c,.o,$(SOURCES))
BIN := question2 question1 process
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

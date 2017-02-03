#Tutorial 2 Conceptual Questions

1. What are some of the benefits of the C language? Name an example where the
C language is used (hint there are many!).

	Programs written in C are faster then other languages such as Java, and due to its built in functions, is often easier to work with 

2. What is a compiler, what does it do?
	
	A compiler takes a source program and converts it from high level language to a target language, removes whitespace, does type checking, etc. 

3. What is a makefile, what does it do?

	A makefile is an easy way to run certain commands on source files for programs. Commands like `make <file_name>`, will look in the make file and automatically use which compiler and flags are set to compile the program. Another common command for makefiles is `clean` which usually removes all compiled files.

4. Name 5 header files from the C library and explain their purpose.

	+ `<assert.h>` - contains the *assert* macro, used to assist with detecting logical errors and other types of bugs in debugging versions of a program.
	+ `<signal.h>` - set of functions for manipulating variables
	+ `<time.h>` - defines time and date handling functions.
	+ `<stdio.h>` - standard input output functions
	+ `<string.h>` - defines string handling functions

5. Lookup one function from each of the header files and put down the function
name and describe what it does.

	+ `void assert(int expression)` - actually a macro not a function, used for debugging (adding assertions)
	+ `signal` - handles signals (SIGABRT, SIGFPE, SIGILL, etc.)
	+ `time` - returns the current time
	+ `remove(<file>)` - removes specified file
	+ `strcpy` - copies specified string to specified destination 


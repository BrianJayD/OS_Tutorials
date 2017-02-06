#Conceptual Questions

1. List each of the modes for the ​ fopen​ function to the perform the following
operations: ​ read​ , ​ write​ , ​ read and write​ , ​ append​ to a file.  

	+ r - read
	+ w - write
	+ a - append​
	+ r+ - read/update
	+ w+ - write/update
	+ a+ - append/update

2. Does dynamic memory use the ​stack​ or heap? What is the difference between
the stack and heap?

stack is fixed length (stack overflow), whereas heap is dynamically assigned, if the heap becomes to big the OS can add memory to it. Dynamic memory is heap.  

3. Explain what a pointer is, and provide examples (in C code) of how to change the
address that a pointer points to and how to access the data the pointer points to.  

a pointer is a variable that stores the address of another variable  

```c
int x = 7;
int y = 9;
int *ptr = &x;
ptr = &y;
printf("%d\n", *ptr);

```   

4. Read the documentation on the ​`malloc` and ​`free`​ functions and explain briefly
how to use `malloc`.   

	malloc is used to allocate a block of memory in bytes, and free is used to deallocate the space allocated by malloc

5. What is the difference between ​`malloc`​ and `​calloc`​?  

	calloc instead of 1 paramater has 2 paramters, usually used to allocate memory for arrays. 

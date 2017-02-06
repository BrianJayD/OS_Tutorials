//   Create a program that does the following
// - Reads the ten integers from the included file ​ question2.txt
// - Stores each integer​ read from the file​ in an array
// - Prints the contents of the array to the terminal
// - You will need to review the ​ fopen​ and ​ fscanf​ documentation

#include <stdlib.h>
#include <stdio.h>

#define BUFFER_LEN 256

int main(void)
{
	FILE *infile;
	char *input[50]; //max 50 lines
	int w = 0;

	printf("opening file..");

	//open file in read mode
	infile = fopen("question2.txt", "r");

	//check for errors opening file
	if (infile == 0) {
		fprintf(stderr, "Error while opening");
		exit(1);
	} else
		printf("OK\n");

	printf("scanning file...");

	//allocate memory for first array location
	input[0] = malloc(BUFFER_LEN);

	//continue reading lines unitl end of file
	while (!feof(infile)) {
		//dynamically allocate memory for each new array position
		input[w] = malloc(BUFFER_LEN);
		fscanf(infile, "%s\n", input[w]);
		w++; //next array element
	}

	printf("OK\n");
	printf("printing array contents:\n");

	for (int i = 0; i < w; ++i)
	{
		printf("> %s\n", input[i]);
	}
	printf("freeing memory and closing file...");
	int x;
	for (x = 0; x < w; x++)
		//clean up allocated memory
		free(input[x]);
	//close input file
	fclose(infile);
	printf("OK\n");
}

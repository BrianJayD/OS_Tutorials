#include <stdlib.h>
#include <stdio.h>

int main(void) {

	// Prints string 1 character at at time until whole string is printed
	char greeting[] = "hello world";
	int index = 0;
	do
	{
		printf("%c", greeting[index]);
		index++;
	} while (greeting[index] != '\0');

	printf("\n");

}

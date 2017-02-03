#include <stdlib.h>
#include <stdio.h>

int main(void) {
	// Loops from 1 - 10 and checks if even or odd
	for (int i = 1; i <= 10; ++i)
	{
		if (i % 2 != 0)
		{
			printf("odd\n");
		} else {
			printf("even\n");
		}
	}
}

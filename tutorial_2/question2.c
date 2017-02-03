#include <stdlib.h>
#include <stdio.h>

int main(void) {
// Prints weather doubles are the same higher or lower then the previous array entry
	double double_array[5] = {1.2, 5.5, 2.1, 3.3, 3.3};

	for (int i = 0; i < 5; ++i)
	{
		// printf("%f\n", double_array[i]);
		if (double_array[i] < double_array[i - 1]) {
			printf("less then\n");
		} else if (double_array[i] > double_array[i - 1]) {
			printf("greater then\n");
		} else {
			printf("the same\n");
		}
	}
}

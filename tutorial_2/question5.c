
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double euclid_func (int x1, int y1, int x2, int y2);

int main(void) {
	int x, y, x2, y2;
	float result;
	// calls euclid_func 10 times 
	for (int i = 0; i < 10; ++i)
	{
		x = rand() % 100;
		y = rand() % 100;
		x2 = rand() % 100;
		y2 = rand() % 100;
		result = euclid_func(x, y, x2, y2);
		printf("x1=%i y1=%i x2=%i y2=%i result=%f\n", x, y, x2, y2, result);
		// printf("result = %f\n", euclid_func(2, -1, -2, 2)); //check line result should = 5
	}
}

double euclid_func (int x, int a, int y, int b) {
	double result;
	result = sqrt(pow((x - a), 2) + pow((y - b), 2));
	return result;
}

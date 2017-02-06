//   Create a program that does the following
// - Prompts the user for their ​ first name​ , ​ age​ , and ​ height​ (hint use a
//   character array for strings).
// - Prints back to the console, their first name, age, and height
// - You will need to review the ​ scanf​ documentation to complete this

#include <stdlib.h>
#include <stdio.h>

#define BUFFER_LEN 256

int main(void)
{
	char input_name[BUFFER_LEN];
	printf("Enter Your Name: ");
	scanf("%s", input_name);

	char input_age[BUFFER_LEN];
	printf("Enter Your Age: ");
	scanf("%s", input_age);
	
	char input_height[BUFFER_LEN];
	printf("Enter Your Height: ");
	scanf("%s", input_height);
	

	printf("%s %s %s\n", input_name, input_age, input_height);
}

/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>




struct gameinfo
{
	char* questionCategory;
	char* question;
	char* answer;
	int value;
	int isAnswered;
};

char* gameCategories[3] = {"Celebs", "Movies", "Games"};
char* cat1Questions[4] = {"q1","q2","q3","q4"};
char* cat1Answers[4] = {"a1","a2","a3","a4"};
char* cat2Questions[4] = {"q5","q6","q7","q8"};
char* cat2Answers[4] = {"a5","a6","a7","a8"};
char* cat3Questions[4] = {"q9","q10","q11","q12"};
char* cat3Answers[4] = {"a9","a10","a11","a12"};
int questionValues[4] = {100, 200, 300, 400};
int wasQuestionAnswered[4] = {0, 0, 0, 0};

struct gameinfo initialsetup[3];
struct gameinfo setupC1[16];
struct gameinfo setupC2[12];
struct gameinfo setupC3[12];


void displaythequestion(char* category, int value);
void already_answered(char *category, int value);
int valid_answer(char *category, int value, char *answer);
bool isGameFinished();

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array

    int i = 0;

	for (int c = 0; c < 3; c++)
	{
		initialsetup[i].questionCategory = gameCategories[c];


		for (int q = 0; q < 4; q++)
		{

			setupC1[i].question = cat1Questions[q];
			setupC1[i].answer = cat1Answers[q];
			setupC1[i].value = questionValues[q];
			setupC1[i].isAnswered = wasQuestionAnswered[q];

			setupC2[i].question = cat2Questions[q];
			setupC2[i].answer = cat2Answers[q];
			setupC2[i].value = questionValues[q];
			setupC2[i].isAnswered = wasQuestionAnswered[q];

			setupC3[i].question = cat3Questions[q];
			setupC3[i].answer = cat3Answers[q];
			setupC3[i].value = questionValues[q];
			setupC3[i].isAnswered = wasQuestionAnswered[q];


			i++;
		}
	}
}



// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void) {
		printf("\n");
    // print categories and dollar values for each unanswered question in questions array
		for (int i = 0; i < 3; i++) {
			printf("%s	", gameCategories[i]);
		}
		printf("\n");
		for (int j = 3; j > -1; j--) {
			for (int k = 0; k < 3; k ++) {
				printf("%d	", questionValues[j]);
			}
			printf("\n\n");
		}
}

// Displays the question for the category and dollar value
void displaythequestion(char* category, int value)
{
	char* compare;
	int failtofind = 0;
	int i;
	int questionDisplayed = (value / 100) - 1;
	char* answer;

	for (i = 0; i < 3; i++)
	{
		initialsetup[i].questionCategory = gameCategories[i];
		compare = initialsetup[i].questionCategory;

		if (strcmp(category, compare) == 0)
		{
			failtofind = 1;
			break;
		}
	}

	if (failtofind == 0)
	{
		printf("Error! The category isn't available\n");
	}

	else
	{
		already_answered(category, value);

		if (i == 0)
		{
			printf("%s: ",setupC1[questionDisplayed].question);
			//scanf ("%s\n", answer);
		}

		else if (i == 1)
		{
			printf("%s: ",setupC2[questionDisplayed].question);
			//scanf ("%s\n", answer);
		}

		else if (i == 2)
		{
			printf("%s: ",setupC3[questionDisplayed].question);
			//scanf ("%s\n", answer);
		}

	}


	return;

}


// Returns true if the answer is correct for the question for that category and dollar value
/*
int valid_answer(char *category, int value, char *answer)
{
	int questionDisplayed = (value / 100) - 1;
    // Look into string comparison functions
    if (strcmp(category, "Celebs") == 0 && strcmp(setupC1[questionDisplayed].answer, answer) == 0)
		{
			return value;
		}

	else if (strcmp(category, "Celebs") == 0 && strcmp(setupC1[questionDisplayed].answer, answer) != 0)
		{
			return value * -1;
		}

	else if (strcmp(category, "Movies") == 0 && strcmp(setupC2[questionDisplayed].answer, answer) == 0)
		{
			return value;
		}

	else if (strcmp(category, "Movies") == 0 && strcmp(setupC2[questionDisplayed].answer, answer) != 0)
		{
			return value * -1;
		}

	else if (strcmp(category, "Games") == 0 && strcmp(setupC3[questionDisplayed].answer, answer) == 0)
		{
			return value;
		}

	else if (strcmp(category, "Games") == 0 && strcmp(setupC3[questionDisplayed].answer, answer) != 0)
		{
			return value * -1;
		}


}
*/

// Returns true if the question has already been answered
void already_answered(char *category, int value)
{
	int questionDisplayed = (value / 100) - 1;
		if (strcmp(category, "Celebs") == 0 && setupC1[questionDisplayed].isAnswered == 0)
		{
			setupC1[questionDisplayed].isAnswered = 1;
		}

		else if (strcmp(category, "Celebs") == 0 && setupC1[questionDisplayed].isAnswered == 1)
		{
			printf("Error! That question was already answered\n");
		}

		else if (strcmp(category, "Movies") == 0 && setupC2[questionDisplayed].isAnswered == 0)
		{
			setupC2[questionDisplayed].isAnswered = 1;
		}

		else if (strcmp(category, "Movies") == 0 && setupC2[questionDisplayed].isAnswered == 1)
		{
			printf("Error! That question was already answered\n");
		}

		else if (strcmp(category, "Games") == 0 && setupC3[questionDisplayed].isAnswered == 0)
		{
			setupC3[questionDisplayed].isAnswered = 1;
		}

		else if (strcmp(category, "Games") == 0 && setupC2[questionDisplayed].isAnswered == 1)
		{
			printf("Error! That question was already answered\n");
		}

    // lookup the question and see if it's already been marked as answered

}

bool isGameFinished()
{
	for (int i = 0; i < 4; i++)
	{
		if (setupC1[i].isAnswered == 0 || setupC2[i].isAnswered == 0 || setupC3[i].isAnswered == 0)
		{
			return false;
		}
	}

	return true;
}

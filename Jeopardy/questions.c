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
#include "questions.h"



struct gameinfo 
{
	char* questionCategory;
	char* question;
	char* answer;
	int value;
	int isAnswered;
};

char* gameCategories[3] = {"Celebrities", "Movies", "Games"};

char* cat1Questions[4] = {"q1","q2","q3","q4"};

char* cat1Answers[4] = {"a1","a2","a3","a4"}; 

char* cat2Questions[4] = {"q5","q6","q7","q8"};

char* cat2Answers[4] = {"a5","a6","a7","a8"};

char* cat3Questions[4] = {"q9","q10","q11","q12"};

char* cat3Answers[4] = {"a9","a10","a11","a12"};

int questionValues[4] = {100, 200, 300, 400};

int wasQuestionAnswered[4] = {0, 0, 0, 0};


// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    struct gameinfo setupC1[12];
    struct gameinfo setupC2[12];
    struct gameinfo setupC3[12];
    int i = 0;

	for (int c = 0; c < 3; c++)
	{
		setupC1[i].questionCategory = gameCategories[c];
		//printf("%s\n",setup[i].questionCategory);
		for (int q = 0; q < 4; q++)
		{
			
			setupC1[i].question = cat1Questions[q];
			setupC1[i].answer = cat1Answers[q];

			setupC2[i].question = cat2Questions[q];
			setupC2[i].answer = cat2Answers[q];

			setupC3[i].question = cat3Questions[q];
			setupC3[i].answer = cat3Answers[q];

			
			i++;
		}
	}


	for (int j = 0; j < 4; j++)
	{
		printf("%s %s\n",setupC1[j].question, setupC1[j].answer);
		printf("%s %s\n",setupC2[j].question, setupC2[j].answer);
		printf("%s %s\n",setupC3[j].question, setupC3[j].answer);
	}

    //printf("%s\n%s\n%s\n%i\n%i\n", jayZ.questionCategory, jayZ.question, jayZ.answer, jayZ.score, jayZ.isAnswered);

}

/*
// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{/
    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{

}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    return false;
}

*/
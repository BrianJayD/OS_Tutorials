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

char* cat1Questions[4] = {"question1","question2","question3","question4"};

char* cat1Answers[4] = {"Answer1","Answer2","Answer3","Answer4"}; 

char* cat2Questions[4] = {"question1","question2","question3","question4"};

char* cat2Answers[4] = {"Answer1","Answer2","Answer3","Answer4"};

char* cat3Questions[4] = {"question1","question2","question3","question4"};

char* cat3Answers[4] = {"Answer1","Answer2","Answer3","Answer4"};

char* cat4Questions[4] = {"question1","question2","question3","question4"};

char* cat4Answers[4] = {"Answer1","Answer2","Answer3","Answer4"};

int questionValues[4] = {100, 200, 300, 400};

int wasQuestionAnswered[4] = {0, 0, 0, 0};


// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    struct gameinfo setup[12];
    int i = 0;

	for (int c = 0; c < 3; c++)
	{
		setup[i].questionCategory = gameCategories[c];
		printf("%s\n",setup[i].questionCategory);
		for (int q = 0; q < 4; q++)
		{
			
			setup[i].question = cat1Questions[q];
			setup[i].answer = cat1Answers[q];

			printf("%s\n%s\n",setup[i].question, setup[i].answer);
			i++;
		}
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
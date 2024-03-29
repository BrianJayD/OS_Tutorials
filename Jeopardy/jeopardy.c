#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "questions.c"
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define BUFFER_LEN 256

struct players
{
	char* name;
	int score;
};


int startScore = 0;
int players;
int startPlayer = 0;
int turn;

int main(int argc, char const *argv[])
{
	printf("Welcome to Jeopardy!");

	do
	{
		printf("How many players? (2-4): ");
		scanf("%d", &players);

		if (players < 2 || players > 4)
		{
			printf("Error! invalid number of players\n");

		}
	} while (players < 2 || players > 4);

	struct players playerSetup[players];
	char playerName[BUFFER_LEN];
	int count = 0;


	for (int i = 0; i < players; i++) {
		count++;
		printf("Player %d please enter in your name: ", count);
		scanf("%s", playerName);
		printf("Welcome %s!\n", playerName);

		playerSetup[i].name = playerName;
		playerSetup[i].score = startScore;
	}

	// This is to consume the newline character from scanf in order to use fgets
	int c;
	do{
    c = getchar();
	}while(c != EOF && c != '\n');

	initialize_game();
	startPlayer = rand() % players;
	turn = startPlayer;
	char catSelect[256];

	printf("%s starts.\n", playerSetup[turn].name);
	display_categories();
	do
	{
		printf("%s, please enter in a category and price: ", playerSetup[turn].name);
		fgets(catSelect, BUFFER_LEN, stdin);
		char *category = strtok(catSelect, " ");
		int price = atoi(strtok(NULL, " "));
		printf("You have chosen %s for %i\n", category, price);
		displaythequestion(category, price);


		turn++;


		if (turn > players)
		{
			turn = 0;
		}

		printf ("%s, it is now your turn\n", playerSetup[turn].name);

	} while (!isGameFinished());

	printf ("The game is over! Here are the scores:\n ");

	for (int i = 0; i < players; i++)
	{
		printf("%s %i\n", playerSetup[i].name, playerSetup[i].score);
	}

	return 0;
}

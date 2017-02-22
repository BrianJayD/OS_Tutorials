#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "players.h"
#include "questions.c"
#include <math.h>
#include <time.h>

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

	//EVERYTHING BELOW THIS LINE DOES NOT RUN


	//initialize_game();
	startPlayer = rand() % players;
	turn = startPlayer;
	char catSelect[256];
	printf("%s starts.\n", playerSetup[turn].name);
	printf("%s, please enter in a category and price: ", playerSetup[turn].name);
	fgets(catSelect, BUFFER_LEN, stdin);
	char *category = strtok(catSelect, " ");
	char *price = strtok(NULL, " ");
	printf("You have chosen %s for %s\n", category, price);



	//displaythequestion(catSelect);


	return 0;
}

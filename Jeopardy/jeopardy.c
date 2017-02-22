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

int main(int argc, char const *argv[])
{
	int players;
	int startPlayer = 0;
	int turn;
	char input[BUFFER_LEN];
	char* selection;
	char space[1] = {" "};
	

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
	int count = 1;
	

	for (int i = 0; i < players; i++)
	{
		printf("Player %d please enter in your name: ", count);
		scanf("%s", playerName);
		printf("Welcome %s!\n", playerName);

		playerSetup[i].name = playerName;
		playerSetup[i].score = startScore;
		count++;
	}

	initialize_game();


	startPlayer = rand() % players;
	turn = startPlayer;
	printf("%s starts.\n", playerSetup[turn].name);
	printf("%s, please enter in a category and price: ", playerSetup[turn].name);


//tokeizer doesnt even begin to work
		/*for (int i = 0; i < 2; i++)
		{	
			fgets(input, BUFFER_LEN, stdin);
		}
		selection = strtok(input, space);
		
		while (selection != NULL)
		{
     		printf("%s\n", selection);
     		selection = strtok(NULL, space);
     	}*/

	return 0;
}
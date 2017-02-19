#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "players.h"

#define BUFFER_LEN 256

int main(int argc, char const *argv[])
{
	int players;

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

	char *name[players];
	char playerName[BUFFER_LEN];
	int count = 1;
	int score[players];

	for (int i = 0; i < players; i++)
	{
		printf("Player %d please enter in your name: ", count);
		scanf("%s", playerName);
		printf("Welcome %s!\n", playerName);

		name[i] = playerName;
		score[i] = 0;
		count++;
	}

	return 0;
}
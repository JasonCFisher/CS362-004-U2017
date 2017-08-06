/* Author:  Jason Fisher
 * Date:  7/11/2017
 * Class:  CS362
 * Filename:  unittest1.c
 * Description:  Program tests the numHandCards function from Dominion.c
 *               Program will run tests with 1 to 4 players
 *				 Program will run tests with 1 to 10 cards for each player
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TEST_OBJ "numHandCards"

int main() {
	int seed = 500;
	int maxCards = 10;
	int numCards;
	int handCards;
    int numPlayers;
	int curPlayer;
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};

	printf("----------------- Testing Function: %s ----------------\n", TEST_OBJ);


	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);

		//loop through tests from 0 to 10 cards
		for (numCards = 0; numCards <= maxCards; numCards++) {
			printf("Testing %d Players with %d Cards in hand\n", numPlayers, numCards);
			//loop through players in the current test implementation
			for (curPlayer = 0; curPlayer < numPlayers; curPlayer++) {
				G.whoseTurn = curPlayer;//set turn to current player being tested
				G.handCount[curPlayer] = numCards;//set curPlayer handCount to numCards being tested
				/*if number returned by numHandCards = numCards being tested, print pass statement
				/ Otherwise, print fail statement*/
				handCards = numHandCards(&G);
				if (handCards == numCards)
					printf("Player %d with %d Cards:  %d Cards Reported.  PASS\n", curPlayer, numCards, handCards);
				else
					printf("Player %d with %d Cards:  %d Cards Reported.  FAIL\n", curPlayer, numCards, handCards);
			}
		}
	}

	printf("\n >>>>>>>>>> Testing %s Complete <<<<<<<<<<\n\n", TEST_OBJ);


	return 0;
}



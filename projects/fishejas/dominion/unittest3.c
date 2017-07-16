/* Author:  Jason Fisher
 * Date:  7/14/2017
 * Class:  CS362
 * Filename:  unittest3.c
 * Description:  Program tests the supplyCount function from Dominion.c
 *               Program will run tests with 1 to 4 players
 *				 Program will run tests with 10 to 0 cards in the target supply count
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TEST_OBJ "supplyCount"

int main() {
	int seed = 500;
	int supPos = 7;//supply position of adventurer card
	int curSup;//current supply count for tests
	int minSup = 0;//minimum supply count that will be tested
    int numPlayers;
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};

	printf("----------------- Testing Function: %s ----------------\n", TEST_OBJ);


	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);

		//loop through tests from 10 to 0 Adventurer cards in supply
		for (curSup = 10; curSup >= minSup; curSup--) {
			printf("Testing %d Players with %d Cards in supply\n", numPlayers, curSup);
			G.supplyCount[supPos] = curSup;//set curPlayer handCount to numCards being tested
			/*if number returned by supplyCount = curSup being tested, print pass statement
			/ Otherwise, print fail statement*/
			if (supplyCount(supPos, &G) == curSup)
				printf("supplyCount %d  :  Expected %d  :  PASS\n", G.supplyCount[supPos], curSup);
			else
				printf("supplyCount %d  :  Expected %d  :  FAIL\n", G.supplyCount[supPos], curSup);
		}
	}

	printf("\n >>>>>>>>>> Testing %s Complete <<<<<<<<<<\n\n", TEST_OBJ);


	return 0;
}



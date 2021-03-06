/* Author:  Jason Fisher
 * Date:  7/25/2017
 * Class:  CS362
 * Filename:  randomtestcard1.c
 * Description:  Program tests the Smithy card from Dominion.c
 *               Program will run tests with 4 players
 *				 Program will test current player playing smithy
 *				 Current player, deck, discard, and hand all set randomly
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TEST_OBJ "Smithy"

void setGame(struct gameState *G, int curPlayer) {
	int z;
	G->deckCount[curPlayer] = floor(Random() * (MAX_DECK/2));//set the deck count
	//fill deck with random cards
	for (z = 0; z < G->deckCount[curPlayer]; z++) {
		G->deck[curPlayer][z] = floor(Random() * (treasure_map+1));
	}
	G->discardCount[curPlayer] = floor(Random() * (MAX_DECK/2));//set the discard count
	//fill discard with random cards
	for (z = 0; z < G->deckCount[curPlayer]; z++) {
		G->discard[curPlayer][z] = floor(Random() * (treasure_map+1));
	}
	G->handCount[curPlayer] = floor(Random() * (MAX_HAND - (G->deckCount[curPlayer] + G->discardCount[curPlayer])));//set the hand count
	//fill hand with random cards
	for (z = 0; z < G->handCount[curPlayer]; z++) {
		G->hand[curPlayer][z] = floor(Random() * (treasure_map+1));
	}
}

void printResults(struct gameState *pre, struct gameState *post, int curPlayer) {
	int x;
	int supCheck = 1;
	//handCount should increase by 3 and smithy should be removed from hand
	//Therefore, total hand change should be +2
	for (x = 0; x < 4; x++) {//loop through all players to check status
		if (x == curPlayer) {//for the current player
			if (post->handCount[x] == pre->handCount[x]+2)//handCount should increase by 2, after removing smithy card from hand
				printf("handCount for Player %d %d  :  Expected %d  :  PASS\n", x, post->handCount[x], pre->handCount[x]+2);
			else
				printf("handCount for Player %d %d  :  Expected %d  :  FAIL\n", x, post->handCount[x], pre->handCount[x]+2);
			//combined deck and discard counts should decrease by 3
			if ((post->deckCount[x]+post->discardCount[x]) == (pre->deckCount[x]+pre->discardCount[x]-3))
				printf("Combined Deck and Discard for Player %d %d  :  Expected %d  :  PASS\n", x, (post->deckCount[x]+post->discardCount[x]), (pre->deckCount[x]+pre->discardCount[x]-3));
			else
				printf("Combined Deck and Discard for Player %d %d  :  Expected %d  :  FAIL\n", x, (post->deckCount[x]+post->discardCount[x]), (pre->deckCount[x]+pre->discardCount[x]-3));
		}
		else {//for all other players
			if (post->handCount[x] == pre->handCount[x])//handCount should be unchanged
				printf("handCount for Player %d %d  :  Expected %d  :  PASS\n", x, post->handCount[x], pre->handCount[x]);
			else
				printf("handCount for Player %d %d  :  Expected %d  :  FAIL\n", x, post->handCount[x], pre->handCount[x]);
			//combined deck and discard counts should be unchanged
			if ((post->deckCount[x]+post->discardCount[x]) == (pre->deckCount[x]+pre->discardCount[x]))
				printf("Combined Deck and Discard for Player %d %d  :  Expected %d  :  PASS\n", x, (post->deckCount[x]+post->discardCount[x]), (pre->deckCount[x]+pre->discardCount[x]));
			else
				printf("Combined Deck and Discard for Player %d %d  :  Expected %d  :  FAIL\n", x, (post->deckCount[x]+post->discardCount[x]), (pre->deckCount[x]+pre->discardCount[x]));
		}
	}
	for (x = 0; x < treasure_map+1; x++) {//All supply piles should be unchanged
		if (post->supplyCount[x] != pre->supplyCount[x])
			supCheck = 0;
	}
	if (supCheck != 0)
		printf("All supplyCounts unchanged.  PASS\n");
	else
		printf("supplyCounts changed.  FAIL\n");

	return;
}


int main() {
	int x;
	int numTests = 100;
	int seed = 500;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int numPlayers = 4;//number of players in each game
	int curPlayer;//current player being checked
	struct gameState G, Gcopy;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};

	printf("----------------- Testing Function: %s ----------------\n", TEST_OBJ);

	// initialize a game state
	initializeGame(numPlayers, k, seed, &G);

	//loop through tests from 2 to 4 players
	for (x = 0; x < numTests; x++) {

		curPlayer = floor(Random() * numPlayers);//set current player
		G.whoseTurn = curPlayer;

		printf("\nTest %d, Current player is %d\n", x, curPlayer);

		setGame(&G, curPlayer);//set random game conditions
		memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to test copy
		cardEffect(smithy, choice1, choice2, choice3, &Gcopy, handpos, &bonus);//call smithy function
		//check game states and print messages
		printResults(&G, &Gcopy, curPlayer);
	}


	printf("\n >>>>>>>>>> Testing %s Complete <<<<<<<<<<\n\n", TEST_OBJ);


	return 0;
}
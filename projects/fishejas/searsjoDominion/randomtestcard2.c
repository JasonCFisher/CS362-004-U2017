/* Author:  Jason Fisher
 * Date:  7/25/2017
 * Class:  CS362
 * Filename:  randomtestcard2.c
 * Description:  Program tests the Sea Hag card from Dominion.c
 *               Program will run tests with 4 players
 *				 Program will test current player playing sea hag
 *				 Current player, deck, discard, and hand all set randomly
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TEST_OBJ "Sea Hag"
#define NUM_PLAYERS	4//number of players in each game

void setGame(struct gameState *G) {
	int y;
	int z;
	for (y = 0; y < NUM_PLAYERS; y++) {
		G->deckCount[y] = floor(Random() * (MAX_DECK/2));//set the deck count
		//fill deck with random cards
		for (z = 0; z < G->deckCount[y]; z++) {
			G->deck[y][z] = floor(Random() * (treasure_map+1));
		}
		G->discardCount[y] = floor(Random() * (MAX_DECK/2));//set the discard count
		//fill discard with random cards
		for (z = 0; z < G->deckCount[y]; z++) {
			G->discard[y][z] = floor(Random() * (treasure_map+1));
		}
		G->handCount[y] = floor(Random() * (MAX_HAND - (G->deckCount[y] + G->discardCount[y])));//set the hand count
		//fill hand with random, non-curse cards
		for (z = 0; z < G->handCount[y]; z++) {
			G->hand[y][z] = floor((Random() * treasure_map) + 1);
		}
	}
}

void printResults(struct gameState *pre, struct gameState *post, int curPlayer) {
	int x;
	int supCheck = 1;
	//current player should remove sea hag from hand
	//Therefore, total hand change should decrease by 1
	for (x = 0; x < NUM_PLAYERS; x++) {//loop through all players to check status
		if (x == curPlayer) {//for the current player
			if (post->handCount[x] == pre->handCount[x]-1)//handCount should decrease by 1, after removing sea hag card from hand
				printf("handCount for Player %d %d  :  Expected %d  :  PASS\n", x, post->handCount[x], pre->handCount[x]-1);
			else
				printf("handCount for Player %d %d  :  Expected %d  :  FAIL\n", x, post->handCount[x], pre->handCount[x]-1);
			//combined deck and discard counts should be unchanged
			if ((post->deckCount[x]+post->discardCount[x]) == (pre->deckCount[x]+pre->discardCount[x]))
				printf("Combined Deck and Discard for Player %d %d  :  Expected %d  :  PASS\n", x, (post->deckCount[x]+post->discardCount[x]), (pre->deckCount[x]+pre->discardCount[x]));
			else
				printf("Combined Deck and Discard for Player %d %d  :  Expected %d  :  FAIL\n", x, (post->deckCount[x]+post->discardCount[x]), (pre->deckCount[x]+pre->discardCount[x]));
			//top deck card of current player should not be curse
			if (post->deck[x][post->deckCount[x]-1] != curse)
				printf("Top deck card for Player %d not curse  :  Expected not curse  :  PASS\n", x);
			else
				printf("Top deck card for Player %d curse  :  Expected not curse  :  FAIL\n", x);
			}
		else {//for all other players
			if (post->handCount[x] == pre->handCount[x])//handCount should be unchanged
				printf("handCount for Player %d %d  :  Expected %d  :  PASS\n", x, post->handCount[x], pre->handCount[x]);
			else
				printf("handCount for Player %d %d  :  Expected %d  :  FAIL\n", x, post->handCount[x], pre->handCount[x]);
			//combined deck and discard counts should be increase by 1
			if ((post->deckCount[x]+post->discardCount[x]) == (pre->deckCount[x]+pre->discardCount[x]+1))
				printf("Combined Deck and Discard for Player %d %d  :  Expected %d  :  PASS\n", x, (post->deckCount[x]+post->discardCount[x]), (pre->deckCount[x]+pre->discardCount[x]+1));
			else
				printf("Combined Deck and Discard for Player %d %d  :  Expected %d  :  FAIL\n", x, (post->deckCount[x]+post->discardCount[x]), (pre->deckCount[x]+pre->discardCount[x]+1));
			//top deck card of all other players should be curse
			if (post->deck[x][post->deckCount[x]-1] == curse)
				printf("Top deck card for Player %d curse  :  Expected curse  :  PASS\n", x);
			else
				printf("Top deck card for Player %d not curse  :  Expected curse  :  FAIL\n", x);
		}
	}
	if (post->supplyCount[curse] == pre->supplyCount[curse]-3)//supply count of curse cards should decrease by 3
		printf("Curse card supply count %d  :  Expected %d  :  PASS\n", post->supplyCount[curse], pre->supplyCount[curse]-3);
	else
		printf("Curse card supply count %d  :  Expected %d  :  FAIL\n", post->supplyCount[curse], pre->supplyCount[curse]-3);
	for (x = 1; x < treasure_map+1; x++) {//All other supply piles should be unchanged
		if (post->supplyCount[x] != pre->supplyCount[x])
			supCheck = 0;
	}
	if (supCheck != 0)
		printf("All other supplyCounts unchanged.  PASS\n");
	else
		printf("Other supplyCounts changed.  FAIL\n");

	return;
}


int main() {
	int x;
	int numTests = 100;
	int seed = 500;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int curPlayer;//current player being checked
	struct gameState G, Gcopy;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};

	printf("----------------- Testing Function: %s ----------------\n", TEST_OBJ);

	// initialize a game state
	initializeGame(NUM_PLAYERS, k, seed, &G);

	//loop through tests from 2 to 4 players
	for (x = 0; x < numTests; x++) {


		curPlayer = floor(Random() * NUM_PLAYERS);//set current player
		G.whoseTurn = curPlayer;

		printf("\nTest %d, Current player is %d\n", x, curPlayer);

		setGame(&G);//set random game conditions
		memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to test copy
		cardEffect(sea_hag, choice1, choice2, choice3, &Gcopy, handpos, &bonus);//call sea_hag function
		//check game states and print messages
		printResults(&G, &Gcopy, curPlayer);
	}


	printf("\n >>>>>>>>>> Testing %s Complete <<<<<<<<<<\n\n", TEST_OBJ);


	return 0;
}
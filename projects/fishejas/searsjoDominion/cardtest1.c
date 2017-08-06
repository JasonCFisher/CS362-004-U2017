/* Author:  Jason Fisher
 * Date:  7/14/2017
 * Class:  CS362
 * Filename:  cardtest1.c
 * Description:  Program tests the Smithy card from Dominion.c
 *               Program will run tests with 2 to 4 players
 *				 Program will test 1 player playing smithy
 *				 Will test with >3 cards in deck, 3 cards in deck, and <3 cards in deck
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TEST_OBJ "Smithy"

int main() {
	int x;
	int seed = 500;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int numPlayers;//number of players in each game
	int curPlayer;//current player being checked
	int supCheck;//1 if supply unchanged, 0 otherwise
	struct gameState G, Gcopy;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};

	printf("----------------- Testing Function: %s ----------------\n", TEST_OBJ);

	printf("Test Case 1:  >3 Cards in deck\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		supCheck = 1;//initialize supCheck

		printf("Testing %d Players with >3 cards in deck\n", numPlayers);
		memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to preserved copy
		cardEffect(smithy, choice1, choice2, choice3, &Gcopy, handpos, &bonus);//call smithy function
		//check game states and print messages
		//handCount should increase by 3, after removing smithy card from hand
		//Therefore, total hand change should be +2
		if (Gcopy.handCount[0] == G.handCount[0]+2)//handCount should increase by 3, after removing smithy card from hand
			printf("handCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.handCount[0], G.handCount[0]+2);
		else
			printf("handCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.handCount[0], G.handCount[0]+2);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.handCount[curPlayer] == G.handCount[curPlayer])//handCount should be unchanged
				printf("handCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
			else
				printf("handCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
		}
		if (Gcopy.deckCount[0] == G.deckCount[0]-3)//deckCount should decrease by 3
			printf("deckCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.deckCount[0], G.deckCount[0]-3);
		else
			printf("deckCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.deckCount[0], G.deckCount[0]-3);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.deckCount[curPlayer] == G.deckCount[curPlayer])//deckCount should be unchanged
				printf("deckCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
			else
				printf("deckCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
		}
		for (x = 0; x < treasure_map+1; x++) {
			if (Gcopy.supplyCount[x] != G.supplyCount[x])
				supCheck = 0;
		}
		if (supCheck != 0)
			printf("All supplyCounts unchanged.  PASS\n");
		else
			printf("supplyCounts changed.  FAIL\n");
	}

	printf("\nTest Case 2:  3 cards in deck\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		supCheck = 1;//initialize supCheck

		//discard player 0 deck down to 3 cards
		for (x = 0; x < 2; x++) {
			G.discard[0][G.discardCount[0]] = G.deck[0][G.deckCount[0]-1];
			G.deckCount[0]--;
			G.discardCount[0]++;
		}

		printf("Testing %d Players with 3 cards in deck\n", numPlayers);
		memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to preserved copy
		cardEffect(smithy, choice1, choice2, choice3, &Gcopy, handpos, &bonus);//call smithy function
		//check game states and print messages
		//handCount should increase by 3, after removing smithy card from hand
		//Therefore, total hand change should be +2
		if (Gcopy.handCount[0] == G.handCount[0]+2)//handCount should increase by 3, after removing smithy card from hand
			printf("handCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.handCount[0], G.handCount[0]+2);
		else
			printf("handCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.handCount[0], G.handCount[0]+2);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.handCount[curPlayer] == G.handCount[curPlayer])//handCount should be unchanged
				printf("handCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
			else
				printf("handCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
		}
		if (Gcopy.deckCount[0] == G.deckCount[0]-3)//deckCount should decrease by 3
			printf("deckCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.deckCount[0], G.deckCount[0]-3);
		else
			printf("deckCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.deckCount[0], G.deckCount[0]-3);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.deckCount[curPlayer] == G.deckCount[curPlayer])//deckCount should be unchanged
				printf("deckCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
			else
				printf("deckCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
		}
		for (x = 0; x < treasure_map+1; x++) {
			if (Gcopy.supplyCount[x] != G.supplyCount[x])
				supCheck = 0;
		}
		if (supCheck != 0)
			printf("All supplyCounts unchanged.  PASS\n");
		else
			printf("supplyCounts changed.  FAIL\n");
	}

		printf("\nTest Case 3:  <3 cards in deck\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		supCheck = 1;//initialize supCheck

		//discard player 0 deck down to 2 cards
		for (x = 0; x < 3; x++) {
			G.discard[0][G.discardCount[0]] = G.deck[0][G.deckCount[0]-1];
			G.deckCount[0]--;
			G.discardCount[0]++;
		}

		printf("Testing %d Players with 3 cards in deck\n", numPlayers);
		memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to preserved copy
		cardEffect(smithy, choice1, choice2, choice3, &Gcopy, handpos, &bonus);//call smithy function
		//check game states and print messages
		//handCount should increase by 3, after removing smithy card from hand
		//Therefore, total hand change should be +2
		if (Gcopy.handCount[0] == G.handCount[0]+2)//handCount should increase by 3, after removing smithy card from hand
			printf("handCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.handCount[0], G.handCount[0]+2);
		else
			printf("handCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.handCount[0], G.handCount[0]+2);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.handCount[curPlayer] == G.handCount[curPlayer])//handCount should be unchanged
				printf("handCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
			else
				printf("handCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
		}
		if (Gcopy.deckCount[0] == (G.deckCount[0] + G.discardCount[0] - 3))//discard pile should be shuffled in, then total decreases by 3
			printf("deckCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.deckCount[0], (G.deckCount[0] + G.discardCount[0] - 3));
		else
			printf("deckCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.deckCount[0], (G.deckCount[0] + G.discardCount[0] - 3));
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.deckCount[curPlayer] == G.deckCount[curPlayer])//deckCount should be unchanged
				printf("deckCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
			else
				printf("deckCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
		}
		for (x = 0; x < treasure_map+1; x++) {
			if (Gcopy.supplyCount[x] != G.supplyCount[x])
				supCheck = 0;
		}
		if (supCheck != 0)
			printf("All supplyCounts unchanged.  PASS\n");
		else
			printf("supplyCounts changed.  FAIL\n");
	}

	printf("\n >>>>>>>>>> Testing %s Complete <<<<<<<<<<\n\n", TEST_OBJ);


	return 0;
}



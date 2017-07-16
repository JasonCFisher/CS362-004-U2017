/* Author:  Jason Fisher
 * Date:  7/15/2017
 * Class:  CS362
 * Filename:  cardtest2.c
 * Description:  Program tests the Adventurer card from Dominion.c
 *               Program will run tests with 2 to 4 players
 *				 Program will test 1 player playing adventurer
 *				 Will test with >2 cards in deck, 2 cards in deck, and <2 cards in deck
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TEST_OBJ "Adventurer"

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

	printf("Test Case 1:  >2 Cards in deck\n");
	printf("Deck order top to bottom:  Copper, Estate, Estate, Copper, Copper\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		supCheck = 1;//initialize supCheck

		//Set deck order as above
		G.deck[0][0] = copper;
		G.deck[0][1] = copper;
		G.deck[0][2] = estate;
		G.deck[0][3] = estate;
		G.deck[0][4] = copper;

		printf("Testing %d Players with >2 cards in deck\n", numPlayers);
		memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to preserved copy
		cardEffect(adventurer, choice1, choice2, choice3, &Gcopy, handpos, &bonus);//call adventurer function
		//check game states and print messages
		//handCount should increase by 2, after removing adventurer card from hand
		//Therefore, total hand change should be +1
		if (Gcopy.handCount[0] == G.handCount[0]+1)//handCount should increase by 2, after removing adventurer card from hand
			printf("handCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.handCount[0], G.handCount[0]+1);
		else
			printf("handCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.handCount[0], G.handCount[0]+1);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.handCount[curPlayer] == G.handCount[curPlayer])//handCount should be unchanged
				printf("handCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
			else
				printf("handCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
		}
		if (Gcopy.deckCount[0] == G.deckCount[0]-4)//deckCount should decrease by 4
			printf("deckCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.deckCount[0], G.deckCount[0]-4);
		else
			printf("deckCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.deckCount[0], G.deckCount[0]-4);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.deckCount[curPlayer] == G.deckCount[curPlayer])//deckCount should be unchanged
				printf("deckCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
			else
				printf("deckCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
		}
		if (Gcopy.discardCount[0] == G.discardCount[0]+2)//discardCount should increase by 2
			printf("discardCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.discardCount[0], G.discardCount[0]+2);
		else
			printf("discardCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.discardCount[0], G.discardCount[0]+2);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.discardCount[curPlayer] == G.discardCount[curPlayer])//discardCount should be unchanged
				printf("discardCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]);
			else
				printf("discardCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]);
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

	printf("\nTest Case 2:  2 Cards in deck, both coins\n");
	printf("Deck order top to bottom:  Copper, Copper\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		supCheck = 1;//initialize supCheck

		//Set deck order as above
		G.deck[0][0] = copper;
		G.deck[0][1] = copper;
		G.deckCount[0] = 2;

		printf("Testing %d Players with 2 cards in deck, both coins\n", numPlayers);
		memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to preserved copy
		cardEffect(adventurer, choice1, choice2, choice3, &Gcopy, handpos, &bonus);//call adventurer function
		//check game states and print messages
		//handCount should increase by 2, after removing adventurer card from hand
		//Therefore, total hand change should be +1
		if (Gcopy.handCount[0] == G.handCount[0]+1)//handCount should increase by 2, after removing adventurer card from hand
			printf("handCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.handCount[0], G.handCount[0]+1);
		else
			printf("handCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.handCount[0], G.handCount[0]+1);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.handCount[curPlayer] == G.handCount[curPlayer])//handCount should be unchanged
				printf("handCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
			else
				printf("handCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
		}
		if (Gcopy.deckCount[0] == 0)//deck should be empty
			printf("deckCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.deckCount[0], 0);
		else
			printf("deckCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.deckCount[0], 0);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.deckCount[curPlayer] == G.deckCount[curPlayer])//deckCount should be unchanged
				printf("deckCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
			else
				printf("deckCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
		}
		if (Gcopy.discardCount[0] == G.discardCount[0])//discardCount should be unchanged
			printf("discardCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.discardCount[0], G.discardCount[0]);
		else
			printf("discardCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.discardCount[0], G.discardCount[0]);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.discardCount[curPlayer] == G.discardCount[curPlayer])//discardCount should be unchanged
				printf("discardCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]);
			else
				printf("discardCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]);
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

	printf("\nTest Case 3:  <2 Coins in deck, 1 coin card in discard\n");
	printf("Deck order top to bottom:  Copper, Estate, Estate, Estate, Estate\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		supCheck = 1;//initialize supCheck

		//Set deck order as above
		G.deck[0][0] = copper;
		G.deck[0][1] = estate;
		G.deck[0][2] = estate;
		G.deck[0][3] = estate;
		G.deck[0][4] = estate;
		G.discard[0][0] = copper;
		G.discardCount[0] = 1;

		printf("Testing %d Players with 1 coin in deck and 1 coin in discard\n", numPlayers);
		memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to preserved copy
		cardEffect(adventurer, choice1, choice2, choice3, &Gcopy, handpos, &bonus);//call adventurer function
		//check game states and print messages
		//handCount should increase by 2, after removing adventurer card from hand
		//Therefore, total hand change should be +1
		if (Gcopy.handCount[0] == G.handCount[0]+1)//handCount should increase by 2, after removing adventurer card from hand
			printf("handCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.handCount[0], G.handCount[0]+1);
		else
			printf("handCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.handCount[0], G.handCount[0]+1);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.handCount[curPlayer] == G.handCount[curPlayer])//handCount should be unchanged
				printf("handCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
			else
				printf("handCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
		}
		if (Gcopy.deckCount[0] == G.deckCount[0]-5)//deckCount should be 0
			printf("deckCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.deckCount[0], G.deckCount[0]-5);
		else
			printf("deckCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.deckCount[0], G.deckCount[0]-5);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.deckCount[curPlayer] == G.deckCount[curPlayer])//deckCount should be unchanged
				printf("deckCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
			else
				printf("deckCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
		}
		if (Gcopy.discardCount[0] == 4)//discardCount should be 4 (4 estates drawn)
			printf("discardCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.discardCount[0], 4);
		else
			printf("discardCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.discardCount[0], 4);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.discardCount[curPlayer] == G.discardCount[curPlayer])//discardCount should be unchanged
				printf("discardCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]);
			else
				printf("discardCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]);
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



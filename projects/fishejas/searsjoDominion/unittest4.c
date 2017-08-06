/* Author:  Jason Fisher
 * Date:  7/14/2017
 * Class:  CS362
 * Filename:  unittest4.c
 * Description:  Program tests the discardCard function from Dominion.c
 *               Program will run tests with 1 to 4 players
 *				 Program will test 1 player discarding from 1st position in hand
 *				 Player will discard down to 0 cards in hand
 *				 Discard with 0 cards in hand will be tested
 *				 Both discard and trash flags will be tested
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TEST_OBJ "discardCard"

int main() {
	int x;
	int seed = 500;
	int handStart[5] = {7, 6, 5, 4, 3};//start hand with adventurer, gold, silver, copper, province
	int hCountStart = 5;//hand count for tests
    int numPlayers;
	struct gameState G, Gcopy;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};

	printf("----------------- Testing Function: %s ----------------\n", TEST_OBJ);

	printf("Test Case 1:  Trash Function\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);

		//set player 1 hand to starting values
		for (x=0; x<hCountStart; x++) {
			G.hand[0][x] = handStart[x];
		}
		G.handCount[0] = hCountStart;

		//loop through hand to trash cards one at a time from 1st position
		for (x = 0; x < hCountStart; x++) {
			printf("Testing %d Players with %d Cards in player 1 hand\n", numPlayers, G.handCount[0]);
			memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to preserved copy
			discardCard(0, 0, &G, 1);//Trash card in 1st position
			//check game states and print messages
			if (Gcopy.handCount[0] > 1) {//Check to see if we started with more than 1 card in the hand
				if (G.hand[0][0] == Gcopy.hand[0][Gcopy.handCount[0]-1])//if card moved from end of hand to index 0
					printf("Card Index %d  :  Expected %d  :  PASS\n", G.hand[0][0], Gcopy.hand[0][Gcopy.handCount[0]-1]);
				else
					printf("Card Index %d  :  Expected %d  :  FAIL\n", G.hand[0][0], Gcopy.hand[0][Gcopy.handCount[0]-1]);
			}
			else {//if there was only 1 card in the hand
				if (G.hand[0][0] == -1)//if card moved from end of hand to index 0
					printf("Card Index %d  :  Expected %d  :  PASS\n", G.hand[0][0], -1);
				else
					printf("Card Index %d  :  Expected %d  :  FAIL\n", G.hand[0][0], -1);
			}
			if (G.handCount[0] == Gcopy.handCount[0]-1)//if handCount decremented
				printf("handCount %d  :  Expected %d  :  PASS\n", G.handCount[0], Gcopy.handCount[0]-1);
			else
				printf("handCount %d  :  Expected %d  :  FAIL\n", G.handCount[0], Gcopy.handCount[0]-1);
			if (G.playedCardCount == Gcopy.playedCardCount)//if playedCardCount did not change
				printf("playedCardCount %d  :  Expected %d  :  PASS\n", G.playedCardCount, Gcopy.playedCardCount);
			else
				printf("playedCardCount %d  :  Expected %d  :  FAIL\n", G.playedCardCount, Gcopy.playedCardCount);
			if (G.discardCount[0] == Gcopy.discardCount[0])//if discardCount did not change
				printf("discardCount %d  :  Expected %d  :  PASS\n", G.discardCount[0], Gcopy.discardCount[0]);
			else
				printf("discardCount %d  :  Expected %d  :  FAIL\n", G.discardCount[0], Gcopy.discardCount[0]);
			if (G.hand[0][G.handCount[0]] == -1)//if previous last card in hand is now -1
				printf("Value at hand index %d %d  :  Expected %d  :  PASS\n", G.handCount[0], G.hand[0][G.handCount[0]], -1);
			else
				printf("Value at hand index %d %d  :  Expected %d  :  FAIL\n", G.handCount[0], G.hand[0][G.handCount[0]], -1);
		}
	}

	printf("\nTest Case 2:  Discard Function\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);

		//set player 1 hand to starting values
		for (x=0; x<hCountStart; x++) {
			G.hand[0][x] = handStart[x];
		}
		G.handCount[0] = hCountStart;

		//loop through hand to trash cards one at a time from 1st position
		for (x = 0; x < hCountStart; x++) {
			printf("Testing %d Players with %d Cards in player 1 hand\n", numPlayers, G.handCount[0]);
			memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to preserved copy
			discardCard(0, 0, &G, 0);//Discard card in 1st position
			//check game states and print messages
			if (Gcopy.handCount[0] > 1) {//Check to see if we started with more than 1 card in the hand
				if (G.hand[0][0] == Gcopy.hand[0][Gcopy.handCount[0]-1])//if card moved from end of hand to index 0
					printf("Card Index %d  :  Expected %d  :  PASS\n", G.hand[0][0], Gcopy.hand[0][Gcopy.handCount[0]-1]);
				else
					printf("Card Index %d  :  Expected %d  :  FAIL\n", G.hand[0][0], Gcopy.hand[0][Gcopy.handCount[0]-1]);
			}
			else {//if there was only 1 card in the hand
				if (G.hand[0][0] == -1)//if card moved from end of hand to index 0
					printf("Card Index %d  :  Expected %d  :  PASS\n", G.hand[0][0], -1);
				else
					printf("Card Index %d  :  Expected %d  :  FAIL\n", G.hand[0][0], -1);
			}
			if (G.handCount[0] == Gcopy.handCount[0]-1)//if handCount decremented
				printf("handCount %d  :  Expected %d  :  PASS\n", G.handCount[0], Gcopy.handCount[0]-1);
			else
				printf("handCount %d  :  Expected %d  :  FAIL\n", G.handCount[0], Gcopy.handCount[0]-1);
			if (G.playedCardCount == Gcopy.playedCardCount+1)//if playedCardCount incremented
				printf("playedCardCount %d  :  Expected %d  :  PASS\n", G.playedCardCount, Gcopy.playedCardCount+1);
			else
				printf("playedCardCount %d  :  Expected %d  :  FAIL\n", G.playedCardCount, Gcopy.playedCardCount+1);
			if (G.discardCount[0] == Gcopy.discardCount[0])//if discardCount did not change
				printf("discardCount %d  :  Expected %d  :  PASS\n", G.discardCount[0], Gcopy.discardCount[0]);
			else
				printf("discardCount %d  :  Expected %d  :  FAIL\n", G.discardCount[0], Gcopy.discardCount[0]);
			if (G.hand[0][G.handCount[0]] == -1)//if previous last card in hand is now -1
				printf("Value at hand index %d %d  :  Expected %d  :  PASS\n", G.handCount[0], G.hand[0][G.handCount[0]], -1);
			else
				printf("Value at hand index %d %d  :  Expected %d  :  FAIL\n", G.handCount[0], G.hand[0][G.handCount[0]], -1);
		}
	}

	printf("\n >>>>>>>>>> Testing %s Complete <<<<<<<<<<\n\n", TEST_OBJ);


	return 0;
}



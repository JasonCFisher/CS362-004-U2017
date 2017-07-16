/* Author:  Jason Fisher
 * Date:  7/15/2017
 * Class:  CS362
 * Filename:  cardtest3.c
 * Description:  Program tests the Village card from Dominion.c
 *               Program will run tests with 2 to 4 players
 *				 Program will test 1 player playing village
 *				 Will test with >=1 card in deck with 1 action
 *				 Will test with 0 cards in deck, >=1 card in discard, and 1 action
 *				 Will test with >= 1 card in deck and >1 actions
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TEST_OBJ "Village"

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

	printf("Test Case 1:  >=1 Card in deck, 1 action\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		supCheck = 1;//initialize supCheck

		printf("Testing %d Players with >=1 card in deck, 1 action\n", numPlayers);
		memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to preserved copy
		cardEffect(village, choice1, choice2, choice3, &Gcopy, handpos, &bonus);//call village function
		//check game states and print messages
		//handCount should increase by 1, after removing village card from hand
		//Therefore, total hand count should be unchanged
		if (Gcopy.handCount[0] == G.handCount[0])//handCount should be unchanged
			printf("handCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.handCount[0], G.handCount[0]);
		else
			printf("handCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.handCount[0], G.handCount[0]);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.handCount[curPlayer] == G.handCount[curPlayer])//handCount should be unchanged
				printf("handCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
			else
				printf("handCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
		}
		if (Gcopy.deckCount[0] == G.deckCount[0]-1)//deckCount should decrease by 1
			printf("deckCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.deckCount[0], G.deckCount[0]-1);
		else
			printf("deckCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.deckCount[0], G.deckCount[0]-1);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.deckCount[curPlayer] == G.deckCount[curPlayer])//deckCount should be unchanged
				printf("deckCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
			else
				printf("deckCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
		}
		//numActions should be orginal state numActions+1
		//1 action spent to use card, 2 actions gained from card
		//net change in numActions is +1
		if (Gcopy.numActions == G.numActions+1)//numActions should be 
			printf("numActions %d  :  Expected %d  :  PASS\n", Gcopy.numActions, G.numActions+1);
		else
			printf("numActions %d  :  Expected %d  :  FAIL\n", Gcopy.numActions, G.numActions+1);
		for (x = 0; x < treasure_map+1; x++) {
			if (Gcopy.supplyCount[x] != G.supplyCount[x])
				supCheck = 0;
		}
		if (supCheck != 0)
			printf("All supplyCounts unchanged.  PASS\n");
		else
			printf("supplyCounts changed.  FAIL\n");
	}

	printf("\nTest Case 2:  <1 Card in deck, 1 action\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		supCheck = 1;//initialize supCheck

		//discard player 0 deck down to 0 cards
		for (x = 0; x < 5; x++) {
			G.discard[0][G.discardCount[0]] = G.deck[0][G.deckCount[0]-1];
			G.deckCount[0]--;
			G.discardCount[0]++;
		}

		printf("Testing %d Players with <1 card in deck, 1 action\n", numPlayers);
		memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to preserved copy
		cardEffect(village, choice1, choice2, choice3, &Gcopy, handpos, &bonus);//call village function
		//check game states and print messages
		//handCount should increase by 1, after removing village card from hand
		//Therefore, total hand count should be unchanged
		if (Gcopy.handCount[0] == G.handCount[0])//handCount should be unchanged
			printf("handCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.handCount[0], G.handCount[0]);
		else
			printf("handCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.handCount[0], G.handCount[0]);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.handCount[curPlayer] == G.handCount[curPlayer])//handCount should be unchanged
				printf("handCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
			else
				printf("handCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
		}
		if (Gcopy.deckCount[0] == (G.deckCount[0] + G.discardCount[0] - 1))//deckCount now include discardCount, -1 for drawn card
			printf("deckCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.deckCount[0], (G.deckCount[0] + G.discardCount[0] - 1));
		else
			printf("deckCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.deckCount[0], (G.deckCount[0] + G.discardCount[0] - 1));
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.deckCount[curPlayer] == G.deckCount[curPlayer])//deckCount should be unchanged
				printf("deckCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
			else
				printf("deckCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
		}
		//numActions should be orginal state numActions+1
		//1 action spent to use card, 2 actions gained from card
		//net change in numActions is +1
		if (Gcopy.numActions == G.numActions+1)//numActions should be 
			printf("numActions %d  :  Expected %d  :  PASS\n", Gcopy.numActions, G.numActions+1);
		else
			printf("numActions %d  :  Expected %d  :  FAIL\n", Gcopy.numActions, G.numActions+1);
		for (x = 0; x < treasure_map+1; x++) {
			if (Gcopy.supplyCount[x] != G.supplyCount[x])
				supCheck = 0;
		}
		if (supCheck != 0)
			printf("All supplyCounts unchanged.  PASS\n");
		else
			printf("supplyCounts changed.  FAIL\n");
	}

	printf("\nTest Case 3:  >=1 Card in deck, >1 actions\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		supCheck = 1;//initialize supCheck

		G.numActions = 3;//set starting numActions to 3

		printf("Testing %d Players with <1 card in deck, >1 actions\n", numPlayers);
		memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to preserved copy
		cardEffect(village, choice1, choice2, choice3, &Gcopy, handpos, &bonus);//call village function
		//check game states and print messages
		//handCount should increase by 1, after removing village card from hand
		//Therefore, total hand count should be unchanged
		if (Gcopy.handCount[0] == G.handCount[0])//handCount should be unchanged
			printf("handCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.handCount[0], G.handCount[0]);
		else
			printf("handCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.handCount[0], G.handCount[0]);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.handCount[curPlayer] == G.handCount[curPlayer])//handCount should be unchanged
				printf("handCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
			else
				printf("handCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.handCount[curPlayer], G.handCount[curPlayer]);
		}
		if (Gcopy.deckCount[0] == (G.deckCount[0] + G.discardCount[0] - 1))//deckCount now include discardCount, -1 for drawn card
			printf("deckCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.deckCount[0], (G.deckCount[0] + G.discardCount[0] - 1));
		else
			printf("deckCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.deckCount[0], (G.deckCount[0] + G.discardCount[0] - 1));
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.deckCount[curPlayer] == G.deckCount[curPlayer])//deckCount should be unchanged
				printf("deckCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
			else
				printf("deckCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
		}
		//numActions should be orginal state numActions+1
		//1 action spent to use card, 2 actions gained from card
		//net change in numActions is +1
		if (Gcopy.numActions == G.numActions+1)//numActions should be 
			printf("numActions %d  :  Expected %d  :  PASS\n", Gcopy.numActions, G.numActions+1);
		else
			printf("numActions %d  :  Expected %d  :  FAIL\n", Gcopy.numActions, G.numActions+1);
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



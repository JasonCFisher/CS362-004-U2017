/* Author:  Jason Fisher
 * Date:  7/15/2017
 * Class:  CS362
 * Filename:  cardtest4.c
 * Description:  Program tests the Sea Hag card from Dominion.c
 *               Program will run tests with 2 to 4 players
 *				 Program will test 1 player playing Sea Hag
 *				 Will test with >=1 card in all players decks
 *				 Will test with 0 cards in all players decks
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TEST_OBJ "Sea Hag"

int main() {
	int x, y;
	int seed = 500;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int startDeck[4] = {5, 10, 10, 10};
    int numPlayers;//number of players in each game
	int curPlayer;//current player being checked
	int supCheck;//1 if supply unchanged, 0 otherwise
	struct gameState G, Gcopy;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};

	printf("----------------- Testing Function: %s ----------------\n", TEST_OBJ);

	printf("Test Case 1:  >=1 Card in all players' decks\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		supCheck = 1;//initialize supCheck

		printf("Testing %d Players with >=1 card in all decks\n", numPlayers);
		memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to preserved copy
		cardEffect(sea_hag, choice1, choice2, choice3, &Gcopy, handpos, &bonus);//call sea_hag function
		//check game states and print messages
		for (curPlayer = 0; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.deckCount[curPlayer] == G.deckCount[curPlayer])//deckCount should be unchanged for all players
				printf("deckCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
			else
				printf("deckCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.deckCount[curPlayer], G.deckCount[curPlayer]);
		}
		if (Gcopy.discardCount[0] == G.discardCount[0])//discardCount for player 0 should be unchanged
			printf("discardCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.discardCount[0], G.discardCount[0]);
		else
			printf("discardCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.discardCount[0], G.discardCount[0]);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.discardCount[curPlayer] == G.discardCount[curPlayer]+1)//discardCount should increase by 1
				printf("discardCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]+1);
			else
				printf("discardCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]+1);
		}
		if (Gcopy.deck[0][Gcopy.deckCount[0]-1] != curse)//top deck card of player 0 should not be curse
			printf("Top deck card for Player 0 not curse  :  Expected not curse  :  PASS\n");
		else
			printf("Top deck card for Player 0 curse  :  Expected not curse  :  FAIL\n");
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.deck[curPlayer][Gcopy.deckCount[curPlayer]-1] == curse)//top deck card for other players should be curse
				printf("Top deck card for Player %d curse  :  Expected curse  :  PASS\n", curPlayer);
			else
				printf("Top deck card for Player %d not curse  :  Expected curse  :  FAIL\n", curPlayer);
		}
		if (Gcopy.supplyCount[0] == G.supplyCount[0]-numPlayers)//check that curse cards were used
			printf("Curse cards decreased as expected:  FAIL\n");
		else
			printf("Curse cards did not decrease as expected:  FAIL\n");
		for (x = 0; x < treasure_map+1; x++) {
			if (Gcopy.supplyCount[x] != G.supplyCount[x])
				supCheck = 0;
		}
		if (supCheck != 0)
			printf("All supplyCounts unchanged.  PASS\n");
		else
			printf("supplyCounts changed.  FAIL\n");
	}


	printf("\nTest Case 2:  <1 Card in all players' decks\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		supCheck = 1;//initialize supCheck

		//Move all cards in all decks to discard piles
		for (x = 0; x < numPlayers; x++) {
			for (y = 0; y < startDeck[x]; y++) {
				G.discard[x][G.discardCount[x]] = G.deck[x][G.deckCount[x]-1];
				G.deckCount[x]--;
				G.discardCount[x]++;
			}
		}

		printf("Testing %d Players with <1 card in all decks\n", numPlayers);
		memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to preserved copy
		cardEffect(sea_hag, choice1, choice2, choice3, &Gcopy, handpos, &bonus);//call sea_hag function
		//check game states and print messages
		if (Gcopy.deckCount[0] == G.deckCount[0])//deckCount should be unchanged for current player
			printf("deckCount for Player %d %d  :  Expected %d  :  PASS\n", 0, Gcopy.deckCount[0], G.deckCount[0]);
		else
			printf("deckCount for Player %d %d  :  Expected %d  :  FAIL\n", 0, Gcopy.deckCount[0], G.deckCount[0]);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.deckCount[curPlayer] == (G.deckCount[curPlayer] + G.discardCount[curPlayer]))//deck should now include discard pile for all other players
				printf("deckCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.deckCount[curPlayer], (G.deckCount[curPlayer] + G.discardCount[curPlayer]));
			else
				printf("deckCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.deckCount[curPlayer], (G.deckCount[curPlayer] + G.discardCount[curPlayer]));
		}
		if (Gcopy.discardCount[0] == G.discardCount[0])//discardCount for player 0 should be unchanged
			printf("discardCount for Player 0 %d  :  Expected %d  :  PASS\n", Gcopy.discardCount[0], G.discardCount[0]);
		else
			printf("discardCount for Player 0 %d  :  Expected %d  :  FAIL\n", Gcopy.discardCount[0], G.discardCount[0]);
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.discardCount[curPlayer] == 1)//discardCount should be 1 for all other players
				printf("discardCount for Player %d %d  :  Expected %d  :  PASS\n", curPlayer, Gcopy.discardCount[curPlayer], 1);
			else
				printf("discardCount for Player %d %d  :  Expected %d  :  FAIL\n", curPlayer, Gcopy.discardCount[curPlayer], 1);
		}
		if (Gcopy.deck[0][Gcopy.deckCount[0]-1] != curse)//top deck card of player 0 should not be curse
			printf("Top deck card for Player 0 not curse  :  Expected not curse  :  PASS\n");
		else
			printf("Top deck card for Player 0 curse  :  Expected not curse  :  FAIL\n");
		for (curPlayer = 1; curPlayer < numPlayers; curPlayer++) {
			if (Gcopy.deck[curPlayer][Gcopy.deckCount[curPlayer]-1] == curse)//top deck card for other players should be curse
				printf("Top deck card for Player %d curse  :  Expected curse  :  PASS\n", curPlayer);
			else
				printf("Top deck card for Player %d not curse  :  Expected curse  :  FAIL\n", curPlayer);
		}
		if (Gcopy.supplyCount[0] == G.supplyCount[0]-numPlayers)//check that curse cards were used
			printf("Curse cards decreased as expected:  FAIL\n");
		else
			printf("Curse cards did not decrease as expected:  FAIL\n");
		for (x = 1; x < treasure_map+1; x++) {
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



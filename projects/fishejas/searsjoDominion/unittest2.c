/* Author:  Jason Fisher
 * Date:  7/13/2017
 * Class:  CS362
 * Filename:  unittest2.c
 * Description:  Program tests the buyCard function from Dominion.c
 *               Program Tests cover the following conditions:
 *					- Player has a buy left and enough money for card
 *					- Player has no buys left
 *					- Play has a buy left, but insufficient money
 *					- No cards of the type specified are left to buy
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TEST_OBJ "buyCard"

int main() {
	int seed = 500;
    int numPlayers;
	int curPlayer;
	int supPos = 7;//supply position of adventurer card
	struct gameState G, Gcopy;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};

	printf("----------------- Testing Function: %s ----------------\n", TEST_OBJ);

	printf("Test Case 1:  Sufficient Coins and Buys for Card\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);//initialize game

		G.numBuys = 1;//set buys to 1
		G.coins = getCost(supPos);//set coins to cost of target card
		G.supplyCount[supPos] = 10;//set supplyCount of Adventurer to 10
		for (curPlayer = 0; curPlayer < numPlayers; curPlayer++) {
			printf("Testing Player %d in Game with %d Players\n", curPlayer, numPlayers);
			memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to test copy
			Gcopy.whoseTurn = curPlayer;//set turn to curPlayer
			buyCard(supPos, &Gcopy);
			//check game states and print messages
			if (Gcopy.numBuys == G.numBuys-1)//numBuys has decreased by 1
				printf("Buys %d  :  Expected %d  :  PASS\n", Gcopy.numBuys, G.numBuys-1);
			else
				printf("Buys %d  :  Expected %d  :  FAIL\n", Gcopy.numBuys, G.numBuys-1);
			if (Gcopy.supplyCount[supPos] == G.supplyCount[supPos]-1)//supplyCount of card decreased by 1
				printf("Supply %d  :  Expected %d  :  PASS\n", Gcopy.supplyCount[supPos], G.supplyCount[supPos]-1);
			else
				printf("Supply %d  :  Expected %d  :  FAIL\n", Gcopy.supplyCount[supPos], G.supplyCount[supPos]-1);
			if (Gcopy.coins == G.coins-getCost(supPos))//coins decreased by cost of card
				printf("Coins %d  :  Expected %d  :  PASS\n", Gcopy.coins, G.coins-getCost(supPos));
			else
				printf("Coins %d  :  Expected %d  :  FAIL\n", Gcopy.coins, G.coins-getCost(supPos));
			if (Gcopy.discardCount[curPlayer] == G.discardCount[curPlayer]+1)//discard count increased by 1
				printf("Discard %d  :  Expected %d  :  PASS\n", Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]+1);
			else
				printf("Discard %d  :  Expected %d  :  FAIL\n", Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]+1);
		}
	}


	printf("\nTest Case 2:  No Buys Left\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);//initialize game

		G.numBuys = 0;//set buys to 0
		G.coins = getCost(supPos);//set coins to cost of target card
		G.supplyCount[supPos] = 10;//set supplyCount of Adventurer to 10
		for (curPlayer = 0; curPlayer < numPlayers; curPlayer++) {
			printf("Testing Player %d in Game with %d Players\n", curPlayer, numPlayers);
			memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to test copy
			Gcopy.whoseTurn = curPlayer;//set turn to curPlayer
			buyCard(supPos, &Gcopy);
			//check game states and print messages
			if (Gcopy.numBuys == G.numBuys)//numBuys is unchanged
				printf("Buys %d  :  Expected %d  :  PASS\n", Gcopy.numBuys, G.numBuys);
			else
				printf("Buys %d  :  Expected %d  :  FAIL\n", Gcopy.numBuys, G.numBuys);
			if (Gcopy.supplyCount[supPos] == G.supplyCount[supPos])//supplyCount is unchanged
				printf("Supply %d  :  Expected %d  :  PASS\n", Gcopy.supplyCount[supPos], G.supplyCount[supPos]);
			else
				printf("Supply %d  :  Expected %d  :  FAIL\n", Gcopy.supplyCount[supPos], G.supplyCount[supPos]);
			if (Gcopy.coins == G.coins)//coins is unchanged
				printf("Coins %d  :  Expected %d  :  PASS\n", Gcopy.coins, G.coins);
			else
				printf("Coins %d  :  Expected %d  :  FAIL\n", Gcopy.coins, G.coins);
			if (Gcopy.discardCount[curPlayer] == G.discardCount[curPlayer])//discard count unchanged
				printf("Discard %d  :  Expected %d  :  PASS\n", Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]);
			else
				printf("Discard %d  :  Expected %d  :  FAIL\n", Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]);
		}
	}


	printf("\nTest Case 3:  Sufficient Buys but Insufficient Coins\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);//initialize game

		G.numBuys = 1;//set buys to 1
		G.coins = getCost(supPos)-1;//set coins to cost of target card - 1
		G.supplyCount[supPos] = 10;//set supplyCount of Adventurer to 10
		for (curPlayer = 0; curPlayer < numPlayers; curPlayer++) {
			printf("Testing Player %d in Game with %d Players\n", curPlayer, numPlayers);
			memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to test copy
			Gcopy.whoseTurn = curPlayer;//set turn to curPlayer
			buyCard(supPos, &Gcopy);
			//check game states and print messages
			if (Gcopy.numBuys == G.numBuys)//numBuys unchanged
				printf("Buys %d  :  Expected %d  :  PASS\n", Gcopy.numBuys, G.numBuys);
			else
				printf("Buys %d  :  Expected %d  :  FAIL\n", Gcopy.numBuys, G.numBuys);
			if (Gcopy.supplyCount[supPos] == G.supplyCount[supPos])//supplyCount unchanged
				printf("Supply %d  :  Expected %d  :  PASS\n", Gcopy.supplyCount[supPos], G.supplyCount[supPos]);
			else
				printf("Supply %d  :  Expected %d  :  FAIL\n", Gcopy.supplyCount[supPos], G.supplyCount[supPos]);
			if (Gcopy.coins == G.coins)//coins unchanged
				printf("Coins %d  :  Expected %d  :  PASS\n", Gcopy.coins, G.coins);
			else
				printf("Coins %d  :  Expected %d  :  FAIL\n", Gcopy.coins, G.coins);
			if (Gcopy.discardCount[curPlayer] == G.discardCount[curPlayer])//discard count unchanged
				printf("Discard %d  :  Expected %d  :  PASS\n", Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]);
			else
				printf("Discard %d  :  Expected %d  :  FAIL\n", Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]);
		}
	}


	printf("\nTest Case 4:  No Card of Type Requested in Supply\n");

	//loop through tests from 2 to 4 players
	for (numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {

		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);//initialize game

		G.numBuys = 1;//set buys to 1
		G.coins = getCost(supPos);//set coins to cost of target card
		G.supplyCount[supPos] = 0;//set supplyCount of Adventurer to 0
		for (curPlayer = 0; curPlayer < numPlayers; curPlayer++) {
			printf("Testing Player %d in Game with %d Players\n", curPlayer, numPlayers);
			memcpy(&Gcopy, &G, sizeof(struct gameState));//copy gameState to test copy
			Gcopy.whoseTurn = curPlayer;//set turn to curPlayer
			buyCard(supPos, &Gcopy);
			//check game states and print messages
			if (Gcopy.numBuys == G.numBuys)//numBuys unchanged
				printf("Buys %d  :  Expected %d  :  PASS\n", Gcopy.numBuys, G.numBuys);
			else
				printf("Buys %d  :  Expected %d  :  FAIL\n", Gcopy.numBuys, G.numBuys);
			if (Gcopy.supplyCount[supPos] == G.supplyCount[supPos])//supplyCount unchanged
				printf("Supply %d  :  Expected %d  :  PASS\n", Gcopy.supplyCount[supPos], G.supplyCount[supPos]);
			else
				printf("Supply %d  :  Expected %d  :  FAIL\n", Gcopy.supplyCount[supPos], G.supplyCount[supPos]);
			if (Gcopy.coins == G.coins)//coins unchanged
				printf("Coins %d  :  Expected %d  :  PASS\n", Gcopy.coins, G.coins);
			else
				printf("Coins %d  :  Expected %d  :  FAIL\n", Gcopy.coins, G.coins);
			if (Gcopy.discardCount[curPlayer] == G.discardCount[curPlayer])//discard count unchanged
				printf("Discard %d  :  Expected %d  :  PASS\n", Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]);
			else
				printf("Discard %d  :  Expected %d  :  FAIL\n", Gcopy.discardCount[curPlayer], G.discardCount[curPlayer]);
		}
	}

	printf("\n >>>>>>>>>> Testing %s Complete <<<<<<<<<<\n\n", TEST_OBJ);


	return 0;
}



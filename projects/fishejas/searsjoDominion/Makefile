CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	echo "Results for Dominion Tests" > unittestresults.out
	echo "Name:  Jason Fisher;  ONID:  fishejas" >> unittestresults.out
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov -c -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtestcard.out: randomtestcard1.c randomtestcard2.c dominion.o rngs.o
	echo "Results for Dominion Tests" > randomtestadventurer.out
	echo "Name:  Jason Fisher;  ONID:  fishejas" >> randomtestadventurer.out
	echo "randomtestadventurer.c" >> randomtestadventurer.out
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	gcov -c -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	echo "Results for Dominion Tests" > randomtestcard1.out
	echo "Name:  Jason Fisher;  ONID:  fishejas" >> randomtestcard1.out
	echo "randomtestcard1.c" >> randomtestcard1.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	gcov -c -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	echo "Results for Dominion Tests" > randomtestcard2.out
	echo "Name:  Jason Fisher;  ONID:  fishejas" >> randomtestcard2.out
	echo "randomtestcard2.c" >> randomtestcard2.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	gcov -c -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out


clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

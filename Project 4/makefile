zooStats: zooStats.o zooStatsMain.o
	gcc -Wall -std=c99 zooStats.o zooStatsMain.c -lm -o zooStats
zooStats.o: zooStats.c givenA1.h
	gcc -Wall -std=c99 -Wall -std=c99 -c zooStats.c
zooStatsMain.o: zooStatsMain.c givenA1.h
	gcc -Wall -std=c99 -Wall -std=c99 -c zooStatsMain.c 
clean:
	rm *.o zooStats

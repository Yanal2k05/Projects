all: a2q1 a2q2

a2q1: q1.o q1_functions.o
	gcc -Wall -std=c99 q1.o q1_functions.o -lm -o a2q1

q1.o: q1.c q1.h
	gcc -Wall -std=c99 -c q1.c

q1_functions.o: q1_functions.c q1.h
	gcc -Wall -std=c99 -c q1_functions.c 

a2q2: q2.o q2_functions.o
	gcc -Wall -std=c99 q2.o q2_functions.o -lm -o a2q2

q2.o: q2.c q2.h
	gcc -Wall -std=c99 -c q2.c

q2_functions.o: q2_functions.c q2.h
	gcc -Wall -std=c99 -c q2_functions.c 

clean:
	rm -f *.o a2q1 a2q2
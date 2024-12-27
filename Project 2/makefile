
all: a3q1 a3q2

a3q1: a3q1_main.o a3q1_functions.o
	gcc -Wall -std=c99 a3q1_main.o a3q1_functions.o -lm -o a3q1

a3q1_main.o: a3q1_main.c a3q1_header.h
	gcc -Wall -std=c99 -c a3q1_main.c

a3q1_functions.o: a3q1_functions.c a3q1_header.h
	gcc -Wall -std=c99 -c a3q1_functions.c 

a3q2: a3q2_main.o a3q2_functions.o
	gcc -Wall -std=c99 a3q2_main.o a3q2_functions.o -lm -o a3q2

a3q2_main.o: a3q2_main.c a3q2_header.h
	gcc -Wall -std=c99 -c a3q2_main.c

a3q2_functions.o: a3q2_functions.c a3q2_header.h
	gcc -Wall -std=c99 -c a3q2_functions.c 

clean:
	rm -f *.o a3q1 a3q2





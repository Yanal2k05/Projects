myContacts: createContactsA2.o readContactsA2.o searchContactsA2.o contactsA2.o
	gcc -Wall -std=c99 createContactsA2.o readContactsA2.o searchContactsA2.o contactsA2.o -o myContacts

createContactsA2.o: createContactsA2.c givenA2.h
	gcc -Wall -std=c99 -c createContactsA2.c -o createContactsA2.o

readContactsA2.o: readContactsA2.c givenA2.h
	gcc -Wall -std=c99 -c readContactsA2.c -o readContactsA2.o

searchContactsA2.o: searchContactsA2.c givenA2.h
	gcc -Wall -std=c99 -c searchContactsA2.c -o searchContactsA2.o

contactsA2.o: contactsA2.c givenA2.h
	gcc -Wall -std=c99 -c contactsA2.c -o contactsA2.o 

clean: 
	rm *.o myContacts

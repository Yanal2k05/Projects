bin/myContacts: createContactsA2.o readContactsA2.o searchContactsA2.o contactsA2.o
	gcc -Wall -std=c99 bin/createContactsA2.o bin/readContactsA2.o bin/searchContactsA2.o bin/contactsA2.o -o bin/myContacts

createContactsA2.o: src/createContactsA2.c include/givenA2.h
	gcc -Wall -std=c99 -c src/createContactsA2.c -o bin/createContactsA2.o

readContactsA2.o: src/readContactsA2.c include/givenA2.h
	gcc -Wall -std=c99 -c src/readContactsA2.c -o bin/readContactsA2.o

searchContactsA2.o: src/searchContactsA2.c include/givenA2.h
	gcc -Wall -std=c99 -c src/searchContactsA2.c -o bin/searchContactsA2.o

contactsA2.o: src/contactsA2.c include/givenA2.h
	gcc -Wall -std=c99 -c src/contactsA2.c -o bin/contactsA2.o 

clean: 
	rm bin/*.o bin/myContacts
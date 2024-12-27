#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct contact {
   long empIdPosn;
   long firstNamePosn;
   long lastNamePosn;
   long emailPosn;
   long next;
};

void createContacts (char * fileName);

void readContacts (char * fileName);

int searchContacts (char * fileName, int keyId);

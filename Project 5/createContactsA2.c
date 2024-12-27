#include "givenA2.h"
#define SIZE 200

void createContacts(char *fileName)
{

    FILE *file = fopen(fileName, "a+b"); // Open in append and read mode for binary file
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    struct contact contacts;
    int empId;
    char *firstName, *lastName, *email;
    int fNameLen, lNameLen, emailLen;

    // Allocate memory and check immediately
    firstName = malloc(SIZE * sizeof(char));
    if (!firstName)
    {

        free(firstName);
        return;
    }

    lastName = malloc(SIZE * sizeof(char));
    if (!lastName)
    {

        free(lastName);
        return;
    }

    email = malloc(SIZE * sizeof(char));
    if (!email)
    {

        free(email);
        return;
    }

    fseek(file, 0, SEEK_END);
    long intialPosn = ftell(file); // Start position of this record

    // Employee ID
    printf("Employee Id: ");
    scanf("%d", &empId);
        while (getchar() != '\n'); // Clear input buffer

    // First Name
    printf("First Name: ");
    fgets(firstName, SIZE, stdin);
    fNameLen = strlen(firstName) + 1; //+1 for null terminator

    // Last Name
    printf("Last Name: ");
    fgets(lastName, SIZE, stdin);
    lNameLen = strlen(lastName) + 1; //+1 for null terminator

    // Email
    printf("Email: ");
    fgets(email, SIZE, stdin);
    printf("\n\n");
    emailLen = strlen(email) + 1; //+1 for null terminator

    // Calculate positions
    contacts.empIdPosn = intialPosn + sizeof(struct contact);
    contacts.firstNamePosn = contacts.empIdPosn + sizeof(empId);
    contacts.lastNamePosn = contacts.firstNamePosn + fNameLen;
    contacts.emailPosn = contacts.lastNamePosn + lNameLen;
    contacts.next = contacts.emailPosn + emailLen;

    // Write the struct
    fwrite(&contacts, sizeof(struct contact), 1, file);

    // Write the data
    fwrite(&empId, sizeof(empId), 1, file); // Employee ID
    fputs(firstName, file);
    fputc('\0', file); // First Name
    fputs(lastName, file);
    fputc('\0', file); // Last Name
    fputs(email, file);
    fputc('\0', file); // Email

    // Free dynamically allocated memory
    free(firstName);
    free(lastName);
    free(email);

    fclose(file);
}


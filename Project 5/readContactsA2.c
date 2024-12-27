/*
  Student Name: Yanal Abu Rahmeh
  Student ID: 1284819
  Due Date: March, 8, 2024
  Course: CIS*2500

  I have exclusive control over this submission via my password.
  By including this header comment, I certify that:
   1) I have read and understood the policy on academic integrity.
   2) I have completed Moodle's module on academic integrity.
   3) I have achieved at least 80% on the academic integrity quiz
  I assert that this work is my own. I have appropriate acknowledged
  any and all material that I have used, be it directly quoted or
  paraphrased. Furthermore, I certify that this assignment was written
  by me in its entirety.
*/

#include "../include/givenA2.h"

#define SIZE 200

// Function to read and display contacts from a file
void readContacts(char *fileName)
{
    FILE *file = fopen(fileName, "r"); // Opening the file for reading
    if (file == NULL)
    {
        printf("Error opening file!\n"); // Exit if file cannot be opened
        return;
    }

    struct contact readContact;
    int empId;
    char *data = malloc(SIZE * sizeof(char)); // Allocating memory for data string
    if (!data)
    {
        printf("Memory allocation failed!\n"); // Exit if memory can not be allocated
        fclose(file);
        return;
    }

    while (fread(&readContact, sizeof(struct contact), 1, file) == 1) // Read one record from file
    {
        printf("****************************\n");

        // Employee ID
        fseek(file, readContact.empIdPosn, SEEK_SET);
        fread(&empId, sizeof(empId), 1, file);
        printf("Employee Id: %d\n", empId);

        // First Name
        fseek(file, readContact.firstNamePosn, SEEK_SET);
        fscanf(file, "%[^\n]%*c", data); // For file input, consuming the newline
        printf("First Name: %s\n", data);

        // Last Name
        fseek(file, readContact.lastNamePosn, SEEK_SET);
        fscanf(file, "%[^\n]%*c", data); // For file input, consuming the newline
        printf("Last Name: %s\n", data);

        // Email
        fseek(file, readContact.emailPosn, SEEK_SET);
        fscanf(file, "%[^\n]%*c", data); // For file input, consuming the newline
        printf("Email: %s\n", data);

        printf("****************************\n");

        // Move to the start of the next record
        fseek(file, readContact.next, SEEK_SET);
    }

    free(data); // Free the dynamically allocated buffer
    fclose(file);
}

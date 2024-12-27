#include "givenA2.h"
#define SIZE 200

int main(int argc, char *argv[])
{
    // Define variables
    char *fileName = argv[1]; // File name from command line argument
    int choice;
    int keyId;
    char option[SIZE];

    // Check if the correct number of arguments are passed
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]); // Display correct usage
        return 1;
    }

    do
    {
        // Prompt for entering a new contact
        printf("Do you wish to enter a new contact (Yes or No)?: ");
        scanf("%[^\n]%*c", option);

        // Check response
        if (strcmp(option, "Yes") == 0)
        {
            do
            {
                createContacts(fileName); //
                printf("Do you wish to enter a new contact (Yes or No)?: ");
                scanf("%[^\n]%*c", option);
                
            } while (strcmp(option, "Yes") == 0);
        }
        else if (strcmp(option, "No") == 0)
        {
            do
            {
                // Display options for the user
                printf("\n\nEnter a choice:\n");
                printf("1 to print, 2 to search, 3 to create more, -1 to exit: ");

                if (scanf("%d", &choice) != 1)
                {
                    printf("Error reading choice.\n");
                }
                getchar(); // Clear input buffer

                if (choice == 1)
                {
                    // Printcontacts
                    printf("\nPrinting Employee records saved on file: \n");
                    readContacts(fileName);
                }
                else if (choice == 2)
                {
                    do
                    {
                        printf("\nSearch for Employee Id? ");
                        scanf("%d", &keyId);

                        getchar(); // Clear the input buffer

                        if (keyId >= 0 && keyId <= 9999)
                        {
                            // If keyId is valid, search for it
                            if (!searchContacts(fileName, keyId))
                            {
                                printf("No match found.\n");
                            }
                            break;
                        }
                        else
                        {
                            printf("Invalid Employee ID\n");
                        }
                    } while (1); // Repeat until a valid ID is entered
                }
                else if (choice == 3)
                {
                    createContacts(fileName); // Create more contacts
                }
                else if (choice == -1)
                {
                    printf("Exiting\n"); // Exit the code
                    return 0;
                }
                else
                {
                    printf("Invalid choice. Please enter a valid option.\n"); // Invalid input is given
                }
            } while (choice != -1);
        }
    } while (strcmp(option, "Yes") != 0 || strcmp(option, "No") != 0); // Loop until a valid option is given

    return 0;
}


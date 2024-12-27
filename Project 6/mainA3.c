#include "headerA3.h"

int main()
{
    struct car *head = NULL; // Head pointer for the linked list of cars
    int choice, carId, position, place, station, option, len, dotPosition, insertPositions, tempIndex, originalIndex;
    char fileName[MAX_LENGTH] = "inputFile.txt"; // Filename to load car data from
    char modelType[100];                         // Buffer to store model type input from user
    char formattedPrice[64];
    int commasInserted = 0;

    // Main loop of the program
    while (1)
    {

        // Display the menu options
        printf("Menu:\n");
        printf("1. Add data on a new car \n");
        printf("2. Load data on cars from a given text file\n");
        printf("3. Print data of all cars\n");
        printf("4. Print data of the nth car\n");
        printf("5. Search car data based on carId \n");
        printf("6. Search car data based on model and type\n");
        printf("7. Count the total number of cars in the list\n");
        printf("8. Sort the cars in the list based on carId\n");
        printf("9. Remove data of the nth car\n");
        printf("10. Remove all car data\n");
        printf("11. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character after choice input

        // Handle invalid choice correctly
        if (choice < 1 || choice > 11)
        {
            printf("Invalid choice. Please select a valid option.\n");
            continue; // This allows the user to try again without exiting
        }

        if (choice == 11)
        {
            printf("Exiting program.\n");
            break; // Exit loop and program
        }

        // Handle user's choice
        switch (choice)
        {

        case 1:
            // Add a new car to the list
            addNewCar(&head);
            printf("\n");
            break;
        case 2:

            // Load car data from file
            loadCarData(&head, fileName);

            // Print the loaded car data
            printf("Loaded Car Data:\n");
            struct car *current = head;
            while (current != NULL)
            {
                printf("Year: %d\n", current->year);
                printf("Price: %.2f\n", current->price);
                printf("Model: %s\n", current->model);
                printf("Type: %s\n", current->type);
                printf("ID: %d\n", current->carId);
                printf("\n");

                current = current->nextCar;
            }

            printf("\n");

            break;
        case 3:

            // Print all car data
            printAll(head);
            printf("\n");

            break;

        case 4:

            // Ask user for position and prints the data of the car at that position in the list
            printf("Enter a position: ");
            scanf("%d", &position);
            printOne(head, position);
            printf("\n");

            break;

        case 5:
            // Searches for a car by its ID. If found, prints the car's details, including a formatted price
            printf("\nEnter a car ID: ");
            scanf("%d", &carId);

            place = lookForCarId(head, carId);

            if (place == -1)
            {
                printf("Car ID not found.\n");
            }
            else
            {
                // Traverse to the found position and print car details
                struct car *current = head;
                for (int i = 1; i < place; i++)
                {
                    current = current->nextCar;
                }

                sprintf(formattedPrice, "%.2f", current->price); // Convert to string with 2 decimal places
                len = strlen(formattedPrice);
                dotPosition = strchr(formattedPrice, '.') - formattedPrice;
                insertPositions = (dotPosition - 1) / 3; // Number of commas to insert

                if (insertPositions > 0)
                {
                    char temp[64] = {0};               // Temporary buffer for formatted price with commas
                    tempIndex = len + insertPositions; // Adjust length for commas
                    temp[tempIndex] = '\0';            // Null-terminate
                    originalIndex = len - 1;

                    for (int i = 0; i < len - dotPosition; ++i)
                    { // Copy decimals and dot without changes
                        temp[--tempIndex] = formattedPrice[originalIndex--];
                    }

                    while (originalIndex >= 0)
                    { // Copy rest of the string with commas
                        temp[--tempIndex] = formattedPrice[originalIndex--];
                        if ((++commasInserted % 3) == 0 && originalIndex >= 0)
                        {
                            temp[--tempIndex] = ','; // Insert comma every 3 digits
                        }
                    }

                    // Print car details
                    printf("Car id: %d\n", current->carId);
                    printf("Model: %s\n", current->model);
                    printf("Type: %s\n", current->type);
                    printf("Price: CDN $%s\n", temp);
                }
                else
                {
                    // Print car details without needing to format price
                    printf("Car id: %d\n", current->carId);
                    printf("Model: %s\n", current->model);
                    printf("Type: %s\n", current->type);
                    printf("Price: CDN $%s\n", formattedPrice);
                }

                printf("Year of Manufacture: %d\n", current->year);
            }

            printf("\n");

            break;

        case 6:

            // Prompts the user for a car model and type, searches the list, and prints the matching car's details
            printf("Enter the model and type (separated by a space): ");
            fgets(modelType, 100, stdin);
            modelType[strcspn(modelType, "\n")] = '\0'; // Remove potential newline

            station = lookForCarModelType(head, modelType);

            if (station != -1)
            {
                struct car *current = head;
                for (int i = 1; i < station; i++)
                {
                    current = current->nextCar;
                }

                // Large enough buffer
                sprintf(formattedPrice, "%.2f", current->price); // Convert to string with 2 decimal places
                len = strlen(formattedPrice);
                dotPosition = strchr(formattedPrice, '.') - formattedPrice;
                insertPositions = (dotPosition - 1) / 3; // Number of commas to insert

                if (insertPositions > 0)
                {
                    char temp[64] = {0};               // Temporary buffer for formatted price with commas
                    tempIndex = len + insertPositions; // Adjust length for commas
                    temp[tempIndex] = '\0';            // Null-terminate
                    originalIndex = len - 1;

                    for (int i = 0; i < len - dotPosition; ++i)
                    { // Copy decimals and dot without changes
                        temp[--tempIndex] = formattedPrice[originalIndex--];
                    }

                    while (originalIndex >= 0)
                    { // Copy rest of the string with commas
                        temp[--tempIndex] = formattedPrice[originalIndex--];
                        if ((++commasInserted % 3) == 0 && originalIndex >= 0)
                        {
                            temp[--tempIndex] = ','; // Insert comma every 3 digits
                        }
                    }

                    // Print car details
                    printf("Car id: %d\n", current->carId);
                    printf("Model: %s\n", current->model);
                    printf("Type: %s\n", current->type);
                    printf("Price: CDN $%s\n", temp);
                }
                else
                {
                    // Print car details without needing to format price
                    printf("Car id: %d\n", current->carId);
                    printf("Model: %s\n", current->model);
                    printf("Type: %s\n", current->type);
                    printf("Price: CDN $%s\n", formattedPrice);
                }

                printf("Year of Manufacture: %d\n", current->year);
            }
            else
            {
                printf("Car not found.\n");
            }
            break;

            printf("\n");

        case 7:

            // Counts and prints the total number of cars currently in the list
            printf("total number of cars %d \n", countCars(head));
            printf("\n");

            break;

        case 8:

            // Sorts the cars in the list by their ID in ascending order and prints the sorted list
            sortCarId(&head);
            printAll(head);
            printf("\n");

            break;

        case 9:

            // Allows the user to select and remove a car from the list by its position
            do
            {
                printf("Currently there are %d cars.\n", countCars(head)); // Prints amount of cars using countCars
                printAll(head);
                printf("Which car do you wish to remove - enter a value between 1 and %d (0 to exit): ", countCars(head));
                scanf("%d", &option);

                //  Check if input is a positive integer, otherwise prompt for valid input again.
                if (option <= 0 || option > countCars(head))
                {
                    printf("Invalid option. Please enter a valid number.\n");
                }
                else if (option > 0) // Check if it is greater than 0
                {
                    oneLessCar(&head, option);
                    printf("Car removed. There are now %d cars remaining.\n", countCars(head));
                    break;
                }
            } while (option != 0);

            printf("\n");

            break;

        case 10:

            // Removes all cars from the list
            noMoreCars(&head);
            printf("\n");

            break;

        case 11:

            // This case is handled before the switch to exit the program. Included here for completeness
            printf("Exiting");

            // Free allocated memory before exiting
            while (head != NULL)
            {
                struct car *temp = head;
                head = head->nextCar;
                free(temp);
            }
            return 0;

        default:

            // Handles any unrecognized choices by prompting the user again
            printf("Invalid option.\n");
            printf("\n");

            break;
        }
    }
    return 0;
}

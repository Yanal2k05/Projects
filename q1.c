#include "q1.h"

// Main function
int main() {

    // Initialize linked lists
    struct car *available = NULL;
    struct car *rented = NULL;
    struct car *repair = NULL;
     
    // File names
    #define AVAILABLE_FILE "available.txt"
    #define RENTED_FILE "rented.txt"
    #define REPAIR_FILE "repair.txt"

    // Read data from files into the linked lists
    read_file_into_list(AVAILABLE_FILE, &available);
    read_file_into_list(RENTED_FILE, &rented);
    read_file_into_list(REPAIR_FILE, &repair);

    // Variables
    int choice;
    char plate[7];
    int mileage, return_date;
    struct car *car = NULL;

    // Main loop
    while (1) {
        prompt(); // Display menu
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');  // Clear input buffer
            continue;
        }
    
        switch (choice) {
            case 1: // Add a new car to the available-for-rent list
                do {
                    printf("Enter plate (2-8 characters): ");
                    scanf("%s", plate);
                } while (!validate_plate(plate));

                // Check if the plate already exists in any of the lists
                if (is_plate_in_list(available, plate)) { 
                    printf("Plate already exists. Try again.\n");
                    break; // Plate already exists
                } else {
                    do {
                        printf("Enter mileage: ");
                    } while (scanf("%d", &mileage) != 1); // Loop until valid mileage input
                    insert_to_list(&available, plate, mileage, -1);
                    printf("Car %s added to available-for-rent list.\n", plate); // Add the car to the list
                }
                break;

            case 2: // Transfer from rented to available
                do {
                    printf("Enter plate: ");
                    scanf("%s", plate);
                } while (!validate_plate(plate));

                car = remove_car_from_list(&rented, plate); // Remove the car from the rented list
                if (car == NULL) {
                    printf("Car not found in rented list.\n"); 
                    break;
                }

                do {
                    printf("Enter current mileage: ");
                } while (scanf("%d", &mileage) != 1 || !validate_mileage(mileage, car->mileage)); // Loop until valid input

                double charge = profit_calculator(car->mileage, mileage); 
                printf("Car %s returned with charge: $%.2f\n", car->plate, charge); // Calculate the charge
                insert_to_list(&available, car->plate, mileage, -1); // Insert the car to the available list with return date -1

                free(car);
                break;

            case 3: // Transfer from rented to in-repair
                do {
                    printf("Enter plate: ");
                    scanf("%s", plate);
                } while (!validate_plate(plate));

                car = remove_car_from_list(&rented, plate); // Remove the car from the rented list
                if (car == NULL) {
                    printf("Car not found in rented list.\n"); 
                    break;
                }

                do {
                    printf("Enter current mileage: ");
                } while (scanf("%d", &mileage) != 1 || !validate_mileage(mileage, car->mileage)); // Loop until valid input

                charge = profit_calculator(car->mileage, mileage);
                printf("Car %s returned and sent to repair with charge: $%.2f\n", car->plate, charge);
                insert_to_list(&repair, car->plate, mileage, -1); // Set return date to -1 when moving to repair

                free(car);
                break;

            case 4: // Transfer from in-repair to available
                do {
                    printf("Enter plate: ");
                    scanf("%s", plate);
                } while (!validate_plate(plate));

                car = remove_car_from_list(&repair, plate);
                if (car == NULL) {
                    printf("Car not found in repair list.\n");
                    break;
                }

                insert_to_list(&available, car->plate, car->mileage, -1); // Set return date to -1 when moving to available

                printf("Car %s transferred from repair to available-for-rent list.\n", car->plate);
                free(car);
                break;

            case 5: // Rent the first available car
                do {
                    printf("Enter expected return date (yymmdd): ");
                } while (scanf("%d", &return_date) != 1 || !validate_return_date(return_date)); // Loop until valid input
                
                car = remove_first_from_list(&available);
                if (car == NULL) {
                    printf("No cars available for rent.\n");
                    break;
                }
                car->return_date = return_date;
                insert_to_list(&rented, car->plate, car->mileage, return_date);
                printf("Car %s rented, expected return date: %d\n", car->plate, return_date);
                free(car);
                break;

            case 6: // Print all the lists
                printf("Available for rent:\n");
                print_list(available);
                printf("\nRented:\n");
                print_list(rented);
                printf("\nIn repair:\n");
                print_list(repair);
                break;

            case 7: // Quit and save data
                write_list_to_file(AVAILABLE_FILE, available);
                write_list_to_file(RENTED_FILE, rented);
                write_list_to_file(REPAIR_FILE, repair);
                free_list(&available);
                free_list(&rented);
                free_list(&repair);
                printf("Saving data...\n");
                printf("Data saved.\n");
                printf("Exiting... Goodbye!\n");
                return 0;

            default:
                printf("Invalid transaction code. Try again.\n");
                break;
        }
    }
}

#include "q1.h"


/* function will display the primary user interface
    This is already done for you*/
void prompt(){
  printf("\nChoose a transaction:\n");
  printf("1. Add a new car to the available-for-rent list,\n");
  printf("2. Add a returned car to the available-for-rent list,\n");
  printf("3. Add a returned car to the repair list,\n");
  printf("4. Transfer a car from the repair list to the available-for-rent list,\n");
  printf("5. Rent the first available car,\n");
  printf("6. Print all the lists,\n");
  printf("7. Quit.\n");
  printf("Enter your choice: ");
}


bool validate_plate(char plate[]) {
    int len = strlen(plate);
    if (len < 2 || len > 7) {
        printf("Invalid plate. Plate number must be 2 to 8 characters long.\n");
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (!isalnum(plate[i])) {
            printf("Invalid plate. Plate number must contain only letters and numbers.\n");
            return false;
        }
    }
    return true;
}

bool validate_mileage(int current_mileage, int previous_mileage) {
    if (current_mileage < previous_mileage) {
        printf("Invalid mileage. Current mileage cannot be less than previous mileage.\n");
        return false;
    }
    return true;
}

bool validate_return_date(int return_date) {
    int month = (return_date / 100) % 100;
    int day = return_date % 100;

    // Check if month and day are in valid ranges
    if (month < 1 || month > 12) {
        printf("Invalid return date. Month must be between 1 and 12.\n");
        return false;
    }
    if (day < 1 || day > 31) {
        printf("Invalid return date. Day must be between 1 and 31.\n");
        return false;
    }
    if (return_date < 0) {
        printf("Invalid return date. Date cannot be negative.\n");
        return false;
    }

    return true;
}


/**
 * Inserts a new car into the linked list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @param mileage Integer representing the car's mileage.
 * @param return_date Integer representing the car's return date, you can have -1 represent no return date.
 * @return Pointer to the newly added car in the list.
 */
// Insert car into a list
struct car* insert_to_list(struct car **head, char plate[], int mileage, int return_date) {
    struct car *new_car = (struct car*)malloc(sizeof(struct car));
    if (new_car == NULL) {
        printf("Memory allocation failed for car with plate: %s\n", plate);
        return NULL;
    }
    strcpy(new_car->plate, plate);
    new_car->mileage = mileage;
    new_car->return_date = return_date;
    new_car->next = NULL;

    // Sorted insert by mileage or return date
    if (*head == NULL || (return_date == -1 && mileage < (*head)->mileage) || (return_date != -1 && return_date < (*head)->return_date)) {
        new_car->next = *head;
        *head = new_car;
    } else {
        struct car *current = *head;
        while (current->next != NULL && ((return_date == -1 && current->next->mileage < mileage) || (return_date != -1 && current->next->return_date < return_date))) {
            current = current->next;
        }
        new_car->next = current->next;
        current->next = new_car;
    }

    return new_car;
}

/**
 * Prints all the cars in the list.
 * @param head Pointer to the head of the list.
 * This function prints out the car details, it should not print return date if it does not exist.
 */
// Print cars in a list
void print_list(struct car *head) {
    struct car *temp = head;
    if (temp == NULL) {
        printf("List is empty.\n");
        return;
    }
    while (temp != NULL) {
        printf("Plate: %s, Mileage: %d, Return Date: %d\n", temp->plate, temp->mileage, temp->return_date);
        temp = temp->next;
    }
}



/**
 * Checks if a car's plate is already in the list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Boolean value indicating if the plate is found.
 */
// Function to check if a plate exists in the list
bool is_plate_in_list(struct car *head, char plate[]) {
    struct car *current = head;
    while (current != NULL) {
        if (strcmp(current->plate, plate) == 0) {
            printf("Error: Duplicate plate detected for %s.\n", plate);
            return true; // Plate found in the list
        }
        current = current->next;
    }
    return false; // Plate not found in the list
}

/**
 * Removes a car from the list by its plate number.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Pointer to the removed car.
 */
// Remove car from list by plate number
struct car* remove_car_from_list(struct car **head, char plate[]) {
    struct car *temp = *head, *prev = NULL;

    while (temp != NULL && strcmp(temp->plate, plate) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Error: Car with plate %s not found in the list.\n", plate);
        return NULL; // Car not found
    }

    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }
    temp->next = NULL;
    return temp;
    free(temp);
}

/**
 * Removes the first car from the list.
 * @param head Pointer to the head of the list.
 * @return Pointer to the removed car.
 */
struct car* remove_first_from_list(struct car **head) {
    if (*head == NULL) {
        printf("Error: No cars available to remove from the list.\n");
        return NULL;
    }

    struct car *temp = *head;
    *head = temp->next;
    temp->next = NULL;
    return temp;
    free(temp);
}


/**
 * Calculates the profit based on the mileage difference.
 * @param initial_mileage Integer representing the car's starting mileage.
 * @param final_mileage Integer representing the car's final mileage.
 * @return Double value representing the calculated profit.
 */
// Function to calculate profit based on mileage
double profit_calculator(int initial_mileage, int final_mileage) {
    int distance = final_mileage - initial_mileage;
    if (distance <= 200) {
        return 80.0;
    } else {
        return 80.0 + (distance - 200) * 0.15;
    }
}
/**
 * Writes the list of cars to a file.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Writes the details of each car in the list to a file.
 */
// Write list data to a file
void write_list_to_file(char *filename, struct car *head) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing: %s\n", filename);
        return;
    }

    struct car *temp = head;
    while (temp != NULL) {
        fprintf(file, "%s,%d,%d\n", temp->plate, temp->mileage, temp->return_date);
        temp = temp->next;
    }

    fclose(file);
}


/**
 * Reads car details from a file and adds them to the list.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Reads data from the file and inserts each car into the list.
 */
// Function to read the file
void read_file_into_list(char *filename, struct car **head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    char line[256];
    char plate[7];
    int mileage, return_date;
    int read_count = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        char *token = strtok(line, ",");
        if (token != NULL) {
            strcpy(plate, token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            mileage = atoi(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            return_date = atoi(token);
        }

        // Insert the car into the list
        insert_to_list(head, plate, mileage, return_date);
        read_count++;
    }

    fclose(file);
}



/**
 * Frees all the memory allocated for the cars in the list.
 * @param head Pointer to the head of the list.
 * Frees each car node in the list.
 */
// Free all cars in a list
void free_list(struct car **head) {
    struct car *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

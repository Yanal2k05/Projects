//Libraries Used Add more here if needed
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

//Our Linked List Node
struct car{
  char plate[7];
  int mileage;
  int return_date; //Return date should be -1 for a car with no return date
  struct car *next;
};



void prompt();
struct car* insert_to_list(struct car **head, char plate[], int mileage, int return_date);
void print_list(struct car *head);
bool is_plate_in_list(struct car *head, char plate[]);
struct car* remove_car_from_list(struct car **head, char plate[]);
struct car* remove_first_from_list(struct car **head);
double profit_calculator(int initial_mileage, int final_mileage);
void write_list_to_file(char *filename, struct car *head);
void read_file_into_list(char *filename, struct car **head);
void free_list(struct car **head);

// Helper Functions
bool validate_plate(char plate[]);
bool validate_mileage(int current_mileage, int previous_mileage);
bool validate_return_date(int return_date);


/**
 * Filename: item.c
 * Author: Pranav Pallerla
 * Date Created: 05-01-2024
 * Last Modified: 12-01-2024
 *
 * Description:
 * Implementation of item.h
 *
 */

#include "item.h"
#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Function to create a new item
int create_item(char *name, char *description, char *category, float price, int quantity){
    // Create a new item
    item_t *new_item = (struct item *)malloc(sizeof(struct item));
    if(new_item == NULL){
        printf("Error creating new item\n");
        return 0;
    }
    // Set the values of the item
    new_item->name = name;
    new_item->description = description;
    new_item->category = category;
    new_item->price = price;
    new_item->quantity = quantity;
    //add item to the global item list
    if(add_item_to_list(new_item, 1) == 0){
        printf("Error adding item to the global item list\n");
        return 0;
    }
    return 1;
}

// Function to reset item_list_head to the start of the global item list
void reset_item_list_head(){
    if (item_list_head == NULL){
        return;
    }
    while(item_list_head->prev != NULL){
        item_list_head = item_list_head->prev;
    }
}

// Function to write the item list to a file
int write_itemlist_to_file(){
    reset_item_list_head();
    // Open the file
    FILE *file = fopen("items.csv", "w");
    if(file == NULL){
        printf("Error opening file\n");
        return 0;
    }

    int count = item_count;
    // Write the count
    fprintf(file, "%d\n", count);

    // Write the items
    while(item_list_head->next != NULL){
        fprintf(file, "%d,%s,%s,%s,%f,%d\n", item_list_head->id, item_list_head->name, item_list_head->description, item_list_head->category, item_list_head->price, item_list_head->quantity);
        item_list_head = item_list_head->next;
    }

    fprintf(file, "%d,%s,%s,%s,%f,%d\n", item_list_head->id, item_list_head->name, item_list_head->description, item_list_head->category, item_list_head->price, item_list_head->quantity);

    // Close the file
    fclose(file);
    return 1;
}

// Function to read the item list from a file
int read_itemlist_from_file() {
    // Initialize the global item list and count
    item_list_head = NULL;
    item_count = 0;

    // Open the file
    FILE *file = fopen("items.csv", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 0;
    }

    // Read the count
    fscanf(file, "%d\n", &item_count);

    // Read the items
    for (int i = 0; i < item_count; i++) {
        item_t *new_item = (item_t *)malloc(sizeof(item_t));
        if (new_item == NULL) {
            printf("Error allocating memory\n");
            return 0;
        }

        // Allocate memory for strings
        new_item->name = malloc(100 * sizeof(char));
        new_item->description = malloc(100 * sizeof(char));
        new_item->category = malloc(100 * sizeof(char));

        // Peek the next character to check for newline
        char nextChar = fgetc(file);
        if (nextChar == '\n' || nextChar == EOF) {
            // Free allocated memory
            free(new_item->name);
            free(new_item->description);
            free(new_item->category);
            free(new_item);
            break;
        }
        ungetc(nextChar, file); // Put the character back for normal processing

        // Read data from file
        if (fscanf(file, "%d,%99[^,],%99[^,],%99[^,],%f,%d\n", 
                &new_item->id, new_item->name, new_item->description, new_item->category, 
                &new_item->price, &new_item->quantity) != 6) {
            printf("Error reading item from file\n");
            // Free allocated memory in case of error
            free(new_item->name);
            free(new_item->description);
            free(new_item->category);
            free(new_item);
            return 0;
        }

        // Add item to the global item list
        if (add_item_to_list(new_item,0) == 0) {
            printf("Error adding item to the global item list\n");
            return 0;
        }
    }


    // Close the file
    fclose(file);
    return 1;
}

// Function to add an item to the global item list
int add_item_to_list( item_t *new_item, int save ){
    reset_item_list_head();
    // Check if the global item list is empty
    if(item_list_head == NULL){
        // If empty, add the item to the list
        if(save == 1){
            new_item->id = item_count;
            item_count++;
        }
        item_list_head = new_item;
        new_item->next = NULL;
        new_item->prev = NULL;
        item_list_head = new_item;
        if(save == 1)
            write_itemlist_to_file();
        return 1;
    }
    // If not empty, add the item to the end of the list
    while(item_list_head->next != NULL){
        item_list_head = item_list_head->next;
    }
    if(save == 1){
        new_item->id = item_count;
        item_count++;
    }
    item_list_head->next = new_item;
    new_item->next = NULL;
    new_item->prev = item_list_head;
    item_list_head = new_item;
    if(save == 1)
        write_itemlist_to_file();
    return 1;
}

// Function to print the global item list
void print_item_list(){
    reset_item_list_head();
    while(item_list_head->next != NULL){
        printf("Item ID: %d\n", item_list_head->id);
        printf("Item Name: %s\n", item_list_head->name);
        printf("Item Description: %s\n", item_list_head->description);
        printf("Item Category: %s\n", item_list_head->category);
        printf("Item Price: %f\n", item_list_head->price);
        printf("Item Quantity: %d\n", item_list_head->quantity);
        printf("\n");
        item_list_head = item_list_head->next;
    }
    printf("Item ID: %d\n", item_list_head->id);
    printf("Item Name: %s\n", item_list_head->name);
    printf("Item Description: %s\n", item_list_head->description);
    printf("Item Category: %s\n", item_list_head->category);
    printf("Item Price: %f\n", item_list_head->price);
    printf("Item Quantity: %d\n", item_list_head->quantity);
    printf("\n");

}

// Function to delete an item from the global item list
int delete_item(int id){
    reset_item_list_head();
    // Check if the global item list is empty
    if(item_list_head == NULL){
        printf("Error deleting item, No items present.\n");
        return 0;
    }
    // Get the item to be deleted
    item_t *item_to_delete = NULL;
    while(item_list_head != NULL){
        if(item_list_head->id == id){
            item_to_delete = item_list_head;
            break;
        }
        item_list_head = item_list_head->next;
    }

    if(item_to_delete == NULL){
        printf("Error deleting item, Item not found.\n");
        return 0;
    }

    // Delete the item
    // if the item is the first item in the list
    if(item_to_delete->prev == NULL){
        item_list_head = item_to_delete->next;
        item_list_head->prev = NULL;
        free(item_to_delete);
        write_itemlist_to_file();
        return 1;
    }
    // if the item is the last item in the list
    if(item_to_delete->next == NULL){
        item_to_delete->prev->next = NULL;
        free(item_to_delete);
        write_itemlist_to_file();
        return 1;
    }
    // if the item is in the middle of the list
    item_to_delete->prev->next = item_to_delete->next;
    item_to_delete->next->prev = item_to_delete->prev;
    free(item_to_delete);
    write_itemlist_to_file();
    return 1;
}

// Function to edit an item in the global item list
int edit_item(int id) {
    reset_item_list_head();
    if (item_list_head == NULL) {
        printf("Error deleting item, No items present.\n");
        return 0;
    }

    item_t *item_to_edit = NULL;
    while (item_list_head != NULL) {
        if (item_list_head->id == id) {
            item_to_edit = item_list_head;
            break;
        }
        item_list_head = item_list_head->next;
    }

    if (item_to_edit == NULL) {
        printf("Error editing item, Item not found.\n");
        return 0;
    }

    // Edit the item
    printf("Leave the field blank if you don't want to edit it.\n");

    char new_name[100];
    printf("Enter the new name: ");
    fgets(new_name, 100, stdin);
    new_name[strcspn(new_name, "\n")] = 0; // Remove newline character

    if (strlen(new_name) > 0) {
        strncpy(item_to_edit->name, new_name, sizeof(item_to_edit->name) - 1);
        item_to_edit->name[sizeof(item_to_edit->name) - 1] = '\0'; // Ensure null-termination
    }

    char new_description[100];
    printf("Enter the new description: ");
    fgets(new_description, 100, stdin);
    new_description[strcspn(new_description, "\n")] = 0; // Remove newline character

    if (strlen(new_description) > 0) {
        strncpy(item_to_edit->description, new_description, sizeof(item_to_edit->description) - 1);
        item_to_edit->description[sizeof(item_to_edit->description) - 1] = '\0'; // Ensure null-termination
    }

    char new_category[100];
    printf("Enter the new category: ");
    fgets(new_category, 100, stdin);
    new_category[strcspn(new_category, "\n")] = 0; // Remove newline character

    if (strlen(new_category) > 0) {
        strncpy(item_to_edit->category, new_category, sizeof(item_to_edit->category) - 1);
        item_to_edit->category[sizeof(item_to_edit->category) - 1] = '\0'; // Ensure null-termination
    }

    char input_buffer[100];

    // Edit quantity
    printf("Enter the new quantity (leave blank to keep current): ");
    fgets(input_buffer, 100, stdin);
    input_buffer[strcspn(input_buffer, "\n")] = 0; // Remove newline character
    if (strlen(input_buffer) > 0) {
        int new_quantity;
        if (sscanf(input_buffer, "%d", &new_quantity) == 1 && new_quantity >= 0) {
            item_to_edit->quantity = new_quantity;
        } else {
            printf("Invalid quantity input. Keeping current value.\n");
        }
    }

    // Edit price
    printf("Enter the new price (leave blank to keep current): ");
    fgets(input_buffer, 100, stdin);
    input_buffer[strcspn(input_buffer, "\n")] = 0; // Remove newline character
    if (strlen(input_buffer) > 0) {
        float new_price;
        if (sscanf(input_buffer, "%f", &new_price) == 1 && new_price > 0) {
            item_to_edit->price = new_price;
        } else {
            printf("Invalid price input. Keeping current value.\n");
        }
    }

    printf("Item edited successfully\n");
    write_itemlist_to_file();
    return 1;
}

// Get an item from the global item list
item_t *get_item(int id) {
    reset_item_list_head();
    while (item_list_head != NULL) {
        if (item_list_head->id == id) {
            return item_list_head;
        }
        item_list_head = item_list_head->next;
    }
    return NULL;
}
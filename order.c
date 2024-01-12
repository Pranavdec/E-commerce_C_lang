/**
 * Filename: order.c
 * Author: Pranav Pallerla
 * Date Created: 12-01-2024
 * Last Modified: 12-01-2024
 *
 * Description:
 * Implementation of order.h
 *
 */

#include "order.h"
#include "globals.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create an order item
int create_item_order( char *customer_name, int id, int quantity) {
    // Check if the item exists
    item_t *item = get_item(id);
    if (item == NULL) {
        printf("Item with id %d does not exist.\n", id);
        return 0;
    }
    // Check if the quantity is valid
    if (quantity <= 0) {
        printf("Quantity should be greater than 0.\n");
        return 0;
    }
    // Check if the quantity is available
    if (item->quantity < quantity) {
        printf("Quantity not available for item %d\n", id);
        return 0;
    }
    // Create the order item
    order_item_t *order_item = (order_item_t *) malloc(sizeof(order_item_t));
    order_item->customer_name = customer_name;
    order_item->product_id = id;
    order_item->quantity = quantity;
    order_item->order_status = 0;
    order_item->next = NULL;
    order_item->prev = NULL;
    // Add the order item to the order list
    if(add_item_to_order_list(order_item, 1) == 0) {
        printf("Error adding item to order list.\n");
        return 0;
    }
   
    // Update the quantity of the item
    item->quantity -= quantity;
    // Update the order count
    order_count++;
    
    write_itemlist_to_file();

    return 1;
}

// Funciton to reset the order list
void reset_order_list() {
    if(order_list_head == NULL) {
        return;
    }
    while(order_list_head->prev != NULL) {
        order_list_head = order_list_head->prev;
    }
}

// Function to write order list to file
int write_order_to_file() {
    // Open the file
    FILE *fp = fopen("orders.csv", "w");
    if(fp == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    // Reset the order list
    reset_order_list();

    int count = order_count;
    // Write the count
    fprintf(fp, "%d\n", count);

    // Write the order items
    while(order_list_head->next != NULL) {
        fprintf(fp, "%s,%d,%d,%d\n", order_list_head->customer_name, order_list_head->product_id, order_list_head->quantity, order_list_head->order_status);
        order_list_head = order_list_head->next;
    }

    fprintf(fp, "%s,%d,%d,%d\n", order_list_head->customer_name, order_list_head->product_id, order_list_head->quantity, order_list_head->order_status);
   
    // Close the file
    fclose(fp);
    return 1;
}

// Function to read order list from file
int read_order_from_file() {
    // Open the file
    FILE *fp = fopen("orders.csv", "r");
    if(fp == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    // Read the count
    fscanf(fp, "%d\n", &order_count);

    // Read the order items
    for(int i = 0; i < order_count; i++) {
        order_item_t *order_item = (order_item_t *) malloc(sizeof(order_item_t));
        if(order_item == NULL) {
            printf("Error allocating memory.\n");
            return 0;
        }

        //Allocate memory for the customer name
        order_item->customer_name = (char *) malloc(sizeof(char) * 100);

        // Peek the next character to check for newline
        char nextChar = fgetc(fp);
        if (nextChar == '\n' || nextChar == EOF) {
            // Free allocated memory
            free(order_item->customer_name);
            break;
        }
        ungetc(nextChar, fp); // Put the character back for normal processing

        // Read data from file
        if (fscanf(fp, "%99[^,],%d,%d,%d\n", order_item->customer_name, &order_item->product_id, &order_item->quantity, &order_item->order_status) != 4) {
            printf("Error reading file.\n");
            // Free allocated memory
            free(order_item->customer_name);
            return 0;
        }

        // Add the order item to the order list
        if(add_item_to_order_list(order_item, 0) == 0) {
            printf("Error adding item to order list.\n");
            return 0;
        }
    }
    // Close the file
    fclose(fp);
    return 1;
}

// Function to add an order item to the order list
int add_item_to_order_list( order_item_t *new_order, int save ){
    //reset the order list
    reset_order_list();

    // Check if the order list is empty
    if(order_list_head == NULL) {
        order_list_head = new_order;
        if(save == 1) {
            order_count++;
            write_order_to_file();
        }
        return 1;
    }

    order_list_head->next = new_order;
    new_order->prev = order_list_head;
    order_list_head = new_order;
    if(save == 1) {
        order_count++;
        write_order_to_file();
    }
    return 1;
}

// Function to print the order list
void print_all_order() {
    // Reset the order list
    reset_order_list();
    
    // Use a temporary pointer for iteration
    order_item_t *current = order_list_head;

    // Print the order items
    while(current != NULL) {
        if(strcmp(current->customer_name, customer_name) == 0) {
            printf("Customer Name: %s\n", current->customer_name);
            printf("Product ID: %d\n", current->product_id);
            printf("Quantity: %d\n", current->quantity);
            printf("Order Status: %d\n", current->order_status);
            printf("\n");
        }
        current = current->next;
    }
}

// Function to delete an order item
int delete_order_item( int order_item_id ){
    // Reset the order list
    reset_order_list();
    // Check if the order item list is empty
    if(order_list_head == NULL) {
        printf("Order list is empty.\n");
        return 0;
    }

    // Get the order item to be deleted
    order_item_t *order_item = NULL;
    while(order_list_head != NULL) {
        if(order_list_head->product_id == order_item_id) {
            order_item = order_list_head;
            break;
        }
        order_list_head = order_list_head->next;
    }

    if(order_item == NULL) {
        printf("Order item with id %d does not exist.\n", order_item_id);
        return 0;
    }

    // Delete the order item
    if(order_item->prev == NULL) {
        order_list_head = order_item->next;
        order_list_head->prev = NULL;
        free(order_item);
        write_order_to_file();
        return 1;
    }
    if(order_item->next == NULL) {
        order_item->prev->next = NULL;
        free(order_item);
        write_order_to_file();
        return 1;
    }

    order_item->prev->next = order_item->next;
    order_item->next->prev = order_item->prev;
    free(order_item);
    write_order_to_file();
    return 1;

}

// Function to confirm an order
int confirm_order() {
    // Reset the order list
    reset_order_list();
    // Check if the order list is empty
    if(order_list_head == NULL) {
        printf("Order list is empty.\n");
        return 0;
    }

    // Use a temporary pointer for iteration
    order_item_t *current = order_list_head;

    // Print the order items
    while(current != NULL) {
        if(strcmp(current->customer_name, customer_name) == 0) {
            current->order_status = 1;
        }
        current = current->next;
    }
    write_order_to_file();
    return 1;
}

// Function to generate a report
void generate_report(){
    reset_order_list();
    // Check if the order list is empty
    if(order_list_head == NULL) {
        printf("Order list is empty.\n");
        return;
    }

    int total = 0;
    int total_quantity = 0;
    while (order_list_head->next != NULL)
    {
        if(order_list_head->order_status == 1) {
            item_t *item = get_item(order_list_head->product_id);
            total += item->price * order_list_head->quantity;
            total_quantity += order_list_head->quantity;
        }
        order_list_head = order_list_head->next;
    }

    if(order_list_head->order_status == 1) {
        item_t *item = get_item(order_list_head->product_id);
        total += item->price * order_list_head->quantity;
        total_quantity += order_list_head->quantity;
    }

    printf("Total amount: %d\n", total);
    printf("Total quantity: %d\n", total_quantity);
}
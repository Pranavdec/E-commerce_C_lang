/**
 * Filename: order.h
 * Author: Pranav Pallerla
 * Date Created: 12-01-2024
 * Last Modified: 12-01-2024
 *
 * Description:
 * This file contains the structure for the order and the function prototypes to be used on the order.
 *
 */

#ifndef ORDER_H
#define ORDER_H

// Order Details
typedef struct order_item {
    char *customer_name;
    int product_id;
    int quantity;
    int order_status;
    struct order_item *next;
    struct order_item *prev;

} order_item_t;

// Function Prototypes
int create_item_order( char *customer_name, int product_id, int quantity );
void print_all_order();
int delete_order_item( int order_item_id );
int add_item_to_order_list( order_item_t *new_order, int save );
int write_order_to_file();
int read_order_from_file();

#endif
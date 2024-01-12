/**
 * Filename: globals.h
 * Author: Pranav Pallerla
 * Date Created: 05-01-2024
 * Last Modified: 12-01-2024
 *
 * Description:
 * Global variables for the program.
 *
 */
#ifndef GLOBALS_H
#define GLOBALS_H

#include "item.h"
#include "order.h"

// Global Variables
extern item_t *item_list_head; // Head of the global item list
extern int item_count; // Count of items
extern int order_count; // Count of items in the order
extern order_item_t *order_list_head; // Head of the global order list
extern char *customer_name; // Name of the customer

#endif
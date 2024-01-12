/**
 * Filename: item.h
 * Author: Pranav Pallerla
 * Date Created: 05-01-2024
 * Last Modified: 12-01-2024
 *
 * Description:
 * This file contains the structure for the item and the function prototypes to be used on the item.
 *
 */

#ifndef ITEM_H
#define ITEM_H

// Item Details
typedef struct item {
    int id;
    char *name;
    char *description;
    char *category;
    float price;
    int quantity;
    struct item *next;
    struct item *prev;
    
} item_t;

// Function Prototypes for item
int create_item( char *name, char *description, char *category, float price, int quantity );
void print_item_list();
int delete_item( int id );
int edit_item( int id );
int add_item_to_list( item_t *item, int save );
int write_itemlist_to_file();
int read_itemlist_from_file();

#endif
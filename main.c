/**
 * Filename: main.c
 * Author: Pranav Pallerla
 * Date Created: 05-01-2024
 * Last Modified: 12-01-2024
 *
 * Description:
 * Main file for the program.
 *
 */
#include "globals.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global Variables
item_t *item_list_head = NULL;
int item_count = 0;

int main(){
    read_itemlist_from_file();
    printf("Welcome to the Inventory Management System\n");
    // create_item("Apple", "A fruit", "Fruits", 10.0, 100);
    // create_item("Orange", "A fruit", "Fruits", 20.0, 100);
    // create_item("Banana", "A fruit", "Fruits", 30.0, 100);
    // create_item("Mango", "A fruit", "Fruits", 40.0, 100);
    // delete_item(2);
    edit_item(1);
    print_item_list();

}
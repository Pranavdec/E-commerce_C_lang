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
#include "order.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global Variables
item_t *item_list_head = NULL;
int item_count = 0;
order_item_t *order_list_head = NULL;
int order_count = 0;
char *customer_name = NULL;

int main(){
    read_itemlist_from_file();
    read_order_from_file();
    printf("Welcome to the Inventory Management System\n");

    printf("Select an option:\n");
    printf("1. Inventory Management\n");
    printf("2. Ordering Items\n");

    int option;
    scanf("%d", &option);

    if(option == 1){
        int running = 1;
        while(running == 1){
            printf("Select an option:\n");
            printf("1. Create Item\n");
            printf("2. Edit Item\n");
            printf("3. Delete Item\n");
            printf("4. Print Item List\n");
            printf("5. Exit\n");
            
            int option_1;
            scanf("%d", &option_1);

            switch (option_1)
            {
            case 1:
                printf("Enter the name of the item: ");
                char name[100];
                scanf("%s", name);
                printf("Enter the description of the item: ");
                char description[100];
                scanf("%s", description);
                printf("Enter the category of the item: ");
                char category[100];
                scanf("%s", category);
                printf("Enter the price of the item: ");
                float price;
                scanf("%f", &price);
                printf("Enter the quantity of the item: ");
                int quantity;
                scanf("%d", &quantity);
                create_item(name, description, category, price, quantity);
                break;
            
            case 2:
                printf("Enter the id of the item: ");
                int id;
                scanf("%d", &id);
                edit_item(id);
                break;

            case 3:
                printf("Enter the id of the item: ");
                int id_1;
                scanf("%d", &id_1);
                delete_item(id_1);
                break;

            case 4:
                print_item_list();
                break;

            case 5:
                running = 0;
                break;

            default:
                printf("Invalid option.\n");
                break;
            }
        }
    }
    else if(option == 2){
        int running_1 = 1;
        print_item_list();
        printf("Enter your name: ");
        char name[100];
        scanf("%s", name);
        customer_name = name;

        while(running_1 == 1){
            printf("Select an option:\n");
            printf("1. Create item in Order\n");
            printf("2. Print all items in Order\n");
            printf("3. Delete an item in Order\n");
            printf("4. Confirm Order\n");
            printf("5. Exit\n");
            
            int option_2;
            scanf("%d", &option_2);

            switch (option_2)
            {
            case 1:
                printf("Enter the id of the item: ");
                int id;
                scanf("%d", &id);
                printf("Enter the quantity of the item: ");
                int quantity;
                scanf("%d", &quantity);
                create_item_order(customer_name, id, quantity);
                break;
            
            case 2:
                print_all_order();
                break;

            case 3:
                printf("Enter the id of the item: ");
                int id_1;
                scanf("%d", &id_1);
                delete_order_item(id_1);
                break;

            case 4:
                confirm_order();
                break;

            case 5:
                running_1 = 0;
                break;

            default:
                printf("Invalid option.\n");
                break;
            }
        }
    }
    else{
        printf("Invalid option.\n");
    }


}
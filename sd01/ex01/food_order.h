#ifndef FOOD_ORDER_H
#define FOOD_ORDER_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char UUID[37]; // UUIDs are 36 characters plus null terminator

typedef struct fooditem
{
	UUID id;		 // Unique identifier for the food item
	char *name;		 // Name of the food item
	double price;	 // Price of the food item
	size_t calories; // Calories in the food item
	size_t amount;	 // Amount of the food item (e.g., in grams or ounces)
} FoodItem;

typedef struct OrderRequest
{
	UUID id;			   // Unique identifier for the user
	char *restaurant_name; // Name of the restaurant
	FoodItem *items;	   // Array of food items in the order
	int item_count;		   // Number of items in the order
} OrderRequest;

typedef struct OrderConfirmation
{
	UUID id;			   // Unique identifier for the order
	char *restaurant_name; // Name of the restaurant
	FoodItem *items;	   // Array of food items in the order
	bool is_preorder;	   // Indicates if this is a pre-order
} OrderConfirmation;

// Checks if the restaurant is open based on the order. Returns 1 if open, 0 if closed.
int check_restaurant_status(struct OrderRequest *request);
// Creates a confirmation for an immediate order. Returns NULL on failure.
struct OrderConfirmation *create_standard_confirmation(void);
// Creates a confirmation for a future (pre-order). Returns NULL on failure.
struct OrderConfirmation *create_preorder_confirmation(void);
// Sends the confirmation to the user.
void send_confirmation_notification(struct OrderConfirmation *confirmation);

int process_food_order(struct OrderRequest *request);

#endif // FOOD_ORDER_H
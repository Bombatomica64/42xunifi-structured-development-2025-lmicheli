#ifndef RECIPE_GENERATOR_H
#define RECIPE_GENERATOR_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ingredient
{
	char *name;	  // Name of the ingredient
	int quantity; // Quantity of the ingredient
	char *unit;	  // Unit of measurement (e.g., "grams", "cups")
} Ingredient;

typedef struct Ingredients
{
	Ingredient *ingredients; // Array of ingredients
	int size;				 // Number of ingredients in the fridge
	int capacity;			 // Capacity of the ingredients array
} Ingredients;

typedef struct TasteProfile
{
	char **flavors;
	int *rating;
	int size; // Number of flavors in the taste profile
} TasteProfile;

typedef struct Recipe
{
	char *name;				 // Name of the recipe
	Ingredient *ingredients; // Array of ingredients required for the recipe
	int ingredient_count;	 // Number of ingredients in the recipe
	char *instructions;		 // Cooking instructions
} Recipe;

// Fetch current ingredients from fridge. Returns a new Ingredients* or NULL on failure.
struct Ingredients *get_current_ingredients(void);
// Fetch user taste profile. Returns a new TasteProfile* or NULL on failure.
struct TasteProfile *get_user_taste_profile(void);

// Generate a new recipe candidate based on ingredients & taste. Returns a new Recipe* or NULL on failure.
struct Recipe *create_recipe(struct Ingredients *ingredients, struct TasteProfile *taste);
// Ask user approval for the given recipe. Returns 1 if approved, 0 otherwise.
int get_user_approval(struct Recipe *recipe);
// Free functions for cleanup:
void free_ingredients(struct Ingredients *ing);
void free_taste_profile(struct TasteProfile *tp);
void free_recipe(struct Recipe *recipe);

struct Recipe *create_custom_recipe(void);

#endif // RECIPE_GENERATOR_H
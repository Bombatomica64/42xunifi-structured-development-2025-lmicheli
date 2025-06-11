#include "recipe_generator.h"

struct Recipe *create_custom_recipe(void)
{
	struct Ingredients *ingredients = get_current_ingredients();
	if (!ingredients)
		return NULL;

	struct TasteProfile *taste = get_user_taste_profile();
	if (!taste)
	{
		free_ingredients(ingredients);
		return NULL;
	}
	struct Recipe *recipe = NULL;
	do
	{
		if (recipe)
			free_recipe(recipe);
		recipe = create_recipe(ingredients, taste);
		if (!recipe)
		{
			free_ingredients(ingredients);
			free_taste_profile(taste);
			return NULL;
		}
	} while (get_user_approval(recipe) == 0);

	free_ingredients(ingredients);
	free_taste_profile(taste);
	return recipe;
}
#include "movie_planner.h"

struct Plan *create_movie_night_plan(void)
{
	// Get user preferences (you don't need to know the internal structure)
	struct Preferences *prefs = get_user_preferences();
	if (!prefs)
		return NULL;

	// Find movies (you don't need to know MovieList internals)
	struct MovieList *movies = find_movies(prefs);
	if (!movies)
	{
		for (int i = 0; prefs->genre[i]; i++)
		{
			free(prefs->genre[i]); // Free each genre string
		}
		free(prefs->username); // Free username string
		free(prefs);
		return NULL;
	}

	// Build plan (you don't need to know Plan internals)
	struct Plan *plan = build_plan(movies);
	if (!plan)
	{
		for (int i = 0; movies->movies[i].title; i++)
		{
			free(movies->movies[i].title);	  // Free each movie title
			free(movies->movies[i].genre);	  // Free each movie genre
			free(movies->movies[i].director); // Free each movie director
			for (int j = 0; movies->movies[i].actors[j]; j++)
			{
				free(movies->movies[i].actors[j]); // Free each actor string
			}
			free(movies->movies[i].actors); // Free the actors array
		}
		free(movies->movies); // Free the movies array
		free(movies);

		for (int i = 0; prefs->genre[i]; i++)
		{
			free(prefs->genre[i]); // Free each genre string
		}
		free(prefs->username); // Free username string
		free(prefs);
		return NULL;
	}

	return plan;
}
#ifndef MOVIE_PLANNER_H
#define MOVIE_PLANNER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
	PG,
	PG13,
	R,
	NC17,
} Rating;

typedef struct Preferences
{
	char *username;
	char **genre;
	struct Preferences *next;
} Preferences;

typedef struct Movie
{
	char *title;
	int year;
	int duration;
	int stars;
	Rating movie_rating;
	char *director;
	char **actors;
	char *genre;
} Movie;

typedef struct MovieList
{
	Movie *movies;
	int size;
} MovieList;

typedef struct Plan
{
	Movie *movie;
} Plan;

// Returns user preferences. Returns NULL on failure.
struct Preferences *get_user_preferences(void);
// Returns a list of movies matching the given preferences. Returns NULL on failure.
struct MovieList *find_movies(struct Preferences *prefs);
// Returns a movie night plan from the given list. Returns NULL on failure.
struct Plan *build_plan(struct MovieList *list);

struct Plan *create_movie_night_plan(void);

#endif // MOVIE_PLANNER_H
#ifndef WORKOUT_SCHEDULER_H
#define WORKOUT_SCHEDULER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct UserData
{
	char *username; // Username of the user
	int age;        // Age of the user
	int weight;     // Weight of the user in kg
	int height;     // Height of the user in cm
	char *goals;    // Fitness goals (e.g., "lose weight", "build muscle")
} UserData;

typedef struct Exercise
{
	char *name;        // Name of the exercise (e.g., "Push-up")
	int sets;          // Number of sets
	int reps;         // Number of repetitions per set
	int duration;      // Duration in seconds (if applicable)
	char *description; // Description of the exercise
	char *tips;        // Tips for performing the exercise
} Exercise;

typedef struct WorkoutPlan
{
	char *username; // Username of the user
	int duration;    // Total duration of the workout plan
	Exercise *exercises; // Array of exercises in the workout plan
} WorkoutPlan;

// Returns a new UserData (mocked). Returns NULL on failure.
struct UserData *get_user_data(char *username);
// Build a base WorkoutPlan from raw user data. Returns NULL on failure.
struct WorkoutPlan *build_base_plan(struct UserData *data);
// Optionally refine an existing plan. Returns the same pointer (or a new one) or NULL on failure.
struct WorkoutPlan *refine_plan(struct WorkoutPlan *plan, struct UserData *data);
// Determine how many days the workout schedule should span. Returns positive int, or <=0 on failure.
int determine_duration(struct WorkoutPlan *plan);
// Assign daily exercises for the next day into the plan.
void assign_daily_exercises(struct WorkoutPlan *plan, int day);
// Assign daily tips for the next day into the plan.
void assign_daily_tips(struct WorkoutPlan *plan, int day);
// Free functions for cleanup.
void free_user_data(struct UserData *data);
void free_workout_plan(struct WorkoutPlan *plan);

struct WorkoutPlan *create_workout_schedule(char *username);

#endif // WORKOUT_SCHEDULER_H
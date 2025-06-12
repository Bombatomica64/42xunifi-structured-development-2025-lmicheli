#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct LoadInfo
{
	int cpu_load; // CPU load percentage
	int io_load;  // I/O load percentage
} LoadInfo;

typedef struct Task
{
	int id;		   // Unique identifier for the task
	LoadInfo load; // Load information for the task
	int core_id;   // ID of the core assigned to this task
} Task;
typedef struct TaskList
{
	Task *tasks;									  // Array of tasks
	int size;										  // Number of tasks in the list
	Task *(*get_task)(struct TaskList *self, int id); // Function to get a task by ID
} TaskList;
typedef struct TaskProfile
{
	TaskList *tasks; // List of tasks being profiled
	LoadInfo *load;	 // Load information for the tasks
} TaskProfile;
typedef struct PriorityMap
{
	Task *tasks;	 // Array of tasks sorted by priority
	int size;		 // Number of tasks in the priority map
} PriorityMap;
typedef struct ScheduleResult
{
	Task *task_assignments; // Array of task assignments to cores
	int core_count;			// Number of CPU cores
} ScheduleResult;

// Analyze task load and I/O behavior. Returns a new TaskProfile or NULL on failure.
struct TaskProfile *profile_tasks(struct TaskList *tasks);
// Compute a priority map from task profiling. Returns a new PriorityMap or NULL on failure.
struct PriorityMap *compute_priorities_mock(struct TaskProfile *profile);
// Return the number of available CPU cores.
int get_available_core_count(void);
// Select the best task to assign next based on the profile. Returns a task ID or -1 on failure.
int select_best_task(struct TaskProfile *profile);
// Create a ScheduleResult structure for the specified number of cores. Returns NULL on failure.
struct ScheduleResult *create_schedule_result(int core_count);
// Update the result schedule with a task assignment.
void update_schedule_entry(struct ScheduleResult *result, int core_id, int task_id);
// Free functions for cleanup
void free_task_profile(struct TaskProfile *profile);
void free_priority_map(struct PriorityMap *priorities);
void free_loadinfo(struct LoadInfo *load);

struct ScheduleResult *schedule_tasks(struct TaskList *tasks);
#endif // TASK_SCHEDULER_H
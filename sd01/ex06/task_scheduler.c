#include "task_scheduler.h"

struct ScheduleResult *schedule_tasks(struct TaskList *tasks)
{
	if (!tasks || tasks->size == 0)
	{
		return NULL; // No tasks to schedule
	}

	TaskProfile *profile = profile_tasks(tasks);
	if (!profile)
	{
		return NULL; // Failed to profile tasks
	}

	PriorityMap *priorities = compute_priorities_mock(profile);
	if (!priorities)
	{
		free_task_profile(profile);
		return NULL; // Failed to compute priorities
	}
	int core_count = get_available_core_count();
	if (core_count <= 0)
	{
		free_priority_map(priorities);
		free_task_profile(profile);
		return NULL; // No available cores
	}
	ScheduleResult *result = create_schedule_result(core_count);
	if (!result)
	{
		free_priority_map(priorities);
		free_task_profile(profile);
		return NULL; // Failed to create schedule result
	}
	for (int i = 0; i < priorities->size; i++)
	{
		Task *task = &priorities->tasks[i];
		int core_id = select_best_task(profile);
		if (core_id < 0)
		{
			free_priority_map(priorities);
			free_task_profile(profile);
			free_schedule_result(result);
			return NULL; // Failed to select a task
		}
		update_schedule_entry(result, core_id, task->id);
	}
	free_priority_map(priorities);
	free_task_profile(profile);
	free_loadinfo(profile->load);
	return result; // Return the final schedule result
}

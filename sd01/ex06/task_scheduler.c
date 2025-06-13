#include "task_scheduler.h"

static Task *get_task(struct TaskList *self, int id)
{
	if (id < 0 || id >= self->size)
	{
		return NULL; // Invalid task ID
	}
	return &self->tasks[id];
}


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
	for (int i = 0; i < priorities->size && i < core_count; i++)
	{
		int task_id = select_best_task_for_current_priorities(profile, priorities);
		const Task *task = tasks->get_task(tasks, task_id);
		if (task->core_id < 0 || task->core_id >= core_count)
		{
			free_priority_map(priorities);
			free_task_profile(profile);
			free_loadinfo(profile->load);
			return NULL; // Invalid core ID
		}
		update_schedule_entry(result, task->core_id, task->id);
	}
	free_priority_map(priorities);
	free_task_profile(profile);
	free_loadinfo(profile->load);
	return result; // Return the final schedule result
}

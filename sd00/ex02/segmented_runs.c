#include "segmented_runs.h"

static int skip_negative_ones(const int *arr, int size, int start)
{
	int i = start;
	while (i < size && arr[i] == -1)
		i++;
	return i;
}

static bool process_segment(const int *arr, int size, int *current_pos)
{
	int i = *current_pos;
	bool has_increasing_seq = false;
	int consecutive_count = 1;
	i++;

	while (i < size && arr[i] != -1)
	{
		if (arr[i] > arr[i - 1])
		{
			consecutive_count++;
			if (consecutive_count >= 3)
				has_increasing_seq = true;
		}
		else
		{
			consecutive_count = 1;
		}
		i++;
	}

	*current_pos = i;
	return has_increasing_seq;
}

int count_segments(const int *arr, int size)
{
	if (size <= 2)
		return 0;

	int nb_segments = 0;
	int i = 0;

	while (i < size)
	{
		i = skip_negative_ones(arr, size, i);
		if (i >= size)
			break;

		if (process_segment(arr, size, &i))
			nb_segments++;
	}

	return nb_segments;
}
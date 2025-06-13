#include "segmented_runs.h"

int count_segments(const int *arr, int size)
{
	if (size <= 2)
		return 0;

	int nb_segments = 0;
	int i = 0;

	while (i < size)
	{
		while (i < size && arr[i] == -1)
			i++;
		if (i >= size)
			break;

		bool has_increasing_seq = false;
		int consecutive_count = 1;
		int segment_start = i;
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
				consecutive_count = 1;
			i++;
		}

		if (has_increasing_seq)
			nb_segments++;
	}

	return nb_segments;
}

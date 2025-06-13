#include "first_last.h"

void first_last(int arr[], int size, int target, int *first, int *last)
{
	*first = -1;
	*last = -1;

	int left = 0;
	int right = size - 1;

	while (left <= right)
	{
		if (*first == -1 && arr[left] == target)
			*first = left;
		if (*last == -1 && arr[right] == target)
			*last = right;
		if (*first != -1 && *last != -1)
			break;
		left++;
		right--;
	}
}

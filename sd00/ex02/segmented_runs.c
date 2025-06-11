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

// int main(void)
// {
// 	// Test case 1: Normal array with segments
// 	int arr1[] = {-1, 1, 2, 3, -1, 4, 5, -1, 6, -1};
// 	int size1 = sizeof(arr1) / sizeof(arr1[0]);
// 	printf("Array 1: ");
// 	for (int i = 0; i < size1; i++)
// 	{
// 		printf("%d ", arr1[i]);
// 	}
// 	printf("\nSegments: %d\n\n", count_segments(arr1, size1));

// 	// Test case 2: Array with no segments (size <= 2)
// 	int arr2[] = {1, 2};
// 	int size2 = sizeof(arr2) / sizeof(arr2[0]);
// 	printf("Array 2: ");
// 	for (int i = 0; i < size2; i++)
// 	{
// 		printf("%d ", arr2[i]);
// 	}
// 	printf("\nSegments: %d\n\n", count_segments(arr2, size2));

// 	// Test case 3: Array starting with -1
// 	int arr3[] = {-1, 1, 2, -1, 3, 4, 5};
// 	int size3 = sizeof(arr3) / sizeof(arr3[0]);
// 	printf("Array 3: ");
// 	for (int i = 0; i < size3; i++)
// 	{
// 		printf("%d ", arr3[i]);
// 	}
// 	printf("\nSegments: %d\n\n", count_segments(arr3, size3));

// 	// Test case 4: All -1s
// 	int arr4[] = {-1, -1, -1, -1};
// 	int size4 = sizeof(arr4) / sizeof(arr4[0]);
// 	printf("Array 4: ");
// 	for (int i = 0; i < size4; i++)
// 	{
// 		printf("%d ", arr4[i]);
// 	}
// 	printf("\nSegments: %d\n", count_segments(arr4, size4));

// 	return 0;
// }
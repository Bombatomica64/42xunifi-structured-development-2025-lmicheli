#include "critical_windows.h"

static bool isCritical(int arr[5])
{
	int strikes = 0;
	int average = 0;

	for (int i = 0; i < 5; i++)
	{
		if (arr[i] > 150)
			return false;
		if (arr[i] >= 70)
			strikes++;
		average += arr[i];
	}
	return ((average / 5) >= 90) && (strikes >= 3);
}

int count_critical_windows(const int *readings, int size)
{
	if (size < 5)
		return 0;

	int window[5] = {0};
	int ret = 0;

	for (int i = 0; i < 5; i++)
	{
		window[i] = readings[i];
	}
	ret += isCritical(window);

	for (int i = 5; i < size; i++)
	{
		window[(i - 5) % 5] = readings[i];
		ret += isCritical(window);
	}

	return ret;
}

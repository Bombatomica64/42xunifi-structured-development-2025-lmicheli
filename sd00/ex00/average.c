#include "average.h"

static bool isValid(int nbr, float *size)
{
	if (nbr >= 0 && nbr <= 100)
		return true;
	*size -= 1;
	return false;
}

float average(const int *array, int size)
{
	float averageRet = 0;
	float validCount = size;
	for (int i = 0; i < size; i++)
	{
		averageRet += isValid(array[i], &validCount) ? array[i] : 0;
	}
	return averageRet / validCount;
}

// int main(void)
// {
// 	int size = 5;
// 	int array[] = {10, 20, 30, 500, 50};
// 	float avg = average(array, size);
// 	printf("Average: %f\n", avg);
// 	return 0;
// }
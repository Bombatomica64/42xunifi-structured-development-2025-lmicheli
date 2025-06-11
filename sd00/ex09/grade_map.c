#include "grade_map.h"

char *get_grade_impl(int score, GradeMapper mapper)
{
	if (score < 0 || score > 100)
		return NULL;

	return mapper.grade[score];
}

static void sort_by_score_desc(const int *scores, const char **mapped_grades, int size)
{
	if (!scores || !mapped_grades || size <= 0)
		return;
	int temp_scores[size];
	const char *temp_grades[size];

	for (int i = 0; i < size; i++)
	{
		temp_scores[i] = scores[i];
		temp_grades[i] = mapped_grades[i];
	}

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (temp_scores[j] < temp_scores[j + 1])
			{
				int score_temp = temp_scores[j];
				temp_scores[j] = temp_scores[j + 1];
				temp_scores[j + 1] = score_temp;
				const char *grade_temp = temp_grades[j];
				temp_grades[j] = temp_grades[j + 1];
				temp_grades[j + 1] = grade_temp;
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		mapped_grades[i] = temp_grades[i];
	}
}

void map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades)
{
	if (!scores || !mapped_grades)
		return;

	for (int i = 0; i < size; i++)
	{
		mapped_grades[i] = mapper.get_grade(scores[i], mapper);
	}

	sort_by_score_desc(scores, mapped_grades, size);
}

int main(void)
{
	// Initialize the grade mapper
	GradeMapper mapper;
	mapper.get_grade = get_grade_impl;

	// Set up grade mapping
	for (int i = 0; i <= 100; i++)
	{
		if (i >= 97)
			mapper.grade[i] = "EXCELLENT";
		else if (i >= 93)
			mapper.grade[i] = "A";
		else if (i >= 90)
			mapper.grade[i] = "A-";
		else if (i >= 87)
			mapper.grade[i] = "B+";
		else if (i >= 83)
			mapper.grade[i] = "B";
		else if (i >= 80)
			mapper.grade[i] = "B-";
		else if (i >= 77)
			mapper.grade[i] = "C+";
		else if (i >= 73)
			mapper.grade[i] = "C";
		else if (i >= 70)
			mapper.grade[i] = "C-";
		else if (i >= 67)
			mapper.grade[i] = "D+";
		else if (i >= 63)
			mapper.grade[i] = "D";
		else if (i >= 60)
			mapper.grade[i] = "D-";
		else
			mapper.grade[i] = "F";
	}

	// Test scores
	int scores[] = {98, 95, 85, 75, 65, 55, 90, 87, 83, 98, 75, 85, 95, 100, 60, 70, 80, 90, 55, 45, 35, 25, 15, 5};
	const int size = sizeof(scores) / sizeof(scores[0]);
	const char *mapped_grades[size];

	// Map scores to grades
	map_scores(scores, size, mapper, mapped_grades);

	printf("=== Score to Grade Mapping ===\n");
	for (int i = 0; i < size; i++)
	{
		printf("Score: %d, Grade: %s\n", scores[i],
			   mapped_grades[i] ? mapped_grades[i] : "INVALID");
	}

	// Compute grade distribution
	GradeNode *distribution = compute_distribution(mapped_grades, size);
	if (distribution)
	{
		printf("\n=== Grade Distribution ===\n");
		print_distribution(distribution);

		// Test the function pointer approach
		printf("\n=== Testing Function Pointers ===\n");
		printf("Adding extra A+ grade...\n");
		distribution->insert(distribution, "A+");
		print_distribution(distribution);

		// Clean up
		free_distribution(distribution);
	}

	return 0;
}
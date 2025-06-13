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

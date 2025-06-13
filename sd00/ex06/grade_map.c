#include "grade_map.h"

char *get_grade_impl(int score, GradeMapper mapper)
{
	if (score < 0 || score > 100)
		return NULL;

	return mapper.grade[score];
}

void map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades)
{
	if (!scores || !mapped_grades)
		return;

	for (int i = 0; i < size; i++)
	{
		mapped_grades[i] = mapper.get_grade(scores[i], mapper);
	}
}

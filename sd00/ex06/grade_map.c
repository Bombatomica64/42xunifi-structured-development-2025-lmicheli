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

// int main(void)
// {
// 	GradeMapper mapper;

// 	mapper.get_grade = get_grade_impl;

// 	// Initialize the grade mapping
// 	for (int i = 0; i <= 100; i++) // Fixed: include 100
// 	{
// 		if (i >= 97)
// 			mapper.grade[i] = "A+";
// 		else if (i >= 93)
// 			mapper.grade[i] = "A";
// 		else if (i >= 90)
// 			mapper.grade[i] = "A-";
// 		else if (i >= 87)
// 			mapper.grade[i] = "B+";
// 		else if (i >= 83)
// 			mapper.grade[i] = "B";
// 		else if (i >= 80)
// 			mapper.grade[i] = "B-";
// 		else if (i >= 77)
// 			mapper.grade[i] = "C+";
// 		else if (i >= 73)
// 			mapper.grade[i] = "C";
// 		else if (i >= 70)
// 			mapper.grade[i] = "C-";
// 		else if (i >= 67)
// 			mapper.grade[i] = "D+";
// 		else if (i >= 63)
// 			mapper.grade[i] = "D";
// 		else if (i >= 60)
// 			mapper.grade[i] = "D-";
// 		else
// 			mapper.grade[i] = "F";
// 	}

// 	int scores[] = {98, 95, 85, 75, 65, 55, -10, 110};
// 	const int size = sizeof(scores) / sizeof(scores[0]);
// 	const char *mapped_grades[size];

// 	map_scores(scores, size, mapper, mapped_grades); // Pass pointer

// 	for (int i = 0; i < size; i++)
// 	{
// 		printf("Score: %d, Grade: %s\n", scores[i],
// 			   mapped_grades[i] ? mapped_grades[i] : "INVALID");
// 	}

// 	return 0;
// }
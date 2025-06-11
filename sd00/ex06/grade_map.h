#ifndef GRADE_MAP_H
#define GRADE_MAP_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct grade_map
{
	char *grade[101];
	char *(*get_grade)(int score, struct grade_map mapper);

} GradeMapper;

void map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades);

#endif // GRADE_MAP_H
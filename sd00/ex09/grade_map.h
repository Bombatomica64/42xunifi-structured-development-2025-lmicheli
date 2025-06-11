#ifndef GRADE_MAP_H
#define GRADE_MAP_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct grade_map
{
	char *grade[102];
	char *(*get_grade)(int score, struct grade_map mapper);

} GradeMapper;

typedef struct gradeEntry
{
	char *grade;
	int count;
} GradeEntry;

typedef struct gradeNode
{
	GradeEntry *entries;
	int capacity;
	int size;
	int maxCount;
	void (*insert)(struct gradeNode *self, char *grade);
	void (*resize_entries)(struct gradeNode *self);
} GradeNode;

void map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades);

GradeNode *compute_distribution(const char **mapped_grades, int size);
void print_distribution(GradeNode *head);
void free_distribution(GradeNode *head);

#endif // GRADE_MAP_H
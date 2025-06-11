#include "grade_map.h"

static void *mycalloc(size_t count, size_t size)
{
	void *ptr = malloc(count * size);
	for (size_t i = 0; i < count * size; i++)
	{
		((unsigned char *)ptr)[i] = 0;
	}
	return ptr;
}

static void resize_entries_impl(GradeNode *self)
{
	int new_capacity = self->capacity * 2;
	GradeEntry *new_entries = mycalloc(new_capacity, sizeof(GradeEntry));
	if (!new_entries)
		return;

	for (int i = 0; i < self->size; i++)
	{
		new_entries[i] = self->entries[i];
	}

	free(self->entries);
	self->entries = new_entries;
	self->capacity = new_capacity;
}

void insert(GradeNode *self, char *grade)
{
	if (!self || !grade)
		return;

	for (int i = 0; i < self->size; i++)
	{
		if (strcmp(self->entries[i].grade, grade) == 0)
		{
			self->entries[i].count++;
			if (self->entries[i].count > self->maxCount)
				self->maxCount = self->entries[i].count;
			return;
		}
	}

	if (self->size >= self->capacity)
	{
		self->resize_entries(self);
	}

	if (self->size < self->capacity)
	{
		self->entries[self->size].grade = malloc(strlen(grade) + 1);
		strncpy(self->entries[self->size].grade, grade, strlen(grade) + 1);
		self->entries[self->size].count = 1;
		self->size++;
	}
}
GradeNode *compute_distribution(const char **mapped_grades, int size)
{
	GradeNode *computed = malloc(sizeof(GradeNode));
	if (!computed)
		return NULL;

	computed->capacity = 4;
	computed->size = 0;
	computed->maxCount = 0;
	computed->entries = mycalloc(computed->capacity, sizeof(GradeEntry));
	if (!computed->entries)
	{
		free(computed);
		return NULL;
	}

	computed->resize_entries = resize_entries_impl;
	computed->insert = insert;

	for (int i = 0; i < size; i++)
	{
		if (mapped_grades[i])
			insert(computed, (char *)mapped_grades[i]);
	}

	return computed;
}

void free_distribution(GradeNode *head)
{
	if (!head)
		return;

	for (int i = 0; i < head->size; i++)
	{
		free(head->entries[i].grade);
	}
	free(head->entries);
	free(head);
}

void print_distribution(GradeNode *head)
{
    if (!head || !head->entries)
        return;

    int maxCount = head->maxCount;
	printf("Grade Distribution:\n");
    
    for (int row = maxCount; row >= 1; row--)
    {
        printf("%2d |", row);
        
        for (int i = 0; i < head->size; i++)
        {
            if (head->entries[i].count >= row)
                printf(" [*]");
            else
                printf(" [ ]");
        }
        printf("\n");
    }
    
    printf("   +");
    for (int i = 0; i < head->size; i++)
    {
        printf("----");
    }
    printf("\n");

    printf("   ");
    for (int i = 0; i < head->size; i++)
    {
        printf(" %3.2s", head->entries[i].grade);
    }
    printf("\n");
}
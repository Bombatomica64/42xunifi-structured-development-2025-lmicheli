#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum
{
	FILEOBJECT,
	DIRECTORY
} NodeType;

typedef struct FSNode
{
	char *name;
	int size;	   // Size in bytes
	NodeType type; // Type of the node (file or directory)
	struct FSNode **children;
	struct FSNode *parent;
	int childCount;
} FSNode;

FSNode *create_file(const char *name, int size);
FSNode *create_folder(const char *name);
void add_child(FSNode *parent, FSNode *child);
FSNode *get_children(const FSNode *parent);
FSNode *get_sibling(const FSNode *node);

//bonus
int compute_total_size(FSNode *node);
void print_structure(const FSNode *node, int indent);
void free_filesystem(FSNode *node);

#endif // FILESYSTEM_H
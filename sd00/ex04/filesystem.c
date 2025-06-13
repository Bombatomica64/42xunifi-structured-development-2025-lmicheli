#include "filesystem.h"

FSNode *create_file(const char *name, int size)
{
	FSNode *node = malloc(sizeof(FSNode));
	if (!node)
		return NULL;

	char *name_copy = strdup(name);
	if (!name_copy)
	{
		free(node);
		return NULL;
	}

	*node = (FSNode){name_copy, size, FILEOBJECT, NULL, NULL, -1};
	return node;
}

FSNode *create_folder(const char *name)
{
	FSNode *node = malloc(sizeof(FSNode));
	if (!node)
		return NULL;

	char *name_copy = strdup(name);
	if (!name_copy)
	{
		free(node);
		return NULL;
	}

	*node = (FSNode){name_copy, -1, DIRECTORY, NULL, NULL, 0};
	return node;
}

void add_child(FSNode *parent, FSNode *child)
{
	if (!parent || !child || parent->type != DIRECTORY)
		return;

	FSNode **temp = malloc((parent->childCount + 1) * sizeof(FSNode *));
	if (!temp)
		return;

	if (parent->children)
	{
		for (int i = 0; i < parent->childCount; i++)
		{
			temp[i] = parent->children[i];
		}
	}

	temp[parent->childCount] = child;
	parent->children = temp;
	parent->childCount++;
	child->parent = parent;
}

FSNode *get_children(const FSNode *parent)
{
	if (!parent || parent->type != DIRECTORY || parent->childCount == 0)
		return NULL;

	return parent->children[0];
}

FSNode *get_sibling(const FSNode *node)
{
	if (!node || !node->parent)
		return NULL;

	const FSNode *parent = node->parent;

	for (int i = 0; i < parent->childCount; i++)
	{
		if (parent->children[i] == node)
		{
			if (i + 1 < parent->childCount)
			{
				return parent->children[i + 1];
			}
			else if (i - 1 >= 0)
			{
				return parent->children[0];
			}
			break;
		}
	}

	return NULL;
}
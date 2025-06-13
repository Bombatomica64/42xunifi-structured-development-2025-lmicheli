#include "filesystem.h"

void mystrcpy(char *dest, const char *src)
{
	if (!dest || !src)
		return;

	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
}

int mystrlen(const char *str)
{
	int ret = 0;
	if (!str)
		return 0;
	while (str[ret] != '\0')
		ret++;
	return ret;
}

int mystrcat(char *dest, const char *src)
{
	if (!dest || !src)
		return -1;

	while (*dest)
		dest++;

	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';

	return 0;
}

int compute_total_size(const FSNode *node)
{
	if (!node)
		return 0;

	int total_size = node->size > 0 ? node->size : 0;

	if (node->type == DIRECTORY && node->children)
	{
		for (int i = 0; i < node->childCount; i++)
		{
			total_size += compute_total_size(node->children[i]);
		}
	}
	return total_size;
}

void print_tree(const FSNode *node, const char *prefix, bool is_last, int indent)
{
	if (!node)
		return;

	printf("%s", prefix);

	printf("%s", is_last ? "└──" : "├──");

	for (int i = 0; i < indent; i++)
	{
		printf("─");
	}
	if (node->type == DIRECTORY)
	{
		printf("📁 %s/", node->name);
		if (node->children && node->childCount > 0)
		{
			int total_size = compute_total_size(node);
			printf(" (%d bytes total)", total_size);
		}
	}
	else
	{
		printf("📄 %s (%d bytes)", node->name, node->size);
	}
	printf("\n");

	if (node->type == DIRECTORY && node->children)
	{
		char new_prefix[256];
		new_prefix[0] = '\0';
		if (prefix)
			mystrcpy(new_prefix, prefix);

		if (is_last)
			mystrcat(new_prefix, "     ");
		else
			mystrcat(new_prefix, "│    ");

		for (int i = 0; i < node->childCount; i++)
		{
			bool child_is_last = (i == node->childCount - 1);
			print_tree(node->children[i], new_prefix, child_is_last, indent);
		}
	}
}

void print_structure(const FSNode *root, int indent)
{
	if (!root || indent < 0)
		return;

	if (root->type == DIRECTORY)
	{
		printf("📁 %s/", root->name);
		if (root->children && root->childCount > 0)
		{
			int total_size = compute_total_size(root);
			printf(" (%d bytes total)", total_size);
		}
	}
	else
	{
		printf("📄 %s (%d bytes)", root->name, root->size);
	}
	printf("\n");

	if (root->type == DIRECTORY && root->children)
	{
		for (int i = 0; i < root->childCount; i++)
		{
			bool is_last = (i == root->childCount - 1);
			print_tree(root->children[i], "", is_last, indent);
		}
	}
}

void free_filesystem(FSNode *node)
{
	if (!node)
		return;

	if (node->children)
	{
		for (int i = 0; i < node->childCount; i++)
		{
			free_filesystem(node->children[i]);
		}
		free(node->children);
	}

	free(node->name);
	free(node);
}

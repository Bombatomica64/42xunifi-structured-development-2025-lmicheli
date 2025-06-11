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
		free(parent->children);
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

	FSNode *parent = node->parent;

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

int main(void)
{
	printf("Filesystem Tree Test\n");
	printf("/===================\\\n\n");

	// Create root directory
	FSNode *root = create_folder("home");
	if (!root)
	{
		printf("Failed to create root directory\n");
		return 1;
	}

	// Create user directory
	FSNode *user = create_folder("user");
	FSNode *documents = create_folder("Documents");
	FSNode *pictures = create_folder("Pictures");
	FSNode *downloads = create_folder("Downloads");

	// Create files
	FSNode *profile = create_file(".bashrc", 2048);
	FSNode *readme = create_file("README.txt", 1024);
	FSNode *report = create_file("project_report.pdf", 512000);
	FSNode *notes = create_file("meeting_notes.txt", 4096);
	FSNode *photo1 = create_file("vacation.jpg", 2048000);
	FSNode *photo2 = create_file("family.png", 1536000);
	FSNode *installer = create_file("software.deb", 8192000);
	FSNode *archive = create_file("backup.zip", 4194304);

	// Check for allocation failures
	if (!user || !documents || !pictures || !downloads ||
		!profile || !readme || !report || !notes ||
		!photo1 || !photo2 || !installer || !archive)
	{
		printf("Failed to create filesystem nodes\n");
		free_filesystem(root);
		return 1;
	}

	// Build directory structure
	add_child(root, user);
	add_child(root, readme);

	add_child(user, profile);
	add_child(user, documents);
	add_child(user, pictures);
	add_child(user, downloads);

	add_child(documents, report);
	add_child(documents, notes);

	add_child(pictures, photo1);
	add_child(pictures, photo2);

	add_child(downloads, installer);
	add_child(downloads, archive);

	// Print the tree structure
	print_structure(root, 2);

	// Free the filesystem
	free_filesystem(root);

	return 0;
}
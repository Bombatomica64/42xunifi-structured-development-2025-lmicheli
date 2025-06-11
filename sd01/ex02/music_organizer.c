#include "music_organizer.h"

struct MusicLibrary *organize_music_library(const char *directory_path)
{
	if (!directory_path)
		return NULL;
	struct MusicLibrary *library = create_music_library();
	if (!library)
		return NULL;
	const char **filenames = scan_directory(directory_path);
	if (!filenames)
	{
		return library; // Return empty library if no files found
	}
	for (int i = 0; filenames[i] != NULL; i++)
	{
		struct MusicFile *song = process_music_file(directory_path, filenames[i]);
		if (song)
		{
			update_music_library(library, song);
		}
		else
		{
			for (int j = 0; j < library->size; j++)
			{
				free(library->songs[j]->filename);
				free(library->songs[j]->artist);
				free(library->songs[j]->album);
				free(library->songs[j]);
			}
			free(library->songs);
			free(library);
			library = NULL;
			break;
		}
	}
	free(filenames);
	return library;
}
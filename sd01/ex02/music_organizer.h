#ifndef MUSIC_ORGANIZER_H
#define MUSIC_ORGANIZER_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MusicFile
{
	char *filename; // Name of the music file
	char *artist;	// Artist of the music file
	char *album;	// Album of the music file
	int duration;	// Duration of the music file in seconds
} MusicFile;

typedef struct MusicLibrary
{
	MusicFile **songs; // Array of pointers to MusicFile structures
	int size;		   // Number of songs in the library
	int capacity;	   // Capacity of the songs array
} MusicLibrary;

// Creates and returns a new music library. Returns NULL on fail
struct MusicLibrary *create_music_library();
// Scans a directory for music files. Returns a NULL terminated array of filenames.
const char **scan_directory(const char *directory_path);
// Processes a single music file. Returns a data structure representing the processed file.
struct MusicFile *process_music_file(const char *directory_path, const char *filename);
// Updates the music library with the processed music file information.
void update_music_library(struct MusicLibrary *library, struct MusicFile *song);

struct MusicLibrary *organize_music_library(const char *directory_path);

#endif // MUSIC_ORGANIZER_H
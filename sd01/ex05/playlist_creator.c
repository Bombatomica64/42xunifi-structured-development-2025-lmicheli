#include "playlist_creator.h"

struct Playlist *create_playlist(void)
{
	MoodSettings *mood = analyze_user_mood();
	if (!mood)
	{
		return NULL;
	}
	FilterSettings *filters = default_filters();
	if (!filters)
	{
		free_mood_settings(mood);
		return NULL;
	}
	while (get_mood_variations(mood))
	{
		filters = refine_filters(filters);
		if (!filters)
		{
			free_mood_settings(mood);
			return NULL;
		}
	}
	if (filters_require_popular_song(filters))
	{
		SongData *song = fetch_popular_song();
		if (!song)
		{
			free_mood_settings(mood);
			free_filter_settings(filters);
			return NULL;
		}
		struct Playlist *playlist = combine_with_mood_playlist(song, mood);
		free_song_data(song);
		free_mood_settings(mood);
		free_filter_settings(filters);
		return playlist;
	}
	else
	{
		SongData *song = fetch_niche_song();
		if (!song)
		{
			free_mood_settings(mood);
			free_filter_settings(filters);
			return NULL;
		}
		struct Playlist *playlist = combine_with_mood_playlist(song, mood);
		free_song_data(song);
		free_mood_settings(mood);
		free_filter_settings(filters);
		return playlist;
	}
	free_mood_settings(mood);
	free_filter_settings(filters);
	return NULL;
}
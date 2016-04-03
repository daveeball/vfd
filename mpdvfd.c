/*
 * HelloVFDWorld.c
 *
 *  Created on: 13 Mar 2016
 *      Author: daveb
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpd/client.h>
#include <mpd/tag.h>
#include <sys/time.h>
#include "futabaVfd.h"

// These macros are in sys/timer.h - not sure why I need to redefine them? Wrong flags?
# define timercmp(a, b, CMP) 						  \
  (((a)->tv_sec == (b)->tv_sec) ? 					  \
   ((a)->tv_usec CMP (b)->tv_usec) : 				  \
   ((a)->tv_sec CMP (b)->tv_sec))
# define timeradd(a, b, result)						  \
  do {									              \
    (result)->tv_sec = (a)->tv_sec + (b)->tv_sec;	  \
    (result)->tv_usec = (a)->tv_usec + (b)->tv_usec;  \
    if ((result)->tv_usec >= 1000000)				  \
      {									              \
	++(result)->tv_sec;						          \
	(result)->tv_usec -= 1000000;					  \
      }									              \
  } while (0)

/////////////////////////////////////////////////////////////////////

// libmpdclient trunk has new tags
// http://git.musicpd.org/cgit/master/libmpdclient.git/commit/?id=11b76ed4527d17153fc12f289bc1d59fabb6ea30
static const int TAG_TITLE = MPD_TAG_TITLE - 2;
static const int TAG_ARTIST = MPD_TAG_ARTIST;

/////////////////////////////////////////////////////////////////////

static int handle_error(struct mpd_connection *c) {
	assert(mpd_connection_get_error(c) != MPD_ERROR_SUCCESS);

	fprintf(stderr, "%s\n", mpd_connection_get_error_message(c));
	mpd_connection_free(c);
	return EXIT_FAILURE;
}

struct mpd_song* fetchSong(struct mpd_connection *conn) {
	mpd_command_list_begin(conn, true);
	mpd_send_current_song(conn);
	mpd_command_list_end(conn);

	struct mpd_song* song = mpd_recv_song(conn);

	if (mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS || !mpd_response_finish(conn))
		exit(handle_error(conn));

	return song;
}

const char* fetchTag(const struct mpd_song *song, enum mpd_tag_type type) {
	if (song == NULL)
		return "";

	unsigned i = 0;
	const char *value;
	while ((value = mpd_song_get_tag(song, type, i++)) != NULL)
		return value;

	printf("Failed to find tag. Falling back to URI.\n");
	return mpd_song_get_uri(song);
}

const char* buildSongDescription(const struct mpd_song *song) {
	const char* artist = fetchTag(song, TAG_ARTIST);
	const char* title = fetchTag(song, TAG_TITLE);

	char * s = malloc(snprintf(NULL, 0, "%s :: %s", artist, title) + 1);
	sprintf(s, "%s :: %s", artist, title);

	return s;
}

int updateRequired(struct timeval* nextUpdateTime) {
	if (nextUpdateTime == NULL) {
		return true;
	}
	struct timeval tNow;
	gettimeofday(&tNow, NULL);
	return timercmp(&tNow, nextUpdateTime, >);
}

void getNextUpdateTime(struct timeval* nextUpdateTime) {
	struct timeval tNow, tLong;
	gettimeofday(&tNow, NULL);

	tLong.tv_sec = 1;
	tLong.tv_usec = 0;
	timeradd(&tNow, &tLong, nextUpdateTime);
}

int differentSongUri(struct mpd_song* songOne, struct mpd_song* songTwo) {
	if (songOne == NULL && songTwo == NULL) {
		return false;
	}

	if (songOne == NULL && songTwo != NULL) {
		return true;
	}

	const char* songOneUri = mpd_song_get_uri(songOne);
	const char* songTwoUri = mpd_song_get_uri(songTwo);
	int sameUri = strcmp(songOneUri, songTwoUri);
	return sameUri != 0;
}

// sudo apt-get install wiringpi (or install from source)
// sudo usermod -a gpio [username]
int main(void) {
	struct mpd_connection *conn;
	conn = mpd_connection_new(NULL, 0, 30000);

	initRPi();
	initVfd();

	struct timeval lastUpdateTime;
	struct mpd_song* song;
	unsigned char *buffer = buildStringData("");
	int size = 0;

	int location = 0;
	for (;;) {
		if (updateRequired(&lastUpdateTime) || location == 0) {
			getNextUpdateTime(&lastUpdateTime);
			// at the end of each scroll, or once every couple of seconds.

			struct mpd_song* newSong = fetchSong(conn);
			if (differentSongUri(song, newSong)) {
				if (song != NULL) {
					mpd_song_free(song);
				}
				song = newSong;
				clearScreen();
				writeString("Now playing...");
				setCursor(0, 1);
				unsigned char *newBuffer = buildStringData(buildSongDescription(song));
				free(buffer);
				buffer = newBuffer;
				size = (buffer[1] * 256) + buffer[0];
				location = 0;
			} else if (newSong != NULL) {
				mpd_song_free(newSong);
			}
		}
		writePixels(112, 1, &buffer[2 + location]);
		if (location <= (size + 112)) {
			location++;
		} else {
			location = 0;
		}
		delayNanoSeconds(100);
	}

	return 0;
}

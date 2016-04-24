/*
 * mpdvfd.c
 *
 * MPD client that displays current song on a Futaba VFD.
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpd/client.h>
#include <mpd/tag.h>
#include <time.h>
#include <sys/time.h>
#include "futabaVfd.h"

static const unsigned char logo[174] = { 0x00, 0x01, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0F, 0x00, 0x1F, 0x00, 0x3F, 0x00, // 13
		0x7F, 0x00, 0xFE, 0x01, 0xFC, 0x03, 0xF8, 0x07, 0xF0, 0x0F, 0xE0, 0x1F, 0xE0, 0x3F, 0xE0, 0x7F, 0xE0, 0x7E, // 18
		0xE0, 0x7C, 0xE0, 0x78, 0xE0, 0x70, 0xE0, 0x70, 0xE0, 0x70, 0xE0, 0x70, 0xE0, 0x70, 0xC0, 0x71, 0xC0, 0x71, // 18
		0xC0, 0x73, 0xC0, 0x77, 0x80, 0x7F, 0x81, 0x7F, 0x83, 0x7F, 0x07, 0x7F, 0x0F, 0x7E, 0x1F, 0x7C, 0x3F, 0x38, // 18
		0x7F, 0x00, 0xFE, 0x01, 0xFC, 0x03, 0xF8, 0x07, 0xF0, 0x07, 0xE0, 0x07, 0xC0, 0x27, 0x80, 0x67, 0x00, 0xE6, // 18
		0x01, 0xE4, 0x03, 0xE0, 0x07, 0xE0, 0x0F, 0xE0, 0x1F, 0xC0, 0x3F, 0x80, 0x7F, 0x00, 0xFE, 0x01, 0xFC, 0x03, // 18
		0xF8, 0x07, 0xF0, 0x0F, 0xE0, 0x1F, 0xC0, 0x3F, 0xC0, 0x7F, 0xC0, 0x7F, 0xC0, 0x7D, 0xC0, 0x79, 0xC0, 0x71, // 18
		0xC0, 0x71, 0xC0, 0x71, 0xC0, 0x71, 0xC0, 0x71, 0x80, 0x71, 0x01, 0x70, 0x03, 0x70, 0x07, 0x70, 0x0F, 0x70, // 18
		0x1F, 0x70, 0x3F, 0x70, 0x7F, 0x70, 0xFE, 0x61, 0xFC, 0x43, 0xF8, 0x07, 0xF0, 0x07, 0xE0, 0x07, 0xC0, 0x27, // 18
		0x80, 0x67, 0x00, 0xE6, 0x00, 0xE4, 0x00, 0xE0, 0x00, 0xE0, 0x00, 0xE0, 0x00, 0xC0, 0x00, 0x80, 0x00 }; // 17

/////////////////////////////////////////////////////////////////////

// libmpdclient trunk has new tags
// http://git.musicpd.org/cgit/master/libmpdclient.git/commit/?id=11b76ed4527d17153fc12f289bc1d59fabb6ea30
static const int TAG_TITLE = MPD_TAG_TITLE - 2;
static const int TAG_ARTIST = MPD_TAG_ARTIST;

/////////////////////////////////////////////////////////////////////

void writeLogo() {
	writePixels(87, 2, (unsigned char*) logo);
}

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

int main(void) {

	initRPi();
	initVfd();

	clearScreen();
	setCursor(12, 0);
	writeLogo();
	delayMilliSeconds(10000);

	struct mpd_connection *conn;
	conn = mpd_connection_new(NULL, 0, 30000);
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
		delayMilliSeconds(50);
	}

	shutdownVfd();
	printf("Exiting... ...\n");
	return 0;
}

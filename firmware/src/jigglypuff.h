#ifndef JIGGLY_H
#define JIGGLY_H

#include "songs.h"

int melody_arr[250] = {

	// Jigglypuff's Song
	// Score available at https://musescore.com/user/28109683/scores/5044153
	
	NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
	NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
	NOTE_FS5,-4, NOTE_E5,8, NOTE_FS5,4,
	NOTE_D5,-2,
	NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
	NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
	NOTE_FS5,-1,
	NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
	NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
	
	NOTE_FS5,-4, NOTE_E5,8, NOTE_FS5,4,
	NOTE_D5,-2,
	NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
	NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
	NOTE_FS5,-1,
	
};

song jigglypuff = {	.name = "Jigglypuff",
	.tempo = 85,
	.melody = melody_arr,
	.notes = sizeof(melody_arr) / sizeof(melody_arr[0]) / 2
};

#endif
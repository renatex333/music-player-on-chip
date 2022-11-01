#ifndef ZELDA_H
#define ZELDA_H

#include "Songs.h"

song zelda = { .name = "Zelda",
	.tempo = 88,
	.melody = {
		
		/* 
			The legend of Zelda theme 
			Connect a piezo buzzer or speaker to pin 11 or select a new pin.
			More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
														Robson Couto, 2019
		*/
		 NOTE_AS4,-2,  NOTE_F4,8,  NOTE_F4,8,  NOTE_AS4,8,//1
		 NOTE_GS4,16,  NOTE_FS4,16,  NOTE_GS4,-2,
		 NOTE_AS4,-2,  NOTE_FS4,8,  NOTE_FS4,8,  NOTE_AS4,8,
		 NOTE_A4,16,  NOTE_G4,16,  NOTE_A4,-2,
		 REST,1,

		 NOTE_AS4,4,  NOTE_F4,-4,  NOTE_AS4,8,  NOTE_AS4,16,  NOTE_C5,16, NOTE_D5,16, NOTE_DS5,16,//7
		 NOTE_F5,2,  NOTE_F5,8,  NOTE_F5,8,  NOTE_F5,8,  NOTE_FS5,16, NOTE_GS5,16,
		 NOTE_AS5,-2,  NOTE_AS5,8,  NOTE_AS5,8,  NOTE_GS5,8,  NOTE_FS5,16,
		 NOTE_GS5,-8,  NOTE_FS5,16,  NOTE_F5,2,  NOTE_F5,4,

		 NOTE_DS5,-8, NOTE_F5,16, NOTE_FS5,2, NOTE_F5,8, NOTE_DS5,8, //11
		 NOTE_CS5,-8, NOTE_DS5,16, NOTE_F5,2, NOTE_DS5,8, NOTE_CS5,8,
		 NOTE_C5,-8, NOTE_D5,16, NOTE_E5,2, NOTE_G5,8,
		 NOTE_F5,16, NOTE_F4,16, NOTE_F4,16, NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,8, NOTE_F4,16,NOTE_F4,8,

		 NOTE_AS4,4,  NOTE_F4,-4,  NOTE_AS4,8,  NOTE_AS4,16,  NOTE_C5,16, NOTE_D5,16, NOTE_DS5,16,//15
		 NOTE_F5,2,  NOTE_F5,8,  NOTE_F5,8,  NOTE_F5,8,  NOTE_FS5,16, NOTE_GS5,16,
		 NOTE_AS5,-2, NOTE_CS6,4,
		 NOTE_C6,4, NOTE_A5,2, NOTE_F5,4,
		 NOTE_FS5,-2, NOTE_AS5,4,
		 NOTE_A5,4, NOTE_F5,2, NOTE_F5,4,

		 NOTE_FS5,-2, NOTE_AS5,4,
		 NOTE_A5,4, NOTE_F5,2, NOTE_D5,4,
		 NOTE_DS5,-2, NOTE_FS5,4,
		 NOTE_F5,4, NOTE_CS5,2, NOTE_AS4,4,
		 NOTE_C5,-8, NOTE_D5,16, NOTE_E5,2, NOTE_G5,8,
		 NOTE_F5,16, NOTE_F4,16, NOTE_F4,16, NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,8, NOTE_F4,16,NOTE_F4,8
	}
};

#endif
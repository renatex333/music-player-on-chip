#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#define BUZZ_PIO			PIOC
#define BUZZ_PIO_ID			ID_PIOC
#define BUZZ_PIO_IDX			19
#define BUZZ_PIO_IDX_MASK	(1 << BUZZ_PIO_IDX)

#define START_PIO			PIOC
#define START_PIO_ID		ID_PIOC
#define START_PIO_IDX		31
#define START_PIO_IDX_MASK	(1u << START_PIO_IDX)

#define SELECAO_PIO			 PIOD
#define SELECAO_PIO_ID		 ID_PIOD
#define SELECAO_PIO_IDX		 28
#define SELECAO_PIO_IDX_MASK (1u << SELECAO_PIO_IDX)


/* Definir as notas */
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0


/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);
void set_buzzer(void);
void clear_buzzer(void);
int get_startstop(void);
int get_selecao(void);
void buzzer_test(int);
void buzzer_play(double);
void tone(int, int);

/************************************************************************/
/* Criando as structs                                                   */
/************************************************************************/

typedef struct  {
	
	// change this to make the song slower or faster
	int tempo;
	
	// notes of the moledy followed by the duration.
	// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
	// !!negative numbers are used to represent dotted notes,
	// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
	int melody[250];
	
} song;

void set_buzzer()
{
	BUZZ_PIO->PIO_SODR = BUZZ_PIO_IDX_MASK;
}

void clear_buzzer()
{
	BUZZ_PIO->PIO_CODR =  BUZZ_PIO_IDX_MASK;
}


int get_startstop()
{
	uint32_t status;
	Pio *p_pio = START_PIO;
	status = p_pio->PIO_ODSR;
	
	if(status && START_PIO_IDX_MASK == 0){
		return 0;
	} else {
		return 1;
	}
}

int get_selecao()
{
	uint32_t status;
	Pio *p_pio = SELECAO_PIO;
	status = p_pio->PIO_ODSR;
	
	if(status && SELECAO_PIO_IDX_MASK == 0){
		return 0;
		} else {
		return 1;
	}
}

void init(void){
		board_init();
		sysclk_init();
		delay_init();
		
		WDT->WDT_MR = WDT_MR_WDDIS;
		
		pmc_enable_periph_clk(ID_PIOC);
		
		//BUZZER
		pio_set_output(BUZZ_PIO, BUZZ_PIO_IDX_MASK, 0, 0, 0);
		
		//START BUTTON
		pio_set_input(START_PIO, START_PIO_IDX_MASK, PIO_DEFAULT);
		
		//SELEÇÃO BUTTON
		pio_set_input(SELECAO_PIO, SELECAO_PIO_IDX_MASK, PIO_DEFAULT);
		
		
			
		
}

void buzzer_test(int freq)
{
	set_buzzer();
	delay_us(500000/freq);
	clear_buzzer();
	delay_us(500000/freq);
}

void buzzer_play(double delay_time)
{
	set_buzzer();
	delay_us(delay_time);
	clear_buzzer();
	delay_us(delay_time);
}

/*
 * freq: Frequecia em Hz
 * time: Tempo em ms que o tom deve ser gerado
 */

void tone(int freq, int time){
	double delay_time = 500000/freq;
	double duracao = (time*freq)/(1000);
	for(int i = 0; i < (int) duracao; i++){
		buzzer_play(delay_time);
	}
	
	
	//float p = ((1.0/freq)/2.0)*1000000;
	//int duracao = (time * 1000000)/(p * 2);
	//for(int i = 0; i < duracao; i++){
		//set_buzzer();
		//delay_us(p);
		//clear_buzzer();
		//delay_us(p);
	//}
}


int main (void)
{
	init();
	
	// Cria os Structs das músicas que utilizaremos
	song mario = {	.tempo = 200,
					.melody = {

							// Super Mario Bros theme
							// Score available at https://musescore.com/user/2123/scores/2145
							// Theme by Koji Kondo
							
							
							NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
							NOTE_G5,4, REST,4, NOTE_G4,8, REST,4,
							NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
							NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
							NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
							REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
							NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
							NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
							NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
							REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

							
							REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//7
							REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
							REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
							NOTE_C5,2, REST,2,

							REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//repeats from 7
							REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
							REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
							NOTE_C5,2, REST,2,

							NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,//11
							NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,

							NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,//13
							REST,1,
							NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
							NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
							NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
							NOTE_G5,4, REST,4, NOTE_G4,4, REST,4,
							NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 19
							
							NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
							NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
							REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

							NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 19
							NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
							NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
							REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

							NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//23
							NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
							NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
							
							NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
							NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
							NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
							NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
							NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,

							NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//repeats from 23
							NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
							NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
							
							NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
							NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
							NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
							NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
							NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
							NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
							REST,1,

							NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, //33
							NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
							NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
							NOTE_G5,4, REST,4, NOTE_G4,4, REST,4,
							NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
							NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
							NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
							
							NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //40
							NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
							NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
							NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
							NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
							
							//game over sound
							NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
							NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
							NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,

						}
	};
	
	song jigglypuff = {	.tempo = 85,
						.melody = {

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
							
						}
	};

	song nevergonnagiveyouup = { .tempo = 114,
								 .melody = {

								// Never Gonna Give You Up - Rick Astley
								// Score available at https://musescore.com/chlorondria_5/never-gonna-give-you-up_alto-sax
								// Arranged by Chlorondria

								NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //1
								NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
								NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
								NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
								NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //repeat from 1
								NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
								NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
								NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
								REST,4, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_D5,8, NOTE_E5,8, NOTE_CS5,-8,
								NOTE_B4,16, NOTE_A4,2, REST,4,

								REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,4, NOTE_A4,8, //7
								NOTE_A5,8, REST,8, NOTE_A5,8, NOTE_E5,-4, REST,4,
								NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,8, REST,8,
								REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
								REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
								NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, REST,4,
			
								NOTE_D5,2, NOTE_E5,8, NOTE_FS5,8, NOTE_D5,8, //13
								NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, NOTE_A4,4,
								REST,2, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8,
								REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
								NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

								NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,-8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //18
								NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,8, NOTE_A4,8, NOTE_A4,8,
								NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
								NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
								NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

								NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  //23
								NOTE_E5,4, NOTE_D5,2, REST,4,
								REST,8, NOTE_B4,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,4, REST,8,
								REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
								REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
								REST,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, NOTE_D5,8,
			
								REST,8, NOTE_A4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, //29
								REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
								NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4, REST,8,
								REST,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,4, NOTE_E5,-4,
								NOTE_D5,2, NOTE_D5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4,
								NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, NOTE_A4,8, NOTE_A4,4,

								REST,-4, NOTE_A4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, //35
								REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
								NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
								NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
								NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,

								NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //40
								NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
								NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
								NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,
								NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
			
								NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //45
								NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
								NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,
								NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
								NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //45
			
								NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
								NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,

								NOTE_E5,4, NOTE_D5,2, REST,4
							}
	};

	song gameofthrones = { .tempo = 85,
						   .melody = {

							// Game of Thrones
							// Score available at https://musescore.com/user/8407786/scores/2156716

							NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16, //1
							NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16,
							NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16,
							NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16,
							NOTE_G4,-4, NOTE_C4,-4,//5

							NOTE_DS4,16, NOTE_F4,16, NOTE_G4,4, NOTE_C4,4, NOTE_DS4,16, NOTE_F4,16, //6
							NOTE_D4,-1, //7 and 8
							NOTE_F4,-4, NOTE_AS3,-4,
							NOTE_DS4,16, NOTE_D4,16, NOTE_F4,4, NOTE_AS3,-4,
							NOTE_DS4,16, NOTE_D4,16, NOTE_C4,-1, //11 and 12

							//repeats from 5
							NOTE_G4,-4, NOTE_C4,-4,//5

							NOTE_DS4,16, NOTE_F4,16, NOTE_G4,4, NOTE_C4,4, NOTE_DS4,16, NOTE_F4,16, //6
							NOTE_D4,-1, //7 and 8
							NOTE_F4,-4, NOTE_AS3,-4,
							NOTE_DS4,16, NOTE_D4,16, NOTE_F4,4, NOTE_AS3,-4,
							NOTE_DS4,16, NOTE_D4,16, NOTE_C4,-1, //11 and 12
							NOTE_G4,-4, NOTE_C4,-4,
							NOTE_DS4,16, NOTE_F4,16, NOTE_G4,4,  NOTE_C4,4, NOTE_DS4,16, NOTE_F4,16,

							NOTE_D4,-2,//15
							NOTE_F4,-4, NOTE_AS3,-4,
							NOTE_D4,-8, NOTE_DS4,-8, NOTE_D4,-8, NOTE_AS3,-8,
							NOTE_C4,-1,
							NOTE_C5,-2,
							NOTE_AS4,-2,
							NOTE_C4,-2,
							NOTE_G4,-2,
							NOTE_DS4,-2,
							NOTE_DS4,-4, NOTE_F4,-4,
							NOTE_G4,-1,
			
							NOTE_C5,-2,//28
							NOTE_AS4,-2,
							NOTE_C4,-2,
							NOTE_G4,-2,
							NOTE_DS4,-2,
							NOTE_DS4,-4, NOTE_D4,-4,
							NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16, NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16,
							NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16, NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16,
			
							REST,4, NOTE_GS5,16, NOTE_AS5,16, NOTE_C6,8, NOTE_G5,8, NOTE_GS5,16, NOTE_AS5,16,
							NOTE_C6,8, NOTE_G5,16, NOTE_GS5,16, NOTE_AS5,16, NOTE_C6,8, NOTE_G5,8, NOTE_GS5,16, NOTE_AS5,16
						}
	};
		
	// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
	// there are two values per note (pitch and duration), so for each note there are four bytes
	
	// jigglypuff.melody
	int notes = sizeof(nevergonnagiveyouup.melody) / sizeof(nevergonnagiveyouup.melody[0]) / 2;

	// this calculates the duration of a whole note in ms
	int wholenote = (60000 * 4) / nevergonnagiveyouup.tempo;

	int divider = 0;

	int noteDuration = 0;
	
	
	

	// Init OLED
	//gfx_mono_ssd1306_init();
  
    // Escreve na tela um circulo e um texto
	//gfx_mono_draw_filled_circle(20, 16, 16, GFX_PIXEL_SET, GFX_WHOLE);
	//gfx_mono_draw_string("mundo", 50,16, &sysfont);
	
	
	/* Insert application code here, after the board has been initialized. */
	//buzzer_test(440);
	while(1) {
		// iterate over the notes of the melody.
		// Remember, the array is twice the number of notes (notes + durations)
		for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

			// calculates the duration of each note
			divider = nevergonnagiveyouup.melody[thisNote + 1];
			noteDuration = (wholenote) / abs(divider);
			if (divider < 0) {
				noteDuration *= 1.5; // increases the duration in half for dotted notes
			}

			// we only play the note for 90% of the duration, leaving 10% as a pause
			tone(nevergonnagiveyouup.melody[thisNote], noteDuration * 0.9);

			// Wait for the specief duration before playing the next note.
			delay_ms(noteDuration * 0.1);
		}
	}
}

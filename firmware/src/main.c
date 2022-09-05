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
void tone(int, int);

void startstop_callback(void);

/************************************************************************/
/* variaveis globais e flags                                            */
/************************************************************************/

volatile int stop = 0;

volatile char buzz_flag;
volatile char stop_flag;
volatile char selecao_flag;

/************************************************************************/
/* handler / callbacks                                                  */
/************************************************************************/

void startstop_callback(void)
{
	stop_flag = 1;
}

void selecao_callback(void)
{
	selecao_flag = 1;
}

void buzz_callback(void)
{
	buzz_flag = 1;
}
/************************************************************************/
/* Criando as structs                                                   */
/************************************************************************/

typedef struct {
	
	// change this to make the song slower or faster
	int tempo;
	
	// notes of the moledy followed by the duration.
	// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
	// !!negative numbers are used to represent dotted notes,
	// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
	int melody[];
	
} song;

int melody[] = {

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

/************************************************************************/
/* Funções                                                              */
/************************************************************************/

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

void buzzer_test(int freq)
{
	set_buzzer();
	delay_us(500000/freq);
	clear_buzzer();
	delay_us(500000/freq);
}

/**
 * freq: Frequecia em Hz
 * time: Tempo em ms que o tom deve ser gerado
 */
void tone(int freq, int time){
	double duracao = (time*freq)/(1000);
	for(int i = 0; i < (int) duracao; i++){
		buzzer_test(freq);
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

		pio_configure(BUZZ_PIO, PIO_OUTPUT_0, BUZZ_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
		pio_set_debounce_filter(BUZZ_PIO, BUZZ_PIO_IDX_MASK, 60);
		
		//START BUTTON
		pio_configure(START_PIO, PIO_INPUT, START_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
		pio_set_debounce_filter(START_PIO, START_PIO_IDX_MASK, 60);
		
		//SELE��O BUTTON
		pio_configure(SELECAO_PIO, PIO_INPUT, SELECAO_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
		pio_set_debounce_filter(SELECAO_PIO, SELECAO_PIO_IDX_MASK, 120);
		
		// associacao callback

		pio_handler_set(BUZZ_PIO,
						BUZZ_PIO_IDX,
						BUZZ_PIO_IDX_MASK,
						PIO_IT_FALL_EDGE,
						buzz_callback);

		pio_handler_set(START_PIO,
						START_PIO_IDX,
						START_PIO_IDX_MASK,
						PIO_IT_FALL_EDGE,
						startstop_callback);
		
		pio_handler_set(SELECAO_PIO,
						SELECAO_PIO_ID,
						SELECAO_PIO_IDX_MASK,
						PIO_IT_EDGE,
						selecao_callback);
		
		// ativa interrupcao e limpa primeira IRQ
		pio_enable_interrupt(BUZZ_PIO, BUZZ_PIO_IDX_MASK);
		pio_get_interrupt_status(BUZZ_PIO);

		pio_enable_interrupt(START_PIO, START_PIO_IDX_MASK);
		pio_get_interrupt_status(START_PIO);
		
		pio_enable_interrupt(SELECAO_PIO, SELECAO_PIO_IDX_MASK);
		pio_get_interrupt_status(SELECAO_PIO);
		
		// configuracao NVIC
		NVIC_EnableIRQ(BUZZ_PIO_ID);
		NVIC_SetPriority(BUZZ_PIO_ID, 8);

		NVIC_EnableIRQ(START_PIO_ID);
		NVIC_SetPriority(START_PIO_ID, 6);
		
		NVIC_EnableIRQ(SELECAO_PIO_ID);
		NVIC_SetPriority(SELECAO_PIO_ID, 2);	
}


int main (void)
{
	init();

	int tempo = 85;
		
	// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
	// there are two values per note (pitch and duration), so for each note there are four bytes
	int notes = sizeof(melody) / sizeof(melody[0]) / 2;

	// this calculates the duration of a whole note in ms
	int wholenote = (60000 * 4) / tempo;

	int divider = 0;

	int noteDuration = 0;
	
	while(1) {
		// iterate over the notes of the melody.
		// Remember, the array is twice the number of notes (notes + durations)
		
			
			for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
				// calculates the duration of each note
				divider = melody[thisNote + 1];
				noteDuration = (wholenote) / abs(divider);
				if (divider < 0) {
					noteDuration *= 1.5; // increases the duration in half for dotted notes
				}
				
				// we only play the note for 90% of the duration, leaving 10% as a pause
				tone(melody[thisNote], noteDuration * 0.9);

				// Wait for the specief duration before playing the next note.
				delay_ms(noteDuration * 0.1);
				
		}

		}
		
}

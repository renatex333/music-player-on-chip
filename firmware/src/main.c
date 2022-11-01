#include <asf.h>


//Inclui o arquivo Header Songs, que contem o struct e define das notas
#include "songs.h"

//Musicas incluidas
#include "jigglypuff.h"
#include "nevergonnagiveyouup.h"
#include "gameofthrones.h"
#include "zelda.h"
#include "doom.h"
#include "starwars.h"

//Inclui definições de pinos
#include "defines.h"

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

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

void startstop_callback(void);
void selecao_callback(void);

/************************************************************************/
/* variaveis globais e flags                                            */
/************************************************************************/

volatile char stop_flag;
volatile char play_flag;
volatile char selecao_flag;
volatile char stopped_flag;

char songname[10];

/************************************************************************/
/* handler / callbacks                                                  */
/************************************************************************/

void startstop_callback(void)
{
	if(stop_flag){
		stop_flag = 0;
	} else {
		stop_flag = 1;
	}
	
}


void selecao_callback(void)
{
	selecao_flag = 1;
}

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
		if(selecao_flag || stop_flag){
			break;
		}
		if(time >= 900){
			pio_clear(LED3_PIO, LED3_PIO_IDX_MASK);
		}
		if(time < 900 && time > 400){
			pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);
		}
		if(time <= 400){
			pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
		}
		
		buzzer_test(freq);
	}
}

void playsong(song now_playing){
		// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
		// there are two values per note (pitch and duration), so for each note there are four bytes
		
		// jigglypuff.melody
		int notes = sizeof(now_playing.melody) / sizeof(now_playing.melody[0]) / 2;

		// this calculates the duration of a whole note in ms
		int wholenote = (60000 * 4) / now_playing.tempo;

		int divider = 0;

		int noteDuration = 0;
		
		// iterate over the notes of the melody.
		// Remember, the array is twice the number of notes (notes + durations)
		for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
			if(selecao_flag){
				 return;
			}
			if(stop_flag){
				pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
				pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
				pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
				
				pmc_sleep(SAM_PM_SMODE_SLEEP_WFI);
			}
			
			// calculates the duration of each note
			divider = now_playing.melody[thisNote + 1];
			noteDuration = (wholenote) / abs(divider);
			if (divider < 0) {
				noteDuration *= 1.5; // increases the duration in half for dotted notes
			}
			
			// we only play the note for 90% of the duration, leaving 10% as a pause
			tone(now_playing.melody[thisNote], noteDuration * 0.9);
			
			
			pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
			pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
			pio_set(LED1_PIO, LED1_PIO_IDX_MASK);

			delay_us(30000);
		}

		// Wait for the specify duration before playing the next note.
		delay_ms(noteDuration * 0.1);
		
		
}


void init(void){
		board_init();
		sysclk_init();
		delay_init();
		
		WDT->WDT_MR = WDT_MR_WDDIS;
		
		pmc_enable_periph_clk(BUZZ_PIO);
		pmc_enable_periph_clk(START_PIO);
		pmc_enable_periph_clk(SELECAO_PIO);
		pmc_enable_periph_clk(LED1_PIO);
		pmc_enable_periph_clk(LED2_PIO);
		pmc_enable_periph_clk(LED3_PIO);
		
		// Configura led
		pio_configure(LED1_PIO, PIO_OUTPUT_0, LED1_PIO_IDX_MASK ,PIO_DEFAULT);
		pio_configure(LED2_PIO, PIO_OUTPUT_0, LED2_PIO_IDX_MASK ,PIO_DEFAULT);
		pio_configure(LED3_PIO, PIO_OUTPUT_0, LED3_PIO_IDX_MASK ,PIO_DEFAULT);
		
		pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
		pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
		pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
		
		
		
		//BUZZER
		pio_set_output(BUZZ_PIO, BUZZ_PIO_IDX_MASK, 0, 0, 0);

		pio_configure(BUZZ_PIO, PIO_OUTPUT_0, BUZZ_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
		pio_set_debounce_filter(BUZZ_PIO, BUZZ_PIO_IDX_MASK, 60);
		
		//START BUTTON
		pio_configure(START_PIO, PIO_INPUT, START_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
		pio_set_debounce_filter(START_PIO, START_PIO_IDX_MASK, 120);
		
		//SELEÇÃO BUTTON
		pio_configure(SELECAO_PIO, PIO_INPUT, SELECAO_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
		pio_set_debounce_filter(SELECAO_PIO, SELECAO_PIO_IDX_MASK, 120);
		
		// associacao callback
		pio_handler_set(START_PIO,
						START_PIO_ID,
						START_PIO_IDX_MASK,
						PIO_IT_FALL_EDGE,
						startstop_callback);
		
		pio_handler_set(SELECAO_PIO,
						SELECAO_PIO_ID,
						SELECAO_PIO_IDX_MASK,
						PIO_IT_FALL_EDGE,
						selecao_callback);
		
		// ativa interrupcao e limpa primeira IRQ

		pio_enable_interrupt(START_PIO, START_PIO_IDX_MASK);
		pio_get_interrupt_status(START_PIO);
		
		pio_enable_interrupt(SELECAO_PIO, SELECAO_PIO_IDX_MASK);
		pio_get_interrupt_status(SELECAO_PIO);
		
		// configuracao NVIC
		NVIC_EnableIRQ(START_PIO_ID);
		NVIC_SetPriority(START_PIO_ID, 4);
		
		NVIC_EnableIRQ(SELECAO_PIO_ID);
		NVIC_SetPriority(SELECAO_PIO_ID, 4);
}


int main (void)
{
	init();
	gfx_mono_ssd1306_init();
	
	song selecao_musicas[6] = {jigglypuff, nevergonnagiveyouup, gameofthrones, zelda, doom, starwars};
	int i = 0; // Index para seleção das músicas do array
	
	while(1) {
		if(selecao_flag){
			selecao_flag = 0;
			i++;
			if(i > 5){
				i = 0;
			}
			gfx_mono_draw_string("               ", 0, 0, &sysfont);
		}
		sprintf(songname, "%s", selecao_musicas[i].name);
		gfx_mono_draw_string(songname, 0, 0, &sysfont);
		playsong(selecao_musicas[i]);		
	}
}

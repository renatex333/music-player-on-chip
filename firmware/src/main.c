#include <asf.h>
#include <string.h>


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

char songname[12];

/************************************************************************/
/* handler / callbacks                                                  */
/************************************************************************/

void startstop_callback(void)
{
	stop_flag = !stop_flag;
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
	if(freq == 0){
		//recebe em milisegundos e multiplica por 1000 para converter para microsegundos
		delay_us(time*1000);
	} else {
		double duracao = (time*freq)/(100);
		if(time >= 900){
			pio_clear(LED3_PIO, LED3_PIO_IDX_MASK);
		} else if(time < 900 && time > 400){
			pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);
		} else if(time <= 400){
			pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
		}
		for(int i = 0; i < (int) duracao; i++){
			if(selecao_flag || stop_flag){
				break;
			}
			buzzer_test(freq);
		}
	}
}

void playsong(Song *now_playing){
		// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
		// there are two values per note (pitch and duration), so for each note there are four bytes

		int divider = 0;

		int noteDuration = 0;
		
		// iterate over the notes of the melody.
		// Remember, the array is twice the number of notes (notes + durations)
		for (int thisNote = 0; thisNote < ((*now_playing).notes) * 2; thisNote = thisNote + 2) {
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
			divider = (*now_playing).melody[thisNote + 1];
			
			noteDuration = ((*now_playing).wholenote) / abs(divider);
			if (divider < 0) {
				noteDuration *= 1.5; // increases the duration in half for dotted notes
			}
			
			if ((*now_playing).melody[thisNote] == 0){
				// Wait for the specief duration before playing the next note.
				delay_ms(noteDuration);
			} else {
				// we only play the note for 90% of the duration, leaving 10% as a pause
				tone((*now_playing).melody[thisNote], noteDuration * 0.9);
				// Wait for the specified duration before playing the next note.
				delay_ms(noteDuration * 0.4);
			}
			
			pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
			pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
			pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
			
		}
		delay_ms(100);
}

void init_songs(Song *song, char name[12], int tempo, int *melody_array, int size_array, int size_array_element){
	strcpy(song->name, name);
	song->tempo = tempo;
	song->melody = &melody_array[0];
	song->wholenote = (6000 * 4)/(song->tempo);
	song->notes = size_array / size_array_element / 2;
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
	
	Song jigglypuff;
	Song nevergonnagiveyouup;
	Song gameofthrones;
	Song zelda;
	Song doom;
	Song starwars;
	
	// Cria um array de pointers para as structs das músicas para otimizar o uso de memória
	Song *selecao_musicas[6] = {&jigglypuff, &nevergonnagiveyouup, &gameofthrones, &zelda, &doom, &starwars};
		
	init_songs(&jigglypuff, "Jigglypuff", 85, melody_jigglypuff, sizeof(melody_jigglypuff), sizeof(melody_jigglypuff[0]));
	init_songs(&nevergonnagiveyouup, "Rick Roll ", 114, melody_nevergonnagiveyouup, sizeof(melody_nevergonnagiveyouup), sizeof(melody_nevergonnagiveyouup[0]));
	init_songs(&gameofthrones, "GOT Theme", 85, melody_gameofthrones, sizeof(melody_gameofthrones), sizeof(melody_gameofthrones[0]));
	init_songs(&zelda, "Zelda", 88, melody_zelda, sizeof(melody_zelda), sizeof(melody_zelda[0]));
	init_songs(&doom, "Doom", 225, melody_doom, sizeof(melody_doom), sizeof(melody_doom[0]));
	init_songs(&starwars, "StarWars", 108, melody_starwars, sizeof(melody_starwars), sizeof(melody_starwars[0]));
	
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
		sprintf(songname, "%s", selecao_musicas[i]->name);
		gfx_mono_draw_string(songname, 0, 0, &sysfont);
		playsong(selecao_musicas[i]);		
	}
}

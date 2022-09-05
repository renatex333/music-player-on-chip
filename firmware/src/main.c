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
	delay_us(1000000/freq);
	clear_buzzer();
	delay_us(1000000/freq);
}

/**
 * freq: Frequecia em Hz
 * time: Tempo em ms que o tom deve ser gerado
 */
void tone(int freq, int time){
	for(int i = 0; i < (time*freq)/2; i++){
		buzzer_test(freq);
	}
}


int main (void)
{
	init();
	

	// Init OLED
	//gfx_mono_ssd1306_init();
  
  // Escreve na tela um circulo e um texto
	//gfx_mono_draw_filled_circle(20, 16, 16, GFX_PIXEL_SET, GFX_WHOLE);
	//gfx_mono_draw_string("mundo", 50,16, &sysfont);
	
	
  /* Insert application code here, after the board has been initialized. */
	//buzzer_test(440);
	while(1) {
		for (int freq=200; freq<5000; freq+=500){
			tone(freq, 5);
			delay_ms(200);
		}
	}
}

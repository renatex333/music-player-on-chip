#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#define BUZZ_PIO			PIOC
#define BUZZ_PIO_ID			ID_PIOC
#define BUZZ_PIO_IDX			19
#define BUZZ_PIO_IDX_MASK	(1 << BUZZ_PIO_IDX)

void set_buzzer(Pio *p_pio, const uint32_t ul_mask)
{
	
	p_pio->PIO_SODR = ul_mask;_
}

void clear_buzzer(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_CODR = ul_mask;
}

void init(void){
		board_init();
		sysclk_init();
		delay_init();
		
		WDT->WDT_MR = WDT_MR_WDDIS;
		
		pmc_enable_periph_clk(ID_PIOC);
		
		pio_set_output(BUZZ_PIO, BUZZ_PIO_IDX_MASK, 0, 0, 0);
		
		
		
		
		
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
	while(1) {

	}
}

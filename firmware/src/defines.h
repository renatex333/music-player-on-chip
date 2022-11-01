#ifndef DEFINES_H
#define DEFINES_H

#include <asf.h>

#define BUZZ_PIO			PIOC
#define BUZZ_PIO_ID			ID_PIOC
#define BUZZ_PIO_IDX		19
#define BUZZ_PIO_IDX_MASK	(1 << BUZZ_PIO_IDX)

#define START_PIO			PIOC
#define START_PIO_ID		ID_PIOC
#define START_PIO_IDX		31
#define START_PIO_IDX_MASK	(1 << START_PIO_IDX)

#define SELECAO_PIO			 PIOD
#define SELECAO_PIO_ID		 ID_PIOD
#define SELECAO_PIO_IDX		 28
#define SELECAO_PIO_IDX_MASK (1 << SELECAO_PIO_IDX)

#define LED1_PIO				 PIOA
#define LED1_PIO_ID				 ID_PIOA
#define LED1_PIO_IDX			 0
#define LED1_PIO_IDX_MASK		 (1 << LED1_PIO_IDX)

#define LED2_PIO				 PIOC
#define LED2_PIO_ID				 ID_PIOC
#define LED2_PIO_IDX			 30
#define LED2_PIO_IDX_MASK		 (1 << LED2_PIO_IDX)

#define LED3_PIO				 PIOB
#define LED3_PIO_ID				 ID_PIOB
#define LED3_PIO_IDX			 2
#define LED3_PIO_IDX_MASK		 (1 << LED3_PIO_IDX)

/*  Default pin configuration (no attribute). */
#define _PIO_DEFAULT             (0u << 0)
/*  The internal pin pull-up is active. */
#define _PIO_PULLUP              (1u << 0)
/*  The internal glitch filter is active. */
#define _PIO_DEGLITCH            (1u << 1)
/*  The internal debouncing filter is active. */
#define _PIO_DEBOUNCE            (1u << 3)

#endif
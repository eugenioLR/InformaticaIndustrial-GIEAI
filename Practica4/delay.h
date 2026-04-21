#ifndef DELAY_H
#define DELAY_H

#include <LPC17xx.h>

// Comentar antes de cargar a placa
#define DEBUG

#ifdef DEBUG
		#define TICKS_1ms_10MHz 200
#else
		#define TICKS_1ms_10MHz 2000
#endif

extern volatile uint32_t CONTADOR_MS;

void configurar_timer(void);
void delay_activo_simple(uint32_t ticks);
void delay_activo_timer(uint32_t ms);


#endif

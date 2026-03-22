#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

// Comentar antes de cargar a placa
#define DEBUG

#ifdef DEBUG
		#define TICKS_1ms_10MHz 200
#else
		#define TICKS_1ms_10MHz 2000
#endif

void delay(uint32_t ticks);

#endif

#ifndef BUFFER_CIRCULAR_H
#define BUFFER_CIRCULAR_H

#define NELEMENTOS 15
#define TAMBUFFER NELEMENTOS + 1 

#include <stdint.h>

typedef struct 
{
	uint16_t memoria[TAMBUFFER];
	volatile uint16_t idx_mete;
	volatile uint16_t idx_saca;
} buffer_circular_t;

extern buffer_circular_t BUFFER;

void iniciar_buffer(void);
uint8_t vacio(buffer_circular_t buffer);
uint8_t lleno(buffer_circular_t buffer);
uint8_t insertar(buffer_circular_t* buffer, uint16_t valor);
uint8_t pop(buffer_circular_t* buffer, uint16_t* dato);
uint16_t n_elementos(buffer_circular_t buffer);


#endif

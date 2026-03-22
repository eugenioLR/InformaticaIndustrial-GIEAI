#include "delay.h"
/*
	Espera activa implementada como un bulce "for" simple.
	Nota: cada iteracion consume 5 ciclos de reloj (5 instrucciones en MCU).
*/
void delay(uint32_t ticks){
	// Declaramos el contador como una variable 'volatile' para evitar que el compilador la elimine.
	volatile uint32_t i = 0;
	for(i = 0; i < ticks; i++);
}

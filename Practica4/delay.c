#include "delay.h"

volatile uint32_t CONTADOR_MS = 0;

/*
	Espera activa implementada como un bulce "for" simple.
	Nota: cada iteracion consume 5 ciclos de reloj (5 instrucciones en MCU).
*/
void delay_activo_simple(uint32_t ticks){
	// Declaramos el contador como una variable 'volatile' para evitar que el compilador la elimine.
	volatile uint32_t i = 0;
	for(i = 0; i < ticks; i++);
}

void configurar_timer()
{
	// Contamos cuantos ciclos de reloj son equivalentes a 1ms
	// SystemCoreClock en Hz (ticks/s)
	//uint32_t ticks_1ms = SystemCoreClock / 1000; // 1ms
	uint32_t ticks_1ms = 100000000 / 1000; // 1ms
	
	// Configurar para que se lance una interrupción cada 1ms
	SysTick->LOAD = ticks_1ms  - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = (1 << 2) | (1 << 1) | (1 << 0);
	
	// Damos la maxima prioridad al timer
	NVIC_SetPriority(SysTick_IRQn, 0);
}

void SysTick_Handler(void)
{
	CONTADOR_MS++;
}

void delay_activo_timer(uint32_t ms)
{
	volatile uint32_t objetivo_tiempo = CONTADOR_MS + ms;
	while(CONTADOR_MS < objetivo_tiempo);
}

#include "manejar_IRQ.h"

void configurar_IRQ()
{
	// Activamos los puertos 2.10, 2.11 y  2.12 para configurar EINT0, EINT1 and EINT2 asignando a cada uno el valor 01.
	// Necesitamos activar los bits 20, 22 y 24.
	LPC_PINCON->PINSEL4 |= (1u << 20);
	LPC_PINCON->PINSEL4 |= (1u << 22);
	LPC_PINCON->PINSEL4 |= (1u << 24);

	// Activamos los bits 0, 1 y 2 para configurar EINT0, EINT1, EINT2 como activos en flanco de subida/bajada.
	LPC_SC->EXTMODE |= (1u << 0);
	LPC_SC->EXTMODE |= (1u << 1);
	LPC_SC->EXTMODE |= (1u << 2);
	
	// Configuramos EINT0 y EINT2 para activarse en flanco de bajada y EINT1 en flanco de subida.
	// Necesitamos que EINT1 se active en flanco de bajada y subida, reconfiguramos cuando encontremos uno de los flancos.
	LPC_SC->EXTPOLAR &= ~(1u << 0);
	LPC_SC->EXTPOLAR &= ~(1u << 1);
	LPC_SC->EXTPOLAR &= ~(1u << 2);
	
	// Asignamos prioridades DISTINTAS a cada interrupcion (no 0, reservado para timer)
	NVIC->IP[EINT0_IRQn] = (1 << 3);
	NVIC->IP[EINT1_IRQn] = (2 << 3);
	NVIC->IP[EINT2_IRQn] = (3 << 3);
	
	// Activamos la escucha a las interrupciones EINT0, EINT1 y EINT2
	NVIC->ISER[0] |= (1u << 18);
	NVIC->ISER[0] |= (1u << 19);
	NVIC->ISER[0] |= (1u << 20);
	
	
	// Nos aseguramos de que los flags de interrupciones empiezan apagados
	LPC_SC->EXTINT &= ~(1u << 0);
	LPC_SC->EXTINT &= ~(1u << 1);
	LPC_SC->EXTINT &= ~(1u << 2);
}

void EINT0_IRQHandler()
{
	// Reseteamos el flag de interrupcion
	LPC_SC->EXTINT |= (1 << 0);
	
	// Cambiamos el modo de visualizacion de los numeros de display de 7 segmentos a LEDs.
	MOSTRAR_DISPLAY7SEG = !MOSTRAR_DISPLAY7SEG;
}

void EINT1_IRQHandler()
{
	uint32_t direccion_flanco;
	
	// Reseteamos el flag de interrupcion
	LPC_SC->EXTINT |= (1 << 1);
	
	// En flanco de subida tendremos un 1 despues del flanco.
	// En flanco de bajada tendremos un 0 despues del flanco.
	direccion_flanco = (LPC_SC->EXTPOLAR >> 1) & 1u;
	if(direccion_flanco != 0)
		VALOR_INIT = leer_numero();
	else
		VALOR_FIN = leer_numero();
	
	// Reconfiguramos la polaridad de la deteccion del flanco. invertimos el valor del bit 2.
	LPC_SC->EXTPOLAR = LPC_SC->EXTPOLAR ^ (1u << 1);
}

void EINT2_IRQHandler()
{
	// Reseteamos el flag de interrupcion
	LPC_SC->EXTINT |= (1 << 2);
	
	// Invertimos la direccion del bucle.
	DIR_BUCLE = !DIR_BUCLE;	
}

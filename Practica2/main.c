#include <LPC17xx.h>
#define MAX_INT16 0xFFFF 							// = 65535
#define TICKS_1ms_10MHz 2000
#define N_PRIMOS_16BITS 6542

// Declaramos el array
uint16_t arr_primos[N_PRIMOS_16BITS];

/*
	Espera activa implementada como un bulce "for" simple.
	Nota: cada iteracion consume 5 ciclos de reloj (5 instrucciones en MCU).
*/
void delay(uint32_t ticks){
	// Declaramos el contador como una variable
	volatile uint32_t i = 0;
	for(i = 0; i < ticks; i++);
}


/*
	Decide si un numero es primo o no en tiempo O(sqrt(n)).
*/
uint8_t es_primo(uint16_t numero)
{
	uint16_t i;
	
	// Si el numero es menor de 16 ya sabemos si es primo o no sin comprobar nada solo usando un uint16_t.
	// Comprobar si 'numero' es igual a 2, 3, 5, 7, 11 o 13 usando operaciones de bits (1 no es primo):
	// · Mueve un bit a la posicion 'numero' empezando en 0 y lo maskea para encontrar si es uno de los numeros que buscamos.
	// Nota: 0x28AC = 0b0010100010101100
	if (numero < 16)
		return ((1 << numero) & 0x28AC) != 0;

	// Comprueba si numero es par para poder comprobar solo divisores impares despues.
	// En binario, si el primer digito es 0, el numero es par.
	if (!(numero & 0x0001))
		return 0;
	
	// Busca todos los numeros impares para encontrar si alguno es divisor de 'numero'
	// Busca hasta sqrt(numero).
	// · i < sqrt(numero) <=> i*i < numero. 	Con (numero > 0) y (i > 0)
	for (i = 3; i*i < numero; i+=2)
		if (!(numero%i))
			return 0;
	
	// Si ningun numero hasta sqrt(numero) es divisor, el numero es primo
	return 1;
}

int main()
{
	// Inicializamos variables, indice del bucle y cursor sobre el array de primo.
	// Nota: se llama cursor a un valor que sirve como indice para recorrer una estrucura de datos estatica (array).
	uint16_t i;
	uint16_t cursor_arr = 0;
	
	// Buscamos numeros primos desde 2 hasta 65535 (el ultimo numero de 16 bits sin signo, = 0xFFFF)
	for(i = 2; i < MAX_INT16; i++)
	{
		if(es_primo(i))
		{
			arr_primos[cursor_arr] = i; 			// Si i es primo lo añadimos al array
			cursor_arr++;												// Incrementamos el cursor
		}
	}

	return 0;
}

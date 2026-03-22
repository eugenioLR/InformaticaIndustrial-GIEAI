#include "es_primo.h"

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
	// Busca hasta sqrt(numero), resolviendo la inecuacion se puede obtener:
	// · i < sqrt(numero) <==> i*i < numero, con numero > 0 y i > 0
	for (i = 3; i*i < numero; i+=2)
		if (!(numero%i))
			return 0;
	
	// Si ningun numero hasta sqrt(numero) es divisor, el numero es primo
	return 1;
}

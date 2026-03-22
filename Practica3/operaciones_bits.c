#include "operaciones_bits.h"

uint8_t reflejar_bits(uint8_t a)
{		
	a = ((a & 0x0F) << 4) | ((a & 0xF0) >> 4);
	a = ((a & 0x33) << 2) | ((a & 0xCC) >> 2);
	a = ((a & 0x55) << 1) | ((a & 0xAA) >> 1);
	return a;
}

uint32_t binario_a_bcd(uint16_t numero)
{	
	// Un numero de 16 bits tiene como máximo el valor de 65535, 5 digitos.
	return numero%10 | (((numero%100)/10) << 4) | (((numero%1000)/100) << 8) | (((numero%10000)/1000) << 12) | (((numero%100000)/10000) << 16);
}

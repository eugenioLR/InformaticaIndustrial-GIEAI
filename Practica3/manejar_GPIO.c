#include "manejar_GPIO.h"

void configurar_GPIO()
{
	LPC_GPIO0->FIODIR = ~(
		  (1u << 26)
		| (1u << 25)
		| (1u << 24)
		| (1u << 23)
		| (1u << 28)
		| (1u << 27)
		| (1u << 29)
		| (1u << 30)
	);
	
	LPC_GPIO1->FIODIR = ~(
			(1u << 31)
		| (1u << 30)
		| (1u << 18)
		| (1u << 19)
		| (1u << 20)
		| (1u << 21)
		| (1u << 22)
		| (1u << 23)
	);

	LPC_GPIO2->FIODIR = 0xFFFFFFFF & ~((1 << 8) | (1 << 20));
	LPC_GPIO2->FIOCLR = (1 << 8);
	
	LPC_GPIO3->FIODIR = 0xFFFFFFFF;
	
	LPC_GPIO4->FIODIR = 0xFFFFFFFF;
	
}

uint8_t leer_ISP()
{
	return (LPC_GPIO2->FIOPIN >> 20) & 1;
}

uint16_t leer_numero()
{
	uint16_t valor_output = 0;
	
	// Leemos los bits 0, 1, 2, 3, 6, 7, 8, 9 desde los pines 0.26, 0.25, 0.24, 0.23, 0.30, 0.31
	valor_output |= (
			 ((LPC_GPIO0->FIOPIN >> 26) & 1)
		| (((LPC_GPIO0->FIOPIN >> 25) & 1) << 1)
		| (((LPC_GPIO0->FIOPIN >> 24) & 1) << 2)
		| (((LPC_GPIO0->FIOPIN >> 23) & 1) << 3)
		| (((LPC_GPIO0->FIOPIN >> 28) & 1) << 6)
		| (((LPC_GPIO0->FIOPIN >> 27) & 1) << 7)
		| (((LPC_GPIO0->FIOPIN >> 29) & 1) << 8)
		| (((LPC_GPIO0->FIOPIN >> 30) & 1) << 9)
	);
	
	// Leemos los bits 4, 5, 10, 11, 12, 13, 14, 15 desde los pines 1.31, 1.30, 1.18, 1.19, 1.20, 1.21, 1.22, 1.23
	valor_output |= (
			(((LPC_GPIO1->FIOPIN >> 31) & 1) << 4)
		| (((LPC_GPIO1->FIOPIN >> 30) & 1) << 5)
		| (((LPC_GPIO1->FIOPIN >> 18) & 1) << 10)
		| (((LPC_GPIO1->FIOPIN >> 19) & 1) << 11)
		| (((LPC_GPIO1->FIOPIN >> 20) & 1) << 12)
		| (((LPC_GPIO1->FIOPIN >> 21) & 1) << 13)
		| (((LPC_GPIO1->FIOPIN >> 22) & 1) << 14)
		| (((LPC_GPIO1->FIOPIN >> 23) & 1) << 15)
	);
		
	return valor_output;
}


void mostrar_numero_bcd_LEDs(uint32_t valor)
{
	// Escribimos los bits 0, 12, 13, 14, 15, 16, 17 a los pines 0.2, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9
	LPC_GPIO0->FIOPIN = (
			((valor         & 1) << 2)
		| (((valor >> 12) & 1) << 4)
		| (((valor >> 13) & 1) << 5)
		| (((valor >> 14) & 1) << 6)
		| (((valor >> 15) & 1) << 7)
		| (((valor >> 16) & 1) << 8)
		| (((valor >> 17) & 1) << 9)
	);
	
	// Escribimos los bits 1, 2, 3, 4, 5, 6, 7, 8, 9 a los pines 1.0, 1.1, 1.4, 1.8, 1.9, 1.10, 1.14, 1.16, 1.17
	LPC_GPIO1->FIOPIN = (
			 ((valor >> 1) & 1)
		| (((valor >> 2) & 1) << 1)
		| (((valor >> 3) & 1) << 4)
		| (((valor >> 4) & 1) << 8)
		| (((valor >> 5) & 1) << 9)
		| (((valor >> 6) & 1) << 10)
		| (((valor >> 7) & 1) << 14)
		| (((valor >> 8) & 1) << 16)
		| (((valor >> 9) & 1) << 17)
	);
	
	// Escribimos el bits 18 al pin 2.0
	LPC_GPIO2->FIOPIN = (valor >> 18) & 1;
	
	// Escribimos los bits 10, 11 a los pines 4.28, 4.29
	LPC_GPIO4->FIOPIN = (((valor >> 10) & 1) << 28) | (((valor >> 11) & 1) << 29);
	
}

void mostrar_numero_bcd_d7s(uint32_t valor, uint8_t digito)
{
	uint8_t digito_bcd;
	uint16_t digito_one_hot;
	
	digito_bcd = (valor >> (digito * 4)) & 0x0000000F;
	digito_one_hot = (1 << digito_bcd);
	
	LPC_GPIO2->FIOPIN0 = 0x00;
	// Segmento A, activo para 0, 2, 3, 5, 6, 7, 8, 9
	if(digito_one_hot & 0x03ED)
		LPC_GPIO2->FIOSET = 1;
	
	// Segmento B, activo para 1, 2, 3, 4, 7, 8, 9
	if(digito_one_hot & 0x039E)
		LPC_GPIO2->FIOSET0 = 0x02;
	
	// Segmento C, activo para 1, 3, 4, 5, 6, 7, 8, 9
	if(digito_one_hot & 0x03BA)
		LPC_GPIO2->FIOSET0 = 0x04;
	
	// Segmento D, activo para 2,3,5,6,8
	if(digito_one_hot & 0x016C)
		LPC_GPIO2->FIOSET0 = 0x08;
	
	// Segmento E, activo para 2, 6, 8
	if(digito_one_hot & 0x0144)
		LPC_GPIO2->FIOSET0 = 0x10;
	
	// Segmento F, activo para 4, 5, 6, 8, 9
	if(digito_one_hot & 0x0307)
		LPC_GPIO2->FIOSET0 = 0x20;
	
	// Segmento G, activo para 2, 3, 4, 5, 6, 8, 9
	if(digito_one_hot & 0x037C)
		LPC_GPIO2->FIOSET0 = 0x40;
}

void actualizar_LD2()
{
	LPC_GPIO3->FIOPIN = LPC_GPIO3->FIOPIN ^ (1 << 25);
}

void actualizar_LD3(uint8_t bit, uint16_t numero)
{
	uint8_t luz_encendida;
	
	// obtenemos si el bit que necesitamos es 0 o 1.
	luz_encendida = (numero & (1u << bit)) != 0;
	
	// Reemplazamos el bit que necesitamos por el valor de "luz_encendida"
	LPC_GPIO3->FIOPIN = (LPC_GPIO3->FIOPIN & ~(1u << 26)) | (luz_encendida << 26);
}

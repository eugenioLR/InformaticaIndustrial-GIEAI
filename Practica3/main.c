#include <LPC17xx.h>
#include "delay.h"
#include "es_primo.h"
#include "operaciones_bits.h"
#include "manejar_GPIO.h"

#define MAX_INT16 0xFFFF
#define N_DIGITOS_DEC_16BIT 5

/*
	Implementamos la funcionalidad principal de nuestro programa.
*/
void bucle_principal()
{
	uint16_t i, valor_init = 0;
	int8_t j;
	uint32_t numero_bcd;
	
	while(1)
	{
		// Leemos el valor inicial a traves de los pines
		valor_init = leer_numero();
		
		// Buscamos numeros primos desde 'valor_init' hasta 65535
		for(i = valor_init; i < MAX_INT16; i++)
		{
			if(es_primo(i))
			{
				// Convertimos nuestro numero a formato BCD
				numero_bcd = binario_a_bcd(i);
				
				// El boton ISP determina si usamos Display de 7 segmentos
				// o los LEDs para mostrar el numero
				if(leer_ISP())
				{
					// Mostramos el numero en BCD a traves de los LEDs
					mostrar_numero_bcd_LEDs(numero_bcd);
				}
				else
				{
					// Muestra secuencialmente cada digito decimal del numero en el display de 7 segmentos
					for(j = N_DIGITOS_DEC_16BIT - 1; j >= 0; j--)
					{
						mostrar_numero_bcd_d7s(numero_bcd, j);
						delay(TICKS_1ms_10MHz*400);
					}
				}
				
				// Muestra los bits del numero secuencialmente y hace que parpadee el LD2
				for(j = 0; j < 16; j++)
				{
					actualizar_LD2();
					actualizar_LD3(j, i);
					delay(TICKS_1ms_10MHz*125);
				}
			}
		} 
	}
}

/*
	Funcion main minima. Se limita a llamar a otras funciones que implementan la logica.
*/
int main()
{
	configurar_GPIO();
	bucle_principal();
	return 0;
}

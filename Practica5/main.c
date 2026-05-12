#include <LPC17xx.h>
#include <cmsis_os.h>
#include "es_primo.h"
#include "operaciones_bits.h"
#include "manejar_GPIO.h"
#include "manejar_IRQ.h"
#include "manejar_hilos.h"

/*
	Funcion main minima. Se limita a llamar a otras funciones que implementan la logica.
*/
int main()
{
	configurar_GPIO();
	configurar_IRQ();
	lanzar_hilos();
	return 0;
}

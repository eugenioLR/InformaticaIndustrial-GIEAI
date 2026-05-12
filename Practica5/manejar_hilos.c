#include "manejar_hilos.h"

buffer_circular_t BUFFER;

volatile uint8_t MOSTRAR_DISPLAY7SEG = 0;
volatile uint16_t VALOR_INIT = 0;
volatile uint16_t VALOR_FIN = MAX_INT16;
volatile uint8_t DIR_BUCLE = 0;

osThreadId productor_id;
osThreadId consumidor_id;
osMutexId mutexFIFO_id;
osSemaphoreId semaforo_contador_id;
osSemaphoreId semaforo_vacio_id;

osMutexDef(mutexFIFODef);
osSemaphoreDef(semaforo_contador);
osSemaphoreDef(semaforo_vacio);
osThreadDef(productor, osPriorityNormal, 1, 0);
osThreadDef(consumidor, osPriorityNormal, 1, 0);


void productor(void const* argument)
{
	uint16_t i;
	
	while(1)
	{		
		// Buscamos numeros primos desde 'valor_init' hasta 65535
		if(DIR_BUCLE == 0)
			i = VALOR_INIT;
		else
			i = VALOR_FIN-1;
		
		while(i >= VALOR_INIT && i < VALOR_FIN)
		{
			if(es_primo_retardo(i))
			{
				osSemaphoreWait(semaforo_contador_id, osWaitForever);
				
				osMutexWait(mutexFIFO_id, osWaitForever);
				insertar(&BUFFER, i);
				osMutexRelease(mutexFIFO_id);
				
				osSemaphoreRelease(semaforo_vacio_id);
			}
			
			if(DIR_BUCLE == 0)
				i++;
			else
				i--;
		} 
	}
}

void consumidor(void const* argument)
{
	int8_t j;
	uint16_t val;
	uint32_t numero_bcd;
	
	while(1)
	{
		osSemaphoreWait(semaforo_vacio_id, osWaitForever);
		
		osMutexWait(mutexFIFO_id, osWaitForever);
		pop(&BUFFER, &val);
		osMutexRelease(mutexFIFO_id);
		
		osSemaphoreRelease(semaforo_contador_id);
		
		// Convertimos nuestro numero a formato BCD
		numero_bcd = binario_a_bcd(val);
		
		// El boton ISP determina si usamos Display de 7 segmentos
		// o los LEDs para mostrar el numero
		if(MOSTRAR_DISPLAY7SEG)
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
				osDelay(400);
			}
		}
		
		// Muestra los bits del numero secuencialmente y hace que parpadee el LD2
		for(j = 0; j < 16; j++)
		{
			actualizar_LD2();
			actualizar_LD3(j, val);
			osDelay(125);
		}
	}
}


void lanzar_hilos(void)
{			
	mutexFIFO_id = osMutexCreate(osMutex(mutexFIFODef));
	semaforo_contador_id = osSemaphoreCreate(osSemaphore(semaforo_contador), TAMBUFFER);
	semaforo_vacio_id = osSemaphoreCreate(osSemaphore(semaforo_vacio), 0);
	productor_id = osThreadCreate(osThread(productor), NULL);
	consumidor_id = osThreadCreate(osThread(consumidor), NULL);
	
	osDelay(osWaitForever);
}

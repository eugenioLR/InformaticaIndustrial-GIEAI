#ifndef MANEJAR_HILOS_H
#define MANEJAR_HILOS_H

#include <cmsis_os.h>
#include "buffer_circular.h"
#include "es_primo.h"
#include "manejar_GPIO.h"
#include "operaciones_bits.h"

#define MAX_INT16 0xFFFF
#define N_DIGITOS_DEC_16BIT 5

extern osThreadId productor_id;
extern osThreadId consumidor_id;
extern osMutexId mutexFIFO;
extern osSemaphoreId semaforo_lleno_id;
extern osSemaphoreId semaforo_vacio_id;

void productor(void const* argument);
void consumidor(void const* argument);
void lanzar_hilos(void);

#endif

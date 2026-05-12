#ifndef MANEJAR_IRQ
#define MANEJAR_IRQ

#include <LPC17xx.h>
#include "manejar_GPIO.h"

extern volatile uint8_t MOSTRAR_DISPLAY7SEG;
extern volatile uint16_t VALOR_INIT;
extern volatile uint16_t VALOR_FIN;
extern volatile uint8_t DIR_BUCLE;

void configurar_IRQ(void);

#endif

#ifndef MANEJAR_GPIO
#define MANEJAR_GPIO

#include <LPC17xx.h>

void configurar_GPIO(void);
uint16_t leer_numero(void);
uint8_t leer_ISP(void);
void mostrar_numero_bcd_LEDs(uint32_t numero);
void mostrar_numero_bcd_d7s(uint32_t numero, uint8_t digito);
void actualizar_LD2(void);
void actualizar_LD3(uint8_t bit, uint16_t numero);

#endif

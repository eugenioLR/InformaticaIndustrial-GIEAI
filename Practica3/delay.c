#include "delay.h"

void delay(uint32_t ticks){
	volatile uint32_t i = 0;
	for(i = 0; i < ticks; i++);
}

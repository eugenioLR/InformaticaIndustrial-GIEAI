#include "configurar_GPIO.h"

void configurar_GPIO()
{
	LPC_GPIO0->FIODIR = (1 << 26)
										| (1 << 25)
										| (1 << 24)
										| (1 << 23)
										| (1 << 28)
										| (1 << 27)
										| (1 << 29)
										| (1 << 30);
	LPC_GPIO0->FIODIR = ~LPC_GPIO0->FIODIR;
	
	LPC_GPIO1->FIODIR = (1 << 31)
										| (1 << 30)
										| (1 << 18)
										| (1 << 19)
										| (1 << 20)
										| (1 << 21)
										| (1 << 22)
										| (1 << 23);
	
	LPC_GPIO2->FIODIR = 0xFFFFFFFF;
	LPC_GPIO4->FIODIR = 0xFFFFFFFF;
}


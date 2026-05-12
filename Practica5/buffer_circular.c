#include "buffer_circular.h"

void iniciar_buffer(void)
{
	BUFFER.idx_mete = 0;
	BUFFER.idx_saca = 0;
}

uint8_t vacio(buffer_circular_t buffer)
{
	return buffer.idx_mete == buffer.idx_saca;
}

uint8_t lleno(buffer_circular_t buffer)
{
	uint16_t idx_mete_sig = buffer.idx_mete + 1;
	if(idx_mete_sig > TAMBUFFER)
			idx_mete_sig = 0;
	
	return idx_mete_sig == buffer.idx_saca;
}

uint8_t insertar(buffer_circular_t* buffer, uint16_t dato)
{
	uint16_t idx_siguiente = buffer->idx_mete + 1;
	if(idx_siguiente > TAMBUFFER)
		idx_siguiente = 0;
	
	if(idx_siguiente == buffer->idx_saca)
		return 0;
	
	buffer->memoria[buffer->idx_mete] = dato;
	buffer->idx_mete = idx_siguiente;
	return 1;
}


uint8_t pop(buffer_circular_t* buffer, uint16_t* dato)
{
	uint16_t idx_siguiente = buffer->idx_saca + 1;
	if(idx_siguiente > TAMBUFFER)
		idx_siguiente = 0;
	
	if(idx_siguiente == buffer->idx_saca)
		return 0;
	
	*dato = buffer->memoria[buffer->idx_saca];
	buffer->idx_saca = idx_siguiente;
	return 1;
}


uint16_t n_elementos(buffer_circular_t buffer)
{
	if(buffer.idx_mete >= buffer.idx_saca)
		return buffer.idx_mete - buffer.idx_saca;
	else
		return TAMBUFFER - buffer.idx_saca + buffer.idx_mete;
}

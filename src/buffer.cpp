#include "buffer.h"

//Funcionando
void Buffer::add() {
	if (isEmpty())
	{
		this->flits.push(din);
    	size++;
	} else if (isEmpty_canais_virtuais())
	{
		this->flits_canais_virtuais.push(din_canais_virtuais);
    	size_canais_virtuais++;
	}
	
}

void Buffer::remove() {
	flits.pop();
	if (size > 0)
		size--;   
}

void Buffer::remove_canais_virtuais() {
	flits_canais_virtuais.pop();
	if (size_canais_virtuais > 0)
		size_canais_virtuais--;   
}

//Se estiver Vazio retorna 1, senão retorna 0
int Buffer::isEmpty() {
	return (this->size < 10) ? 1: 0;
}

int Buffer::isEmpty_canais_virtuais() {
	return (this->size_canais_virtuais < 10) ? 1: 0;
}


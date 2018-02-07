#include "buffer.h"

//Funcionando
void Buffer::add() {
	this->flits.push(din);
    size++;
}
//Funcionando
void Buffer::remove() {
	flits.pop();
	if (size > 0)
	{
		size--;
	}
    
}

//Se estiver Vazio retorna 1, senão retorna 0
int Buffer::isEmpty() {
	return (this->size < 10) ? 1: 0;
}

int Buffer::isEmpty_canais_virtuais() {
	return (this->size_canais_virtuais < 10) ? 1: 0;
}


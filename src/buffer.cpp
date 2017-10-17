#include "buffer.h"

//Funcionando
void Buffer::add() {
	this->flits.push(din);	
}
//Funcionando
void Buffer::remove() {
	flits.pop();	
}

//Se estiver Vazio retorna 1, senão retorna 0
int Buffer::isEmpty() {
	return (this->flits.empty() == 1) ? 1: 0;
}


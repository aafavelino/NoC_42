#include "buffer.h"

//Funcionando
void Buffer::add() {
	this->flits.push(din);
    size++;
}
//Funcionando
void Buffer::remove() {
	flits.pop();
    size--;
}

//Se estiver Vazio retorna 1, senão retorna 0
int Buffer::isEmpty() {
    
	// cout << "Buffer Size :" <<  ((this->size < 4) ? 1: 0 )<< "\n";
	return (this->size < 10) ? 1: 0;
}


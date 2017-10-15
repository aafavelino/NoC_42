#include "buffer.h"



//Funcionando
void Buffer::add() {
	if (wr == 1)
	{
		this->flits.push(din);
		wok = 1;
	}
	
}
//Funcionando
void Buffer::remove() {
	flits.pop();	
}

//Se estiver Vazio retorna 1, senão retorna 0
int Buffer::isEmpty() {
	return (this->flits.empty() == 1) ? 1: 0;
}


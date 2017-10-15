#include "buffer.h"



//Funcionando
void Buffer::add() {
	if (wr == 1)
	{
		if (flits.size() == this->length){
			wok = 0; // error, value not added
		} else {
			this->flits.push(din);
			wok = 1;
		}	
	}
	
}
//Funcionando
void Buffer::remove() {
	if (flits.size() < 1){
		rok = 0; // queue is empty. Nothing to remove
	} else if (rd == 1){
		flits.pop();
		rok = 1;
	}
}

//Se estiver Vazio retorna 1, senão retorna 0
int Buffer::isEmpty() {
	return (this->flits.empty() == 1) ? 1: 0;
}


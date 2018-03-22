//
// Created by Adelino on 30/11/17.
//

#include "buffer.h"

//Funcionando
void Buffer::add() {
	this->flits.push(din);
    size++;

    // cout << "size no buffer "<< size << endl;
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
	// cout << "Buffer Size :" <<  ((this->size < 1) ? 1: 0 )<< "\n";
	return (this->size < 10) ? 1: 0;
}


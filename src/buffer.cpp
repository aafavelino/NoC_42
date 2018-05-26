//
// Created by Adelino on 30/11/17.
//

#include "buffer.h"

//Funcionando
void Buffer::add(int x) {
	buffer_virtual[x].push(din);
    size[0]++;

}
//Funcionando
void Buffer::remove(int x) {
	buffer_virtual[x].pop();
	if (size[0] > 0)
	{
		size[0]--;
	}   
}

//Se estiver Vazio retorna 1, senão retorna 0
int Buffer::isEmpty(int x) {
	// cout << "Buffer Size :" <<  ((this->size < 1) ? 1: 0 )<< "\n";
	return (this->size[0] < TAMANHO_BUFFER) ? 1: 0;
}


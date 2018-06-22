//
// Created by Adelino on 30/11/17.
//

#include "buffer.h"

//Funcionando
void Buffer::add(int x) {
	buffer_virtual[x].push(din);
    size[x]++;

}
//Funcionando
void Buffer::remove(int x) {
	buffer_virtual[x].pop();
	if (size[x] > 0)
	{
		size[x]--;
	}   
}

//Se estiver Vazio retorna 1, senão retorna 0
int Buffer::isEmpty(int x) {
	// cout << "Buffer Size :" <<  ((this->size < 1) ? 1: 0 )<< "\n";
	return (this->buffer_virtual[x].empty()) ? 1: 0;
}

int Buffer::espaco(int x) {
	// cout << "Buffer Size :" <<  (TAMANHO_BUFFER - this->size[x])<< endl;
	return (this->size[x] < TAMANHO_BUFFER) ? (TAMANHO_BUFFER - this->size[x]): 0;
}

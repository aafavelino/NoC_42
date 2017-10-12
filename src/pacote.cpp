#include "pacote.h"

Pacote::Pacote () {
	for (int i = 0; i < 10; ++i)
		this->flit[i].cabeca = 1;

	for (int i = 0; i < 10; ++i)
		this->flit[i].terminador = -1;

	for (int i = 0; i < 10; ++i)
		this->flit[i].payload = 2;
}
#ifndef _BUFFER_H_
#define _BUFFER_H_ 

#include <iostream>
#include <queue>
#include "systemc.h"
#include "flit.h"
#include "controle_fluxo.h"


SC_MODULE (Buffer)
{

public:
	
	std::queue<Flit> flits;

	Flit din; //Entrada data + bop + eop
	Flit dout; //Saída que vai para o roteamento

	sc_int<4>  wr; //Entrada que vem do controle de fluxo
	sc_int<4>  wok; //Saída que volta para o buffer

	void add();
	void remove();
	int isEmpty();

	SC_CTOR(Buffer) {
        SC_METHOD(add);
        SC_METHOD(remove);
    }

	
};
#endif
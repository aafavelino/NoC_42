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
	std::queue<Flit> flits_canais_virtuais;
    int size;
    int size_canais_virtuais;
    
	Flit din; //Entrada data + bop + eop
	Flit din_canais_virtuais; //Entrada data + bop + eop

	sc_int<4>  wr; //Entrada que vem do controle de fluxo
	sc_int<4>  wok; //Saída que volta para o buffer

	void add();
	void remove();
	void remove_canais_virtuais();
	int isEmpty();
	int isEmpty_canais_virtuais();

	SC_CTOR(Buffer) {
		SC_METHOD(add);
		SC_METHOD(remove);
        size = 0;
        size_canais_virtuais = 0;
	}

	
};
#endif

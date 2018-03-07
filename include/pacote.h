//
// Created by Adelino on 30/11/17.
//

#ifndef _PACOTE_H_
#define _PACOTE_H_ 
#include <iostream>
#include <systemc.h>
#include "flit.h"

class Pacote 
{
public:

// 0 0 2 0 23 1 1
// end


// — sintaxes:


// 1) Mesh padrão:  xs ys xd yd #flits idleCycles size
//       xs: X source; xd: X dest
//       xs: Y source; xd: Y dest
//		 #flits:  quantos flits tem para enviar 
//		 idleCycles: De quanto em quanto tempo é enviado 
//       size: quantas vezes o pacote é reenviado pela rede.

	int last_flit;
	int first_flit;
	int xs, ys;
	int xd, yd;
	int qt_flits;
	int idleCycles;
	int size;
	int contador_ciclos;
	int contador_size;
	std::queue<Flit> qtd_flits;
	Flit flits;
	Pacote(int xs, int ys, int xd, int yd, int qt_flits, int idleCycles, int size) {
		this->last_flit = 0;
		this->first_flit = 0;
		this->contador_ciclos = 0;
		this->contador_size = 0;
		this->xs = xs;
		this->ys = ys;
		this->xd = xd;
		this->yd = yd;
		this->qt_flits = qt_flits;
		this->idleCycles = idleCycles;
		this->size = size;
		flits.cordenadas_f.x = xd;
		flits.cordenadas_f.y = yd;
		for (int i = 0; i < qt_flits; ++i)
			qtd_flits.push(flits);		
	}
};

#endif
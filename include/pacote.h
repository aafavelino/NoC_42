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

// 0 0 2 0 23 1 1 0
// end

// Mesh padrão:  
// 	     xs ys xd yd tamanho_pct idleCycles prioridade_pct
//       xs: X source; 
// 		 xd: X dest
//       xs: Y source; 
// 		 xd: Y dest             
//       idleCycles: De quanto em quanto tempo é enviado 
//       prioridade_pct: prioridade do pacote com canais virtuais, se não tiver canais a prioridade é 0...


	std::queue<Flit> fila_flits;
	std::tuple<int, int> origem;
	std::tuple<int, int> destino;
	int tamanho_pct;
	int idleCycles; 
	int prioridade;
	int first_flit = 0;
	int last_flit = 0;
	int first_flit_end = 0;
	int contador_flits = 0;
	int contador_ciclos = 0;
	Flit flit;


	Pacote(int xs, int ys, int xd, int yd, int tamanho_pct, int idleCycles, int prioridade, int id) {
		this->origem = std::make_tuple (xs,ys);
		this->destino = std::make_tuple (xd,yd);
		this->tamanho_pct = tamanho_pct;
		this->idleCycles = idleCycles;
		this->prioridade = prioridade;
		this->flit.destino = destino;
		this->flit.prioridade = prioridade;
		this->flit.id = id;
		for (int i = 0; i < tamanho_pct; ++i)
		{
			this->flit.begin = -1;
			if(i == 0)
				this->flit.begin = id;
			else if(i == (tamanho_pct-1))
				this->flit.end = id;
			
			fila_flits.push(flit);
		}
	};
};

#endif
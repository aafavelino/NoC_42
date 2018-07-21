//
// Created by Adelino on 30/11/17.
//

#ifndef _ARBITRO_H_
#define _ARBITRO_H_ 

#include <iostream>
#include <systemc.h>
#include <deque>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "../constantes/constantes.h"
#include "flit.h"


class Arbitro 
{
public:
	sc_uint<32> portaDestino;
	int arquivo[3];
	int buffercircular[5][2];
	int prioridade = -1;
	int rotatividade = 0;
	int arbitragem = -1;
	int id_pacote = -3;
	bool arbitra = true;
	bool livre = true;
	std::deque<int> prioridades;
	int conta = 0;


	Arbitro();
	void addSolicitacao(int, Flit);
	void remSolicitacao(int, Flit);
	void setPrioridade();
	int checkPrioridade();
	
};

#endif
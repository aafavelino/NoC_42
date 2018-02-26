//
// Created by Adelino on 30/11/17.
//

#ifndef _ARBITRO_H_
#define _ARBITRO_H_ 

#include <iostream>
#include <systemc.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "../constantes/constantes.h"


class Arbitro 
{
public:
	sc_uint<32> portaDestino;
	int buffercircular[5];
	int prioridade;

	Arbitro();
	void addSolicitacao(int);
	void remSolicitacao(int);
	void setPrioridade();
	int checkPrioridade();
	
};

#endif
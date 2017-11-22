#ifndef _ARBITRO_H_
#define _ARBITRO_H_ 

#include <iostream>
#include <systemc.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define NORTE 0
#define LESTE 1
#define SUL 2
#define OESTE 3
#define LOCAL 4

class Arbitro 
{
public:
	sc_uint<32> portaDestino;
	int buffercircular[5];
	int prioridade;

	Arbitro();
	void setPrioridade();
	int checkPrioridade();
	
};

#endif
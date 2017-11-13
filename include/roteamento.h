#ifndef _ROTEAMENTO_H_
#define _ROTEAMENTO_H_ 

#include <iostream>
#include "flit.h"
#include <systemc.h>
#define NORTE 0
#define LESTE 1
#define SUL 2
#define OESTE 3
#define LOCAL 4

class Roteamento 
{
public:
	Flit in_data; //n+2

	struct cordenada_local
	{
	public:
		int x;
		int y;
	} cordenada;
	struct cordenada_dest
	{
	public:
		int x;
		int y;
	} cordenada_destino;

	int portaDestino; //NSLO

	Roteamento();
	void rotear_xy();
	
};
#endif
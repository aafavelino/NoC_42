#ifndef _ROTEAMENTO_H_
#define _ROTEAMENTO_H_ 

#include <iostream>
#include "flit.h"
#include <systemc.h>
#include "../constantes/constantes.h"

class Roteamento 
{
public:

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

	int portaDestino = -1;
	int portaAnterior = -1; 

	void rotear_west_first();
	void rotear_xy();
	void rotear_nort_last();
	void rotear_odd_even();
	void rotear_negative_first();
	
};
#endif
//
// Created by Adelino on 30/11/17.
//

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

	int odd_even = -1;

	void rotear_west_first();
	void rotear_xy();
	void rotear_north_last();
	void rotear_negative_first();
	void rotear_odd_even();
	
};
#endif
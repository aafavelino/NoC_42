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
	Flit v[10];
	Pacote(int x, int y, int quantidade) {
		Flit flit;
		flit.cordenadas_f.x = x;
		flit.cordenadas_f.y = y;
		for (int i = 0; i < quantidade; ++i)
		{
			v[i] = flit;
		}
	}
};

#endif
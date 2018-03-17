//
// Created by Adelino on 30/11/17.
//

#ifndef _FLIT_H_
#define _FLIT_H_ 
#include <iostream>
#include <systemc.h>

class Flit 
{
public:
	int payload;
	int ciclo;
	int begin;
	int end = -1;
	int stop = false;
	struct cordenadas
	{
		int x;
		int y;
	}cordenadas_f;
};

#endif
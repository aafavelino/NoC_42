#ifndef _FLIT_H_
#define _FLIT_H_ 
#include <iostream>
#include <systemc.h>

class Flit 
{
public:
	int cabeca;
	int terminador;
	int payload;
	struct cordenadas
	{
	public:
		int x;
		int y;
	}cordenadas_f;
	
	
};

#endif
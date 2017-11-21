#ifndef _FLIT_H_
#define _FLIT_H_ 
#include <iostream>
#include <systemc.h>

class Flit 
{
public:
	int payload;
	struct cordenadas
	{
		int x;
		int y;
	}cordenadas_f;
};

#endif
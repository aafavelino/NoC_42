#ifndef _PACOTE_H_
#define _PACOTE_H_ 

#include <iostream>
#include "flit.h"
#include <systemc.h>
class Pacote 
{
public:
	//Vetor de Flits com 10 flits
	Flit flit[10];
	Pacote();
	
};
#endif
#ifndef _ROTEAMENTO_H_
#define _ROTEAMENTO_H_ 

#include <iostream>
#include "flit.h"
#include <systemc.h>
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define LOCAL 4

class Roteamento 
{
public:
	//Acho que falta colocar o n+2
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
	~Roteamento();
	void rotear_xy();
	
};
#endif
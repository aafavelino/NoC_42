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
	int inicio = -1;
	int fim = -1;
	int ciclo;
	int begin = -1;
	int prioridade;
	int end = -1;
	int id;
	std::tuple<int, int> destino;
};

#endif
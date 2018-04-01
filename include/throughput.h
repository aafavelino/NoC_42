//
// Created by Adelino on 31/04/18.
//

#ifndef _THROUGHPUT_H_
#define _THROUGHPUT_H_ 
#include <iostream>
#include <systemc.h>

class Throughput 
{
public:
	int saida_norte;
	int saida_sul;
	int saida_leste;
	int saida_oeste;

	Throughput() {
		this->saida_norte = 0;
		this->saida_sul = 0;
		this->saida_leste = 0;
		this->saida_oeste = 0;
	}
};

#endif
#ifndef _CONTROLE_FLUXO_H_
#define _CONTROLE_FLUXO_H_ 

#include <iostream>
#include <systemc.h>

SC_MODULE (controle_fluxo)
{

	sc_in <int> in_val; //Entrada pra ver se no buffer terá espaço 
	sc_out<int> in_ack; //Retorno da solicitação se terá espaço

	sc_int<4> wr; //Saída que vai para o buffer
	sc_int<4> wok; //Entrada que vem do buffer

	SC_CTOR(controle_fluxo){
	}
	
};
#endif
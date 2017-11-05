#ifndef _CONTROLE_FLUXO_H_
#define _CONTROLE_FLUXO_H_ 

#include <iostream>
#include <systemc.h>

SC_MODULE (controle_fluxo)
{

	sc_in <int> in_val; //Entrada pra ver se no buffer terá espaço 
	sc_out<int> in_ack; //Retorno da solicitação se terá espaço

	sc_out<int> out_cf_buffer; //Saída que vai para o buffer
	sc_in <int> in_cf_buffer; //Entrada que vem do buffer

	SC_CTOR(controle_fluxo){
	}
	
};
#endif
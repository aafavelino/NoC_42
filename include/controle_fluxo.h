#ifndef _CONTROLE_FLUXO_H_
#define _CONTROLE_FLUXO_H_ 

#include <iostream>
#include <systemc.h>

SC_MODULE (controle_fluxo)
{

	sc_in < sc_uint<32> > in_val; //Entrada pra ver se no buffer terá espaço 
	sc_out< sc_uint<32> > in_ack; //Retorno da solicitação se terá espaço

	sc_out< sc_uint<32> > wr; //Saída que vai para o buffer
	sc_in < sc_uint<32> > wok; //Entrada que vem do buffer


	void request();
	void response();

	SC_CTOR(controle_fluxo){
		SC_METHOD(request);
		sensitive << in_val;
		SC_METHOD(response);
		sensitive << wok;
	}
	
};
#endif
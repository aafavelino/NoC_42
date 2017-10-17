#ifndef _CONTROLE_FLUXO_H_
#define _CONTROLE_FLUXO_H_ 

#include <iostream>
#include <systemc.h>

SC_MODULE (controle_fluxo)
{

	sc_in <bool> in_val; //Entrada pra ver se no buffer terá espaço 
	sc_out<bool> in_ack; //Retorno da solicitação se terá espaço

	sc_out<bool> out_cf_buffer; //Saída que vai para o buffer
	sc_in <bool> in_cf_buffer; //Entrada que vem do buffer

	SC_CTOR(controle_fluxo){


		
	}
	
};
#endif
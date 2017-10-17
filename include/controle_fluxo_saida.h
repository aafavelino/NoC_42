#ifndef _CONTROLE_FLUXO_SAIDA_H_
#define _CONTROLE_FLUXO_SAIDA_H_

#include <iostream>
#include <systemc.h>

SC_MODULE (controle_fluxo_saida)
{

	sc_in <bool> rok; //Entrada pra ver se no buffer terá espaço 
	sc_out<bool> rd; //Retorno da solicitação se terá espaço

	sc_out<bool> val; //Saída que vai para o cf
	sc_in <bool> ack; //Entrada que vem do cf


	SC_CTOR(controle_fluxo_saida){

		
	}
	
};
#endif
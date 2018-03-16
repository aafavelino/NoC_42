//
// Created by Adelino on 30/11/17.
//

#ifndef _CONTROLE_FLUXO_SAIDA_H_
#define _CONTROLE_FLUXO_SAIDA_H_

#include <iostream>
#include <systemc.h>

SC_MODULE (controle_fluxo_saida)
{

	sc_out<int> out_val; //Saída que vai para o cf
	sc_in <int> out_ack; //Entrada que vem do cf

	sc_int<4> rok; //Entrada pra ver se no buffer terá espaço 
	sc_int<4> rd; //Retorno da solicitação se terá espaço



	SC_CTOR(controle_fluxo_saida){		
	}
	
};
#endif
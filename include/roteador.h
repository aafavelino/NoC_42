#include <iostream>
#include <systemc.h>
#include "arbitro.h"
#include "roteamento.h"
#include "controle_fluxo.h"
#include "controle_fluxo_saida.h"
#include "buffer.h"
#include "flit.h"

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define LOCAL 4


SC_MODULE (roteador)
{
	sc_signal <int> val_cf_norte_to_sul_wire[2]; //Sai do norte e entra no sul
	sc_signal <int> val_cf_sul_to_norte_wire[2]; //Sai do sul e entra no norte
	sc_signal <int> val_cf_leste_to_oeste_wire[2]; //Sai do leste e entra no oeste
	sc_signal <int> val_cf_oeste_to_leste_wire[2]; //Sai do oeste e entra no leste

	sc_signal <int> ack_cf_norte_to_sul_wire[2]; //Sai do norte e entra no sul
	sc_signal <int> ack_cf_sul_to_norte_wire[2]; //Sai do sul e entra no norte
	sc_signal <int> ack_cf_leste_to_oeste_wire[2]; //Sai do leste e entra no oeste
	sc_signal <int> ack_cf_oeste_to_leste_wire[2]; //Sai do oeste e entra no leste


	sc_signal <int> rd_cf_norte[2];
	sc_signal <int> rd_cf_sul[2];
	sc_signal <int> rd_cf_leste[2];
	sc_signal <int> rd_cf_oeste[2];

	sc_signal <int> rok_cf_norte[2];
	sc_signal <int> rok_cf_sul[2];
	sc_signal <int> rok_cf_leste[2];
	sc_signal <int> rok_cf_oeste[2];

	//TESTES...
	//sc_in <int> in_cff; 
	//sc_out<int> out_cff; 
	sc_signal <int> roteia;



	Flit in_data; //n+2 data + bop + eop
	Flit out_data; // Saída do roteamento n+2

	Arbitro arbitro_centralizado;
	
	
	// Roteamentos...
	Roteamento roteamento_norte;
	Roteamento roteamento_sul;
	Roteamento roteamento_leste;
	Roteamento roteamento_oeste;
	Roteamento roteamento_local;
	//Controles de fluxo
	controle_fluxo *cf_norte;
	controle_fluxo *cf_sul;
	controle_fluxo *cf_leste;
	controle_fluxo *cf_oeste;
	//controle_fluxo *cf_local;

	controle_fluxo_saida *cf_saida_norte;
	controle_fluxo_saida *cf_saida_sul;
	controle_fluxo_saida *cf_saida_leste;
	controle_fluxo_saida *cf_saida_oeste;


	void execute();

	SC_CTOR(roteador) {

	    
		cf_norte = new controle_fluxo("cf_buffer_Norte");
		cf_sul = new controle_fluxo("cf_buffer_Sul");
		cf_leste = new controle_fluxo("cf_buffer_Leste");
		cf_oeste = new controle_fluxo("cf_buffer_Oeste");
		//cf_local = new controle_fluxo("cf_buffer_Local");

		cf_saida_norte = new controle_fluxo_saida("cf_saida_Norte");
		cf_saida_sul = new controle_fluxo_saida("cf_saida_Sul");
		cf_saida_leste = new controle_fluxo_saida("cf_saida_Leste");
		cf_saida_oeste = new controle_fluxo_saida("cf_saida_Oeste");
		//cf_saida_local = new controle_fluxo_saida("cf_saida_Local");	


        SC_METHOD(execute);
		//sensitive << in_cff;
		
    }

	
};
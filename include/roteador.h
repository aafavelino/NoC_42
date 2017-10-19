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
	//Da comunicação entre roteadores
	sc_signal <int> val_cf_norte_to_sul_wire; //Sai do norte e entra no sul
	sc_signal <int> val_cf_sul_to_norte_wire; //Sai do sul e entra no norte
	sc_signal <int> val_cf_leste_to_oeste_wire; //Sai do leste e entra no oeste
	sc_signal <int> val_cf_oeste_to_leste_wire; //Sai do oeste e entra no leste

	sc_signal <int> ack_cf_norte_to_sul_wire; //Sai do norte e entra no sul
	sc_signal <int> ack_cf_sul_to_norte_wire; //Sai do sul e entra no norte
	sc_signal <int> ack_cf_leste_to_oeste_wire; //Sai do leste e entra no oeste
	sc_signal <int> ack_cf_oeste_to_leste_wire; //Sai do oeste e entra no leste
	
	sc_signal <int> val_cf_local_to_local_wire; //Sai do oeste e entra no leste
	sc_signal <int> ack_cf_local_to_local_wire; //Sai do oeste e entra no leste


	//Sinais do cf para o buffer
	sc_signal <int> wr_norte;
	sc_signal <int> wr_sul;
	sc_signal <int> wr_leste;
	sc_signal <int> wr_oeste;
	sc_signal <int> wr_local;

	sc_signal <int> wok_norte;
	sc_signal <int> wok_sul;
	sc_signal <int> wok_leste;
	sc_signal <int> wok_oeste;
	sc_signal <int> wok_local;




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
	controle_fluxo *cf_local;

	controle_fluxo_saida *cf_saida_norte;
	controle_fluxo_saida *cf_saida_sul;
	controle_fluxo_saida *cf_saida_leste;
	controle_fluxo_saida *cf_saida_oeste;

	Buffer *buffer_norte;
	Buffer *buffer_sul;
	Buffer *buffer_leste;
	Buffer *buffer_oeste;
	Buffer *buffer_local;

	void execute();

	SC_CTOR(roteador) {

	    
		cf_norte = new controle_fluxo("cf_buffer_Norte");
		cf_sul = new controle_fluxo("cf_buffer_Sul");
		cf_leste = new controle_fluxo("cf_buffer_Leste");
		cf_oeste = new controle_fluxo("cf_buffer_Oeste");
		cf_local = new controle_fluxo("cf_buffer_Local");

		cf_saida_norte = new controle_fluxo_saida("cf_saida_Norte");
		cf_saida_sul = new controle_fluxo_saida("cf_saida_Sul");
		cf_saida_leste = new controle_fluxo_saida("cf_saida_Leste");
		cf_saida_oeste = new controle_fluxo_saida("cf_saida_Oeste");
		//cf_saida_local = new controle_fluxo_saida("cf_saida_Local");	
		
		buffer_norte = new Buffer("Buffer_norte");
		buffer_sul = new Buffer("Buffer_sul");
		buffer_leste = new Buffer("Buffer_leste");
		buffer_oeste = new Buffer("Buffer_oeste");
		buffer_local = new Buffer("Buffer_local");

        SC_METHOD(execute);
		
		
    }

	
};
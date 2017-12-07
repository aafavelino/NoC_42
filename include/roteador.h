#ifndef _ROTEADOR_H_
#define _ROTEADOR_H_

#include <iostream>
#include <systemc.h>
#include "arbitro.h"
#include "roteamento.h"
#include "controle_fluxo.h"
#include "controle_fluxo_saida.h"
#include "buffer.h"
#include "flit.h"
#include "pacote.h"
#include <time.h>




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
	

	// Ver isso aqui DEPOISSSS
	Flit in_data; //n+2 data + bop + eop
	Flit out_data; // Saída do roteamento n+2

	// Arbitros
	Arbitro arbitro_norte;
	Arbitro arbitro_sul;
	Arbitro arbitro_leste;
	Arbitro arbitro_oeste;
	
	// Roteamentos...
	Roteamento roteamento_norte;
	Roteamento roteamento_sul;
	Roteamento roteamento_leste;
	Roteamento roteamento_oeste;
	Roteamento roteamento_local;

	// Controles de fluxo
	controle_fluxo *cf_norte;
	controle_fluxo *cf_sul;
	controle_fluxo *cf_leste;
	controle_fluxo *cf_oeste;
	
	// Controles de fluxo de saída
	controle_fluxo_saida *cf_saida_norte;
	controle_fluxo_saida *cf_saida_sul;
	controle_fluxo_saida *cf_saida_leste;
	controle_fluxo_saida *cf_saida_oeste;
	
	// Buffers
	Buffer *buffer_norte;
	Buffer *buffer_sul;
	Buffer *buffer_leste;
	Buffer *buffer_oeste;
	Buffer *buffer_local;

	void entrada_controle_de_fluxo();
	void entrada_buffer();
	void confirmacao_buffer();
	void execute_retorno_controle_de_fluxo();



	SC_CTOR(roteador) { 
		cf_norte = new controle_fluxo("controle_de_fluxo_buffer_Norte");
		cf_sul = new controle_fluxo("controle_de_fluxo_buffer_Sul");
		cf_leste = new controle_fluxo("controle_de_fluxo_buffer_Leste");
		cf_oeste = new controle_fluxo("controle_de_fluxo_buffer_Oeste");
		
		cf_saida_norte = new controle_fluxo_saida("controle_de_fluxo_saida_Norte");
		cf_saida_sul = new controle_fluxo_saida("controle_de_fluxo_saida_Sul");
		cf_saida_leste = new controle_fluxo_saida("controle_de_fluxo_saida_Leste");
		cf_saida_oeste = new controle_fluxo_saida("controle_de_fluxo_saida_Oeste");
			
		buffer_norte = new Buffer("Buffer_norte");
		buffer_sul = new Buffer("Buffer_sul");
		buffer_leste = new Buffer("Buffer_leste");
		buffer_oeste = new Buffer("Buffer_oeste");
		buffer_local = new Buffer("Buffer_local");

		//Ligação dos controles de fluxo internos...
		cf_saida_norte->out_val(val_cf_norte_to_sul_wire);
		cf_saida_norte->out_ack(ack_cf_norte_to_sul_wire);
		cf_saida_sul->out_val(val_cf_sul_to_norte_wire);
		cf_saida_sul->out_ack(ack_cf_sul_to_norte_wire);
		cf_saida_leste->out_val(val_cf_leste_to_oeste_wire);
		cf_saida_leste->out_ack(ack_cf_leste_to_oeste_wire);
		cf_saida_oeste->out_val(val_cf_oeste_to_leste_wire);
		cf_saida_oeste->out_ack(ack_cf_oeste_to_leste_wire);

		SC_METHOD(entrada_controle_de_fluxo);
			sensitive << cf_norte->in_val; 
	        sensitive << cf_sul->in_val;
	        sensitive << cf_leste->in_val; 
	        sensitive << cf_oeste->in_val; 
    }

	
};
#endif
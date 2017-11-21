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
#include <time.h>

#define NORTE 0
#define LESTE 1
#define SUL 2
#define OESTE 3
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

	void execute_controle_fluxo();
	void execute_buffer();
	void execute_buffer_retorno();


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
	
		// Ligação de tudo do buffer local e controle de fluxo local 
		buffer_norte->in_bf_controle_fluxo(wr_norte);
		cf_norte->out_cf_buffer(wr_norte);
		buffer_norte->out_bf_controle_fluxo(wok_norte);
		cf_norte->in_cf_buffer(wok_norte);		

		buffer_sul->in_bf_controle_fluxo(wr_sul);
		cf_sul->out_cf_buffer(wr_sul);
		buffer_sul->out_bf_controle_fluxo(wok_sul);
		cf_sul->in_cf_buffer(wok_sul);		

		buffer_leste->in_bf_controle_fluxo(wr_leste);
		cf_leste->out_cf_buffer(wr_leste);
		buffer_leste->out_bf_controle_fluxo(wok_leste);
		cf_leste->in_cf_buffer(wok_leste);		

		buffer_oeste->in_bf_controle_fluxo(wr_oeste);
		cf_oeste->out_cf_buffer(wr_oeste);
		buffer_oeste->out_bf_controle_fluxo(wok_oeste);
		cf_oeste->in_cf_buffer(wok_oeste);		

		buffer_local->in_bf_controle_fluxo(wr_local);
		cf_local->out_cf_buffer(wr_local);
		buffer_local->out_bf_controle_fluxo(wok_local);
		cf_local->in_cf_buffer(wok_local);		

		//Ligação dos controles de fluxo internos...
		cf_saida_oeste->val(val_cf_oeste_to_leste_wire);
		cf_saida_oeste->ack(ack_cf_oeste_to_leste_wire);
		cf_saida_sul->val(val_cf_sul_to_norte_wire);
		cf_saida_sul->ack(ack_cf_sul_to_norte_wire);

		cf_saida_leste->val(val_cf_leste_to_oeste_wire);
		cf_saida_leste->ack(ack_cf_leste_to_oeste_wire);
		cf_saida_norte->val(val_cf_norte_to_sul_wire);
		cf_saida_norte->ack(ack_cf_norte_to_sul_wire);

		// Ligação das entradas dos cf's locais
		cf_local->in_val(val_cf_local_to_local_wire);
		cf_local->in_ack(ack_cf_local_to_local_wire);



        SC_METHOD(execute_controle_fluxo);
	        sensitive << cf_norte->in_val; 
	        sensitive << cf_sul->in_val;
	        sensitive << cf_leste->in_val; 
	        sensitive << cf_oeste->in_val; 
	        sensitive << cf_local->in_val;	
        

        SC_METHOD(execute_buffer);
        	sensitive << buffer_norte->in_bf_controle_fluxo;
        	sensitive << buffer_sul->in_bf_controle_fluxo;
        	sensitive << buffer_leste->in_bf_controle_fluxo;
        	sensitive << buffer_oeste->in_bf_controle_fluxo;
        	sensitive << buffer_local->in_bf_controle_fluxo;
        
        SC_METHOD(execute_buffer_retorno);
        	sensitive << cf_norte->in_cf_buffer;
        	sensitive << cf_sul->in_cf_buffer;
        	sensitive << cf_leste->in_cf_buffer;
        	sensitive << cf_oeste->in_cf_buffer;
        	sensitive << cf_local->in_cf_buffer;

    }

	
};
#endif
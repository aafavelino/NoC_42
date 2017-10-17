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

	sc_in <int> in_cff; //Entrada pra ver se no buffer terá espaço 
	sc_out<int> out_cff; 
	sc_signal <int>   roteia;
	//SINAIS DO CF NORMAL
	sc_signal<bool> cf_bf_wire_local; // Sinal que sai do CF e vai para o buffer
	sc_signal<bool> bf_cf_wire_local; // Sinal que sai do buffer e entra no CF
	sc_signal<bool> in_val_local; // Sinal que vem de outro CF e entra no CF Local
	sc_signal<bool> out_ack_local; // Sinal que sai do CF e entra num outro CF 

	sc_signal<bool> cf_bf_wire_oeste; // Sinal que sai do CF e vai para o buffer
	sc_signal<bool> bf_cf_wire_oeste; // Sinal que sai do buffer e entra no CF
	sc_signal<bool> in_val_oeste; // Sinal que vem de outro CF e entra no CF Local
	sc_signal<bool> out_ack_oeste; // Sinal que sai do CF e entra num outro CF 

	sc_signal<bool> cf_bf_wire_leste; // Sinal que sai do CF e vai para o buffer
	sc_signal<bool> bf_cf_wire_leste; // Sinal que sai do buffer e entra no CF
	sc_signal<bool> in_val_leste; // Sinal que vem de outro CF e entra no CF Local
	sc_signal<bool> out_ack_leste; // Sinal que sai do CF e entra num outro CF 

	sc_signal<bool> cf_bf_wire_sul; // Sinal que sai do CF e vai para o buffer
	sc_signal<bool> bf_cf_wire_sul; // Sinal que sai do buffer e entra no CF
	sc_signal<bool> in_val_sul; // Sinal que vem de outro CF e entra no CF Local
	sc_signal<bool> out_ack_sul; // Sinal que sai do CF e entra num outro CF 

	sc_signal<bool> cf_bf_wire_norte; // Sinal que sai do CF e vai para o buffer
	sc_signal<bool> bf_cf_wire_norte; // Sinal que sai do buffer e entra no CF
	sc_signal<bool> in_val_norte; // Sinal que vem de outro CF e entra no CF Local
	sc_signal<bool> out_ack_norte; // Sinal que sai do CF e entra num outro CF 
	//SINAIS DO CF DE SAIDA
	sc_signal<bool> rok_local;
	sc_signal<bool> rd_local;

	sc_signal<bool> rok_leste;
	sc_signal<bool> rd_leste;

	sc_signal<bool> rok_oeste;
	sc_signal<bool> rd_oeste;

	sc_signal<bool> rok_norte;
	sc_signal<bool> rd_norte;

	sc_signal<bool> rok_sul;
	sc_signal<bool> rd_sul;



	//sinal de teste
	sc_signal<bool> entrada1;
	sc_signal<bool> saida1;









	Flit in_data; //n+2 data + bop + eop
	Flit out_data; // Saída do roteamento n+2

	sc_int<32> in_val; // Entrada para o controle de fluxo
	sc_int<32> in_ack; // Saída do controle de fluxo 

	sc_int<32> x_rok; // É a variável que solicita se pode mandar para o outro roteador ao chaveamento (Arbitro)
	sc_int<32> rd; // É a resposta que vem do arbitro 
	
	Arbitro arbitro_centralizado;
	
	Buffer *buffer_norte;
	Buffer *buffer_sul;
	Buffer *buffer_leste;
	Buffer *buffer_oeste;
	Buffer *buffer_local;

	controle_fluxo *cf_buffer_norte;
	controle_fluxo *cf_buffer_sul;
	controle_fluxo *cf_buffer_leste;
	controle_fluxo *cf_buffer_oeste;
	controle_fluxo *cf_buffer_local;

	controle_fluxo_saida *cf_saida_norte;
	controle_fluxo_saida *cf_saida_sul;
	controle_fluxo_saida *cf_saida_leste;
	controle_fluxo_saida *cf_saida_oeste;
	//controle_fluxo_saida *cf_saida_local;

	Roteamento roteamento_norte;
	Roteamento roteamento_sul;
	Roteamento roteamento_leste;
	Roteamento roteamento_oeste;
	Roteamento roteamento_local;





	void execute();

	SC_CTOR(roteador) {
		buffer_norte = new Buffer("bufferNorte");
		buffer_sul = new Buffer("bufferSul");
		buffer_leste = new Buffer("bufferLeste");
		buffer_oeste = new Buffer("bufferOeste");
		buffer_local = new Buffer("bufferLocal");
		
		cf_buffer_norte = new controle_fluxo("cf_buffer_Norte");
		cf_buffer_sul = new controle_fluxo("cf_buffer_Sul");
		cf_buffer_leste = new controle_fluxo("cf_buffer_Leste");
		cf_buffer_oeste = new controle_fluxo("cf_buffer_Oeste");
		cf_buffer_local = new controle_fluxo("cf_buffer_Local");

		cf_saida_norte = new controle_fluxo_saida("cf_saida_Norte");
		cf_saida_sul = new controle_fluxo_saida("cf_saida_Sul");
		cf_saida_leste = new controle_fluxo_saida("cf_saida_Leste");
		cf_saida_oeste = new controle_fluxo_saida("cf_saida_Oeste");
		//cf_saida_local = new controle_fluxo_saida("cf_saida_Local");		

	    in_cff(roteia);
	    out_cff(roteia);

	    //Ligações de sinais...

	    //LOCAL
	    cf_buffer_local->in_val(in_val_local); // Falta ligar com Saída de outro cf de saída
	    cf_buffer_local->in_ack(out_ack_local); // Falta ligar com Saída de outro cf de saída

	    cf_buffer_local->out_cf_buffer(cf_bf_wire_local); // Saída do buffer para o controle de fluxo 
	    buffer_local->in_bf_controle_fluxo(cf_bf_wire_local); // Entrada no Controle de fluxo vindo do buffer

	    buffer_local->out_bf_controle_fluxo(bf_cf_wire_local); // Saída do controle de fluxo que vai para o buffer
	    cf_buffer_local->in_cf_buffer(bf_cf_wire_local); // Entrada do buffer que vai para o controle de fluxo
	    //OESTE
	    cf_buffer_oeste->in_val(in_val_oeste); // Falta ligar com Saída de outro cf de saída
	    cf_buffer_oeste->in_ack(out_ack_oeste); // Falta ligar com Saída de outro cf de saída

	    cf_buffer_oeste->out_cf_buffer(cf_bf_wire_oeste); // Saída do buffer para o controle de fluxo 
	    buffer_oeste->in_bf_controle_fluxo(cf_bf_wire_oeste); // Entrada no Controle de fluxo vindo do buffer

	    buffer_oeste->out_bf_controle_fluxo(bf_cf_wire_oeste); // Saída do controle de fluxo que vai para o buffer
	    cf_buffer_oeste->in_cf_buffer(bf_cf_wire_oeste); // Entrada do buffer que vai para o controle de fluxo
	    //LESTE
	    cf_buffer_leste->in_val(in_val_leste); // Falta ligar com Saída de outro cf de saída
	    cf_buffer_leste->in_ack(out_ack_leste); // Falta ligar com Saída de outro cf de saída

	    cf_buffer_leste->out_cf_buffer(cf_bf_wire_leste); // Saída do buffer para o controle de fluxo 
	    buffer_leste->in_bf_controle_fluxo(cf_bf_wire_leste); // Entrada no Controle de fluxo vindo do buffer

	    buffer_leste->out_bf_controle_fluxo(bf_cf_wire_leste); // Saída do controle de fluxo que vai para o buffer
	    cf_buffer_leste->in_cf_buffer(bf_cf_wire_leste); // Entrada do buffer que vai para o controle de fluxo
	    //SUL
	    cf_buffer_sul->in_val(in_val_sul); // Falta ligar com Saída de outro cf de saída
	    cf_buffer_sul->in_ack(out_ack_sul); // Falta ligar com Saída de outro cf de saída

	    cf_buffer_sul->out_cf_buffer(cf_bf_wire_sul); // Saída do buffer para o controle de fluxo 
	    buffer_sul->in_bf_controle_fluxo(cf_bf_wire_sul); // Entrada no Controle de fluxo vindo do buffer

	    buffer_sul->out_bf_controle_fluxo(bf_cf_wire_sul); // Saída do controle de fluxo que vai para o buffer
	    cf_buffer_sul->in_cf_buffer(bf_cf_wire_sul); // Entrada do buffer que vai para o controle de fluxo
	    //NORTE
	    cf_buffer_norte->in_val(in_val_norte); // Falta ligar com Saída de outro cf de saída
	    cf_buffer_norte->in_ack(out_ack_norte); // Falta ligar com Saída de outro cf de saída

	    cf_buffer_norte->out_cf_buffer(cf_bf_wire_norte); // Saída do buffer para o controle de fluxo 
	    buffer_norte->in_bf_controle_fluxo(cf_bf_wire_norte); // Entrada no Controle de fluxo vindo do buffer

	    buffer_norte->out_bf_controle_fluxo(bf_cf_wire_norte); // Saída do controle de fluxo que vai para o buffer
	    cf_buffer_norte->in_cf_buffer(bf_cf_wire_norte); // Entrada do buffer que vai para o controle de fluxo

	    // Ligação dos sinais somente do cf de saída
		cf_saida_norte->rok(rok_norte);
		cf_saida_norte->rd(rd_norte);
		
		cf_saida_sul->rok(rok_sul);
		cf_saida_sul->rd(rd_sul);
		
		cf_saida_leste->rok(rok_leste);
		cf_saida_leste->rd(rd_leste);
		
		cf_saida_oeste->rok(rok_oeste);
		cf_saida_oeste->rd(rd_oeste);
		



        SC_METHOD(execute);
		sensitive << in_cff;
		
    }

	
};
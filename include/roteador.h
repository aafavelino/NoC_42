#include <iostream>
#include <systemc.h>
#include "arbitro.h"
#include "roteamento.h"
#include "controle_fluxo.h"
#include "buffer.h"
#include "flit.h"

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define LOCAL 4


SC_MODULE (roteador)
{
public:

	Flit in_data; //n+2
	Flit din; //din do buffer que é data + bop + eop
	Flit x_dout; // Saída do roteamento n+2

	sc_in < sc_uint<32> > in_val; // Entrada para o controle de fluxo
	sc_out< sc_uint<32> > in_ack; // Saída do controle de fluxo 

	sc_out< sc_uint<32> > x_rok; // É a variável que solicita se pode mandar para o outro roteador ao chaveamento (Arbitro)
	sc_uint<32> rd; // É a resposta que vem do arbitro 

	
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

	Roteamento roteamento_norte;
	Roteamento roteamento_sul;
	Roteamento roteamento_leste;
	Roteamento roteamento_oeste;

	controle_fluxo *cf_saida_norte;
	controle_fluxo *cf_saida_sul;
	controle_fluxo *cf_saida_leste;
	controle_fluxo *cf_saida_oeste;
	controle_fluxo *cf_saida_local;


	void execute() {

	}
	void arbitragem() {

	}

	SC_CTOR(roteador) {
		buffer_norte = new Buffer("bufferN");
		buffer_sul = new Buffer("bufferS");
		buffer_leste = new Buffer("bufferL");
		buffer_oeste = new Buffer("bufferO");
		buffer_local = new Buffer("bufferLocal");
		
		cf_buffer_norte = new controle_fluxo("cf_buffer_N");
		cf_buffer_sul = new controle_fluxo("cf_buffer_S");
		cf_buffer_leste = new controle_fluxo("cf_buffer_L");
		cf_buffer_oeste = new controle_fluxo("cf_buffer_O");
		cf_buffer_local = new controle_fluxo("cf_buffer_Local");

		cf_saida_norte = new controle_fluxo("cf_saida_N");
		cf_saida_sul = new controle_fluxo("cf_saida_S");
		cf_saida_leste = new controle_fluxo("cf_saida_L");
		cf_saida_oeste = new controle_fluxo("cf_saida_O");
		cf_saida_local = new controle_fluxo("cf_saida_Local");

        SC_METHOD(execute);
        SC_METHOD(arbitragem);
        
		sensitive << in_val;
		
    }

	
};
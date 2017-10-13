#include <iostream>
#include <vector>
#include "systemc.h"
#include "pacote.h"
#include "buffer.h"
#include "flit.h"
#include "roteamento.h"
#include "roteador.h"


using namespace std;

int main(int argc, char const *argv[])
{



	Pacote pct;
	//Setar as cordenadas destinos dos flits...
	pct.flit[0].cordenadas_f.x = 2;
	pct.flit[0].cordenadas_f.y = 2;


	//Sinais do controle de fluxo
	sc_signal < sc_int<32> > in_ack;
	sc_signal < sc_int<32> > in_val;


	//Sinais do controle de fluxo para o buffer
	sc_signal < sc_int<32> > wr;
	sc_signal < sc_int<32> > wok;
	

//****************************************
	sc_signal < sc_int<32> > rd;
	sc_signal < sc_int<32> > rok;
//****************************************


// Criar uma Rede 4x4
	roteador *rede[3][3];

// Criando os roteadores para alocar na rede
	roteador roteador1("rot1");
	roteador roteador2("rot2");
	roteador roteador3("rot3");
	roteador roteador4("rot4");
	roteador roteador5("rot5");
	roteador roteador6("rot6");
	roteador roteador7("rot7");
	roteador roteador8("rot8");
	roteador roteador9("rot9");
// Alocando os roteadores no vetor rede
	rede[0][0] = &roteador1;	
	rede[0][1] = &roteador2;	
	rede[0][2] = &roteador3;	
	rede[1][0] = &roteador4;	
	rede[1][1] = &roteador5;	
	rede[1][2] = &roteador6;	
	rede[2][0] = &roteador7;	
	rede[2][1] = &roteador8;	
	rede[2][2] = &roteador9;

	rede[0][0]->in_val(in_val);
	rede[0][1]->in_val(in_val);
	rede[0][2]->in_val(in_val);
	rede[1][0]->in_val(in_val);
	rede[1][1]->in_val(in_val);
	rede[1][2]->in_val(in_val);
	rede[2][0]->in_val(in_val);
	rede[2][1]->in_val(in_val);
	rede[2][2]->in_val(in_val);

	rede[0][0]->in_ack(in_ack);
	rede[0][1]->in_ack(in_ack);
	rede[0][2]->in_ack(in_ack);
	rede[1][0]->in_ack(in_ack);
	rede[1][1]->in_ack(in_ack);
	rede[1][2]->in_ack(in_ack);
	rede[2][0]->in_ack(in_ack);
	rede[2][1]->in_ack(in_ack);
	rede[2][2]->in_ack(in_ack);

	rede[0][0]->buffer_norte->wr(wr);
	rede[0][1]->buffer_norte->wr(wr);
	rede[0][2]->buffer_norte->wr(wr);
	rede[1][0]->buffer_norte->wr(wr);
	rede[1][1]->buffer_norte->wr(wr);
	rede[1][2]->buffer_norte->wr(wr);
	rede[2][0]->buffer_norte->wr(wr);
	rede[2][1]->buffer_norte->wr(wr);
	rede[2][2]->buffer_norte->wr(wr);

	rede[0][0]->buffer_sul->wr(wr);
	rede[0][1]->buffer_sul->wr(wr);
	rede[0][2]->buffer_sul->wr(wr);
	rede[1][0]->buffer_sul->wr(wr);
	rede[1][1]->buffer_sul->wr(wr);
	rede[1][2]->buffer_sul->wr(wr);
	rede[2][0]->buffer_sul->wr(wr);
	rede[2][1]->buffer_sul->wr(wr);
	rede[2][2]->buffer_sul->wr(wr);

	rede[0][0]->buffer_leste->wr(wr);
	rede[0][1]->buffer_leste->wr(wr);
	rede[0][2]->buffer_leste->wr(wr);
	rede[1][0]->buffer_leste->wr(wr);
	rede[1][1]->buffer_leste->wr(wr);
	rede[1][2]->buffer_leste->wr(wr);
	rede[2][0]->buffer_leste->wr(wr);
	rede[2][1]->buffer_leste->wr(wr);
	rede[2][2]->buffer_leste->wr(wr);

	rede[0][0]->buffer_oeste->wr(wr);
	rede[0][1]->buffer_oeste->wr(wr);
	rede[0][2]->buffer_oeste->wr(wr);
	rede[1][0]->buffer_oeste->wr(wr);
	rede[1][1]->buffer_oeste->wr(wr);
	rede[1][2]->buffer_oeste->wr(wr);
	rede[2][0]->buffer_oeste->wr(wr);
	rede[2][1]->buffer_oeste->wr(wr);
	rede[2][2]->buffer_oeste->wr(wr);

	rede[0][0]->buffer_local->wr(wr);
	rede[0][1]->buffer_local->wr(wr);
	rede[0][2]->buffer_local->wr(wr);
	rede[1][0]->buffer_local->wr(wr);
	rede[1][1]->buffer_local->wr(wr);
	rede[1][2]->buffer_local->wr(wr);
	rede[2][0]->buffer_local->wr(wr);
	rede[2][1]->buffer_local->wr(wr);
	rede[2][2]->buffer_local->wr(wr);


	rede[0][0]->buffer_norte->wok(wok);
	rede[0][1]->buffer_norte->wok(wok);
	rede[0][2]->buffer_norte->wok(wok);
	rede[1][0]->buffer_norte->wok(wok);
	rede[1][1]->buffer_norte->wok(wok);
	rede[1][2]->buffer_norte->wok(wok);
	rede[2][0]->buffer_norte->wok(wok);
	rede[2][1]->buffer_norte->wok(wok);
	rede[2][2]->buffer_norte->wok(wok);

	rede[0][0]->buffer_sul->wok(wok);
	rede[0][1]->buffer_sul->wok(wok);
	rede[0][2]->buffer_sul->wok(wok);
	rede[1][0]->buffer_sul->wok(wok);
	rede[1][1]->buffer_sul->wok(wok);
	rede[1][2]->buffer_sul->wok(wok);
	rede[2][0]->buffer_sul->wok(wok);
	rede[2][1]->buffer_sul->wok(wok);
	rede[2][2]->buffer_sul->wok(wok);

	rede[0][0]->buffer_leste->wok(wok);
	rede[0][1]->buffer_leste->wok(wok);
	rede[0][2]->buffer_leste->wok(wok);
	rede[1][0]->buffer_leste->wok(wok);
	rede[1][1]->buffer_leste->wok(wok);
	rede[1][2]->buffer_leste->wok(wok);
	rede[2][0]->buffer_leste->wok(wok);
	rede[2][1]->buffer_leste->wok(wok);
	rede[2][2]->buffer_leste->wok(wok);

	rede[0][0]->buffer_oeste->wok(wok);
	rede[0][1]->buffer_oeste->wok(wok);
	rede[0][2]->buffer_oeste->wok(wok);
	rede[1][0]->buffer_oeste->wok(wok);
	rede[1][1]->buffer_oeste->wok(wok);
	rede[1][2]->buffer_oeste->wok(wok);
	rede[2][0]->buffer_oeste->wok(wok);
	rede[2][1]->buffer_oeste->wok(wok);
	rede[2][2]->buffer_oeste->wok(wok);

	rede[0][0]->buffer_local->wok(wok);
	rede[0][1]->buffer_local->wok(wok);
	rede[0][2]->buffer_local->wok(wok);
	rede[1][0]->buffer_local->wok(wok);
	rede[1][1]->buffer_local->wok(wok);
	rede[1][2]->buffer_local->wok(wok);
	rede[2][0]->buffer_local->wok(wok);
	rede[2][1]->buffer_local->wok(wok);
	rede[2][2]->buffer_local->wok(wok);

	rede[0][0]->cf_buffer_norte->in_val(in_val);
	rede[0][1]->cf_buffer_norte->in_val(in_val);
	rede[0][2]->cf_buffer_norte->in_val(in_val);
	rede[1][0]->cf_buffer_norte->in_val(in_val);
	rede[1][1]->cf_buffer_norte->in_val(in_val);
	rede[1][2]->cf_buffer_norte->in_val(in_val);
	rede[2][0]->cf_buffer_norte->in_val(in_val);
	rede[2][1]->cf_buffer_norte->in_val(in_val);
	rede[2][2]->cf_buffer_norte->in_val(in_val);

	rede[0][0]->cf_buffer_sul->in_val(in_val);
	rede[0][1]->cf_buffer_sul->in_val(in_val);
	rede[0][2]->cf_buffer_sul->in_val(in_val);
	rede[1][0]->cf_buffer_sul->in_val(in_val);
	rede[1][1]->cf_buffer_sul->in_val(in_val);
	rede[1][2]->cf_buffer_sul->in_val(in_val);
	rede[2][0]->cf_buffer_sul->in_val(in_val);
	rede[2][1]->cf_buffer_sul->in_val(in_val);
	rede[2][2]->cf_buffer_sul->in_val(in_val);


	
	rede[0][0]->cf_buffer_leste->in_val(in_val);
	rede[0][1]->cf_buffer_leste->in_val(in_val);
	rede[0][2]->cf_buffer_leste->in_val(in_val);
	rede[1][0]->cf_buffer_leste->in_val(in_val);
	rede[1][1]->cf_buffer_leste->in_val(in_val);
	rede[1][2]->cf_buffer_leste->in_val(in_val);
	rede[2][0]->cf_buffer_leste->in_val(in_val);
	rede[2][1]->cf_buffer_leste->in_val(in_val);
	rede[2][2]->cf_buffer_leste->in_val(in_val);

	
	rede[0][0]->cf_buffer_oeste->in_val(in_val);
	rede[0][1]->cf_buffer_oeste->in_val(in_val);
	rede[0][2]->cf_buffer_oeste->in_val(in_val);
	rede[1][0]->cf_buffer_oeste->in_val(in_val);
	rede[1][1]->cf_buffer_oeste->in_val(in_val);
	rede[1][2]->cf_buffer_oeste->in_val(in_val);
	rede[2][0]->cf_buffer_oeste->in_val(in_val);
	rede[2][1]->cf_buffer_oeste->in_val(in_val);
	rede[2][2]->cf_buffer_oeste->in_val(in_val);

	rede[0][0]->cf_buffer_local->in_val(in_val);
	rede[0][1]->cf_buffer_local->in_val(in_val);
	rede[0][2]->cf_buffer_local->in_val(in_val);
	rede[1][0]->cf_buffer_local->in_val(in_val);
	rede[1][1]->cf_buffer_local->in_val(in_val);
	rede[1][2]->cf_buffer_local->in_val(in_val);
	rede[2][0]->cf_buffer_local->in_val(in_val);
	rede[2][1]->cf_buffer_local->in_val(in_val);
	rede[2][2]->cf_buffer_local->in_val(in_val);


	rede[0][0]->cf_buffer_norte->in_ack(in_ack);
	rede[0][1]->cf_buffer_norte->in_ack(in_ack);
	rede[0][2]->cf_buffer_norte->in_ack(in_ack);
	rede[1][0]->cf_buffer_norte->in_ack(in_ack);
	rede[1][1]->cf_buffer_norte->in_ack(in_ack);
	rede[1][2]->cf_buffer_norte->in_ack(in_ack);
	rede[2][0]->cf_buffer_norte->in_ack(in_ack);
	rede[2][1]->cf_buffer_norte->in_ack(in_ack);
	rede[2][2]->cf_buffer_norte->in_ack(in_ack);

	rede[0][0]->cf_buffer_sul->in_ack(in_ack);
	rede[0][1]->cf_buffer_sul->in_ack(in_ack);
	rede[0][2]->cf_buffer_sul->in_ack(in_ack);
	rede[1][0]->cf_buffer_sul->in_ack(in_ack);
	rede[1][1]->cf_buffer_sul->in_ack(in_ack);
	rede[1][2]->cf_buffer_sul->in_ack(in_ack);
	rede[2][0]->cf_buffer_sul->in_ack(in_ack);
	rede[2][1]->cf_buffer_sul->in_ack(in_ack);
	rede[2][2]->cf_buffer_sul->in_ack(in_ack);


	
	rede[0][0]->cf_buffer_leste->in_ack(in_ack);
	rede[0][1]->cf_buffer_leste->in_ack(in_ack);
	rede[0][2]->cf_buffer_leste->in_ack(in_ack);
	rede[1][0]->cf_buffer_leste->in_ack(in_ack);
	rede[1][1]->cf_buffer_leste->in_ack(in_ack);
	rede[1][2]->cf_buffer_leste->in_ack(in_ack);
	rede[2][0]->cf_buffer_leste->in_ack(in_ack);
	rede[2][1]->cf_buffer_leste->in_ack(in_ack);
	rede[2][2]->cf_buffer_leste->in_ack(in_ack);

	
	rede[0][0]->cf_buffer_oeste->in_ack(in_ack);
	rede[0][1]->cf_buffer_oeste->in_ack(in_ack);
	rede[0][2]->cf_buffer_oeste->in_ack(in_ack);
	rede[1][0]->cf_buffer_oeste->in_ack(in_ack);
	rede[1][1]->cf_buffer_oeste->in_ack(in_ack);
	rede[1][2]->cf_buffer_oeste->in_ack(in_ack);
	rede[2][0]->cf_buffer_oeste->in_ack(in_ack);
	rede[2][1]->cf_buffer_oeste->in_ack(in_ack);
	rede[2][2]->cf_buffer_oeste->in_ack(in_ack);

	rede[0][0]->cf_buffer_local->in_ack(in_ack);
	rede[0][1]->cf_buffer_local->in_ack(in_ack);
	rede[0][2]->cf_buffer_local->in_ack(in_ack);
	rede[1][0]->cf_buffer_local->in_ack(in_ack);
	rede[1][1]->cf_buffer_local->in_ack(in_ack);
	rede[1][2]->cf_buffer_local->in_ack(in_ack);
	rede[2][0]->cf_buffer_local->in_ack(in_ack);
	rede[2][1]->cf_buffer_local->in_ack(in_ack);
	rede[2][2]->cf_buffer_local->in_ack(in_ack);


	rede[0][0]->cf_buffer_norte->wok(wok);
	rede[0][1]->cf_buffer_norte->wok(wok);
	rede[0][2]->cf_buffer_norte->wok(wok);
	rede[1][0]->cf_buffer_norte->wok(wok);
	rede[1][1]->cf_buffer_norte->wok(wok);
	rede[1][2]->cf_buffer_norte->wok(wok);
	rede[2][0]->cf_buffer_norte->wok(wok);
	rede[2][1]->cf_buffer_norte->wok(wok);
	rede[2][2]->cf_buffer_norte->wok(wok);

	rede[0][0]->cf_buffer_sul->wok(wok);
	rede[0][1]->cf_buffer_sul->wok(wok);
	rede[0][2]->cf_buffer_sul->wok(wok);
	rede[1][0]->cf_buffer_sul->wok(wok);
	rede[1][1]->cf_buffer_sul->wok(wok);
	rede[1][2]->cf_buffer_sul->wok(wok);
	rede[2][0]->cf_buffer_sul->wok(wok);
	rede[2][1]->cf_buffer_sul->wok(wok);
	rede[2][2]->cf_buffer_sul->wok(wok);


	
	rede[0][0]->cf_buffer_leste->wok(wok);
	rede[0][1]->cf_buffer_leste->wok(wok);
	rede[0][2]->cf_buffer_leste->wok(wok);
	rede[1][0]->cf_buffer_leste->wok(wok);
	rede[1][1]->cf_buffer_leste->wok(wok);
	rede[1][2]->cf_buffer_leste->wok(wok);
	rede[2][0]->cf_buffer_leste->wok(wok);
	rede[2][1]->cf_buffer_leste->wok(wok);
	rede[2][2]->cf_buffer_leste->wok(wok);

	
	rede[0][0]->cf_buffer_oeste->wok(wok);
	rede[0][1]->cf_buffer_oeste->wok(wok);
	rede[0][2]->cf_buffer_oeste->wok(wok);
	rede[1][0]->cf_buffer_oeste->wok(wok);
	rede[1][1]->cf_buffer_oeste->wok(wok);
	rede[1][2]->cf_buffer_oeste->wok(wok);
	rede[2][0]->cf_buffer_oeste->wok(wok);
	rede[2][1]->cf_buffer_oeste->wok(wok);
	rede[2][2]->cf_buffer_oeste->wok(wok);

	rede[0][0]->cf_buffer_local->wok(wok);
	rede[0][1]->cf_buffer_local->wok(wok);
	rede[0][2]->cf_buffer_local->wok(wok);
	rede[1][0]->cf_buffer_local->wok(wok);
	rede[1][1]->cf_buffer_local->wok(wok);
	rede[1][2]->cf_buffer_local->wok(wok);
	rede[2][0]->cf_buffer_local->wok(wok);
	rede[2][1]->cf_buffer_local->wok(wok);
	rede[2][2]->cf_buffer_local->wok(wok);

	rede[0][0]->cf_buffer_norte->wr(wr);
	rede[0][1]->cf_buffer_norte->wr(wr);
	rede[0][2]->cf_buffer_norte->wr(wr);
	rede[1][0]->cf_buffer_norte->wr(wr);
	rede[1][1]->cf_buffer_norte->wr(wr);
	rede[1][2]->cf_buffer_norte->wr(wr);
	rede[2][0]->cf_buffer_norte->wr(wr);
	rede[2][1]->cf_buffer_norte->wr(wr);
	rede[2][2]->cf_buffer_norte->wr(wr);

	rede[0][0]->cf_buffer_sul->wr(wr);
	rede[0][1]->cf_buffer_sul->wr(wr);
	rede[0][2]->cf_buffer_sul->wr(wr);
	rede[1][0]->cf_buffer_sul->wr(wr);
	rede[1][1]->cf_buffer_sul->wr(wr);
	rede[1][2]->cf_buffer_sul->wr(wr);
	rede[2][0]->cf_buffer_sul->wr(wr);
	rede[2][1]->cf_buffer_sul->wr(wr);
	rede[2][2]->cf_buffer_sul->wr(wr);


	
	rede[0][0]->cf_buffer_leste->wr(wr);
	rede[0][1]->cf_buffer_leste->wr(wr);
	rede[0][2]->cf_buffer_leste->wr(wr);
	rede[1][0]->cf_buffer_leste->wr(wr);
	rede[1][1]->cf_buffer_leste->wr(wr);
	rede[1][2]->cf_buffer_leste->wr(wr);
	rede[2][0]->cf_buffer_leste->wr(wr);
	rede[2][1]->cf_buffer_leste->wr(wr);
	rede[2][2]->cf_buffer_leste->wr(wr);

	rede[0][0]->cf_buffer_oeste->wr(wr);
	rede[0][1]->cf_buffer_oeste->wr(wr);
	rede[0][2]->cf_buffer_oeste->wr(wr);
	rede[1][0]->cf_buffer_oeste->wr(wr);
	rede[1][1]->cf_buffer_oeste->wr(wr);
	rede[1][2]->cf_buffer_oeste->wr(wr);
	rede[2][0]->cf_buffer_oeste->wr(wr);
	rede[2][1]->cf_buffer_oeste->wr(wr);
	rede[2][2]->cf_buffer_oeste->wr(wr);

	rede[0][0]->cf_buffer_local->wr(wr);
	rede[0][1]->cf_buffer_local->wr(wr);
	rede[0][2]->cf_buffer_local->wr(wr);
	rede[1][0]->cf_buffer_local->wr(wr);
	rede[1][1]->cf_buffer_local->wr(wr);
	rede[1][2]->cf_buffer_local->wr(wr);
	rede[2][0]->cf_buffer_local->wr(wr);
	rede[2][1]->cf_buffer_local->wr(wr);
	rede[2][2]->cf_buffer_local->wr(wr);

		//Cordenadas do roteador 1
	rede[0][0]->roteamento_norte.cordenada.x = 0;
	rede[0][0]->roteamento_norte.cordenada.y = 0;

	//Cordenadas do roteador 2
	rede[0][1]->roteamento_norte.cordenada.x = 0;
	rede[0][1]->roteamento_norte.cordenada.y = 1;

	//Cordenadas do roteador 3
	rede[0][2]->roteamento_norte.cordenada.x = 0;
	rede[0][2]->roteamento_norte.cordenada.y = 2;
	
	//Cordenadas do roteador 4
	rede[1][0]->roteamento_norte.cordenada.x = 1;
	rede[1][0]->roteamento_norte.cordenada.y = 0;
	
	//Cordenadas do roteador 5
	rede[1][1]->roteamento_norte.cordenada.x = 1;
	rede[1][1]->roteamento_norte.cordenada.y = 1;
	
	//Cordenadas do roteador 6
	rede[1][2]->roteamento_norte.cordenada.x = 1;
	rede[1][2]->roteamento_norte.cordenada.y = 2;
	
	//Cordenadas do roteador 7
	rede[2][0]->roteamento_norte.cordenada.x = 2;
	rede[2][0]->roteamento_norte.cordenada.y = 0;
	
	//Cordenadas do roteador 8
	rede[2][1]->roteamento_norte.cordenada.x = 2;
	rede[2][1]->roteamento_norte.cordenada.y = 1;
	
	//Cordenadas do roteador 9
	rede[2][2]->roteamento_norte.cordenada.x = 2;
	rede[2][2]->roteamento_norte.cordenada.y = 2;



	return 0;

}

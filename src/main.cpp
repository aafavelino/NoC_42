#include <systemc.h>
#include "roteador.h"
#include "pacote.h"


#define LARGURA_REDE 2
#define ALTURA_REDE 2
#define QUANT_ROTEADORES 9

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define LOCAL 4

using namespace std;

int sc_main (int argc, char* argv[]) {

	/**
	 * Por fazer.:
	 *	-- Pegar tamanho da rede pelo argv[1].
	 *  -- Pegar quantidade de pacotes da rede pelo argv[2].
	 *	-- Ver o que deve setar manualmente...
	 */

//***********************************************************************	
// Dados dos pacotes e dos flits AINDA MANUALMENTE
// Criando um pacote de flits
	Pacote pct;
//Setar as cordenadas destinos dos flits...
	pct.flit[0].cordenadas_f.x = 1;
	pct.flit[0].cordenadas_f.y = 1;
//***********************************************************************



//***********************************************************************
	sc_signal<bool> terra0;
	sc_signal<bool> terra1;
	sc_signal<bool> terra2;
	sc_signal<bool> terra3;
	sc_signal<bool> terra4;
	sc_signal<bool> terra5;
	sc_signal<bool> terra6;
	sc_signal<bool> terra7;
	sc_signal<bool> terra8;
	sc_signal<bool> terra9;
	sc_signal<bool> terra10;
	sc_signal<bool> terra11;
	sc_signal<bool> terra12;
	sc_signal<bool> terra13;
	sc_signal<bool> terra14;
	sc_signal<bool> terra15;
	sc_signal<bool> terra16;
	sc_signal<bool> terra17;
	sc_signal<bool> terra18;
	sc_signal<bool> terra19;
	sc_signal<bool> terra20;
//***********************************************************************





	// Criando uma Rede Altura x Largura
	roteador *rede[ALTURA_REDE][LARGURA_REDE];


  	roteador roteador1("roteador_1");
  	roteador roteador2("roteador_2");
  	roteador roteador3("roteador_3");
  	roteador roteador4("roteador_4");

  	// Alocando os roteadores na matriz rede MANUALMENTE AINDA
	rede[0][0] = &roteador1;
	rede[0][1] = &roteador2;
	rede[1][0] = &roteador3;
	rede[1][1] = &roteador4;


//<<<<SINAIS NULOS QUE NAO SAO USADOS>>>>

	rede[0][0]->cf_saida_norte->val(terra0);
	rede[0][0]->cf_saida_norte->ack(terra0);
	rede[0][0]->cf_saida_oeste->val(terra1);
	rede[0][0]->cf_saida_oeste->ack(terra1);

	rede[0][1]->cf_saida_norte->val(terra2);
	rede[0][1]->cf_saida_norte->ack(terra2);
	rede[0][1]->cf_saida_leste->val(terra3);
	rede[0][1]->cf_saida_leste->ack(terra3);

	rede[1][0]->cf_saida_sul->val(terra4);
	rede[1][0]->cf_saida_sul->ack(terra4);
	rede[1][0]->cf_saida_oeste->val(terra5);
	rede[1][0]->cf_saida_oeste->ack(terra5);

	rede[1][1]->cf_saida_sul->val(terra6);
	rede[1][1]->cf_saida_sul->ack(terra6);
	rede[1][1]->cf_saida_leste->val(terra7);
	rede[1][1]->cf_saida_leste->ack(terra7);		



//Conexões Controles de fluxo entrada e controle de fluxo saída.
//***********************************************************************

	//Sinais do roteador 1 para o roteador 2
	rede[0][0]->cf_saida_leste->val(rede[0][1]->in_val_oeste);
	rede[0][0]->cf_saida_leste->ack(rede[0][1]->out_ack_oeste);
	//Sinais do roteador 2 para o roteador 1
	rede[0][1]->cf_saida_oeste->val(rede[0][0]->in_val_leste);
	rede[0][1]->cf_saida_oeste->ack(rede[0][0]->out_ack_leste);
		


	//Sinais do roteador 1 para o roteador 3
	rede[0][0]->cf_saida_sul->val(rede[1][0]->in_val_norte);
	rede[0][0]->cf_saida_sul->ack(rede[1][0]->out_ack_norte);
	//Sinais do roteador 3 para o roteador 1
	rede[1][0]->cf_saida_norte->val(rede[0][0]->in_val_sul);
	rede[1][0]->cf_saida_norte->ack(rede[0][0]->out_ack_sul);
		


	//Sinais do roteador 2 para o roteador 4
	rede[0][1]->cf_saida_sul->val(rede[1][1]->in_val_norte);
	rede[0][1]->cf_saida_sul->ack(rede[1][1]->out_ack_norte);
	//Sinais do roteador 4 para o roteador 2
	rede[1][1]->cf_saida_norte->val(rede[0][1]->in_val_sul);
	rede[1][1]->cf_saida_norte->ack(rede[0][1]->out_ack_sul);


	//Sinais do roteador 3 para o roteador 4
	rede[1][0]->cf_saida_leste->val(rede[1][1]->in_val_oeste);
	rede[1][0]->cf_saida_leste->ack(rede[1][1]->out_ack_oeste);
	//Sinais do roteador 4 para o roteador 3
	rede[1][1]->cf_saida_oeste->val(rede[1][0]->in_val_leste);
	rede[1][1]->cf_saida_oeste->ack(rede[1][0]->out_ack_leste);

//***********************************************************************



  	roteador1.roteia = 20;


	sc_start();

  

  return 0;// Terminate simulation
}
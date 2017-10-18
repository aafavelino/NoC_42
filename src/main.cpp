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






	// Criando uma Rede Altura x Largura
	roteador *rede[ALTURA_REDE][LARGURA_REDE];


  	roteador roteador1("roteador1");
  	roteador roteador2("roteador2");
  	roteador roteador3("roteador3");
  	roteador roteador4("roteador4");


  	// Alocando os roteadores na matriz rede MANUALMENTE AINDA
	rede[0][0] = &roteador1;
	rede[0][1] = &roteador2;
	rede[1][0] = &roteador3;
	rede[1][1] = &roteador4;

// Aterramentos
//***********************************************************************
	sc_signal<int> terra[100];

//***********************************************************************




//<<<<SINAIS NULOS QUE NAO SAO USADOS>>>>


	rede[0][1]->cf_saida_leste->ack(terra[0]);
	rede[0][1]->cf_saida_leste->rd(terra[1]);
	rede[0][1]->cf_saida_leste->val(terra[2]);
	rede[0][1]->cf_saida_leste->rok(terra[3]);

	rede[0][1]->cf_saida_norte->ack(terra[4]);
	rede[0][1]->cf_saida_norte->rd(terra[5]);
	rede[0][1]->cf_saida_norte->val(terra[6]);
	rede[0][1]->cf_saida_norte->rok(terra[7]);
	
	rede[0][1]->cf_leste->in_ack(terra[8]);
	rede[0][1]->cf_leste->in_val(terra[9]);
	rede[0][1]->cf_norte->in_ack(terra[10]);
	rede[0][1]->cf_norte->in_val(terra[11]);


	rede[0][0]->cf_saida_oeste->ack(terra[12]);
	rede[0][0]->cf_saida_oeste->rd(terra[13]);
	rede[0][0]->cf_saida_oeste->val(terra[14]);
	rede[0][0]->cf_saida_oeste->rok(terra[15]);

	rede[0][0]->cf_saida_norte->ack(terra[16]);
	rede[0][0]->cf_saida_norte->rd(terra[17]);
	rede[0][0]->cf_saida_norte->val(terra[18]);
	rede[0][0]->cf_saida_norte->rok(terra[19]);	

	rede[0][0]->cf_oeste->in_ack(terra[20]);
	rede[0][0]->cf_oeste->in_val(terra[21]);
	rede[0][0]->cf_norte->in_ack(terra[22]);
	rede[0][0]->cf_norte->in_val(terra[23]);

	rede[1][1]->cf_saida_leste->ack(terra[24]);
	rede[1][1]->cf_saida_leste->rd(terra[25]);
	rede[1][1]->cf_saida_leste->val(terra[26]);
	rede[1][1]->cf_saida_leste->rok(terra[27]);

	rede[1][1]->cf_sul->in_ack(terra[32]);
	rede[1][1]->cf_sul->in_val(terra[33]);
	rede[1][1]->cf_leste->in_ack(terra[34]);
	rede[1][1]->cf_leste->in_val(terra[35]);

	rede[1][1]->cf_saida_sul->ack(terra[28]);
	rede[1][1]->cf_saida_sul->rd(terra[29]);
	rede[1][1]->cf_saida_sul->val(terra[30]);
	rede[1][1]->cf_saida_sul->rok(terra[31]);

	rede[1][0]->cf_saida_oeste->ack(terra[36]);
	rede[1][0]->cf_saida_oeste->rd(terra[37]);
	rede[1][0]->cf_saida_oeste->val(terra[38]);
	rede[1][0]->cf_saida_oeste->rok(terra[39]);

	rede[1][0]->cf_sul->in_ack(terra[40]);
	rede[1][0]->cf_sul->in_val(terra[41]);
	rede[1][0]->cf_oeste->in_ack(terra[42]);
	rede[1][0]->cf_oeste->in_val(terra[43]);

	rede[1][0]->cf_saida_sul->ack(terra[44]);
	rede[1][0]->cf_saida_sul->rd(terra[45]);
	rede[1][0]->cf_saida_sul->val(terra[46]);
	rede[1][0]->cf_saida_sul->rok(terra[47]);
//***********************************************************************
	// Roteador 2 para roteador 1
	//Val
	rede[0][1]->cf_saida_oeste->val(rede[0][1]->val_cf_oeste_to_leste_wire[0]);
	rede[0][0]->cf_leste->in_val(rede[0][1]->val_cf_oeste_to_leste_wire[0]);
	//ack
	rede[0][1]->cf_saida_oeste->ack(rede[0][1]->ack_cf_oeste_to_leste_wire[0]);
	rede[0][0]->cf_leste->in_ack(rede[0][1]->ack_cf_oeste_to_leste_wire[0]);

	// Roteador 1 para roteador 2
	//Val
	rede[0][0]->cf_saida_leste->val(rede[0][0]->val_cf_leste_to_oeste_wire[0]);
	rede[0][1]->cf_oeste->in_val(rede[0][0]->val_cf_leste_to_oeste_wire[0]);
	//ack
	rede[0][0]->cf_saida_leste->ack(rede[0][0]->ack_cf_leste_to_oeste_wire[0]);
	rede[0][1]->cf_oeste->in_ack(rede[0][0]->ack_cf_leste_to_oeste_wire[0]);
	

		//Sinal ainda não usado...
	rede[0][1]->cf_saida_oeste->rd(rede[0][1]->rd_cf_oeste[0]);
	rede[0][1]->cf_saida_oeste->rok(rede[0][1]->rok_cf_oeste[0]);
	rede[0][0]->cf_saida_leste->rd(rede[0][0]->rd_cf_oeste[0]);
	rede[0][0]->cf_saida_leste->rok(rede[0][0]->rok_cf_oeste[0]);




	// Roteador 4 para roteador 3
	//Val
	rede[1][1]->cf_saida_oeste->val(rede[1][1]->val_cf_oeste_to_leste_wire[1]);
	rede[1][0]->cf_leste->in_val(rede[1][1]->val_cf_oeste_to_leste_wire[1]);
	//ack
	rede[1][1]->cf_saida_oeste->ack(rede[1][1]->ack_cf_oeste_to_leste_wire[1]);
	rede[1][0]->cf_leste->in_ack(rede[1][1]->ack_cf_oeste_to_leste_wire[1]);

	// Roteador 3 para roteador 4
	//Val
	rede[1][0]->cf_saida_leste->val(rede[1][0]->val_cf_leste_to_oeste_wire[1]);
	rede[1][1]->cf_oeste->in_val(rede[1][0]->val_cf_leste_to_oeste_wire[1]);
	//ack
	rede[1][0]->cf_saida_leste->ack(rede[1][0]->ack_cf_leste_to_oeste_wire[1]);
	rede[1][1]->cf_oeste->in_ack(rede[1][0]->ack_cf_leste_to_oeste_wire[1]);
	

		//Sinal ainda não usado...
	rede[1][1]->cf_saida_oeste->rd(rede[1][1]->rd_cf_oeste[1]);
	rede[1][1]->cf_saida_oeste->rok(rede[1][1]->rok_cf_oeste[1]);
	rede[1][0]->cf_saida_leste->rd(rede[1][0]->rd_cf_oeste[1]);
	rede[1][0]->cf_saida_leste->rok(rede[1][0]->rok_cf_oeste[1]);







	// Roteador 4 para roteador 2
	//Val
	rede[1][1]->cf_saida_norte->val(rede[1][1]->val_cf_norte_to_sul_wire[1]);
	rede[0][1]->cf_sul->in_val(rede[1][1]->val_cf_norte_to_sul_wire[1]);
	//ack
	rede[1][1]->cf_saida_norte->ack(rede[1][1]->ack_cf_norte_to_sul_wire[1]);
	rede[0][1]->cf_sul->in_ack(rede[1][1]->ack_cf_norte_to_sul_wire[1]);

	// Roteador 2 para roteador 4
	//Val
	rede[0][1]->cf_saida_sul->val(rede[0][1]->val_cf_sul_to_norte_wire[0]);
	rede[1][1]->cf_norte->in_val(rede[0][1]->val_cf_sul_to_norte_wire[0]);
	//ack
	rede[0][1]->cf_saida_sul->ack(rede[0][1]->ack_cf_sul_to_norte_wire[0]);
	rede[1][1]->cf_norte->in_ack(rede[0][1]->ack_cf_sul_to_norte_wire[0]);
	

		//Sinal ainda não usado...
	rede[0][1]->cf_saida_sul->rd(rede[0][1]->rd_cf_sul[1]);
	rede[0][1]->cf_saida_sul->rok(rede[0][1]->rok_cf_sul[1]);
	rede[1][1]->cf_saida_norte->rd(rede[1][1]->rd_cf_norte[1]);
	rede[1][1]->cf_saida_norte->rok(rede[1][1]->rok_cf_norte[1]);











	// Roteador 3 para roteador 1
	//Val
	rede[1][0]->cf_saida_norte->val(rede[1][0]->val_cf_norte_to_sul_wire[1]);
	rede[0][0]->cf_sul->in_val(rede[1][0]->val_cf_norte_to_sul_wire[1]);
	//ack
	rede[1][0]->cf_saida_norte->ack(rede[1][0]->ack_cf_norte_to_sul_wire[1]);
	rede[0][0]->cf_sul->in_ack(rede[1][0]->ack_cf_norte_to_sul_wire[1]);

	// Roteador 1 para roteador 3
	//Val
	rede[0][0]->cf_saida_sul->val(rede[0][0]->val_cf_sul_to_norte_wire[0]);
	rede[1][0]->cf_norte->in_val(rede[0][0]->val_cf_sul_to_norte_wire[0]);
	//ack
	rede[0][0]->cf_saida_sul->ack(rede[0][0]->ack_cf_sul_to_norte_wire[0]);
	rede[1][0]->cf_norte->in_ack(rede[0][0]->ack_cf_sul_to_norte_wire[0]);
	

		//Sinal ainda não usado...
	rede[1][0]->cf_saida_norte->rd(rede[1][0]->rd_cf_norte[1]);
	rede[1][0]->cf_saida_norte->rok(rede[1][0]->rok_cf_norte[1]);
	rede[0][0]->cf_saida_sul->rd(rede[0][0]->rd_cf_sul[1]);
	rede[0][0]->cf_saida_sul->rok(rede[0][0]->rok_cf_sul[1]);




/*

	rede[0][1]->in_cff(rede[0][1]->roteia);
	rede[0][0]->out_cff(rede[0][1]->roteia);
	
	rede[0][0]->in_cff(rede[0][0]->roteia);
	rede[0][1]->out_cff(rede[0][0]->roteia);
*/

	

	

	
//	rede[0][1]->roteia = 20;
	sc_start();
//cout << "rede[0][0]->  " << rede[0][0]->out_cff.read() << endl;		
//	rede[0][1]->roteia = 50;
//	sc_start();
//cout << "rede[0][0]->  " << rede[0][0]->out_cff.read() << endl;		
  

  return 0;// Terminate simulation
}
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
	rede[0][1]->cf_saida_leste->val(terra[2]);

	rede[0][1]->cf_saida_norte->ack(terra[4]);
	rede[0][1]->cf_saida_norte->val(terra[6]);
	
	rede[0][1]->cf_leste->in_ack(terra[8]);
	rede[0][1]->cf_leste->in_val(terra[9]);
	rede[0][1]->cf_norte->in_ack(terra[10]);
	rede[0][1]->cf_norte->in_val(terra[11]);


	rede[0][0]->cf_saida_oeste->ack(terra[12]);
	rede[0][0]->cf_saida_oeste->val(terra[14]);

	rede[0][0]->cf_saida_norte->ack(terra[16]);
	rede[0][0]->cf_saida_norte->val(terra[18]);

	rede[0][0]->cf_oeste->in_ack(terra[20]);
	rede[0][0]->cf_oeste->in_val(terra[21]);
	rede[0][0]->cf_norte->in_ack(terra[22]);
	rede[0][0]->cf_norte->in_val(terra[23]);

	rede[1][1]->cf_saida_leste->ack(terra[24]);
	rede[1][1]->cf_saida_leste->val(terra[26]);

	rede[1][1]->cf_sul->in_ack(terra[32]);
	rede[1][1]->cf_sul->in_val(terra[33]);
	rede[1][1]->cf_leste->in_ack(terra[34]);
	rede[1][1]->cf_leste->in_val(terra[35]);

	rede[1][1]->cf_saida_sul->ack(terra[28]);
	rede[1][1]->cf_saida_sul->val(terra[30]);

	rede[1][0]->cf_saida_oeste->ack(terra[36]);
	rede[1][0]->cf_saida_oeste->val(terra[38]);

	rede[1][0]->cf_sul->in_ack(terra[40]);
	rede[1][0]->cf_sul->in_val(terra[41]);
	rede[1][0]->cf_oeste->in_ack(terra[42]);
	rede[1][0]->cf_oeste->in_val(terra[43]);

	rede[1][0]->cf_saida_sul->ack(terra[44]);
	rede[1][0]->cf_saida_sul->val(terra[46]);
//***********************************************************************
	


	// Roteador 2 para roteador 1
	//Val
	rede[0][1]->cf_saida_oeste->val(rede[0][1]->val_cf_oeste_to_leste_wire);
	rede[0][0]->cf_leste->in_val(rede[0][1]->val_cf_oeste_to_leste_wire);
	//ack
	rede[0][1]->cf_saida_oeste->ack(rede[0][1]->ack_cf_oeste_to_leste_wire);
	rede[0][0]->cf_leste->in_ack(rede[0][1]->ack_cf_oeste_to_leste_wire);

	// Roteador 1 para roteador 2
	//Val
	rede[0][0]->cf_saida_leste->val(rede[0][0]->val_cf_leste_to_oeste_wire);
	rede[0][1]->cf_oeste->in_val(rede[0][0]->val_cf_leste_to_oeste_wire);
	//ack
	rede[0][0]->cf_saida_leste->ack(rede[0][0]->ack_cf_leste_to_oeste_wire);
	rede[0][1]->cf_oeste->in_ack(rede[0][0]->ack_cf_leste_to_oeste_wire);
	



	// Roteador 4 para roteador 3
	//Val
	rede[1][1]->cf_saida_oeste->val(rede[1][1]->val_cf_oeste_to_leste_wire);
	rede[1][0]->cf_leste->in_val(rede[1][1]->val_cf_oeste_to_leste_wire);
	//ack
	rede[1][1]->cf_saida_oeste->ack(rede[1][1]->ack_cf_oeste_to_leste_wire);
	rede[1][0]->cf_leste->in_ack(rede[1][1]->ack_cf_oeste_to_leste_wire);

	// Roteador 3 para roteador 4
	//Val
	rede[1][0]->cf_saida_leste->val(rede[1][0]->val_cf_leste_to_oeste_wire);
	rede[1][1]->cf_oeste->in_val(rede[1][0]->val_cf_leste_to_oeste_wire);
	//ack
	rede[1][0]->cf_saida_leste->ack(rede[1][0]->ack_cf_leste_to_oeste_wire);
	rede[1][1]->cf_oeste->in_ack(rede[1][0]->ack_cf_leste_to_oeste_wire);
	






	// Roteador 4 para roteador 2
	//Val
	rede[1][1]->cf_saida_norte->val(rede[1][1]->val_cf_norte_to_sul_wire);
	rede[0][1]->cf_sul->in_val(rede[1][1]->val_cf_norte_to_sul_wire);
	//ack
	rede[1][1]->cf_saida_norte->ack(rede[1][1]->ack_cf_norte_to_sul_wire);
	rede[0][1]->cf_sul->in_ack(rede[1][1]->ack_cf_norte_to_sul_wire);

	// Roteador 2 para roteador 4
	//Val
	rede[0][1]->cf_saida_sul->val(rede[0][1]->val_cf_sul_to_norte_wire);
	rede[1][1]->cf_norte->in_val(rede[0][1]->val_cf_sul_to_norte_wire);
	//ack
	rede[0][1]->cf_saida_sul->ack(rede[0][1]->ack_cf_sul_to_norte_wire);
	rede[1][1]->cf_norte->in_ack(rede[0][1]->ack_cf_sul_to_norte_wire);
	








	// Roteador 3 para roteador 1
	//Val
	rede[1][0]->cf_saida_norte->val(rede[1][0]->val_cf_norte_to_sul_wire);
	rede[0][0]->cf_sul->in_val(rede[1][0]->val_cf_norte_to_sul_wire);
	//ack
	rede[1][0]->cf_saida_norte->ack(rede[1][0]->ack_cf_norte_to_sul_wire);
	rede[0][0]->cf_sul->in_ack(rede[1][0]->ack_cf_norte_to_sul_wire);

	// Roteador 1 para roteador 3
	//Val
	rede[0][0]->cf_saida_sul->val(rede[0][0]->val_cf_sul_to_norte_wire);
	rede[1][0]->cf_norte->in_val(rede[0][0]->val_cf_sul_to_norte_wire);
	//ack
	rede[0][0]->cf_saida_sul->ack(rede[0][0]->ack_cf_sul_to_norte_wire);
	rede[1][0]->cf_norte->in_ack(rede[0][0]->ack_cf_sul_to_norte_wire);
	


//Ligando sinais dos cfs para os buffers
	//norte
	rede[1][1]->buffer_norte->in_bf_controle_fluxo(rede[1][1]->wr_norte);
	rede[1][1]->cf_norte->out_cf_buffer(rede[1][1]->wr_norte);
	rede[1][1]->buffer_norte->out_bf_controle_fluxo(rede[1][1]->wok_norte);
	rede[1][1]->cf_norte->in_cf_buffer(rede[1][1]->wok_norte);

	rede[1][0]->buffer_norte->in_bf_controle_fluxo(rede[1][0]->wr_norte);
	rede[1][0]->cf_norte->out_cf_buffer(rede[1][0]->wr_norte);
	rede[1][0]->buffer_norte->out_bf_controle_fluxo(rede[1][0]->wok_norte);
	rede[1][0]->cf_norte->in_cf_buffer(rede[1][0]->wok_norte);

	rede[0][1]->buffer_norte->in_bf_controle_fluxo(rede[0][1]->wr_norte);
	rede[0][1]->cf_norte->out_cf_buffer(rede[0][1]->wr_norte);
	rede[0][1]->buffer_norte->out_bf_controle_fluxo(rede[0][1]->wok_norte);
	rede[0][1]->cf_norte->in_cf_buffer(rede[0][1]->wok_norte);

	rede[0][0]->buffer_norte->in_bf_controle_fluxo(rede[0][0]->wr_norte);
	rede[0][0]->cf_norte->out_cf_buffer(rede[0][0]->wr_norte);
	rede[0][0]->buffer_norte->out_bf_controle_fluxo(rede[0][0]->wok_norte);
	rede[0][0]->cf_norte->in_cf_buffer(rede[0][0]->wok_norte);

	//Sul
	rede[1][1]->buffer_sul->in_bf_controle_fluxo(rede[1][1]->wr_sul);
	rede[1][1]->cf_sul->out_cf_buffer(rede[1][1]->wr_sul);
	rede[1][1]->buffer_sul->out_bf_controle_fluxo(rede[1][1]->wok_sul);
	rede[1][1]->cf_sul->in_cf_buffer(rede[1][1]->wok_sul);

	rede[1][0]->buffer_sul->in_bf_controle_fluxo(rede[1][0]->wr_sul);
	rede[1][0]->cf_sul->out_cf_buffer(rede[1][0]->wr_sul);
	rede[1][0]->buffer_sul->out_bf_controle_fluxo(rede[1][0]->wok_sul);
	rede[1][0]->cf_sul->in_cf_buffer(rede[1][0]->wok_sul);

	rede[0][1]->buffer_sul->in_bf_controle_fluxo(rede[0][1]->wr_sul);
	rede[0][1]->cf_sul->out_cf_buffer(rede[0][1]->wr_sul);
	rede[0][1]->buffer_sul->out_bf_controle_fluxo(rede[0][1]->wok_sul);
	rede[0][1]->cf_sul->in_cf_buffer(rede[0][1]->wok_sul);

	rede[0][0]->buffer_sul->in_bf_controle_fluxo(rede[0][0]->wr_sul);
	rede[0][0]->cf_sul->out_cf_buffer(rede[0][0]->wr_sul);
	rede[0][0]->buffer_sul->out_bf_controle_fluxo(rede[0][0]->wok_sul);
	rede[0][0]->cf_sul->in_cf_buffer(rede[0][0]->wok_sul);

	//Leste
	rede[1][1]->buffer_leste->in_bf_controle_fluxo(rede[1][1]->wr_leste);
	rede[1][1]->cf_leste->out_cf_buffer(rede[1][1]->wr_leste);
	rede[1][1]->buffer_leste->out_bf_controle_fluxo(rede[1][1]->wok_leste);
	rede[1][1]->cf_leste->in_cf_buffer(rede[1][1]->wok_leste);

	rede[1][0]->buffer_leste->in_bf_controle_fluxo(rede[1][0]->wr_leste);
	rede[1][0]->cf_leste->out_cf_buffer(rede[1][0]->wr_leste);
	rede[1][0]->buffer_leste->out_bf_controle_fluxo(rede[1][0]->wok_leste);
	rede[1][0]->cf_leste->in_cf_buffer(rede[1][0]->wok_leste);

	rede[0][1]->buffer_leste->in_bf_controle_fluxo(rede[0][1]->wr_leste);
	rede[0][1]->cf_leste->out_cf_buffer(rede[0][1]->wr_leste);
	rede[0][1]->buffer_leste->out_bf_controle_fluxo(rede[0][1]->wok_leste);
	rede[0][1]->cf_leste->in_cf_buffer(rede[0][1]->wok_leste);

	rede[0][0]->buffer_leste->in_bf_controle_fluxo(rede[0][0]->wr_leste);
	rede[0][0]->cf_leste->out_cf_buffer(rede[0][0]->wr_leste);
	rede[0][0]->buffer_leste->out_bf_controle_fluxo(rede[0][0]->wok_leste);
	rede[0][0]->cf_leste->in_cf_buffer(rede[0][0]->wok_leste);

	//Oeste
	rede[1][1]->buffer_oeste->in_bf_controle_fluxo(rede[1][1]->wr_oeste);
	rede[1][1]->cf_oeste->out_cf_buffer(rede[1][1]->wr_oeste);
	rede[1][1]->buffer_oeste->out_bf_controle_fluxo(rede[1][1]->wok_oeste);
	rede[1][1]->cf_oeste->in_cf_buffer(rede[1][1]->wok_oeste);

	rede[1][0]->buffer_oeste->in_bf_controle_fluxo(rede[1][0]->wr_oeste);
	rede[1][0]->cf_oeste->out_cf_buffer(rede[1][0]->wr_oeste);
	rede[1][0]->buffer_oeste->out_bf_controle_fluxo(rede[1][0]->wok_oeste);
	rede[1][0]->cf_oeste->in_cf_buffer(rede[1][0]->wok_oeste);

	rede[0][1]->buffer_oeste->in_bf_controle_fluxo(rede[0][1]->wr_oeste);
	rede[0][1]->cf_oeste->out_cf_buffer(rede[0][1]->wr_oeste);
	rede[0][1]->buffer_oeste->out_bf_controle_fluxo(rede[0][1]->wok_oeste);
	rede[0][1]->cf_oeste->in_cf_buffer(rede[0][1]->wok_oeste);

	rede[0][0]->buffer_oeste->in_bf_controle_fluxo(rede[0][0]->wr_oeste);
	rede[0][0]->cf_oeste->out_cf_buffer(rede[0][0]->wr_oeste);
	rede[0][0]->buffer_oeste->out_bf_controle_fluxo(rede[0][0]->wok_oeste);
	rede[0][0]->cf_oeste->in_cf_buffer(rede[0][0]->wok_oeste);


// Ligação das entradas dos cf's locais
	rede[0][0]->cf_local->in_val(rede[0][0]->val_cf_local_to_local_wire);
	rede[0][0]->cf_local->in_ack(rede[0][0]->ack_cf_local_to_local_wire);

	rede[0][1]->cf_local->in_val(rede[0][1]->val_cf_local_to_local_wire);
	rede[0][1]->cf_local->in_ack(rede[0][1]->ack_cf_local_to_local_wire);

	rede[1][0]->cf_local->in_val(rede[1][0]->val_cf_local_to_local_wire);
	rede[1][0]->cf_local->in_ack(rede[1][0]->ack_cf_local_to_local_wire);

	rede[1][1]->cf_local->in_val(rede[1][1]->val_cf_local_to_local_wire);
	rede[1][1]->cf_local->in_ack(rede[1][1]->ack_cf_local_to_local_wire);			


// Ligação de tudo do buffer local e controle de fluxo local 
	rede[0][0]->buffer_local->in_bf_controle_fluxo(rede[0][0]->wr_local);
	rede[0][0]->cf_local->out_cf_buffer(rede[0][0]->wr_local);
	rede[0][0]->buffer_local->out_bf_controle_fluxo(rede[0][0]->wok_local);
	rede[0][0]->cf_local->in_cf_buffer(rede[0][0]->wok_local);

	rede[0][1]->buffer_local->in_bf_controle_fluxo(rede[0][1]->wr_local);
	rede[0][1]->cf_local->out_cf_buffer(rede[0][1]->wr_local);
	rede[0][1]->buffer_local->out_bf_controle_fluxo(rede[0][1]->wok_local);
	rede[0][1]->cf_local->in_cf_buffer(rede[0][1]->wok_local);

	rede[1][0]->buffer_local->in_bf_controle_fluxo(rede[1][0]->wr_local);
	rede[1][0]->cf_local->out_cf_buffer(rede[1][0]->wr_local);
	rede[1][0]->buffer_local->out_bf_controle_fluxo(rede[1][0]->wok_local);
	rede[1][0]->cf_local->in_cf_buffer(rede[1][0]->wok_local);

	rede[1][1]->buffer_local->in_bf_controle_fluxo(rede[1][1]->wr_local);
	rede[1][1]->cf_local->out_cf_buffer(rede[1][1]->wr_local);
	rede[1][1]->buffer_local->out_bf_controle_fluxo(rede[1][1]->wok_local);
	rede[1][1]->cf_local->in_cf_buffer(rede[1][1]->wok_local);


	//Setando as Cordenadas dos roteadores Ex.: roteador1 se encontra em rede[0][0]
	for (int x = 0; x < ALTURA_REDE; ++x){
		for (int y = 0; y < LARGURA_REDE; ++y) {	
			rede[x][y]->roteamento_norte.cordenada.x = x;
			rede[x][y]->roteamento_norte.cordenada.y = y;
			rede[x][y]->roteamento_sul.cordenada.x = x;
			rede[x][y]->roteamento_sul.cordenada.y = y;
			rede[x][y]->roteamento_leste.cordenada.x = x;
			rede[x][y]->roteamento_leste.cordenada.y = y;
			rede[x][y]->roteamento_oeste.cordenada.x = x;
			rede[x][y]->roteamento_oeste.cordenada.y = y;
			rede[x][y]->roteamento_local.cordenada.x = x;
			rede[x][y]->roteamento_local.cordenada.y = y;			
		}
	}

	rede[0][0]->roteamento_norte.cordenada_destino.x = pct.flit[0].cordenadas_f.x;
	rede[0][0]->roteamento_norte.cordenada_destino.y = pct.flit[0].cordenadas_f.y;






	rede[0][0]->buffer_norte->din = pct.flit[0];
	rede[0][0]->roteamento_norte.rotear_xy();


	



	
	rede[0][0]->arbitro_centralizado.portaDestino = rede[0][0]->roteamento_norte.portaDestino;
	rede[0][0]->arbitro_centralizado.setPrioridade();
	rede[0][0]->cf_saida_leste->val.write(1);




	


	
	



	sc_start();


	if (rede[0][1]->cf_oeste->in_val.read() == 1)
	{
		
		rede[0][1]->buffer_oeste->out_bf_controle_fluxo.write(rede[0][1]->buffer_oeste->isEmpty());
	}

	std::cout << "\n \ncontrole fluxo saida  LESTE " << rede[0][0]->cf_saida_leste->ack.read() << endl;
















  return 0;// Terminate simulation
}
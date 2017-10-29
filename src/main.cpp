#include <systemc.h>
#include "roteador.h"
#include "pacote.h"

// Não tá simples, nem manutenível
// Tem que melhorar o código
// refactorring 

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
	pct.flit[0].cordenadas_f.x = 0;
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
	sc_signal<int> ground_connection_val[100];
	sc_signal<int> ground_connection_ack[100];

//***********************************************************************
//<<<<SINAIS NULOS QUE NAO SAO USADOS>>>>
	int cont = 0;
	for (int i = 0; i < ALTURA_REDE; ++i)
	{
		for (int j = 0; j < LARGURA_REDE; ++j)
		{
			if (i == 0)
			{	
				
				cout << "rede[" << i << "][" << j << "]->cf_norte->in_val(ground_connection_val[" << cont<< "])"  << endl;
				cout << "rede[" << i << "][" << j << "]->cf_norte->in_ack(ground_connection_val[" << cont<< "])"  << endl;
				rede[i][j]->cf_norte->in_val(ground_connection_val[cont]);
				rede[i][j]->cf_norte->in_ack(ground_connection_ack[cont]);
				cont++;
			}
			if (j == 0)
			{	
				cout << "rede[" << i << "][" << j << "]->cf_oeste->in_val(ground_connection_val[" << cont<< "])"  << endl;
				cout << "rede[" << i << "][" << j << "]->cf_oeste->in_ack(ground_connection_val[" << cont<< "])"  << endl;				
				rede[i][j]->cf_oeste->in_val(ground_connection_val[cont]);
				rede[i][j]->cf_oeste->in_ack(ground_connection_ack[cont]);
				cont++;
			}
			if (i == ALTURA_REDE-1)
			{	
				cout << "rede[" << i << "][" << j << "]->cf_sul->in_val(ground_connection_val[" << cont<< "])"  << endl;
				cout << "rede[" << i << "][" << j << "]->cf_sul->in_ack(ground_connection_val[" << cont<< "])"  << endl;				
				rede[i][j]->cf_sul->in_val(ground_connection_val[cont]);
				rede[i][j]->cf_sul->in_ack(ground_connection_ack[cont]);
				cont++;
			}
			if (j == LARGURA_REDE-1)
			{	
				cout << "rede[" << i << "][" << j << "]->cf_leste->in_val(ground_connection_val[" << cont<< "])"  << endl;
				cout << "rede[" << i << "][" << j << "]->cf_leste->in_ack(ground_connection_val[" << cont<< "])"  << endl;				
				rede[i][j]->cf_leste->in_val(ground_connection_val[cont]);
				rede[i][j]->cf_leste->in_ack(ground_connection_ack[cont]);
				cont++;
			}

		}
	}

//***********************************************************************
	
	for (int i = 0; i < ALTURA_REDE; ++i)
	{
		for (int j = 0; j < LARGURA_REDE; ++j)
		{
			if (j != LARGURA_REDE-1)
			{
				rede[i][j]->cf_leste->in_val(rede[i][j+1]->val_cf_oeste_to_leste_wire);
				rede[i][j]->cf_leste->in_ack(rede[i][j+1]->ack_cf_oeste_to_leste_wire);
			}
			if (j != 0)
			{
				rede[i][j]->cf_oeste->in_val(rede[i][j-1]->val_cf_leste_to_oeste_wire);
				rede[i][j]->cf_oeste->in_ack(rede[i][j-1]->ack_cf_leste_to_oeste_wire);
				
			}
			if (i != ALTURA_REDE-1)
			{
				rede[i][j]->cf_sul->in_val(rede[i+1][j]->val_cf_norte_to_sul_wire);
				rede[i][j]->cf_sul->in_ack(rede[i+1][j]->ack_cf_norte_to_sul_wire);
			}
			if (i != 0)
			{
				rede[i][j]->cf_norte->in_val(rede[i-1][j]->val_cf_sul_to_norte_wire);
				rede[i][j]->cf_norte->in_ack(rede[i-1][j]->ack_cf_sul_to_norte_wire);
			}

		}
	}

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

	//Setando as cordenadas do primeiro flit
	rede[0][0]->roteamento_leste.cordenada_destino.x = pct.flit[0].cordenadas_f.x;
	rede[0][0]->roteamento_leste.cordenada_destino.y = pct.flit[0].cordenadas_f.y;
	//Alocando o flit no buffer
	rede[0][0]->buffer_leste->din = pct.flit[0];
	//Roteando
	rede[0][0]->roteamento_leste.rotear_xy();
	//Recebendo na porta destino do arbitro 
	rede[0][0]->arbitro_centralizado.portaDestino = rede[0][0]->roteamento_norte.portaDestino;
	//Colocando no buffer circular
	rede[0][0]->arbitro_centralizado.setPrioridade();

	rede[0][0]->cf_saida_leste->val.write(1);

	sc_start();



	if (rede[0][0]->cf_saida_leste->ack.read() == 1)
	{
		std::cout << "Gravar no buffer oeste r2" << endl;


		rede[0][1]->buffer_oeste->din = pct.flit[0];
		rede[0][1]->buffer_oeste->add();
		rede[0][1]->roteamento_oeste.cordenada_destino.x = pct.flit[0].cordenadas_f.x;
		rede[0][1]->roteamento_oeste.cordenada_destino.y = pct.flit[0].cordenadas_f.y;

		rede[0][1]->roteamento_oeste.rotear_xy();
	
		rede[0][1]->arbitro_centralizado.portaDestino = rede[0][1]->roteamento_oeste.portaDestino;
		rede[0][1]->arbitro_centralizado.setPrioridade();
		// teste


		if ((rede[0][1]->roteamento_oeste.cordenada.x == pct.flit[0].cordenadas_f.x) and (rede[0][1]->roteamento_oeste.cordenada.y == pct.flit[0].cordenadas_f.y))
		{
			cout << "Chegou" << endl;\
			//jogar no buffer local
			rede[0][1]->buffer_local->din = rede[0][1]->buffer_oeste->flits.front();
			rede[0][1]->buffer_oeste->remove();
			rede[0][1]->buffer_local->add();

		} else {
			if (rede[0][1]->arbitro_centralizado.portaDestino == 2)
				rede[0][1]->cf_saida_sul->val.write(1);
			sc_start();
		}

	} 

	if (rede[0][0]->cf_saida_sul->ack.read() == 1)
	{
		std::cout << "Gravar no buffer oeste r2" << endl;
		rede[1][0]->buffer_norte->din = pct.flit[0];
		rede[1][0]->buffer_norte->add();
		rede[1][0]->roteamento_norte.cordenada_destino.x = pct.flit[0].cordenadas_f.x;
		rede[1][0]->roteamento_norte.cordenada_destino.y = pct.flit[0].cordenadas_f.y;

		rede[1][0]->roteamento_norte.rotear_xy();
	
		rede[1][0]->arbitro_centralizado.portaDestino = rede[1][0]->roteamento_norte.portaDestino;
		rede[1][0]->arbitro_centralizado.setPrioridade();
		// teste


		if ((rede[1][0]->roteamento_norte.cordenada.x == pct.flit[0].cordenadas_f.x) and (rede[1][0]->roteamento_norte.cordenada.y == pct.flit[0].cordenadas_f.y))
		{
			cout << "Chegou" << endl;
			//jogar no buffer local
			rede[1][0]->buffer_local->din = rede[0][1]->buffer_norte->flits.front();
			rede[1][0]->buffer_norte->remove();
			rede[1][0]->buffer_local->add();
		} else {
			if (rede[1][0]->arbitro_centralizado.portaDestino == 1)
				rede[1][0]->cf_saida_leste->val.write(1);
			sc_start();
		}

	} 

	if (rede[0][1]->cf_saida_sul->ack.read() == 1)
	{
		std::cout << "Gravar no buffer norte r4" << endl;
		rede[1][1]->buffer_norte->din = pct.flit[0];
		rede[1][1]->buffer_norte->add();
		rede[1][1]->roteamento_norte.cordenada_destino.x = pct.flit[0].cordenadas_f.x;
		rede[1][1]->roteamento_norte.cordenada_destino.y = pct.flit[0].cordenadas_f.y;

		rede[1][1]->roteamento_norte.rotear_xy();
	
		rede[1][1]->arbitro_centralizado.portaDestino = rede[1][1]->roteamento_norte.portaDestino;
		rede[1][1]->arbitro_centralizado.setPrioridade();

		if ((rede[1][1]->roteamento_norte.cordenada.x == pct.flit[0].cordenadas_f.x) and (rede[1][1]->roteamento_norte.cordenada.y == pct.flit[0].cordenadas_f.y))
		{
			cout << "Chegou..." << endl;
			rede[1][1]->buffer_local->din = rede[1][1]->buffer_norte->flits.front();
			rede[1][1]->buffer_norte->remove();
			rede[1][1]->buffer_local->add();
		} else {
			if (rede[1][1]->arbitro_centralizado.portaDestino == 3)
				rede[1][1]->cf_saida_oeste->val.write(1);
			sc_start();
		}

	} 

	if (rede[0][1]->cf_saida_oeste->ack.read() == 1)
	{
		std::cout << "Gravar no buffer oeste r2" << endl;
		rede[0][0]->buffer_leste->din = pct.flit[0];
		rede[0][0]->buffer_leste->add();
		rede[0][0]->roteamento_leste.cordenada_destino.x = pct.flit[0].cordenadas_f.x;
		rede[0][0]->roteamento_leste.cordenada_destino.y = pct.flit[0].cordenadas_f.y;

		rede[0][0]->roteamento_leste.rotear_xy();
	
		rede[0][0]->arbitro_centralizado.portaDestino = rede[0][0]->roteamento_leste.portaDestino;
		rede[0][0]->arbitro_centralizado.setPrioridade();
		// teste


		if ((rede[0][0]->roteamento_leste.cordenada.x == pct.flit[0].cordenadas_f.x) and (rede[0][1]->roteamento_leste.cordenada.y == pct.flit[0].cordenadas_f.y))
		{
			cout << "Chegou" << endl;
			rede[0][0]->buffer_local->din = rede[0][0]->buffer_leste->flits.front();
			rede[0][0]->buffer_leste->remove();
			rede[0][0]->buffer_local->add();			

		} else {
			if (rede[0][0]->arbitro_centralizado.portaDestino == 2)
				rede[0][0]->cf_saida_sul->val.write(1);		
			sc_start();
		}

	} 	




	if (rede[1][1]->cf_saida_norte->ack.read() == 1)
	{
		std::cout << "Gravar no buffer sul r2" << endl;
		rede[0][1]->buffer_sul->din = pct.flit[0];
		rede[0][1]->buffer_sul->add();
		rede[0][1]->roteamento_sul.cordenada_destino.x = pct.flit[0].cordenadas_f.x;
		rede[0][1]->roteamento_sul.cordenada_destino.y = pct.flit[0].cordenadas_f.y;

		rede[0][1]->roteamento_sul.rotear_xy();
	
		rede[0][1]->arbitro_centralizado.portaDestino = rede[0][1]->roteamento_sul.portaDestino;
		rede[0][1]->arbitro_centralizado.setPrioridade();
		// teste


		if ((rede[0][1]->roteamento_sul.cordenada.x == pct.flit[0].cordenadas_f.x) and (rede[0][1]->roteamento_sul.cordenada.y == pct.flit[0].cordenadas_f.y))
		{
			cout << "Chegou" << endl;
			//jogar no buffer local
			rede[0][1]->buffer_local->din = rede[0][1]->buffer_sul->flits.front();
			rede[0][1]->buffer_sul->remove();
			rede[0][1]->buffer_local->add();
		} else {
			if (rede[0][1]->arbitro_centralizado.portaDestino == 3)
				rede[0][1]->cf_saida_oeste->val.write(1);
			sc_start();
		}

	} 	


	if (rede[1][1]->cf_saida_oeste->ack.read() == 1)
	{
		std::cout << "Gravar no buffer leste r3" << endl;
		rede[1][0]->buffer_leste->din = pct.flit[0];
		rede[1][0]->buffer_leste->add();
		rede[1][0]->roteamento_leste.cordenada_destino.x = pct.flit[0].cordenadas_f.x;
		rede[1][0]->roteamento_leste.cordenada_destino.y = pct.flit[0].cordenadas_f.y;

		rede[1][0]->roteamento_leste.rotear_xy();
	
		rede[1][0]->arbitro_centralizado.portaDestino = rede[1][0]->roteamento_leste.portaDestino;
		rede[1][0]->arbitro_centralizado.setPrioridade();
		// teste


		if ((rede[1][0]->roteamento_leste.cordenada.x == pct.flit[0].cordenadas_f.x) and (rede[1][0]->roteamento_leste.cordenada.y == pct.flit[0].cordenadas_f.y))
		{
			cout << "Chegou" << endl;
			//jogar no buffer local
			rede[1][0]->buffer_local->din = rede[1][0]->buffer_leste->flits.front();
			rede[1][0]->buffer_leste->remove();
			rede[1][0]->buffer_local->add();
		} else {
			if (rede[1][0]->arbitro_centralizado.portaDestino == 0)
				rede[1][0]->cf_saida_norte->val.write(1);
			sc_start();
		}

	} 	



	if (rede[1][0]->cf_saida_norte->ack.read() == 1)
	{
		std::cout << "Gravar no buffer leste r3" << endl;
		rede[0][0]->buffer_sul->din = pct.flit[0];
		rede[0][0]->buffer_sul->add();
		rede[0][0]->roteamento_sul.cordenada_destino.x = pct.flit[0].cordenadas_f.x;
		rede[0][0]->roteamento_sul.cordenada_destino.y = pct.flit[0].cordenadas_f.y;

		rede[0][0]->roteamento_sul.rotear_xy();
	
		rede[0][0]->arbitro_centralizado.portaDestino = rede[0][0]->roteamento_sul.portaDestino;
		rede[0][0]->arbitro_centralizado.setPrioridade();
		// teste


		if ((rede[0][0]->roteamento_sul.cordenada.x == pct.flit[0].cordenadas_f.x) and (rede[0][0]->roteamento_sul.cordenada.y == pct.flit[0].cordenadas_f.y))
		{
			cout << "Chegou" << endl;
			//jogar no buffer local
			rede[0][0]->buffer_local->din = rede[0][0]->buffer_sul->flits.front();
			rede[0][0]->buffer_sul->remove();
			rede[0][0]->buffer_local->add();
		} else {
			if (rede[0][0]->arbitro_centralizado.portaDestino == 1)
				rede[0][0]->cf_saida_leste->val.write(1);
			sc_start();
		}

	} 	



	if (rede[1][0]->cf_saida_leste->ack.read() == 1)
	{
		std::cout << "Gravar no buffer leste r3" << endl;
		rede[1][1]->buffer_oeste->din = pct.flit[0];
		rede[1][1]->buffer_oeste->add();
		rede[1][1]->roteamento_oeste.cordenada_destino.x = pct.flit[0].cordenadas_f.x;
		rede[1][1]->roteamento_oeste.cordenada_destino.y = pct.flit[0].cordenadas_f.y;

		rede[1][1]->roteamento_oeste.rotear_xy();
	
		rede[1][1]->arbitro_centralizado.portaDestino = rede[1][1]->roteamento_oeste.portaDestino;
		rede[1][1]->arbitro_centralizado.setPrioridade();


		if ((rede[1][1]->roteamento_oeste.cordenada.x == pct.flit[0].cordenadas_f.x) and (rede[1][1]->roteamento_oeste.cordenada.y == pct.flit[0].cordenadas_f.y))
		{
			cout << "Chegou" << endl;
			//jogar no buffer local
			rede[1][0]->buffer_local->din = rede[0][1]->buffer_oeste->flits.front();
			rede[1][0]->buffer_oeste->remove();
			rede[1][0]->buffer_local->add();			
		} else {
			if (rede[1][1]->arbitro_centralizado.portaDestino == 1)
				rede[1][1]->cf_saida_norte->val.write(1);
			sc_start(10, SC_NS );
		}

	} 	

  return 0;// Terminate simulation
}
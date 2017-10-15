#include <iostream>
#include <vector>
#include "systemc.h"
#include "pacote.h"
#include "buffer.h"
#include "flit.h"
#include "roteamento.h"
#include "roteador.h"


#define LARGURA_REDE 2
#define ALTURA_REDE 2
#define QUANT_ROTEADORES 4

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define LOCAL 4

using namespace std;


int main(int argc, char const *argv[])
{

	sc_clock clock("clock", 10, SC_NS, 1, 10, SC_NS);
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
	pct.flit[0].cordenadas_f.x = 2;
	pct.flit[0].cordenadas_f.y = 2;
//***********************************************************************




//***********************************************************************
//Sinais do controle de fluxo
	sc_signal < sc_int<32> > in_ack[ALTURA_REDE][LARGURA_REDE][5];
	sc_signal < sc_int<32> > in_val[ALTURA_REDE][LARGURA_REDE][5];
//Sinais do controle de fluxo para o buffer
	sc_signal < sc_int<32> > wr[ALTURA_REDE][LARGURA_REDE][5];
	sc_signal < sc_int<32> > wok[ALTURA_REDE][LARGURA_REDE][5];
// Sinais da outra ponta do buffer
	sc_signal < sc_int<32> > rok[ALTURA_REDE][LARGURA_REDE][5];
	sc_signal < sc_int<32> > rd[ALTURA_REDE][LARGURA_REDE][5];

//Sinais de cada ROTEADOR
sc_signal < sc_int<32> > in_ack_r[QUANT_ROTEADORES];
sc_signal < sc_int<32> > in_val_r[QUANT_ROTEADORES];


//***********************************************************************







// Criando uma Rede Altura X Largura
	roteador *rede[ALTURA_REDE][LARGURA_REDE];
	
// Criando os roteadores para alocar na rede MANUALMENTE AINDA
	roteador roteador1("roteador1");
	roteador roteador2("roteador2");
	roteador roteador3("roteador3");
	roteador roteador4("roteador4");

// Alocando os roteadores na matriz rede MANUALMENTE AINDA
	rede[0][0] = &roteador1;	
	rede[0][1] = &roteador2;	
	rede[1][0] = &roteador3;	
	rede[1][1] = &roteador4;	


//***********************************************************************
//***********************Ligando os SINAIS*******************************
	//SINAIS DOS ROTEADORES
	int aux_cont_rot = 0;
	for (int x = 0; x < ALTURA_REDE; ++x){
		for (int y = 0; y < LARGURA_REDE; ++y){
			rede[x][y]->in_val(in_val_r[aux_cont_rot]);
			rede[x][y]->in_ack(in_ack_r[aux_cont_rot]);
			//std::cout << "[" << x << "][" << y << "] = " <<  aux_cont_rot<< endl;
			aux_cont_rot++;
		}
	}

	//SINAIS DOS COMPONENTES DOS ROTEADORES
	for (int x = 0; x < ALTURA_REDE; ++x){
		for (int y = 0; y < LARGURA_REDE; ++y){
			//Controle de fluxo Local
			rede[x][y]->cf_buffer_local->in_ack(in_ack[x][y][LOCAL]);
			rede[x][y]->cf_buffer_local->wr(wr[x][y][LOCAL]);
			//Controle de fluxo oeste
			rede[x][y]->cf_buffer_oeste->in_ack(in_ack[x][y][WEST]);
			rede[x][y]->cf_buffer_oeste->wr(wr[x][y][WEST]);
			//Controle de fluxo leste
			rede[x][y]->cf_buffer_leste->in_ack(in_ack[x][y][EAST]);
			rede[x][y]->cf_buffer_leste->wr(wr[x][y][EAST]);
			//Controle de fluxo sul
			rede[x][y]->cf_buffer_sul->in_ack(in_ack[x][y][SOUTH]);
			rede[x][y]->cf_buffer_sul->wr(wr[x][y][SOUTH]);
			//Controle de fluxo norte
			rede[x][y]->cf_buffer_norte->in_ack(in_ack[x][y][NORTH]);
			rede[x][y]->cf_buffer_norte->wr(wr[x][y][NORTH]);
		//*********SINAIS DOS BUFFERS********

		}
	}
//***********************************************************************



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
		}
	}
	
	// Setando um flit inicial para teste...
	std::cout << "Dados do primeiro flit a ser enviado... " << endl;
	rede[0][0]->in_data = pct.flit[0];
	std::cout << "Cabeça: " << rede[0][0]->in_data.cabeca << endl;
	std::cout << "Terminador: " << rede[0][0]->in_data.terminador << endl;
	std::cout << "Payload: " << rede[0][0]->in_data.payload << endl;
	std::cout << "Cordenadas: " << rede[0][0]->in_data.cordenadas_f.x <<" "<< rede[0][0]->in_data.cordenadas_f.y << endl;
	

	//sc_start(); // Run the simulation till sc_stop is encountered
	sc_int<32> i = 1;
	
	cout << i;


	return 0;

}

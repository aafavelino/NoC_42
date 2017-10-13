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

	Pacote pct;
//Setar as cordenadas destinos dos flits...
	pct.flit[0].cordenadas_f.x = 2;
	pct.flit[0].cordenadas_f.y = 2;

//Sinais do controle de fluxo
	sc_signal < sc_int<32> > in_ack[QUANT_ROTEADORES][2][5];
	sc_signal < sc_int<32> > in_val[QUANT_ROTEADORES][2][5];
//Sinais do controle de fluxo para o buffer
	sc_signal < sc_int<32> > wr[QUANT_ROTEADORES][2][5];
	sc_signal < sc_int<32> > wok[QUANT_ROTEADORES][2][5];
// Sinais da outra ponta do buffer
	sc_signal < sc_int<32> > rok[QUANT_ROTEADORES][2][5];
	sc_signal < sc_int<32> > rd[QUANT_ROTEADORES][2][5];


//Sinais do ROTEADOR
sc_signal < sc_int<32> > in_ack_r[QUANT_ROTEADORES];
sc_signal < sc_int<32> > in_val_r[QUANT_ROTEADORES];



// Criar uma Rede Altura X Largura
	roteador *rede[ALTURA_REDE][LARGURA_REDE];
	

// Criando os roteadores para alocar na rede
	roteador roteador1("roteador1");
	roteador roteador2("roteador2");
	roteador roteador3("roteador3");
	roteador roteador4("roteador4");

// Alocando os roteadores na matriz rede
	rede[0][0] = &roteador1;	
	rede[0][1] = &roteador2;	
	rede[1][0] = &roteador3;	
	rede[1][1] = &roteador4;	


// Ligando os SINAIS
	//SINAIS DOS ROTEADORES
	rede[0][0]->in_val(in_val_r[0]);
	rede[0][0]->in_ack(in_ack_r[0]);
	rede[0][1]->in_val(in_val_r[1]);
	rede[0][1]->in_ack(in_ack_r[1]);
	rede[1][0]->in_val(in_val_r[2]);
	rede[1][0]->in_ack(in_ack_r[2]);
	rede[1][1]->in_val(in_val_r[3]);
	rede[1][1]->in_ack(in_ack_r[3]);


	//SINAIS DOS COMPONENTES DOS ROTEADORES
	for (int x = 0; x < ALTURA_REDE; ++x)
		for (int y = 0; y < LARGURA_REDE; ++y){
			//Controle de fluxo Local
			rede[x][y]->cf_buffer_local->in_val(in_val[x][y][LOCAL]);
			rede[x][y]->cf_buffer_local->in_ack(in_ack[x][y][LOCAL]);
			rede[x][y]->cf_buffer_local->wr(wr[x][y][LOCAL]);
			rede[x][y]->cf_buffer_local->wok(wok[x][y][LOCAL]);
			//Controle de fluxo oeste
			rede[x][y]->cf_buffer_oeste->in_val(in_val[x][y][WEST]);
			rede[x][y]->cf_buffer_oeste->in_ack(in_ack[x][y][WEST]);
			rede[x][y]->cf_buffer_oeste->wr(wr[x][y][WEST]);
			rede[x][y]->cf_buffer_oeste->wok(wok[x][y][WEST]);
			//Controle de fluxo leste
			rede[x][y]->cf_buffer_leste->in_val(in_val[x][y][EAST]);
			rede[x][y]->cf_buffer_leste->in_ack(in_ack[x][y][EAST]);
			rede[x][y]->cf_buffer_leste->wr(wr[x][y][EAST]);
			rede[x][y]->cf_buffer_leste->wok(wok[x][y][EAST]);
			//Controle de fluxo sul
			rede[x][y]->cf_buffer_sul->in_val(in_val[x][y][SOUTH]);
			rede[x][y]->cf_buffer_sul->in_ack(in_ack[x][y][SOUTH]);
			rede[x][y]->cf_buffer_sul->wr(wr[x][y][SOUTH]);
			rede[x][y]->cf_buffer_sul->wok(wok[x][y][SOUTH]);
			//Controle de fluxo norte
			rede[x][y]->cf_buffer_norte->in_val(in_val[x][y][NORTH]);
			rede[x][y]->cf_buffer_norte->in_ack(in_ack[x][y][NORTH]);
			rede[x][y]->cf_buffer_norte->wr(wr[x][y][NORTH]);
			rede[x][y]->cf_buffer_norte->wok(wok[x][y][NORTH]);
		//*********SINAIS DOS BUFFERS********
			//Buffer Local
			rede[x][y]->buffer_local->wr(wr[x][y][LOCAL]);
			rede[x][y]->buffer_local->wok(wok[x][y][LOCAL]);
			rede[x][y]->buffer_local->rok(rok[x][y][LOCAL]);
			rede[x][y]->buffer_local->rd(rd[x][y][LOCAL]);
			//Buffer oeste
			rede[x][y]->buffer_oeste->wr(wr[x][y][WEST]);
			rede[x][y]->buffer_oeste->wok(wok[x][y][WEST]);
			rede[x][y]->buffer_oeste->rok(rok[x][y][WEST]);
			rede[x][y]->buffer_oeste->rd(rd[x][y][WEST]);			
			//Buffer leste
			rede[x][y]->buffer_leste->wr(wr[x][y][EAST]);
			rede[x][y]->buffer_leste->wok(wok[x][y][EAST]);
			rede[x][y]->buffer_leste->rok(rok[x][y][EAST]);
			rede[x][y]->buffer_leste->rd(rd[x][y][EAST]);			
			//Buffer sul
			rede[x][y]->buffer_sul->wr(wr[x][y][SOUTH]);
			rede[x][y]->buffer_sul->wok(wok[x][y][SOUTH]);
			rede[x][y]->buffer_sul->rok(rok[x][y][SOUTH]);
			rede[x][y]->buffer_sul->rd(rd[x][y][SOUTH]);
			//Buffer norte
			rede[x][y]->buffer_norte->wr(wr[x][y][NORTH]);
			rede[x][y]->buffer_norte->wok(wok[x][y][NORTH]);
			rede[x][y]->buffer_norte->rok(rok[x][y][NORTH]);
			rede[x][y]->buffer_norte->rd(rd[x][y][NORTH]);
		}


	//Setando as Cordenadas dos roteadores

	for (int x = 0; x < ALTURA_REDE; ++x)
		for (int y = 0; y < LARGURA_REDE; ++y) {	
			rede[x][y]->roteamento_norte.cordenada.x = x;
			rede[x][y]->roteamento_norte.cordenada.y = y;
		}

	cout << "CORDENADA TESTE >>>>>" << rede[1][1]->roteamento_norte.cordenada.y << endl;

	// Setando um flit inicial para teste...
	std::cout << "Dados do primeiro flit a ser enviado... " << endl;

	rede[0][0]->in_data = pct.flit[0];

	std::cout << "Cabeça: " << rede[0][0]->in_data.cabeca << endl;
	std::cout << "Terminador: " << rede[0][0]->in_data.terminador << endl;
	std::cout << "Payload: " << rede[0][0]->in_data.payload << endl;
	std::cout << "Cordenadas: " << rede[0][0]->in_data.cordenadas_f.x <<" "<< rede[0][0]->in_data.cordenadas_f.y << endl;


	sc_start();



	return 0;

}

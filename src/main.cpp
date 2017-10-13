#include <iostream>
#include <vector>
#include "systemc.h"
#include "pacote.h"
#include "buffer.h"
#include "flit.h"
#include "roteamento.h"
#include "roteador.h"


#define TAM_REDE 1

using namespace std;


int main(int argc, char const *argv[])
{

	Pacote pct;
//Setar as cordenadas destinos dos flits...
	pct.flit[0].cordenadas_f.x = 2;
	pct.flit[0].cordenadas_f.y = 2;


//Sinais do controle de fluxo
	sc_signal < sc_int<32> > in_ack[5];
	sc_signal < sc_int<32> > in_val[5];

//Sinais do controle de fluxo para o buffer
	sc_signal < sc_int<32> > wr[5];
	sc_signal < sc_int<32> > wok[5];

// Sinais da outra ponta do buffer
	sc_signal < sc_int<32> > rok[5];
	sc_signal < sc_int<32> > rd[5];


//Sinais do ROTEADOR
sc_signal < sc_int<32> > in_ack_r[9];
sc_signal < sc_int<32> > in_val_r[9];



// Criar uma Rede 4x4
	roteador *rede[1][1];

// Criando os roteadores para alocar na rede
	roteador roteador1("roteador1");

// Alocando os roteadores no vetor rede
	rede[0][0] = &roteador1;	





// Ligando os SINAIS
	//SINAIS DOS ROTEADORES
	rede[0][0]->in_val(in_val_r[0]);
	rede[0][0]->in_ack(in_ack_r[0]);
	//SINAIS DOS COMPONENTES DOS ROTEADORES
	for (int x = 0; x < TAM_REDE; ++x)
		for (int y = 0; y < TAM_REDE; ++y){
			//Controle de fluxo Local
			rede[x][y]->cf_buffer_local->in_val(in_val[4]);
			rede[x][y]->cf_buffer_local->in_ack(in_ack[4]);
			rede[x][y]->cf_buffer_local->wr(wr[4]);
			rede[x][y]->cf_buffer_local->wok(wok[4]);
			//Controle de fluxo oeste
			rede[x][y]->cf_buffer_oeste->in_val(in_val[3]);
			rede[x][y]->cf_buffer_oeste->in_ack(in_ack[3]);
			rede[x][y]->cf_buffer_oeste->wr(wr[3]);
			rede[x][y]->cf_buffer_oeste->wok(wok[3]);
			//Controle de fluxo leste
			rede[x][y]->cf_buffer_leste->in_val(in_val[1]);
			rede[x][y]->cf_buffer_leste->in_ack(in_ack[1]);
			rede[x][y]->cf_buffer_leste->wr(wr[1]);
			rede[x][y]->cf_buffer_leste->wok(wok[1]);
			//Controle de fluxo sul
			rede[x][y]->cf_buffer_sul->in_val(in_val[2]);
			rede[x][y]->cf_buffer_sul->in_ack(in_ack[2]);
			rede[x][y]->cf_buffer_sul->wr(wr[2]);
			rede[x][y]->cf_buffer_sul->wok(wok[2]);
			//Controle de fluxo norte
			rede[x][y]->cf_buffer_norte->in_val(in_val[0]);
			rede[x][y]->cf_buffer_norte->in_ack(in_ack[0]);
			rede[x][y]->cf_buffer_norte->wr(wr[0]);
			rede[x][y]->cf_buffer_norte->wok(wok[0]);
		//*********SINAIS DOS BUFFERS********
			//Buffer Local
			rede[0][0]->buffer_local->wr(wr[4]);
			rede[0][0]->buffer_local->wok(wok[4]);
			rede[0][0]->buffer_local->rok(rok[4]);
			rede[0][0]->buffer_local->rd(rd[4]);
			//Buffer oeste
			rede[0][0]->buffer_oeste->wr(wr[3]);
			rede[0][0]->buffer_oeste->wok(wok[3]);
			rede[0][0]->buffer_oeste->rok(rok[3]);
			rede[0][0]->buffer_oeste->rd(rd[3]);			
			//Buffer leste
			rede[0][0]->buffer_leste->wr(wr[1]);
			rede[0][0]->buffer_leste->wok(wok[1]);
			rede[0][0]->buffer_leste->rok(rok[1]);
			rede[0][0]->buffer_leste->rd(rd[1]);			
			//Buffer sul
			rede[0][0]->buffer_sul->wr(wr[2]);
			rede[0][0]->buffer_sul->wok(wok[2]);
			rede[0][0]->buffer_sul->rok(rok[2]);
			rede[0][0]->buffer_sul->rd(rd[2]);
			//Buffer norte
			rede[0][0]->buffer_norte->wr(wr[0]);
			rede[0][0]->buffer_norte->wok(wok[0]);
			rede[0][0]->buffer_norte->rok(rok[0]);
			rede[0][0]->buffer_norte->rd(rd[0]);
		}



	
	


	//Cordenadas do roteador 1
	rede[0][0]->roteamento_norte.cordenada.x = 0;
	rede[0][0]->roteamento_norte.cordenada.y = 0;


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
